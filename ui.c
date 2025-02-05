#include <ncurses.h>
#include "ui.h"


WINDOW *disasm, *toolbar;

void init_scr() 
{
	initscr();
}

void set_cursor(int cursor, int state) 
{

	char t[1];
	int i;

	for (i = 0; i < 6; i++) {
		t[0] = mvwinch(disasm, cursor, i);
		t[0] &= 0xff;
		mvwaddch(disasm, cursor, i, t[0] | (state?A_REVERSE:A_NORMAL));
	}

}

void set_disasm_window(char *commands[], int len) 
{


	int i, j;

	disasm = newpad(LINES * 3, 160);
	toolbar = newpad(1, COLS);
	

	for (i = 0, j = 0; i < len; i++) {
		if (commands[i]) {
			mvwaddstr(disasm, j, 0, commands[i]);
			j++;
			if (j > LINES * 3) break;
		}
	}
	curs_set(0);
	set_cursor(0,1);
	prefresh(disasm, 0, 0, 0, 0, LINES - 2, COLS / 2);	

	

}

void close_scr() 
{

	delwin(disasm);
	delwin(toolbar);
	endwin();

}

int get_key() 
{

	int ch;

	ch = wgetch(disasm);

	if (ch == 0x1b) {
		ch = wgetch(disasm);
		if (ch == 0x5b) {
			ch = wgetch(disasm);
			if (ch == 0x41) return(K_UP); // up
			if (ch == 0x42) return(K_DOWN); // down
			if (ch == 0x43) return(K_RIGHT); // right
			if (ch == 0x44) return(K_LEFT); // left
			}
		}
		if (ch == 0x35) return(K_PGUP);
		if (ch == 0x36) return(K_PGDOWN);

	return(ch);
}

int get_addr(int cursor) 
{

	char t[4];
	int addr;
	int i;

	for (i = 0; i < 4; i++) t[i] = mvwinch(disasm, cursor, i);
	sscanf(t, "%x", &addr);
	return(addr);
}

void refresh_disasm_window(int *line, int *cursor, char *commands[], int *address, int dst_addr) 
{

	int i, j, addr;

	if (dst_addr != -1) {
		*address = addr = dst_addr;
		*line = 0; *cursor = 0;
	}
	else {
	*address = addr = get_addr(*cursor);
	}

	if (*cursor == 0 || *cursor >= LINES * 2 - 2) {	
		if (*cursor == 0) {
			*cursor = LINES;
			*line = LINES;
		}
		else {
			*cursor = LINES;
			*line = 2;
		}
		
		for (i = addr, j = LINES;; i++) {
			if (commands[i]) {
				mvwaddstr(disasm, j, 0,"                                                                        ");
				mvwaddstr(disasm, j, 0, commands[i]);
				j++;
				if (j > LINES * 3) break;
			}
		}
		for (i = addr, j = LINES; i >= 0; i--) {
			if (commands[i]) {
				mvwaddstr(disasm, j, 0,"                                                                         ");
				mvwaddstr(disasm, j, 0, commands[i]);
				j--;
				if (j < 0) break;
			}
		}
	}
	wmove(disasm, *cursor, 0);
	set_cursor(*cursor, 1);			
	prefresh(disasm, *line, 0, 0, 0, LINES - 2, COLS / 2);

}

void go_to(int addr,int *line, int *cursor,char *commands[],int *address) 
{

	
	refresh_disasm_window(line, cursor, commands, address, addr);
}

int line2addr(int steps, int addr, char *commands[], int len) 
{

	int i, j;

	if (steps < 0) {
		for(i = 0, j = addr;i >= steps && j > 0; j--) if (commands[j]) i--;
	}
	else{
		for(i = 0, j = addr; i < steps && j < len; j++) if (commands[j]) i++;
	}
	return(j);
}

void show_help() 
{

	WINDOW *help;

	help = newpad(10, 40);
	mvwaddstr(help, 0, 0, "========================================");
	mvwaddstr(help, 1, 0," <right>     follow jump/call           ");
	mvwaddstr(help, 1, 0," <left>    return to jump address     ");
	mvwaddstr(help, 9, 0,"========================================");
	prefresh(help, 0, 0, 20, 20, 20 + 10, 20 + 40);
	
	wgetch(help);
	delwin(help);
}

int follow_jmp(char *line) 
{

	int addr,retval;

	retval = sscanf(line, "%*[^l]ljmp 0x%x", &addr);
	if (retval == 1) return(addr);

	retval = sscanf(line, "%*[^l]lcall 0x%x", &addr);
	if (retval == 1) return(addr);

	retval = sscanf(line, "%*[^s]sjmp 0x%x", &addr);
	if (retval == 1) return(addr);

	
	return -1;
}


void event_loop(int len, char *commands[]) 
{

	int ch;
	int line = 0;
	int cursor = 0;
	char t[64];
	int padlen = LINES * 3;
	int addr = 0;
	int jump_chain[100] = {0};
	int jmp_index = 0;
	int jmp_addr;

	while(1) {
		ch = get_key();
		set_cursor(cursor, 0);
		switch(ch) {
		case 'q': return;
		case K_UP:
			if (addr > 0) cursor--;
			if (cursor < line && line > 0) line--;
			break;
		case K_DOWN:
			if (cursor < padlen - 4) cursor++;
			if (cursor > line + LINES - 2 && line < padlen - 2-LINES) line++;
			break;
		case K_PGDOWN:
			go_to(line2addr(LINES - 5, addr, commands, len), &line, &cursor, commands, &addr);
			break;
		case K_PGUP:
			go_to(line2addr(-LINES - 5, addr, commands, len), &line, &cursor, commands, &addr);
			//if (line == 0) cursor = 0;
			break;
		case 'h':
			show_help();
			break;
		case '?':
			show_help();
			break;
		case K_RIGHT:
			jmp_addr = follow_jmp(commands[addr]);
			if (jmp_addr == -1) break;
			jump_chain[jmp_index] = addr;
			jmp_index++;
			if (jmp_index >= 100) jmp_index = 0;
			go_to(jmp_addr, &line, &cursor, commands, &addr);
			break;
		case K_LEFT:
			jmp_index--;
			if (jmp_index < 0) jmp_index = 99;
			go_to(jump_chain[jmp_index], &line, &cursor, commands, &addr);			
			break;
		}
		//sprintf(t,"line=%d, cursor=%d",line,cursor);	
			
		
		refresh_disasm_window(&line, &cursor, commands, &addr, -1);
		
		sprintf(t,"line = %d, cursor= %d, addr = 0x%04x LINES = %d                  ", line, cursor, addr, LINES);
		mvwaddstr(toolbar, 0, 0, t);
		prefresh(toolbar,0, 0, LINES - 1, 0, LINES - 1, COLS - 1);

		
	}
}

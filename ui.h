
#define K_UP 0x1b5b41
#define K_DOWN 0x1b5b42
#define K_RIGHT 0x1b5b43
#define K_LEFT 0x1b5b44
#define K_PGUP 0x35
#define K_PGDOWN 0x36


void init_scr();
void set_disasm_window(char *commands[], int len) ;
void close_scr();
int get_key();
void event_loop(int len, char *commands[]);




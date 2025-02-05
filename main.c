#include "op.h"
#include "ui.h"


int main(int argc, char *argv[]) {
	FILE *h;
	int i;
	int retval;
	struct core core1;
	char result[1024];
	uint8_t  map[MEM_SIZE] = {0};
	char *commands[MEM_SIZE];

	core1.ram1 = (uint8_t*) malloc(MEM_SIZE);
	core1.ram1_size = MEM_SIZE;
	h = fopen(argv[1], "r");
	if (h == NULL) {
		printf("usage: %s <binary>\n", argv[0]);
		return(1);
	}
	for(i = 0; i < core1.ram1_size; i++){
		retval = fread(core1.ram1 + i, 1, 1, h);
		if (retval != 1) break;
	}
	fclose(h);
	printf("read %d bytes.\n", i);

	retval = analyze_code_flow(&core1, map, 0, commands);
	/* analyze areas pointed by interrupt vector table */
	for (i = 3;i < 0xa0;i+= 8){		
		analyze_code_flow(&core1, map, i, commands);
	}

	for (i = 0; i < MEM_SIZE; i++) {
		if (commands[i] || map[i]) continue;
		sprintf(result, "%04x\t%02x          \t byte 0x%02x", i, core1.ram1[i], core1.ram1[i]);
		commands[i] = strdup(result);
	}
	for(i = 0, retval = 0; i < MEM_SIZE; i++) if (map[i]) retval++;
	printf("%.1f %% disassembled\n", retval * 100.0 / (1.0 * MEM_SIZE)); 

	
	init_scr();
	set_disasm_window(commands, MEM_SIZE);
	event_loop(MEM_SIZE, commands);
	close_scr();



}


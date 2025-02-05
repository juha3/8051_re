
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>




#define MEM_SIZE 128*1024

#define SFR_SP 0x81
#define SFR_DPL 0x82
#define SFR_DPH 0x83
#define SFR_ACC 0xe0
#define SFR_B 0xb0
#define SFR_P0 0x80
#define SFR_P1 0x90
#define SFR_P2 0xa0
#define SFR_P3 0xb0
#define SFR_P4 0xe8
#define SFR_P5 0xf8
#define SFR_P6 0xfa
#define SFR_P7 0xdb
#define SFR_P8 0xdd
#define SFR_PSW 0xd0

#define WOULD_JUMP (1<<20)
#define FUNC_START (1<<21)
#define FUNC_END   (1<<22)

struct core {
	uint8_t *ram1;
	uint8_t ram2[256];
	uint8_t ram3[65536]; /* XRAM */
	uint32_t ram1_size;
	struct regs *regs;
};


int analyze_code_flow(struct core *c1,uint8_t *map,uint32_t addr, char *commands[]);


 



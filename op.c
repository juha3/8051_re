#include "op.h"

char *regs[256] = {

	"0x00", "0x01", "0x02", "0x03", "0x04", "0x05", "0x06", "0x07", "0x08", "0x09", "0x0a", "0x0b", "0x0c", "0x0d", "0x0e", "0x0f",
	"0x10", "0x11", "0x12", "0x13", "0x14", "0x15", "0x16", "0x17", "0x18", "0x19", "0x1a", "0x1b", "0x1c", "0x1d", "0x1e", "0x1f",
	"0x20", "0x21", "0x22", "0x23", "0x24", "0x25", "0x26", "0x27", "0x28", "0x29", "0x2a", "0x2b", "0x2c", "0x2d", "0x2e", "0x2f",
	"0x30", "0x31", "0x32", "0x33", "0x34", "0x35", "0x36", "0x37", "0x38", "0x39", "0x3a", "0x3b", "0x3c", "0x3d", "0x3e", "0x3f",
	"0x40", "0x41", "0x42", "0x43", "0x44", "0x45", "0x46", "0x47", "0x48", "0x49", "0x4a", "0x4b", "0x4c", "0x4d", "0x4e", "0x4f",
	"0x50", "0x51", "0x52", "0x53", "0x54", "0x55", "0x56", "0x57", "0x58", "0x59", "0x5a", "0x5b", "0x5c", "0x5d", "0x5e", "0x5f",
	"0x60", "0x61", "0x62", "0x63", "0x64", "0x65", "0x66", "0x67", "0x68", "0x69", "0x6a", "0x6b", "0x6c", "0x6d", "0x6e", "0x6f",
	"0x70", "0x71", "0x72", "0x73", "0x74", "0x75", "0x76", "0x77", "0x78", "0x79", "0x7a", "0x7b", "0x7c", "0x7d", "0x7e", "0x7f",
	"P0",
	"SP",
	"DPL",
	"DPH",
	"WDTL",
	"WDTH",
	"WDTREL",
	"PCON",
	"TCON",
	"TMOD",
	"TL0",
	"TL1",
	"TH0",
	"TH1",
	"0x8e",
	"0x8f",

	"P1",
	"XPAGE",
	"DPSEL",
	"0x93",
	"0x94",
	"0x95",
	"0x96",
	"0x97"
	"S0CON",
	"S0BUF",
	"IEN2",
	"S1CON",
	"S1BUF",
	"S1RELL",
	"0x9e",
	"0x9f",

	"P2",
	"COMSETL",
	"COMSETH",
	"COMCLRL",
	"COMCLRH",
	"SETMSK",
	"CLKMSK",
	"0xa7",
	"IEN0",
	"IP0",
	"S0RELL",
	"0xab",
	"0xac",
	"0xad",
	"0xae",
	"0xaf",

	"P3",
	"SYSCON",
	"0xb2",
	"0xb3",
	"0xb4",
	"0xb5",
	"0xb6",
	"0xb7",
	"IEN1",
	"IP1",
	"S0RELH",
	"S1RELH",
	"0xbc",
	"0xbd",
	"0xbe",
	"0xbf",

	"IRCON0",
	"CCEN",
	"CCL1",
	"CCH1",
	"CCL2",
	"CCH2",
	"CCL3",
	"CCH3",
	"T2CON",
	"CC4EN",
	"CRCL",
	"CRCH",
	"TL2",
	"TH2",
	"CCL4",
	"CCH4",

	"PSW",
	"IRCON1",
	"CML0",
	"CMH0",
	"CML1",
	"CMH1",
	"CML2",
	"CMH2",
	"ADCON0",
	"ADDATH",
	"ADDATL",
	"P7",
	"ADCON1",
	"P8",
	"CTRELL",
	"CTRELH",

	"ACC",
	"CTCON",
	"CML3",
	"CMH3",
	"CML4",
	"CMH4",
	"CML5",
	"CMH5",
	"P4",
	"MD0",
	"MD1",
	"MD2",
	"MD3",
	"MD4",
	"MD5",
	"ARCON",

	"B",
	"0xf1",
	"CML6",
	"CMH6",
	"CML7",
	"CMH7",
	"CMEN",
	"CMSEL",
	"P5",
	"0xf9",
	"P6",
	"0xfb",
	"0xfc",
	"IS0",
	"IS1",
	"0xff"
};


void push(struct core *c1, uint8_t val) {

	uint8_t sp;

	c1->ram2[SFR_SP]++;
	sp = c1->ram2[SFR_SP];
	//printf("pushed 0x%02x to 0x%02x\n", val, sp);
	c1->ram2[sp] = val;
}

uint8_t pop(struct core *c1) {

	uint8_t sp = c1->ram2[SFR_SP];
	uint8_t val;

	val = c1->ram2[sp];
	//printf("popped 0x%02x from 0x%02x\n", val, sp);
	c1->ram2[SFR_SP]--;
	return(val);
}

void clear_bit(struct core *c1, uint8_t val) {

	uint8_t byte;
	int bit;

	byte = 0x20 + val/8;
	bit = val % 8;
	c1->ram2[byte] &= ~(1 << bit);
}

void set_bit(struct core *c1, uint8_t val) {

	uint8_t byte;
	int bit;

	byte = 0x20 + val/8;
	bit = val % 8;
	c1->ram2[byte] |= (1 << bit);
}

int read_bit(struct core *c1, uint8_t val) {

	uint8_t byte;
	int bit;

	byte = 0x20 + val/8;
	bit = val % 8;
	return((c1->ram2[byte] & (1 << bit)) ? 1 : 0);
}

void write_reg(struct core *c1, int reg, int8_t val) {

	int bank;

	bank = (c1->ram2[SFR_PSW] >> 3) & 0x3;
	c1->ram2[bank * 8 + reg] = val;
}

uint8_t read_reg(struct core *c1, int reg) {

	int bank;

	bank = (c1->ram2[SFR_PSW] >> 3) & 0x3;
	return(c1->ram2[bank * 8 + reg]);
}


int analyze(struct core *c1, int32_t addr, char *result, int *jmp_addr, int *cond) {

	uint8_t *op;
	uint32_t val;
	uint32_t val2;
	uint32_t val3;
	uint32_t dptr;
	int32_t sval;
	char s1[256]={0};
	char s2[256]={0};
	char s3[256]={0};
	int addr2 = -1;
	int c2 = 0;
	int retval;

	//if (c1->ram2[0xf8] & (1 << 7)) printf("addr[16] set high!\n"); 
	if (!result) return(-1);
	op = &c1->ram1[addr];
	sprintf(s1, "%04x\t", addr);
	
	/* LJMP */
	if (op[0] == 0x02){
		val = (op[1] << 8) | op[2];
		sprintf(s2, "%02x %02x %02x\t ljmp 0x%04x", op[0], op[1], op[2], val);
		addr2 = val;
		retval = 3;
		goto done1;
	}
	/* JMP @A+DPTR*/
	if (op[0] == 0x73){
		sprintf(s2, "%02x          \t jmp @a+dptr", op[0]);
		val = c1->ram2[SFR_ACC];
		dptr = (c1->ram2[SFR_DPH] << 8) | c1->ram2[SFR_DPL];
		addr2 = val + dptr;
		retval = 1;
		goto done1;
	}
	/* SJMP */
	if (op[0] == 0x80){
		val = op[1];
		sprintf(s2, "%02x %02x     \t sjmp 0x%04x", op[0], op[1], (int8_t)val + addr + 2);
		addr2 = addr + (int8_t)val + 2;
		retval = 2;
		goto done1;
	}
	/* LCALL */
	if (op[0] == 0x12){
		val = (op[1] << 8) | op[2];
		sprintf(s2, "%02x %02x %02x\t lcall 0x%04x", op[0], op[1], op[2], val);
		addr2 = addr + 3;
		push(c1, addr2 & 0xff);
		push(c1, (addr2 >> 8) & 0xff);
		addr2 = val | WOULD_JUMP | FUNC_START;
		retval = 3;
		c2 = 1; /* not conditional, but execution continues after call, so ... */
		goto done1;
	}
	/* ACALL */
	if (op[0] == 0x11 || op[0] == 0x31 || op[0] == 0x51 || op[0] == 0x71 || op[0] == 0x91 ||
		op[0] == 0xb1 || op[0] == 0xd1 || op[0] == 0xf1){
		val = op[1];
		val2 = op[0] >> 5;
		val |= val2 << 8;
		sprintf(s2, "%02x %02x     \t acall 0x%04x", op[0], op[1], val);
		addr2 = addr + 3;
		push(c1, addr2 & 0xff);
		push(c1, (addr2 >> 8) & 0xff);
		addr2 = val | WOULD_JUMP | FUNC_START;
		retval = 3;
		c2 = 1;
		goto done1;
	}
	/* AJMP */
	if (op[0] == 0x01 || op[0] == 0x21 || op[0] == 0x41 || op[0] == 0x61 || op[0] == 0x81 ||
		op[0] == 0xa1 || op[0] == 0xc1 || op[0] == 0xe1){
		val = op[1];
		val2 = op[0] >> 5;
		val |= val2 << 8;
		sprintf(s2, "%02x %02x     \t ajmp 0x%04x", op[0], op[1], val);
		addr2 = addr + 3;
		addr2 = val;
		retval = 3;
		goto done1;
	}
	/* CLR bit addr */
	if (op[0] == 0xc2){
		val = op[1];
		sprintf(s2, "%02x %02x    \t clr bit 0x%02x", op[0], op[1], val);
		clear_bit(c1, val);
		retval = 2;
		goto done1;
	}
	/* SETB bit addr */
	if (op[0] == 0xd2){
		val = op[1];
		sprintf(s2, "%02x %02x    \t setb bit 0x%02x", op[0], op[1], val);
		set_bit(c1, val);
		retval = 2;
		goto done1;
	}
	/* SETB C */
	if (op[0] == 0xd3){
		val = op[1];
		sprintf(s2, "%02x         \t setb c", op[0]);
		c1->ram2[SFR_PSW] |= (1 << 7);
		retval = 2;
		goto done1;
	}
	/* NOP */
	if (op[0] == 0x00){
		sprintf(s2, "%02x        \t nop", op[0]);
		retval = 1;
		goto done1;
	}
	/* RET */
	if (op[0] == 0x22){
		sprintf(s2, "%02x        \t ret", op[0]);
		val = (pop(c1) << 8);
		val |= pop(c1);
		addr2 = val | FUNC_END;
		retval = 1;
		goto done1;
	}
	/* RETI */
	if (op[0] == 0x32){
		sprintf(s2, "%02x        \t reti", op[0]);
		val = (pop(c1) << 8);
		val |= pop(c1);
		// TODO : enable interrupts
		addr2 = val | FUNC_END;
		retval = 1;
		goto done1;
	}
	/* MOV iram addr, #data */
	if (op[0] == 0x75){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x\t mov %s, #0x%02x", op[0], op[1], op[2], regs[val], val2);
		c1->ram2[val] = val2;
		retval = 3;
		goto done1;
	}
	/* MOV iram addr, A */
	if (op[0] == 0xf5){
		val = op[1];
		sprintf(s2, "%02x %02x     \t mov %s, a", op[0], op[1], regs[val]);
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		c1->ram2[val] = c1->ram2[SFR_ACC];
		retval = 2;
		goto done1;
	}
	/* MOV iram addr, R[0-7] */
	if (op[0] >= 0x88 && op[0] <= 0x8f){
		val = op[0] - 0x88;
		val2 = op[1];
		sprintf(s2, "%02x %02x     \t mov %s, r%d", op[0], op[1], regs[val2], val);
		c1->ram2[val2] = read_reg(c1, val);
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, read_reg(c1, val));
		retval = 2;
		goto done1;
	}
	/* MOV R[0-7], iram addr */
	if (op[0] >= 0xa8 && op[0] <= 0xaf){
		val = op[0] - 0xa8;
		val2 = op[1];
		sprintf(s2, "%02x %02x     \t mov r%d, %s", op[0], op[1], val, regs[val2]);
		write_reg(c1, val, c1->ram2[val2]);
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, read_reg(c1, val));
		retval = 2;
		goto done1;
	}
	/* MOV dptr, #data */
	if (op[0] == 0x90){
		val = (op[1] << 8) | op[2];
		sprintf(s2, "%02x %02x %02x\t mov dptr, #0x%04x", op[0], op[1], op[2], val);
		c1->ram2[SFR_DPH] = op[1];
		c1->ram2[SFR_DPL] = op[2];
		retval = 3;
		goto done1;
	}
	/* MOV a, #data */
	if (op[0] == 0x74){
		val = op[1];
		sprintf(s2, "%02x %02x     \t mov a, #0x%02x", op[0], op[1], val);
		c1->ram2[SFR_ACC] = op[1];
		retval = 2;
		goto done1;
	}
	/* MOV c, bit addr */
	if (op[0] == 0xa2){
		val = op[1];
		sprintf(s2, "%02x %02x     \t mov c, bit 0x%02x", op[0], op[1], val);
		c1->ram2[SFR_PSW] &= ~(1 << 7);
		c1->ram2[SFR_PSW] |= read_bit(c1, val) ? (1 << 7) : 0;
		sprintf(s3, "\t; c = %d", (c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0);
		retval = 2;
		goto done1;
	}
	/* MOV bit addr, c */
	if (op[0] == 0x92){
		val = op[1];
		sprintf(s2, "%02x %02x     \t mov bit 0x%02x, c", op[0], op[1], val);
		val2 = (c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0;
		if (val2) set_bit(c1, val);
		else clear_bit(c1, val);
		sprintf(s3, "\t; c = %d", (c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0);
		retval = 2;
		goto done1;
	}
	/* MOV a, iram addr */
	if (op[0] == 0xe5){
		val = op[1];
		sprintf(s2, "%02x %02x     \t mov a, %s", op[0], op[1], regs[val]);
		c1->ram2[SFR_ACC] = c1->ram2[val];
		retval = 2;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val, c1->ram2[val]);
		goto done1;
	}
	/* MOV iram addr, iram addr */
	if (op[0] == 0x85){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x\t mov %s, %s", op[0], op[1], op[2], regs[val], regs[val2]);
		c1->ram2[val2] = c1->ram2[val];
		retval = 3;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}

	/* MOVX @dptr, a */
	if (op[0] == 0xF0){
		sprintf(s2, "%02x          \t movx @dptr, a", op[0]);
		c1->ram2[SFR_P0] = c1->ram2[SFR_DPL];
		c1->ram2[SFR_P2] = c1->ram2[SFR_DPH];
		dptr = (c1->ram2[SFR_DPH] << 8) | c1->ram2[SFR_DPL];
		c1->ram3[dptr] = c1->ram2[SFR_ACC];
		retval = 1;
		sprintf(s3, "\t; [0x%04x] = 0x%02x", dptr, c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* MOVX a, @dptr */
	if (op[0] == 0xE0){
		sprintf(s2, "%02x          \t movx a, @dptr", op[0]);
		c1->ram2[SFR_P0] = c1->ram2[SFR_DPL];
		c1->ram2[SFR_P2] = c1->ram2[SFR_DPH];
		dptr = (c1->ram2[SFR_DPH] << 8) | c1->ram2[SFR_DPL];
		c1->ram2[SFR_ACC] = c1->ram3[dptr];
		sprintf(s3, "\t; [0x%04x] = 0x%02x", dptr, c1->ram3[dptr]);
		retval = 1;
		goto done1;
	}
	/* MOVX a, @r[0-1] */
	if (op[0] == 0xe2 || op[0] == 0xe3){
		val = op[0]-0xe2;
		sprintf(s2, "%02x          \t movx a, @r%d", op[0], val);
		c1->ram2[SFR_P0] = read_reg(c1, val);
		dptr = (c1->ram2[SFR_P2] << 8) | c1->ram2[SFR_P0];
		c1->ram2[SFR_ACC] = c1->ram3[dptr];
		sprintf(s3, "\t; [0x%04x] = 0x%02x", dptr, c1->ram3[dptr]);
		retval = 1;
		goto done1;
	}
	/* MOVX @r[0-1], a */
	if (op[0] == 0xf2 || op[0] == 0xf3){
		val = op[0]-0xf2;
		sprintf(s2, "%02x          \t movx @r%d, a", op[0], val);
		c1->ram2[SFR_P0] = read_reg(c1, val);
		dptr = (c1->ram2[SFR_P2] << 8) | c1->ram2[SFR_P0];
		c1->ram3[dptr] = c1->ram2[SFR_ACC];
		sprintf(s3, "\t; [0x%04x] = 0x%02x", dptr, c1->ram3[dptr]);
		retval = 1;
		goto done1;
	}
	/* MOV @r[0-1], iram addr */
	if (op[0] == 0xa6 || op[0] == 0xa7){
		val = op[0] - 0xa6;
		val3 = op[1];
		sprintf(s2, "%02x %02x       \t mov @r%d, %s", op[0], op[1], val, regs[val3]);
		val2 = read_reg(c1, val);
		c1->ram2[val2] = c1->ram2[val3];
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* MOV iram addr, @r[0-1] */
	if (op[0] == 0x86 || op[0] == 0x87){
		val = op[0] - 0x86;
		val3 = op[1];
		sprintf(s2, "%02x %02x       \t mov %s, r%d", op[0], op[1], regs[val3], val);
		val2 = read_reg(c1, val);
		c1->ram2[val3] = c1->ram2[val2];
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* MOV @r[0-1], #data */
	if (op[0] == 0x76 || op[0] == 0x77){
		val = op[0] - 0x76;
		val3 = op[1];
		sprintf(s2, "%02x %02x       \t mov @r%d, #0x%02x", op[0], op[1], val, val3);
		val2 = read_reg(c1, val);
		c1->ram2[val2] = val3;
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* JB bit addr, reladdr */
	if (op[0] == 0x20){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x  \t jb bit 0x%02x, 0x%04x", op[0], op[1], op[2], val, (int8_t)val2 + addr + 3);
		retval = 3;
		addr2 = addr + (int8_t) val2 + 3;
		if (read_bit(c1, val)) addr2 |= WOULD_JUMP;
		c2 = 1;
		goto done1;
	}
	/* JNB bit addr, reladdr */
	if (op[0] == 0x30){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x  \t jnb bit 0x%02x, 0x%04x", op[0], op[1], op[2], val, (int8_t)val2 + addr + 3);
		retval = 3;
		addr2 = addr + (int8_t)val2 + 3;
		if (!read_bit(c1, val)) addr2 |= WOULD_JUMP;
		c2 = 1;
		goto done1;
	}
	/* JBC bit addr, reladdr */
	if (op[0] == 0x10){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x  \t jbc bit 0x%02x, 0x%04x", op[0], op[1], op[2], val, (int8_t)val2 + addr + 3);
		retval = 3;
		addr2 = addr + (int8_t)val2 + 3;
		if (read_bit(c1, val)) addr2 |= WOULD_JUMP;
		clear_bit(c1, val);
		c2 = 1;
		goto done1;
	}
	/* mov R[0-7], #data */
	if (op[0] >= 0x78 && op[0] <= 0x7f){
		val = op[1];
		val2 = op[0]-0x78;
		sprintf(s2, "%02x %02x       \t mov r%d, #0x%02x", op[0], op[1], val2, val);
		write_reg(c1, val2, val);
		retval = 2;
		goto done1;
	}
	/* CLR A / CLR C */
	if (op[0] == 0xe4 || op[0] == 0xc3){
		sprintf(s2, "%02x            \t clr %c", op[0], op[0] == 0xe4 ? 'a' : 'c');
		if (op[0] == 0xe4) c1->ram2[SFR_ACC] = 0;
		else c1->ram2[SFR_PSW] &= ~(1 << 7);
		retval = 1;
		goto done1;
	}
	/* MOV @R[0-1], A */
	if (op[0] == 0xf6 || op[0] == 0xf7){
		val = op[0]-0xf6;
		sprintf(s2, "%02x            \t mov @r%d, a", op[0], val);
		val2 = read_reg(c1, val);
		c1->ram2[val2] = c1->ram2[SFR_ACC];
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* MOV A, @R[0-1] */
	if (op[0] == 0xe6 || op[0] == 0xe7){
		val = op[0]-0xe6;
		sprintf(s2, "%02x            \t mov a, @r%d", op[0], val);
		val2 = read_reg(c1, val);
		c1->ram2[SFR_ACC] = c1->ram2[val];
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* ADD A, @R[0-1] */
	if (op[0] == 0x26 || op[0] == 0x27){
		val = op[0]-0x26;
		sprintf(s2, "%02x            \t add a, @r%d", op[0], val);
		val2 = read_reg(c1, val);
		c1->ram2[SFR_ACC] += c1->ram2[val];
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* ADDC A, @R[0-1] */
	if (op[0] == 0x36 || op[0] == 0x37){
		val = op[0]-0x36;
		sprintf(s2, "%02x            \t addc a, @r%d", op[0], val);
		val2 = read_reg(c1, val);
		c1->ram2[SFR_ACC] += c1->ram2[val] + (c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0;
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* MOV R[0-1], A */
	if (op[0] >= 0xf8 && op[0] <= 0xff){
		val = op[0]-0xf8;
		sprintf(s2, "%02x            \t mov r%d, a", op[0], val);
		write_reg(c1, val, c1->ram2[SFR_ACC]);
		retval = 1;
		sprintf(s3, "\t; r%d = 0x%02x", val, c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* MOV A, R[0-7] */
	if (op[0] >= 0xe8 && op[0] <= 0xef){
		val = op[0]-0xe8;
		sprintf(s2, "%02x            \t mov r%d, a", op[0], val);
		c1->ram2[SFR_ACC] = read_reg(c1, val);
		retval = 1;
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* ADD A, R[0-7] */
	if (op[0] >= 0x28 && op[0] <= 0x2f){
		val = op[0]-0x28;
		sprintf(s2, "%02x            \t add r%d, a", op[0], val);
		c1->ram2[SFR_ACC] = read_reg(c1, val);
		retval = 1;
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* ADDC A, R[0-7] */
	if (op[0] >= 0x38 && op[0] <= 0x3f){
		val = op[0]-0x38;
		sprintf(s2, "%02x            \t addc r%d, a", op[0], val);
		c1->ram2[SFR_ACC] = read_reg(c1, val) + (c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0;
		retval = 1;
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* DJNZ R[0-7], reladdr */
	if (op[0] >= 0xd8 && op[0] <= 0xdf){
		val = op[0]-0xd8;
		val2 = op[1];
		sprintf(s2, "%02x %02x       \t djnz r%d, 0x%04x", op[0], op[1], val, (int8_t)val2 + addr + 2);
		val3 = read_reg(c1, val);
		val3--;
		write_reg(c1, val, val3);
		retval = 2;
		addr2 = addr + (int8_t)val2 + 2;
		if (val3 != 0) addr2 |= WOULD_JUMP;
		c2 = 1;
		goto done1;
	}
	/* DJNZ iram addr, reladdr */
	if (op[0] == 0xd5){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x  \t djnz %s, 0x%04x", op[0], op[1], op[2], regs[val], (int8_t)val2 + addr + 2);
		val3 = c1->ram2[val];
		val3--;
		c1->ram2[val] = val3 & 0xff;
		retval = 3;
		addr2 = addr + (int8_t)val2 + 3;
		if (val3 != 0) addr2 |= WOULD_JUMP;
		c2 = 1;
		goto done1;
	}
	/* JZ */
	if (op[0] == 0x60){
		sprintf(s2, "%02x %02x       \t jz 0x%04x", op[0], op[1], (int8_t)op[1] + addr + 2);
		retval = 2;
		addr2 = addr + (int8_t)op[1] + 2;
		if (!c1->ram2[SFR_ACC]) addr2 |= WOULD_JUMP;
		c2 = 1;
		goto done1;

	}
	/* JC */
	if (op[0] == 0x40){
		val = op[1];
		sprintf(s2, "%02x %02x       \t jc 0x%04x", op[0], op[1], (int8_t)op[1] + addr + 2);
		retval = 2;
		addr2 = addr + (int8_t)val + 2;
		if (c1->ram2[SFR_PSW] & (1 << 7)) addr2 |= WOULD_JUMP; 
		c2 = 1;
		goto done1;

	}
	/* JNZ */
	if (op[0] == 0x70){
		sprintf(s2, "%02x %02x        \t jnz 0x%04x", op[0], op[1], (int8_t)op[1] + addr + 2);
		retval = 2;
		addr2 = addr + (int8_t)op[1] + 2;
		if (c1->ram2[SFR_ACC]) addr2 |= WOULD_JUMP;
		c2 = 1;
		goto done1;

	}
	/* JNC */
	if (op[0] == 0x50){
		val = op[1];
		sprintf(s2, "%02x %02x        \t jnc 0x%04x", op[0], op[1], (int8_t)val + addr + 2);
		retval = 2;
		addr2 = addr + (int8_t)val + 2;
		if (!(c1->ram2[SFR_PSW] & (1 << 7))) addr2 |= WOULD_JUMP;
		c2 = 1;
		goto done1;

	}
	/* ADD a, #data */
	if (op[0] == 0x24 || op[0] == 0x34){
		val = op[1];
		sprintf(s2, "%02x %02x     \t ad%c a, #0x%02x", op[0], op[1], op[0] == 0x24 ? 'd' : 'c', val);
		val2 = c1->ram2[SFR_ACC] + op[1];
		if (op[0] == 0x34) val2 += ((c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0);
		if (val2>255) c1->ram2[SFR_PSW] |= (1 << 7);
		//TODO : aux carry, overflow flag
		c1->ram2[SFR_ACC] = val2 & 0xff;
		retval = 2;
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* SUBB a, #data */
	if (op[0] == 0x94){
		val = op[1];
		sprintf(s2, "%02x %02x     \t subb a, #0x%02x", op[0], op[1], val);
		val2 = c1->ram2[SFR_ACC] - op[1];
		if (val2>255) c1->ram2[SFR_PSW] |= (1 << 7);
		//TODO : aux carry, overflow flag
		retval = 2;
		c1->ram2[SFR_ACC] = val2 & 0xff;
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		goto done1;
	}

	/* ADD/ADC a, r[0-7] */
	if ((op[0] >= 0x29 && op[0] <= 0x2f) || (op[0] >= 0x39 && op[0] <= 0x3f)){
		val = (op[0]>0x2f) ? op[0]-0x39 : op[0]-0x29;
		val2 = c1->ram2[SFR_ACC] + read_reg(c1, val);
		sval = (int8_t)c1->ram2[SFR_ACC] + (int8_t)read_reg(c1, val);
		if (op[0]>0x2f) {
			val2 += (c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0; /* carry bit */
			sval += (c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0; /* carry bit */
		}
		sprintf(s2, "%02x            \t ad%c a, r%d", op[0], (op[0]>0x2f) ? 'c' : 'd', val);
		c1->ram2[SFR_ACC] = val2 & 0xff;
		c1->ram2[SFR_PSW] &= ~((1 << 7) | (1 << 6) | (1 << 2)); /* clear carry, aux carry and overflow */
		if (val2>255) c1->ram2[SFR_PSW] |= (1 << 7);
		if (val2>15) c1->ram2[SFR_PSW] |= (1 << 6);
		if (sval>127 || sval<-128) c1->ram2[SFR_PSW] |= (1 << 2);
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		retval = 1;
		goto done1;
	}
	/* SUBB a, r[0-7] */
	if ((op[0] >= 0x98 && op[0] <= 0x9f)){
		val = op[0]-0x98;
		sval = c1->ram2[SFR_ACC] - read_reg(c1, val);
		sprintf(s2, "%02x            \t subb a, r%d", op[0], val);
		c1->ram2[SFR_ACC] = sval & 0xff;
		c1->ram2[SFR_PSW] &= ~((1 << 7) | (1 << 6) | (1 << 2)); /* clear carry, aux carry and overflow */
		if (sval<0) c1->ram2[SFR_PSW] |= (1 << 7);
		// TODO : aux carry if (val2>15) c1->ram2[SFR_PSW] |= (1 << 6);
		if (sval>127 || sval<-128) c1->ram2[SFR_PSW] |= (1 << 2);
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		retval = 1;
		goto done1;
	}
	/* CJNE a, #data, reladdr */
	if (op[0] == 0xb4){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x  \t cjne a, #0x%02x, 0x%04x", op[0], op[1], op[2], val, (int8_t)val2 + addr + 3);
		val3 = c1->ram2[SFR_ACC];
		retval = 3;
		addr2 = addr + (int8_t)val2 + 3;
		if (val3 != val) addr2 |= WOULD_JUMP;
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		c2 = 1;
		goto done1;
	}
	/* CJNE a, iram addr, reladdr */
	if (op[0] == 0xb5){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x  \t cjne a, %s, 0x%04x", op[0], op[1], op[2], regs[val], (int8_t)val2 + addr + 3);
		val3 = c1->ram2[SFR_ACC];
		retval = 3;
		addr2 = addr + (int8_t)val2 + 3;
		if (val3 != c1->ram2[val]) addr2 |= WOULD_JUMP;
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		c2 = 1;
		goto done1;
	}
	/* CJNE R[0-7], #data, reladdr */
	if (op[0] >= 0xb8 && op[0] <= 0xbf){
		val = op[0]-0xb8;
		val3 = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x  \t cjne r%d, #0x%02x, 0x%04x", op[0], op[1], op[2], val, val3, (int8_t)val2 + addr + 3);
		retval = 3;
		addr2 = addr + (int8_t)val2 + 3;
		if (val3 != read_reg(c1, val)) addr2 |= WOULD_JUMP;
		sprintf(s3, "\t; r%d = 0x%02x", val, read_reg(c1, val));
		c2 = 1;
		goto done1;
	}
	/* CJNE @R[0-1], #data, reladdr */
	if (op[0] == 0xb6 || op[0] == 0xb7){
		val = op[0]-0xb6;
		val3 = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x  \t cjne @r%d, #0x%02x, 0x%04x", op[0], op[1], op[2], val, val3, (int8_t)val2 + addr + 3);
		dptr = read_reg(c1, val);
		retval = 3;
		addr2 = addr + (int8_t)val2 + 3;
		if (val3 != c1->ram2[dptr]) addr2 |= WOULD_JUMP;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", dptr, c1->ram2[dptr]);
		c2 = 1;
		goto done1;
	}
	/* MOVC A, @A+DPTR */
	if (op[0] == 0x93){
		sprintf(s2, "%02x            \t movc a, @a+dptr", op[0]);
		val = c1->ram2[SFR_ACC] + (c1->ram2[SFR_DPH] << 8) + c1->ram2[SFR_DPL];
		dptr = (c1->ram2[SFR_DPH] << 8) + c1->ram2[SFR_DPL];
		val2 = c1->ram3[val];
		c1->ram2[SFR_ACC] = val2;
		retval = 1;
		sprintf(s3, "\t; [code : 0x%04x] = 0x%02x", dptr, val2);
		goto done1;
	}
	/* MOVC A, @A+PC */
	if (op[0] == 0x83){
		sprintf(s2, "%02x            \t movc a, @a+pc", op[0]);
		val = c1->ram2[SFR_ACC] + addr + 1;
		val2 = c1->ram1[val];
		c1->ram2[SFR_ACC] = val2;
		retval = 1;
		sprintf(s3, "\t; [0x%04x] = 0x%02x", val, val2);
		goto done1;
	}
	/* INC R[0-7] */
	if (op[0] >= 0x08 && op[0] <= 0x0f){
		val = op[0]-0x08;
		sprintf(s2, "%02x          \t inc r%d", op[0], val);
		val2 = read_reg(c1, val) + 1;
		write_reg(c1, val, val2 & 0xff);
		sprintf(s3, "\t; r%d = 0x%02x", val, val2 & 0xff);
		retval = 1;
		goto done1;
	}
	/* DEC R[0-7] */
	if (op[0] >= 0x18 && op[0] <= 0x1f){
		val = op[0]-0x18;
		sprintf(s2, "%02x          \t dec r%d", op[0], val);
		val2 = read_reg(c1, val) - 1;
		write_reg(c1, val, val2 & 0xff);
		sprintf(s3, "\t; r%d = 0x%02x", val, val2 & 0xff);
		retval = 1;
		goto done1;
	}
	/* INC DPTR */
	if (op[0] == 0xa3){
		sprintf(s2, "%02x          \t inc dptr", op[0]);
		dptr = (c1->ram2[SFR_DPH] << 8) + c1->ram2[SFR_DPL] + 1;
		c1->ram2[SFR_DPH] = (dptr >> 8) & 0xff;
		c1->ram2[SFR_DPL] = dptr & 0xff;
		sprintf(s3, "\t; dptr = 0x%04x", dptr);
		retval = 1;
		goto done1;
	}
	/* INC @R[0-1] */
	if (op[0] == 0x06 || op[0] == 0x07){
		val = op[0]-0x06;
		sprintf(s2, "%02x            \t inc @r%d", op[0], val);
		val2 = read_reg(c1, val);
		c1->ram2[val2]++;
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* DEC @R[0-1] */
	if (op[0] == 0x16 || op[0] == 0x17){
		val = op[0]-0x16;
		sprintf(s2, "%02x            \t dec @r%d", op[0], val);
		val2 = read_reg(c1, val);
		c1->ram2[val2]--;
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* INC a */
	if (op[0] == 0x04){
		sprintf(s2, "%02x          \t inc a", op[0]);
		c1->ram2[SFR_ACC]++; //++;
		sprintf(s3, "\t; a = 0x%04x", c1->ram2[SFR_ACC]);
		retval = 1;
		goto done1;
	}
	/* SWAP a */
	if (op[0] == 0xc4){
		sprintf(s2, "%02x          \t swap a", op[0]);
		val = (c1->ram2[SFR_ACC] & 0xf) << 4;
		val |= (c1->ram2[SFR_ACC] >> 4) & 0xf;
		c1->ram2[SFR_ACC] = val;
		sprintf(s3, "\t; a = 0x%04x", c1->ram2[SFR_ACC]);
		retval = 1;
		goto done1;
	}
	/* MUL AB */
	if (op[0] == 0xa4){
		sprintf(s2, "%02x          \t mul ab", op[0]);
		val = (uint32_t)c1->ram2[SFR_ACC] * (uint32_t)c1->ram2[SFR_B];
		val2 = c1->ram2[SFR_ACC];
		val3 = c1->ram2[SFR_B];
		if (val>65535) c1->ram2[SFR_PSW] |= (1 << 2); // overflow
		c1->ram2[SFR_PSW] &= ~(1 << 7); // clear carry
		c1->ram2[SFR_ACC] = val&0xff;
		c1->ram2[SFR_B] = (val >> 8)&0xff;
		sprintf(s3, "\t; %d*%d = %d(%04x)", val2, val3, val, val);
		retval = 1;
		goto done1;
	}
	/* DIV AB */
	if (op[0] == 0x84){
		sprintf(s2, "%02x          \t div ab", op[0]);
		if ((uint32_t)c1->ram2[SFR_B] != 0) {
			val = (uint32_t)c1->ram2[SFR_ACC] / (uint32_t)c1->ram2[SFR_B];
			val2 = (uint32_t)c1->ram2[SFR_ACC] % (uint32_t)c1->ram2[SFR_B];
		}
		else {
			c1->ram2[SFR_PSW] |= (1 << 2); // divide by zero
		}
		c1->ram2[SFR_PSW] &= ~(1 << 7); // clear carry
		c1->ram2[SFR_ACC] = val&0xff;
		c1->ram2[SFR_B] = val2;
		sprintf(s3, "\t; %d/%d = %d, remainder = %d", c1->ram2[SFR_ACC], c1->ram2[SFR_B], val, val2);
		retval = 1;
		goto done1;
	}
	/* DEC a */
	if (op[0] == 0x14){
		sprintf(s2, "%02x          \t dec a", op[0]);
		c1->ram2[SFR_ACC]--;
		sprintf(s3, "\t; a = 0x%04x", c1->ram2[SFR_ACC]);
		retval = 1;
		goto done1;
	}
	/* INC iram addr */
	if (op[0] == 0x05){
		val = op[1];
		sprintf(s2, "%02x %02x     \t inc %s", op[0], op[1], regs[val]);
		c1->ram2[val]++;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val, c1->ram2[val]);
		retval = 2;
		goto done1;
	}
	/* CPL A */
	if (op[0] == 0xf4){
		sprintf(s2, "%02x            \t cpl a", op[0]);
		c1->ram2[SFR_ACC] = 255 - c1->ram2[SFR_ACC];
		retval = 1;
		goto done1;
	}
	/* CPL C */
	if (op[0] == 0xb3){
		sprintf(s2, "%02x            \t cpl c", op[0]);
		if (c1->ram2[SFR_PSW] & (1 << 7)) c1->ram2[SFR_PSW] &= ~(1 << 7);
		else c1->ram2[SFR_PSW] |= (1 << 7);
		retval = 1;
		goto done1;
	}
	/* CPL bit addr */
	if (op[0] == 0xb2){
		val = op[1];
		sprintf(s2, "%02x %02x       \t cpl bit 0x%02x", op[0], op[1], val);
		val2 = read_bit(c1, val);
		if (val2) clear_bit(c1, val);
		else set_bit(c1, val);
		retval = 2;
		goto done1;
	}
	/* XLR iram addr, #data */
	if (op[0] == 0x62){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x\t xlr %s, #0x%02x", op[0], op[1], op[2], regs[val], val2);
		c1->ram2[val] = val2;
		retval = 3;
		goto done1;
	}
	/* XLR @R[0-1], A */
	if (op[0] == 0x66 || op[0] == 0x67){
		val = op[0]-0x66;
		sprintf(s2, "%02x            \t xlr @r%d, a", op[0], val);
		val2 = read_reg(c1, val);
		c1->ram2[val2] ^= c1->ram2[SFR_ACC];
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* XLR A, R[0-7] */
	if (op[0] >= 0x68 && op[0] <= 0x6f){
		val = op[0]-0x68;
		sprintf(s2, "%02x         \t xlr a, r%d", op[0], val);
		c1->ram2[SFR_ACC] ^= read_reg(c1, val);
		sprintf(s3, "\t; a = 0x%02x", read_reg(c1, val));
		retval = 2;
		goto done1;
	}
	/* XRL a, #data */
	if (op[0] == 0x64){
		val = op[1];
		sprintf(s2, "%02x %02x     \t xrl a, #0x%02x", op[0], op[1], val);
		c1->ram2[SFR_ACC] ^= op[1];
		retval = 2;
		sprintf(s3, "\t; a = 0x%02x", c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* XRL A, iram addr */
	if (op[0] == 0x65){
		val = op[1];
		sprintf(s2, "%02x %02x     \t xlr a, %s", op[0], op[1], regs[val]);
		c1->ram2[SFR_ACC] ^= c1->ram2[val];
		retval = 2;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val, c1->ram2[val]);
		goto done1;
	}
	/* XLR iram addr, #data */
	if (op[0] == 0x63){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x\t xlr %s, #0x%02x", op[0], op[1], op[2], regs[val], val2);
		c1->ram2[val] ^= val2;
		retval = 3;
		goto done1;
	}
	/* XCH A, R[0-1] */
	if (op[0] >= 0xc8 && op[0] <= 0xcf){
		val = op[0]-0xc8;
		sprintf(s2, "%02x            \t xch r%d, a", op[0], val);
		val2 = c1->ram2[SFR_ACC];
		c1->ram2[SFR_ACC] = read_reg(c1, val);
		write_reg(c1, val, val2);
		retval = 1;
		goto done1;
	}
	/* XCH A, iram addr */
	if (op[0] == 0xc5){
		val = op[1];
		sprintf(s2, "%02x %02x     \t xch a, %s", op[0], op[1], regs[val]);
		val2 = c1->ram2[val];
		c1->ram2[val] = c1->ram2[SFR_ACC];
		c1->ram2[SFR_ACC] = val2;
		retval = 2;
		sprintf(s3, "\t; [0x%02x] = 0x%02x, a = 0x%02x", val, c1->ram2[val], c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* XCH A, @R[0-1] */
	if (op[0] == 0xc6 || op[0] == 0xc7){
		val = op[0]-0xc6;
		sprintf(s2, "%02x            \t xch a, @r%d", op[0], val);
		val2 = read_reg(c1, val);
		val = c1->ram2[SFR_ACC];
		c1->ram2[SFR_ACC] = c1->ram2[val2];
		c1->ram2[val2] = val;
		retval = 1;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val2, c1->ram2[val2]);
		goto done1;
	}
	/* RR */
	if (op[0] == 0x23){
		sprintf(s2, "%02x            \t rr a", op[0]);
		val = c1->ram2[SFR_ACC];
		val <<= 1;
		val |= (val & (1 << 8)) ? 1 : 0; /* bit7 to bit0 */
		c1->ram2[SFR_ACC] =val & 0xff;
		retval = 1;
		goto done1;
	}
	/* RL */
	if (op[0] == 0x03){
		sprintf(s2, "%02x            \t rl a", op[0]);
		val = c1->ram2[SFR_ACC];
		val |= (val & 0x1) ? (1 << 8) : 0; /* bit7 to bit0 */
		val >>= 1;
		c1->ram2[SFR_ACC] =val & 0xff;
		retval = 1;
		goto done1;
	}
	/* RLC */
	if (op[0] == 0x33){
		sprintf(s2, "%02x            \t rlc a", op[0]);
		val = c1->ram2[SFR_ACC];
		val <<= 1;
		val |= (c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0; /* carry to bit0 */
		c1->ram2[SFR_ACC] =val & 0xff;
		c1->ram2[SFR_PSW] &= ~(1 << 7);
		if (val & (1 << 8)) c1->ram2[SFR_PSW] |= (1 << 7);
		retval = 1;
		goto done1;
	}
	/* RRC */
	if (op[0] == 0x13){
		sprintf(s2, "%02x            \t rrc a", op[0]);
		val = c1->ram2[SFR_ACC];
		val2 = (c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0;
		c1->ram2[SFR_PSW] &= ~(1 << 7);
		if (val & (1 << 0)) c1->ram2[SFR_PSW] |= (1 << 7);
		val >>= 1;
		val |= (c1->ram2[SFR_PSW] & (1 << 7)) ? (1 << 7) : 0; /* carry to bit7 */
		c1->ram2[SFR_ACC] = val & 0xff;
		retval = 1;
		goto done1;
	}
	/* ORL iram addr, #data */
	if (op[0] == 0x43){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x\t orl %s, #0x%02x", op[0], op[1], op[2], regs[val], val2);
		c1->ram2[val] |= val2;
		retval = 3;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val, val2);
		goto done1;
	}
	/* ORL iram addr, A */
	if (op[0] == 0x42){
		val = op[1];
		sprintf(s2, "%02x %02x     \t orl %s, a", op[0], op[1], regs[val]);
		c1->ram2[val] |= c1->ram2[SFR_ACC];
		retval = 2;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val, c1->ram2[val]);
		goto done1;
	}
	/* ANL iram addr, #data */
	if (op[0] == 0x53){
		val = op[1];
		val2 = op[2];
		sprintf(s2, "%02x %02x %02x\t anl %s, #0x%02x", op[0], op[1], op[2], regs[val], val2);
		c1->ram2[val] |= val2;
		retval = 3;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val, val2);
		goto done1;
	}
	/* ORL A, R[0-7] */
	if (op[0] >= 0x48 && op[0] <= 0x4f){
		val = op[0]-0x48;
		sprintf(s2, "%02x            \t orl r%d, a", op[0], val);
		c1->ram2[SFR_ACC] |= read_reg(c1, val);
		retval = 1;
		sprintf(s3, "\t; a = %d", c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* ANL A, R[0-7] */
	if (op[0] >= 0x58 && op[0] <= 0x5f){
		val = op[0]-0x58;
		sprintf(s2, "%02x            \t anl r%d, a", op[0], val);
		c1->ram2[SFR_ACC] &= read_reg(c1, val);
		retval = 1;
		sprintf(s3, "\t; a = %d", c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* ORL c, bit addr */
	if (op[0] == 0x72){
		val = op[1];
		sprintf(s2, "%02x %02x     \t orl c, bit 0x%02x", op[0], op[1], val);
		c1->ram2[SFR_PSW] |= read_bit(c1, val) ? (1 << 7) : 0;
		sprintf(s3, "\t; c = %d", read_bit(c1, val) ? (1 << 7) : 0);
		retval = 2;
		goto done1;
	}
	/* ANL a, #data */
	if (op[0] == 0x54){
		val = op[1];
		sprintf(s2, "%02x %02x     \t anl a, #0x%02x", op[0], op[1], val);
		c1->ram2[SFR_ACC] &= op[1];
		retval = 2;
		sprintf(s3, "\t; a = %d", c1->ram2[SFR_ACC]);
		goto done1;
	}
	/* ANL c, bit addr */
	if (op[0] == 0x82){
		val = op[1];
		sprintf(s2, "%02x %02x     \t anl c, bit 0x%02x", op[0], op[1], val);
		c1->ram2[SFR_PSW] &= ~(1 << 7);
		c1->ram2[SFR_PSW] &= read_bit(c1, val) ? (1 << 7) : 0;
		sprintf(s3, "\t; c = %d", read_bit(c1, val) ? (1 << 7) : 0);
		retval = 2;
		goto done1;
	}
	/* ANL c, ~bit addr */
	if (op[0] == 0xB0){
		val = op[1];
		sprintf(s2, "%02x %02x     \t anl c, ~bit 0x%02x", op[0], op[1], val);
		c1->ram2[SFR_PSW] &= ~(1 << 7);
		c1->ram2[SFR_PSW] &= read_bit(c1, val) ? 0 : (1 << 7);
		sprintf(s3, "\t; c = %d", read_bit(c1, val) ? (1 << 7) : 0);
		retval = 2;
		goto done1;
	}
	/* ORL c, ~bit addr */
	if (op[0] == 0xa0){
		val = op[1];
		sprintf(s2, "%02x %02x     \t orl c, ~bit 0x%02x", op[0], op[1], val);
		c1->ram2[SFR_PSW] |= read_bit(c1, val) ? 0 : (1 << 7);
		sprintf(s3, "\t; c = %d", read_bit(c1, val) ? (1 << 7) : 0);
		retval = 2;
		goto done1;
	}
	/* ORL a, #data */
	if (op[0] == 0x44){
		val = op[1];
		sprintf(s2, "%02x %02x     \t orl a, #0x%02x", op[0], op[1], val);
		c1->ram2[SFR_ACC] |= op[1];
		retval = 2;
		goto done1;
	}
	/* ORL a, iram addr */
	if (op[0] == 0x45){
		val = op[1];
		sprintf(s2, "%02x %02x     \t orl a, %s", op[0], op[1], regs[val]);
		c1->ram2[SFR_ACC] |= c1->ram2[op[1]];
		retval = 2;
		goto done1;
	}
	/* ANL a, iram addr */
	if (op[0] == 0x55){
		val = op[1];
		sprintf(s2, "%02x %02x     \t anl a, %s", op[0], op[1], regs[val]);
		c1->ram2[SFR_ACC] &= c1->ram2[op[1]];
		retval = 2;
		goto done1;
	}
	/* add a, iram addr */
	if (op[0] == 0x25){
		val = op[1];
		sprintf(s2, "%02x %02x     \t add a, %s", op[0], op[1], regs[val]);
		c1->ram2[SFR_ACC] += c1->ram2[op[1]];
		retval = 2;
		goto done1;
	}
	/* addc a, iram addr */
	if (op[0] == 0x35){
		val = op[1];
		sprintf(s2, "%02x %02x     \t addc a, %s", op[0], op[1], regs[val]);
		c1->ram2[SFR_ACC] += c1->ram2[op[1]] + (c1->ram2[SFR_PSW] & (1 << 7)) ? 1 : 0;
		retval = 2;
		goto done1;
	}
	/* subb a, iram addr */
	if (op[0] == 0x95){
		val = op[1];
		sprintf(s2, "%02x %02x     \t subb a, %s", op[0], op[1], regs[val]);
		c1->ram2[SFR_ACC] -= c1->ram2[op[1]];
		retval = 2;
		goto done1;
	}
	/* PUSH iram addr */
	if (op[0] == 0xc0){
		val = op[1];
		sprintf(s2, "%02x %02x     \t push %s", op[0], op[1], regs[val]);
		push(c1, c1->ram2[val]);
		sprintf(s3, "\t; sp = 0x%02x", c1->ram2[SFR_SP]);
		retval = 2;
		goto done1;
	}
	/* POP iram addr */
	if (op[0] == 0xd0){
		val = op[1];
		sprintf(s2, "%02x %02x     \t pop %s", op[0], op[1], regs[val]);
		c1->ram2[val] = pop(c1);
		sprintf(s3, "\t; [0x%02x] = 0x%02x, sp = 0x%02x", val, c1->ram2[val], c1->ram2[SFR_SP]);
		retval = 2;
		goto done1;
	}
	/* DEC iram addr */
	if (op[0] == 0x15){
		val = op[1];
		sprintf(s2, "%02x %02x     \t dec %s", op[0], op[1], regs[val]);
		c1->ram2[val]--;
		sprintf(s3, "\t; [0x%02x] = 0x%02x", val, c1->ram2[val]);
		retval = 2;
		goto done1;
	}
	/* SUBB a, @r[0-1] */ //TODO : fix this. not XRAM
	if (op[0] == 0x96 || op[0] == 0x97){
		val = op[0]-0x96;
		sprintf(s2, "%02x          \t subb a, @r%d", op[0], val);
		c1->ram2[SFR_P0] = read_reg(c1, val);
		dptr = (c1->ram2[SFR_P2] << 8) | c1->ram2[SFR_P0];
		c1->ram2[SFR_ACC] -= c1->ram3[dptr];
		sprintf(s3, "\t; [0x%04x] = 0x%02x, a = 0x%02x", dptr, c1->ram3[dptr], c1->ram2[SFR_ACC]);
		retval = 1;
		goto done1;
	}
	/* ORL a, @r[0-1] */ //TODO : fix this. not XRAM
	if (op[0] == 0x46 || op[0] == 0x47){
		val = op[0]-0x46;
		sprintf(s2, "%02x          \t orl a, @r%d", op[0], val);
		c1->ram2[SFR_P0] = read_reg(c1, val);
		dptr = (c1->ram2[SFR_P2] << 8) | c1->ram2[SFR_P0];
		c1->ram2[SFR_ACC] |= c1->ram3[dptr];
		sprintf(s3, "\t; [0x%04x] = 0x%02x, a = 0x%02x", dptr, c1->ram3[dptr], c1->ram2[SFR_ACC]);
		retval = 1;
		goto done1;
	}


	sprintf(s2, "Unknown opcode 0x%02x", op[0]);

	 
	//sprintf(result, "%s%s%s", s1, s2, s3);
	sprintf(result, "%s%s", s1, s2);
	return(-2000);

done1 :
	if (cond) *cond = c2;
	if (jmp_addr) *jmp_addr = addr2;

	//sprintf(result, "%s%s%s", s1, s2, s3);
	sprintf(result, "%s%s", s1, s2);
	return(retval);
}

void reset(struct core *c1) {

	memset(c1->ram2, 0, sizeof(c1->ram2));
	c1->ram2[SFR_SP] = 0x07;

	// value set possibly by boot loader

	c1->ram3[0xf86b] = 0x55;
}

int d = 0;

//TODO : CPU flags
char result[1024];

/*
#define TYPE_CODE 0
#define TYPE_DATA 1

struct block{
	char *string[];
	int type;
	int len;
	uint8_t op[8];
	struct block *prev;
	struct block *next;
	struct block *xref;
}

*/

int analyze_code_flow(struct core *c1, uint8_t *map, uint32_t addr, char *commands[]) {

	uint32_t a1, a2;
	int i;
	int addr2, cond;
	int retval;
	
	int jump;

	d++;
	a2 = addr;


	while(1){
		
		//for(i=0;i<d;i++) printf(" ");
		//printf(" : :%05d : :   ", d);
		if (map[a2]) {retval=-3;break;}
		map[a2] = 1;
		jump = 0;
		retval = analyze(c1, a2, result, &addr2, &cond);
		if (retval == -2000) {
			printf("%s\n", result);
			break;
		}
		if (addr2 != -1) {
			if (addr2 & WOULD_JUMP) jump = 1;
			if (addr2 & FUNC_START) map[a2]=3;
			addr2 &= ~(WOULD_JUMP | FUNC_START);
		}
		// 0x73 is opcode for jmp @dptr+a. We can't follow that in static analysis
		if (addr2 != -1 && c1->ram1[a2] != 0x73) a1 = addr2;
		else a1 = a2 + retval;
		for(i = a2 + 1; i < a2 + retval; i++) map[i] = 2;
		//printf("%s\n", result);
		commands[a2] = strdup(result);
		if (c1->ram1[a2] == 0x22 || c1->ram1[a2] == 0x32) {
			retval=-3;
			map[a2] = 4;
			break;
		}
		if (cond) {
			retval = analyze_code_flow(c1, map, retval + a2, commands);
			if (retval == -2000) break;
			a2 = addr2;
		}
		else a2 = a1;
	}
	d--;
	return(retval);
}


int dddd(int argc, char* argv[]) {

	uint32_t addr;
	FILE *h;
	int i;
	int retval;
	struct core core1;
	int cond, addr2;
	char result[1024];
	uint8_t  map[MEM_SIZE]={0};
	char *commands[MEM_SIZE];
	int fs, fe;

	core1.ram1 = (uint8_t*) malloc(MEM_SIZE);
	core1.ram1_size = MEM_SIZE;
	addr = 0;
	h = fopen(argv[1], "r");
	if (h == NULL) {
		printf("analyze what?\n");
		return(1);
	}
	for(i=0;i<core1.ram1_size;i++){
		retval = fread(core1.ram1 + i, 1, 1, h);
		if (retval != 1) break;
	}
	fclose(h);
	printf("read %d bytes.\n", i);

	retval = analyze_code_flow(&core1, map, 0, commands);
	printf("retval = %d\n", retval);


	/* analyze areas pointed by interrupt vector table */
	for (i=3;i<0xa0;i+=8){		
		analyze_code_flow(&core1, map, i, commands);
	}


	
	fs= -1; fe = -1;
	for(i = 0; i < MEM_SIZE; i++) {
		//if (commands[i]) printf("%s\n", commands[i]);
		//else if (!map[i]) printf("%04x\t byte 0x%02x\n", i, core1.ram1[i]);
		if (map[i] == 3) {	
			fs = i;
		}
		if (map[i] == 4 && fs != -1) {
			printf("possible function 0x%04x-0x%04x (%d bytes)\n", fs, i, i - fs);
			fs = -1;
		}
	}
	for(i = 0; i < MEM_SIZE; i++) {
		if (commands[i]) printf("%s\n", commands[i]);
		else if (!map[i]) printf("%04x\t byte 0x%02x\n", i, core1.ram1[i]);
	
	}
	for(i=0, retval=0;i<MEM_SIZE;i++) if (map[i]) retval++;
	printf("%.1f %% disassembled\n", retval * 100.0 / (1.0 * MEM_SIZE)); 
	
	return(0);

	
	reset(&core1);

	for(i=0;;) {
		retval = analyze(&core1, i, result, &addr2, &cond);
		if (retval == -2000) {
			printf("%s\n", result);
			break;
		}
		if (addr2 != -1) i = addr2;
		else i += retval;
		if (i < 0 || i > MEM_SIZE) {
			printf("PC out of control!\n");
			break;
		}
		printf("%s\n", result);
	}
	return(0);
}


#include <stdint.h>
#include <standard_buffers.h>
#include <lib.h>
#include <registers.h>

#define REGS_QTY 22

typedef struct
{
	char * name;
	uint64_t content;
}regsType;

regsType regs[REGS_QTY] = {{"  [gs]", 0}, {"  [fs]", 0}, {"  [R15]", 0}, {"  [R14]", 0}, {"  [R13]", 0}, {"  [R12]", 0}, {"  [R11]", 0}, {"  [R10]", 0}, {"  [R9]", 0}, {"  [R8]", 0}, {"  [RSI]", 0}, {"  [RDI]", 0}, {"  [RBP]", 0}, {"  [RDX]", 0}, {"  [RCX]", 0}, {"  [RBX]", 0}, {"  [RAX]", 0}, {"  [RIP]", 0}, {"  [CS]", 0}, {"  [RFLAGS]", 0}, {"  [RSP]", 0}, {"  [SS]", 0}};

int info_reg(){
    return _syscall(__info_reg);
}

void printRegs(uint64_t * rsp)
{	for (int i = 0 ; i < REGS_QTY ; i++)
	{
		regs[i].content = rsp[i];
	}

	for(int j = REGS_QTY-1; j >= 0; j--)
	{
		write_string_buffer(STD_OUT, regs[j].name);
		write_string_buffer(STD_OUT," - ");
		write_int_buffer(STD_OUT,(uint64_t)regs[j].content,16);
		write_char_buffer(STD_OUT,'\n');

	}
}
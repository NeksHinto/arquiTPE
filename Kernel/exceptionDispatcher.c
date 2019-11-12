#include <stdint.h>
#include <standard_buffers.h>
#include <lib.h>

#define REGISTER_NUM 15

typedef void (* exception_ptr)(uint64_t * instructionPointer, uint64_t * stackPointer);

static void zero_division(uint64_t * instructionPointer, uint64_t * stackPointer);
static void invalid_opcode(uint64_t * instructionPointer, uint64_t * stackPointer);
static void write_registers(uint64_t * instructionPointer, uint64_t * stackPointer);

exception_ptr exceptions[] = {
        zero_division,0,0,0,0,0,invalid_opcode};

void exceptionDispatcher(int exceptionNum, uint64_t * instructionPointer, uint64_t * stackPointer) {
	exceptions[exceptionNum](instructionPointer,stackPointer);
}

static void zero_division(uint64_t * instructionPointer, uint64_t * stackPointer){
	write_string_buffer(STD_ERR,"ERROR: DIVISION BY ZERO\n");
	write_registers(instructionPointer, stackPointer);
}

static void invalid_opcode(uint64_t * instructionPointer, uint64_t * stackPointer){
	write_string_buffer(STD_ERR,"ERROR: INVALID INSTRUCTION\n");
	write_registers(instructionPointer, stackPointer);
}

/* Write register current status in Standard Error buffer */
static void write_registers(uint64_t * instructionPointer, uint64_t * stackPointer){
	write_string_buffer(STD_ERR,"RIP: ");
	write_int_buffer(STD_ERR,(uint64_t)instructionPointer,16);
	write_char_buffer(STD_ERR,'\n');
	char * registers[] = {"R15","R14","R13","R12","R11","R10","R9","R8","RSI","RDI","RBP","RDX","RCX","RBX","RAX"};
	int i;
	for(i = 0; i < REGISTER_NUM; i++){
		write_string_buffer(STD_ERR,registers[i]);
		write_string_buffer(STD_ERR,": ");
		write_int_buffer(STD_ERR,*(stackPointer + i),16);
		write_char_buffer(STD_ERR,'\n');
	}
}

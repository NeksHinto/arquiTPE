#include <stdint.h>
#include <std_buffers.h>
#include <lib.h>

#define REGISTER_NUM 15

typedef void (*exception_ptr)(uint64_t * instructionPointer, uint64_t * stackPointer);

static void zero_division(uint64_t * instructionPointer, uint64_t * stackPointer);
static void invalid_opcode(uint64_t * instructionPointer, uint64_t * stackPointer);
static void write_registers(uint64_t * instructionPointer, uint64_t * stackPointer);

/** ============================================== */
/**             Exceptions Handler                 */
/** ============================================== */
exception_ptr exceptions[] = {
        zero_division,  // EXCEPTION 0
        0,0,0,0,0,
        invalid_opcode  // EXCEPTION 1
};
/** ============================================== */
void exceptionDispatcher(int exceptionNum, uint64_t * instructionPointer, uint64_t * stackPointer) {
	exceptions[exceptionNum](instructionPointer,stackPointer);
}

/** Division by Zero exception routine */
static void zero_division(uint64_t * instructionPointer, uint64_t * stackPointer){
	write_string_in_buffer(STD_ERR,"ERROR: DIVISION BY ZERO\n");
	write_registers(instructionPointer, stackPointer);
}

/** Invalid Operation Code exception routine  */
static void invalid_opcode(uint64_t * instructionPointer, uint64_t * stackPointer){
	write_string_in_buffer(STD_ERR,"ERROR: INVALID OPERATION CODE\n");
	write_registers(instructionPointer, stackPointer);
}

/** Write registers current status in Standard Error buffer */
static void write_registers(uint64_t * instructionPointer, uint64_t * stackPointer){
	write_string_in_buffer(STD_ERR,"RIP: ");
	write_int_in_buffer(STD_ERR,(uint64_t)instructionPointer,16);
	write_char_in_buffer(STD_ERR,'\n');
	char * registers[] = {"R15","R14","R13","R12","R11","R10","R9","R8","RSI","RDI","RBP","RDX","RCX","RBX","RAX"};
	int i;
	for(i = 0; i < REGISTER_NUM; i++){
		write_string_in_buffer(STD_ERR,registers[i]);
		write_string_in_buffer(STD_ERR,": ");
		write_int_in_buffer(STD_ERR,*(stackPointer + i),16);
		write_char_in_buffer(STD_ERR,'\n');
	}
}

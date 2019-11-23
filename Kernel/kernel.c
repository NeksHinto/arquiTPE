#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <idt.h>
#include <std_buffers.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;


typedef int (*EntryPoint)();



/************************************************************
 * PageSize: Paging system defines the size of a page as
 *                4096 bytes = 0x1000 bytes.
************************************************************/
static const uint64_t PageSize = 0x1000;

/************************************************************
 * sampeCodeModuleAddress:
************************************************************/
static void* const sampleCodeModuleAddress = (void*)0x400000;
extern void* instructionPointerBackup;
extern void* stackPointerBackup;

/************************************************************
 * sampleDatModuleAddress:
************************************************************/
static void* const sampleDataModuleAddress = (void*)0x500000;

/*************************************************************
 * EntryPoint: 
*************************************************************/
typedef int (*EntryPoint)();


/*************************************************************
 * Function: clearBss
 * Use: clearBSS( bssAdress, bssSize );
 * -----------------------------------------------------------
 * Description: Clears BSS Memory to start the OS.
 * -----------------------------------------------------------
 * Pre-Condition: BSS Memory with variables saved.
 * Post-Condition: BSS Memory cleared.
*************************************************************/
void clearBSS(void* bssAddress, uint64_t bssSize)
{
	memset(bssAddress,0,bssSize);
}

/*************************************************************
 * Function: getStackBase
 * Use: void* stackBaseAddress = getStackBase();
 * -----------------------------------------------------------
 * Description: Returns the stack base. The size of the
 * 				           Stack is of 32KiB.
 * -----------------------------------------------------------
 * Pre-Condition: Stack base address unknown.
 * Post-Condition: Variable with address of the stack base.
*************************************************************/
void* getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel+PageSize*8				
		-sizeof(uint64_t)			//Begin at the top of the stack
	);
}

/*************************************************************
 * Function: initializeKernelBinary
 * Use: void* stackBaseAddress = initializeKernelBinary();
 * -----------------------------------------------------------
 * Description: Sets all important assets of the binary,
 *				such as the BSS Memory, Module Adresses
 *                          Buffer and Stack
 * -----------------------------------------------------------
 * Pre-Condition: The beginnings of all times
 * Post-Condition: Binary set up
*************************************************************/
void* initializeKernelBinary()
{
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	set_up_buffers();
	return getStackBase();
}


int main()
{	
	load_idt();
	set_up_buffers();
	instructionPointerBackup = sampleCodeModuleAddress;
	stackPointerBackup = getStackPointer() + 2* 8;
	((EntryPoint)sampleCodeModuleAddress)();

	return 1;
}

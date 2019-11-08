#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>


static void loadModule(uint8_t ** module, void * targetModuleAddress);
static uint32_t readUint32(uint8_t ** address);

/*************************************************************
 * Function: loadModules
 * Use: loadModules(payloadStart, targetModuleAddress);
 * -----------------------------------------------------------
 * Description: Loads the modules passed as arguments in
 * 				    an array into the current module.
 * -----------------------------------------------------------
 * Pre-Condition: Modules not loaded.
 * Post-Condition: Modules loaded.
*************************************************************/
void loadModules(void * payloadStart, void ** targetModuleAddress)
{
	int i;
	uint8_t* currentModule = (uint8_t*)payloadStart;
	uint32_t moduleCount = readUint32(&currentModule);
	for (i = 0; i < moduleCount; i++)
		loadModule(&currentModule, targetModuleAddress[i]);
}

/*************************************************************
 * Function: loadModule
 * Use: loadModule(module,targetModuleAddress);
 * -----------------------------------------------------------
 * Description: Loads the module into the target module
 * 						       address.
 * -----------------------------------------------------------
 * Pre-Condition: module not loaded into the target.
 * Post-Condition: Module loaded.
*************************************************************/
static void loadModule(uint8_t ** module, void * targetModuleAddress)
{
	uint32_t moduleSize = readUint32(module);
	memcpy(targetModuleAddress, *module, moduleSize);
	*module += moduleSize;
}

/*************************************************************
 * Function: readUint32
 * Use: uint32 moduleCount = readUint32(moduleAddress)
 * -----------------------------------------------------------
 * Description: Returns the module's size.
 * -----------------------------------------------------------
 * Pre-Condition: Unknown module size.
 * Post-Condition: Known module size.
*************************************************************/
static uint32_t readUint32(uint8_t ** address)
{
	uint32_t result = *(uint32_t*)(*address);
	*address += sizeof(uint32_t);
	return result;
}

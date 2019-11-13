#ifndef MODULELOADER_H
#define MODULELOADER_H

/*************************************************************
 * Function: loadModules
 * Use: loadModules(payloadStart, targetModuleAddress);
 * -----------------------------------------------------------
 * Description: Loads the modules passed as argument
 *                    into the current module.
 * -----------------------------------------------------------
 * Pre-Condition: -
 * Post-Condition: Modules loaded.
*************************************************************/
void loadModules(void * payloadStart, void ** moduleTargetAddress);

#endif
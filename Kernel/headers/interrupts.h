#ifndef INTERRUPTS_H_
    #define INTERRUPTS_H_

#include <idt.h>
/** ============================================== */
/**       Declaration for ASM functions:           */
/** Al this exists in 'interrupts.asm'             */
/** ============================================== */

/** See 'irqDispatcher.c' for IRQx declaration */
extern void _irq00Handler(void);

extern void _irq01Handler(void);

/** See 'exceptionDispatcher.c' for Exception declarations */
extern void _exception0Handler(void);

extern void _exception6Handler(void);

extern void _syscallHandler(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);

extern void _cli(void);

extern void _sti(void);

extern void _hlt(void);

extern void picMasterMask(uint8_t mask);

extern id picSlaveMask(uint8_t mask);

/** Ends cpu execution */
extern void haltcpu(void);


#endif /* INTERRUPTS_H_ */

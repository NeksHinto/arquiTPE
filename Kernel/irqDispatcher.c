#include <time.h>
#include <standard_buffers.h>
#include <keyboard_driver.h>

/** Prototypes */
static void int_20();
static void int_21();

/** ===================================== */
/**        Interruptions Handler          */
/** ===================================== */
void (* irq_handler[])() = {
        int_20, // IRQ00: Timer INT20
        int_21  // IRQ01: Keyboard INT21
};
/** ===================================== */


/** IRQ Dispatcher */
/** -------------- */
/** receive IRQ-number and call corresponding handler */
void irqDispatcher(uint64_t irq) {
	irq_handler[irq]();
}


void int_20() {
	timer_handler();
}

void int_21() {
	keyboard_handler();
}

#include <time.h>
#include <standard_buffers.h>
#include <keyboard_driver.h>

static void int_20();
static void int_21();


void (* irq_handler[])() = {int_20,int_21};

void irqDispatcher(uint64_t irq) {
	irq_handler[irq]();
}

void int_20() {
	timer_handler();
}

void int_21() {
	keyboard_handler();
}

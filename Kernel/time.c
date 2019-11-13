#include <time.h>
#include <interrupts.h>

/** Initial reference */
static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

int get_minutes(){
	return _get_minutes();
}

int get_hours(){
	return _get_hours();
}

int get_seconds(){
	return _get_seconds();
}

void wait(int ticks) {
	_sti();
	int start = ticks_elapsed();
	int end = ticks + start;
	while(ticks_elapsed() < end);
}
#ifndef _TIME_H_
#define _TIME_H_

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
int get_hours();
int get_minutes();
int get_seconds();
void wait(int ticks);

//Assembly library
int _get_hours();
int _get_seconds();
int _get_minutes();

#endif

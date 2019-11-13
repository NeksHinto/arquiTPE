#ifndef _TIME_H_
    #define _TIME_H_

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
int get_hours();
int get_minutes();
int get_seconds();
void wait(int ticks);

/** This exists in 'time.asm' */
extern int _get_hours();
extern int _get_seconds();
extern int _get_minutes();

#endif

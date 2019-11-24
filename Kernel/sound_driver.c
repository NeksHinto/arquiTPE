#include <sound_driver.h>
#include <time.h>

/** This exists in 'beep.asm' */
extern void _beepOn();
extern void _beepOff();

void beep(int ticks){
  activate_beep();
  wait(ticks);
  deactivate_beep();
}

void activate_beep(){
  _beepOn();
}

void deactivate_beep(){
  _beepOff();
}
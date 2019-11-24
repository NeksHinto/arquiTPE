#include <sound_driver.h>
#include <time.h>
#include <beep.h>

void beep(int ticks){
  activate_beep();
  wait(ticks);
  deactivate_beep();
}

void activate_beep(){
  _beep();
}

void deactivate_beep(){
  _unbeep();
}
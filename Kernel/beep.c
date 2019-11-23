#include <beep.h>
#include <time.h>

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
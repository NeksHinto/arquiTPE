#include <beep.h>
#include <syscall.h>

void beep(int ticks) {
    _syscall(__beep, ticks);
}
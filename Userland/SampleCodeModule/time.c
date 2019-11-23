#include <time.h>
#include <syscall.h>

int system_hours() {
    return _syscall(__get_hours);
}

int system_minutes() {
    return _syscall(__get_minutes);
}

int system_seconds() {
    return _syscall(__get_seconds);
}

void wait(int ticks) {
    _syscall(__wait, ticks);
}

int ticks_elapsed() {
   return _syscall(__ticks_elapsed);
}

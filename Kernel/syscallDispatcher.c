#include <std_buffers.h>
#include <video_driver.h>
#include <time.h>

typedef uint64_t(*SystemCall)();

//video_driver.h
static uint64_t __get_width();
static uint64_t __get_height();
static void __read_pixel(uint64_t x, uint64_t y, Color * color);
static void __write_pixel(uint64_t x, uint64_t y, Color color);
static void __write_block(uint64_t x, uint64_t y, int base, int height, Color color);
static void __move_screen_up(int pixels, Color background_color);
static void __fill_screen(Color color);
 
// standard_buffers.h
static void __clear_buffers(int index);
static int __write_char_buffer(int index, char character);
static int __write_int_buffer(int index, uint64_t value,int base);
static int __write_string_buffer(int index, char * str);
static char __read_char_buffer(int index);
static int __read_string_buffer(int index, char * str,int size);
 
//sound_driver.h
// TODO: static void __beep(int ticks);
 
 //time.h
static void __wait(int ticks);
static int __get_hours();
static int __get_minutes();
static int __get_seconds();
static int __ticks_elapsed();

SystemCall syscall_array[] = {
        0, 0, 0,
    (SystemCall)__get_width,
    (SystemCall)__get_height,
    (SystemCall)__read_pixel,
    (SystemCall)__write_pixel,
    (SystemCall)__write_block,
    (SystemCall)__move_screen_up,
    (SystemCall)__fill_screen,
    (SystemCall)__clear_buffers,
    (SystemCall)__write_char_buffer,
    (SystemCall)__write_int_buffer,
    (SystemCall)__write_string_buffer,
    (SystemCall)__read_char_buffer,
    (SystemCall)__read_string_buffer,
    (SystemCall)__beep,
    (SystemCall)__wait,
    (SystemCall)__get_hours,
    (SystemCall)__get_minutes,
    (SystemCall)__get_seconds,
    (SystemCall)__ticks_elapsed
};

void syscallDispatcher(uint64_t index, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e){
  syscall_array[index](a, b, c, d , e);
}

static uint64_t __get_width() {
    return get_width();
}

static uint64_t __get_height() {
    return get_height();
}

static void __read_pixel(uint64_t x, uint64_t y, Color * color) {
    *color = read_pixel(x, y);
}

static void __write_pixel(uint64_t x, uint64_t y, Color color){
    write_pixel(x, y, color);
}

static void __write_block(uint64_t x, uint64_t y, int base, int height, Color color) {
    write_block(x, y, base, height, color);
}

static void __move_screen_up(int pixels, Color background_color) {
    move_screen_up(pixels, background_color);
}

static void __fill_screen(Color color) {
    fill_screen(color);
}

static void __clear_buffers(int index) {
    clear_buffers(index);
}

static int __write_char_buffer(int index, char character) {
    return write_char_buffer(index, character);
}

static int __write_int_buffer(int index, uint64_t value,int base) {
    return write_int_buffer(index, value, base);
}

static int __write_string_buffer(int index, char * str) {
    return write_string_buffer(index, str);
}

static char __read_char_buffer(int index) {
    return read_char_buffer(index);
}

static int __read_string_buffer(int index, char * str,int size){
    return read_string_buffer(index, str, size);
}

/**
static void __beep(int ticks){
    beep(ticks);
}
*/

static void __wait(int ticks) {
    return wait(ticks);
}

static int __get_hours() {
    return get_hours();
}

static int __get_minutes() {
    return get_minutes();
}

static int __get_seconds() {
    return get_seconds();
}

static int __ticks_elapsed() {
    return ticks_elapsed();
}
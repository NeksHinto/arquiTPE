#ifndef SYSTEMCALL_H
    #define SYSTEMCALL_H

#include <stdint.h>

#define __get_width                   3
#define __get_height                  4
#define __read_pixel                  5
#define __write_pixel                 6
#define __write_block                 7
#define __move_screen_up              8
#define __fill_screen                 9
#define __clear_buffers              10
#define __write_char_in_buffer       11
#define __write_int_in_buffer        12
#define __write_string_in_buffer     13
#define __read_char_from_buffer      14
#define __read_string_from_buffer    15
#define __beep                       16
#define __wait                       17
#define __get_hours                  18
#define __get_minutes                19
#define __get_seconds                20
#define __ticks_elapsed              21

/** This exists in 'syscall.asm' */
extern unsigned int _syscall(uint64_t arg1, ...);

#endif

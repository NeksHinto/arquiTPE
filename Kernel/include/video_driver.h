#ifndef videoDriver_h
    #define videoDriver_h

#include <stdint.h>

/** RGB Color Structure */
typedef struct Color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}Color;


uint64_t get_width();

uint64_t get_height();

Color read_pixel(uint64_t x, uint64_t y);

void write_pixel(uint64_t x, uint64_t y, Color color);

void write_block(uint64_t x, uint64_t y, int base, int height, Color color);

void move_screen_up(int pixels, Color background_color);

void fill_screen(Color color);


#endif

#include <stdint.h>

#ifndef VIDEO_MODULE_H
#define VIDEO_MODULE_H

typedef struct Color {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}Color;

//writes a char of the given color with a starting position of x,y.
void write_char(char c, uint64_t x, uint64_t y, Color color );
//writes a char of the given color and the given size with a starting position of x, y.
void write_sized_char(char c, uint64_t x, uint64_t y, Color color, Color background, uint64_t size);
//writes a string of the given color and the given size with a starting position of x, y.
void write_sized_string(char* s, uint64_t x, uint64_t y, Color color, Color background, uint64_t size, uint64_t spacing);
//same as write char but with strings.
void write_string(char* string, uint64_t x, uint64_t y, Color color); 
//writes a block of pixels of a designated color.
void write_block(uint64_t x, uint64_t y, int base, int height, Color color);
void write_pixel(uint64_t x, uint64_t y, Color color );

void move_screen_up(int amount, Color background_color);
void fill_screen(Color background_color);
int get_screen_width();
int get_screen_height();

#endif

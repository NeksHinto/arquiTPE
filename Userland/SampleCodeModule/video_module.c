#include <syscall.h>
#include <font.h>
#include <stdint.h>
#include <video_module.h>

static int SCREEN_WIDTH = -1;
static int SCREEN_HEIGHT = -1;
static int invalid_char(char c) {
	return c < 32 || c > 255;
}

void write_char(char c, uint64_t x, uint64_t y, Color color){
	if(invalid_char(c))
		return;
	char * char_pointer = getLetter(c);

	for(int j=0; j<HEIGHT; j++) {
		for(int i=0; i< WIDTH; i++) {
			if((1<<i) & char_pointer[j])
				_syscall(__write_pixel, (WIDTH - i) + x, j+y, color);
		}
	}
}

void write_sized_char(char c, uint64_t x, uint64_t y, Color color, Color background, uint64_t size){
	if(c < 32 || c > 255)
		return;

	 char * pos_of_char = getLetter(c);
	for(int j = 0; j < HEIGHT ; j++) {
		for(int i = 0, k = 128; i < WIDTH; i++, k/=2){
			if(k & pos_of_char[j])
        write_block(i*size + x, j*size + y,size,size, color);
			else
      write_block(i*size + x, j*size + y,size,size, background);
	
		}
	}
}

void write_pixel(uint64_t x, uint64_t y, Color color ) {
	_syscall(__write_pixel, x, y, color);
}

void write_string(char* string, uint64_t x, uint64_t y, Color color){
	while(*string != 0){
		write_char(*string,x,y,color);
		x += (WIDTH + 1);
		string++;
	}
}

void move_screen_up(int amount, Color background_color) {
	_syscall(__move_screen_up, amount, background_color);
}
void fill_screen(Color background_color) {
	_syscall(__fill_screen, background_color);
}

int get_screen_width() {
	return SCREEN_WIDTH = (SCREEN_WIDTH == -1) ? _syscall(__get_width) : SCREEN_WIDTH;
}

int get_screen_height() {
	return SCREEN_HEIGHT = (SCREEN_HEIGHT == -1) ? _syscall(__get_height) : SCREEN_HEIGHT;
}
void write_block(uint64_t x, uint64_t y, int base, int height, Color color) {
	_syscall(__write_block, x, y , base, height, color);
}
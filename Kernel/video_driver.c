#include <video_driver.h>
#include <lib.h>

InfoBlock screen = (InfoBlock) 0x5C00;

static int valid_position(int x, int y) {
    return x > 0 || x < get_width() || y > 0 || y < get_height(); 
}
static unsigned char* pixel_position(uint64_t pixel_offset) {
    return (unsigned char*)(screen->framebuffer + pixel_offset*(screen->bpp/8));
}


uint64_t get_width() {
    return screen->width;
}

uint64_t get_height(){
    return screen->height; 
}

Color read_pixel(uint64_t x, uint64_t y) {
    Color color_to_return = {0, 0, 0};

    if(valid_position(x,y)){
        uint64_t pixel_offset = x + y*get_width();
        unsigned char * current_pixel_position = pixel_position(pixel_offset);
        color_to_return.red = *(current_pixel_position+2);
        color_to_return.green = *(current_pixel_position+1);
        color_to_return.blue = *(current_pixel_position);
    }

    return color_to_return;
}

void write_pixel(uint64_t x, uint64_t y, Color color) {
    if(!valid_position(x, y))
        return;
    uint64_t pixel_offset = x + y*get_width();
    
    unsigned char * current_pixel_position = pixel_position(pixel_offset);
    
    *(current_pixel_position+2) = color.red;
    *(current_pixel_position+1) = color.green;
    *(current_pixel_position) = color.blue;
}

void write_block(uint64_t x, uint64_t y, int base, int height, Color color){
    for(int i=x; i< x+base; i++)
        for(int j=y; j< y+height; j++)
            write_pixel(i, j, color);
}
void fill_screen(Color color) {
    for(int i=0; i<get_width(); i++) 
        for(int j=0; j<get_height(); j++)
            write_pixel(i, j, color);
}
void move_screen_up(int pixels, Color background_color) {
    if(pixels <0)
        return;
    
    unsigned char * pixel_position_write = (unsigned char*)((uint64_t)screen->framebuffer);
	unsigned char * pixel_position_read = (unsigned char*)(screen->framebuffer + (uint64_t)(pixels*get_width())*(screen->bpp/8));
	unsigned char * max_position = (unsigned char *)(screen->framebuffer + (uint64_t)get_height()*get_width() *(screen->bpp/8));

		while(pixel_position_write < max_position){
			if(pixel_position_read < max_position) {
				*(pixel_position_write+2) = *(pixel_position_read+2);
				*(pixel_position_write+1) = *(pixel_position_read+1);
				*(pixel_position_write) = *(pixel_position_read);
			}
			else {
				*(pixel_position_write+2) = background_color.red;
				*(pixel_position_write+1) = background_color.green;
				*(pixel_position_write) = background_color.blue;
			}

			pixel_position_write += screen->bpp/8;
			pixel_position_read += screen->bpp/8;
		}
}
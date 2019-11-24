#include <standard_buffers.h>
static struct Buffer buffers[STANDARD_BUFFERS_AMOUNT];
static int invalid_index(int index) {
    return index > STANDARD_BUFFERS_AMOUNT-1 || index < 0;
}


void set_up_buffers() {
    struct Buffer stdout = {{0}, 0, 0};
    buffers[STD_OUT] = stdout;
    struct Buffer stdin = {{0}, 0, 0};
    buffers[STD_IN] = stdin;
    struct Buffer stderr = {{0}, 0, 0};
    buffers[STD_ERR] = stderr;
}

void clear_buffers(int index) {
    if(invalid_index(index))
        return;
    
    for(int i=0; i<BUFFER_SIZE; i++) {
        buffers[index].buffer[i] = 0;
        buffers[index].start = 0;
        buffers[index].size = 0;
    }
}

int write_char_buffer(int index, char c) {
    if(invalid_index(index))
        return 1;
    

    //Resets buffer position to the start of the array if it's full.
    if(buffers[index].size >= BUFFER_SIZE)
        buffers[index].start++;

    int offset = (buffers[index].start + buffers[index].size) % BUFFER_SIZE;
	buffers[index].buffer[offset] = c;

    if(buffers[index].size < BUFFER_SIZE)
        buffers[index].size++;
    
    return 0;
}
int write_int_buffer(int index, uint64_t value,int base) {
	if(invalid_index(index))
		return 1;
	int remainder;
	char number[20];
	int i = 0;
	int digits = 0;
	do{
	    remainder = value % base;
		number[i++] = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}while (value /= base);

	for(i = digits - 1; i >= 0; i--)
		write_char_buffer(index,number[i]);
  return 0;
}

int write_string_buffer(int index, char * str) {
    if(invalid_index(index))
        return 1;
    for(int i=0; str[i] != 0; i++)
        write_char_buffer(index, str[i]);
    
    return 0;
}

char read_char_buffer(int index) {
    if(invalid_index(index))
        return 0;
    
    
    if(buffers[index].size == 0)
        return 0;

    char c_to_return = buffers[index].buffer[buffers[index].start];

    //cleans read character and shifts start position.
    buffers[index].buffer[buffers[index].start++] = 0;
    //adjusts size;
    buffers[index].size--;

    if(buffers[index].start >= BUFFER_SIZE)
        buffers[index].start = 0;
    
    return c_to_return;
}

int read_string_buffer(int index, char *str, int size) {
    if(invalid_index(index))
        return 1;
    
    int i=0;
    char c;
    do {
        c = read_char_buffer(index);
        str[i++] = c;
        
    } while( c != 0 && i < size);

    return 0;
}


#include <std_buffers.h>

/*************************************************************
 * Buffer: Buffer struct to save information regarding the
 *         buffer ( buffer and it's displayed elements,
 *         it's size and  )
*************************************************************/
/**
typedef struct Buffer {
    char buffer[BUFFER_SIZE];
    int start;
    int size;
}  Buffer;
*/

static Buffer buffers[STANDARD_BUFFERS_AMOUNT];

static int invalid_index(int index) {
    return !(index >= 0 && index < 3 );
}


void set_up_buffers() {
    Buffer stdout = {{0}, 0, 0};
    Buffer stdin = {{0}, 0, 0};
    Buffer stderr = {{0}, 0, 0};

    buffers[STD_OUT] = stdout;
    buffers[STD_IN] = stdin;
    buffers[STD_ERR] = stderr;
}

void clear_buffers(int index) {
    if(!invalid_index(index)){
        Buffer indexed_buffer = buffers[index];
        indexed_buffer.start = 0;
        indexed_buffer.size = 0;

        for(int i=0; i<BUFFER_SIZE; i++) {
            indexed_buffer.buffer[i] = 0; 
        }

        buffers[index] = indexed_buffer;
    }
}

int write_char_in_buffer(int index, char c) {
    if(invalid_index(index))
        return 1;
    
    Buffer indexed_buffer = buffers[index];
    //Resets buffer position to the start of the array if it's full.
    if(indexed_buffer.size >= BUFFER_SIZE)
        indexed_buffer.start++;

    int offset = (indexed_buffer.start + indexed_buffer.size) % BUFFER_SIZE;
	indexed_buffer.buffer[offset] = c;

    if(indexed_buffer.size < BUFFER_SIZE)
        indexed_buffer.size++;
    
    buffers[index] = indexed_buffer;
    return 0;
}
int write_int_in_buffer(int index, uint64_t value,int base) {
	if(invalid_index(index))
		return 1;

	int remainder;
	char number[33];
	int i = 0;
	int digits = 0;
	do{
	    remainder = value % base;
		number[i++] = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}while (value /= base);

	for(i = digits - 1; i >= 0; i--)
		write_char_in_buffer(index,number[i]);
  return 0;
}

int write_string_in_buffer(int index, char * str) {
    if(invalid_index(index))
        return 1;

    while( str )
        write_char_in_buffer(index, str++);
    
    return 0;
}

char read_char_from_buffer(int index) {
    if(invalid_index(index) || buffers[index].size == 0)
        return 0;

    char char_to_return = buffers[index].buffer[buffers[index].start];

    //cleans read character and shifts start position.
    buffers[index].buffer[buffers[index].start++] = 0;
    //adjusts size;
    buffers[index].size--;

    if(buffers[index].start >= BUFFER_SIZE)
        buffers[index].start = 0;
    
    return char_to_return;
}

int read_string_from_buffer(int index, char *str, int size) {
    if(invalid_index(index))
        return 1;
    
    int i=0;
    char c;
    do {
        c = read_char_from_buffer(index);
        str[i++] = c;
    } while( c != 0 && i < size);

    return 0;
}


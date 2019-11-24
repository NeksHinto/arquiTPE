
#ifndef STANDARD_BUFFERS_H
#define STANDARD_BUFFERS_H
#include <stdint.h>

#define STD_IN 0
#define STD_OUT 1
#define STD_ERR 2
#define BUFFER_SIZE 1024
#define STANDARD_BUFFERS_AMOUNT 3

typedef struct Buffer {
    char buffer[BUFFER_SIZE];
    int start;
    int size;
} Buffer;

//Initializes stdin, stdout and stderr buffers;
void set_up_buffers();

//Index defines the buffer on which to perform the function.
void clear_buffers(int index);
int write_char_buffer(int index, char character);
int write_string_buffer(int index, char * str);
int write_int_buffer(int index, uint64_t value,int base);

//Reads a character and removes it from the buffer.
char read_char_buffer(int index);

//Loads size amount of chars on str from the buffer.
int read_string_buffer(int index, char * str,int size);

#endif

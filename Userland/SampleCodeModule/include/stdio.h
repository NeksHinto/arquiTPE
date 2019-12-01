#ifndef STDIO_H
#define STDIO_H

#define _stdin 0
#define _stdout 1
#define _stderr 2

void printMem(void *addr);
void printf(char* format, ...);
int scanf(char* format, ...);
void putchar(char c);
char getchar();
void write(char c, int dest);
char read(int dest);
char getchar_from_buffer(int buffer);

#endif

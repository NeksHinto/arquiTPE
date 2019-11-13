#ifndef STDLIB_H
#define STDLIB_H

// Compares two strings and returns 1 if they're equal.
int strcmp( char * s1,  char* s2);
//recieves an int and converts it to a char* using the given base.
char * itoa(int value,int base, char * buffer);
void reverse(char *s, int size);
int strlen(char* s);
int atoi(char* str);
int isdigit(char c);
#endif

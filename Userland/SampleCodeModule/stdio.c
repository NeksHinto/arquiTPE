#include <syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static void dumpMem(void *addr, int len);

void putchar(char c){
  _syscall(__write_char_buffer, 1, c);
}

char getchar(){
	return _syscall(__read_char_buffer, 0);
}

char getchar_from_buffer(int buffer) {
  if(buffer <1 || buffer > 2)
    return 0;
  return _syscall(__read_char_buffer, buffer);
}

char putint(uint64_t v, int base) {
  return _syscall(__write_int_buffer, 1, v, base);
}

void printf(char* format, ...){
  va_list arg;
  va_start(arg, format);
  int i;
  char* s;
  for(; *format != 0; format++){
    if(*format == '%'){
      format++;
      switch(*format){
          case 'c' :
              i = va_arg(arg, int);
              putchar(i);
              break;

          case 'd' :
              i = va_arg(arg, int);
              putint(i, 10);
              break;

          case 's':
              s = va_arg(arg, char*);
              while(*s){
                  putchar(*s);
                  s++;
              }
              break;

      }
    }
    else{
      putchar(*format);
    }
  }
}

int scanf(char* format, ...){
  va_list arg;
  va_start(arg, format);
  int i = 0;
  char c;
  int reading = 1;
  void * loadValue;
  int valuesLoaded = 0;
  int number = 0;

  while((c = getchar()) != '\n' && c != 0){
    if(!reading && c == format[0])
      reading = 1;
    if(reading){
      if(format[i] == '%'){
        loadValue = va_arg(arg,void *);
        switch(format[i+1]){
            case 'c' :
              *(char *)loadValue = c;
              break;
            case 'd' :
              do{
                number *= 10;
                number += (c - '0');
              }while((c = getchar()) >= '0' && c <= '9');

              *(int *)loadValue = number;
              number = 0;
              break;
            case 's':
              do{
                *(char *)loadValue = c;
                loadValue++;
              }while((c = getchar()) != ' ' && c != '\n' && c != 0);
              break;
        }
        valuesLoaded++;
      }
      else if(c != format[i]){
        reading = 0;
        continue;
      }
      i++;
    }
  }
  return valuesLoaded;
}

/** PRINT MEMORY */
void printMem(void *addr){
    dumpMem(addr, 32);
}

static void dumpMem(void *addr, int len){
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    printf ("Dumping %d bytes from %d:\n\n", len, addr);

    for (i = 0; i < len; i++) {
        if ((i % 16) == 0 && i != 0) {
            printf("  %s\n", buff);
        }
        printf(" %d", pc[i]);
        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) {
            buff[i % 16] = '.';
        } else {
            buff[i % 16] = pc[i];
        }
        buff[(i % 16) + 1] = '\0';
    }
    while ((i % 16) != 0) {
        printf("   ");
        i++;
    }
    printf("  %s\n", buff);
}
/*****************/

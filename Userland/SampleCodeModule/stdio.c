#include <syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void putchar(char c){
  _syscall(__write_char_in_buffer, 1, c);
}

char getchar(){
	return _syscall(__read_char_from_buffer, 0);
}

char getchar_from_buffer(int buffer) {
  if(buffer <1 || buffer > 2)
    return 0;
  return _syscall(__read_char_from_buffer, buffer);
}

char putint(uint64_t v, int base) {
  return _syscall(__write_int_in_buffer, 1, v, base);
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
              i = va_arg(arg,int);
              putchar(i);
              break;

            case 'd' :
              i = va_arg(arg,int);
              putint(i, 10);
             break;

            case 's':
              s = va_arg(arg,char*);
              while(*s){
                putchar(*s);
                s++;
              }
              break;
      }
    }else{
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

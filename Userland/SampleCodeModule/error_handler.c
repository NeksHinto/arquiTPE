#include <error_handler.h>
#include <syscall.h>
#include <stdarg.h>

void send_error(char * format, ...) {
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
              _syscall(__write_char_buffer, 2, i);
              break;

            case 'd' :
              i = va_arg(arg,int);
              _syscall(__write_int_buffer, 2, i, 10);
             break;

            case 's':
              s = va_arg(arg,char*);
              while(*s){
                _syscall(__write_char_buffer, 2, *s);
                s++;
              }
              break;
      }
    }else{
      _syscall(__write_char_buffer, 2, *format);
    }
  }
}
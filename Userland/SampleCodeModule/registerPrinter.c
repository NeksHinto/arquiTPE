//
// Created by ignacio on 2/12/19.
//
#include <stdio.h>
#include <time_module.h>


void write_registers(unsigned * stackPointer){
    char * registers[] = {"R15","R14","R13","R12","R11","R10","R9","R8","RSI","RDI","RBP","RDX","RCX","RBX","RAX"};
    int i;
    for(i = 0; i < 15; i++){
        printf("%s: %d\n", registers[i], *(stackPointer + i));
    }

}
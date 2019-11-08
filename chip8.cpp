#include "chip8.h"

#ifdef DEBUG
#include <stdio.h>
#endif

chip8::chip8() {
    // TODO
}

long chip8::getSize() {
    long size = SIZE;
    return size;
}

void chip8::load(char* buffer, long size) {
    for (int i = 0; i < size; i++) {
        mem[i+0x200] = (u8) buffer[i];
    }
}

void chip8::run() {
    while (1);
}
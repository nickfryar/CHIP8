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

bool chip8::running() {
    return running_;
}

void chip8::quit() {
    running_ = false;
}

void chip8::clearKeys() {
    for (int i = 0; i < 0x10; i++) {
        input[i] = 0;
    }
}

void chip8::setKey(u8 key) {
    input[key] = 1;
}

void chip8::cycle() {
    if (running_) {
        u16 opcode = mem[pc];

        switch (opcode & 0xf000) {
            case 0x0000: break;
            case 0x1000: break;
            case 0x2000: break;
            case 0x3000: break;
            case 0x4000: break;
            case 0x5000: break;
            case 0x6000: break;
            case 0x7000: break;
            case 0x8000: break;
            case 0x9000: break;
            case 0xa000: break;
            case 0xb000: break;
            case 0xc000: break;
            case 0xd000: break;
            case 0xe000: break;
            case 0xf000: break;
        }
    }
}

void chip8::op0NNN() {
    
}

void chip8::op00E0() {
    // CLear the screen
}

void chip8::op00EE() {
    sp--;
    pc = stack[sp];
    pc += 2;
}

void chip8::op1NNN(u16 opcode) {
    pc = NNN;
}

void chip8::op2NNN(u16 opcode) {
    stack[sp] = pc;
    sp++;
    pc = NNN;
}

void chip8::op3XNN(u16 opcode) {
    if (VX == NN) {
        pc += 4;
    }
    else {
        pc += 2;
    }
}

void chip8::op4XNN(u16 opcode) {
    if (VX != NN) {
        pc += 4;
    }
    else {
        pc += 2;
    }
}

void chip8::op5XY0(u16 opcode) {
    if (VX == VY) {
        pc += 4;
    }
    else {
        pc += 2;
    }
}

void chip8::op6XNN(u16 opcode) {
    VX = NN;
    pc += 2;
}

void chip8::op7XNN(u16 opcode) {
    VX += NN;
    pc += 2;
}

void chip8::op8XY0(u16 opcode) {
    VX = VY;
    pc += 2;
}

void chip8::op8XY1(u16 opcode) {
    VX |= VY;
    pc += 2;
}

void chip8::op8XY2(u16 opcode) {
    VX &= VY;
    pc += 2;
}

void chip8::op8XY3(u16 opcode) {
    VX ^= VY;
    pc += 2;
}

void chip8::op8XY4(u16 opcode) {
    VX += VY;
    if (VY > VX) {
        VF = 1;
    }
    else {
        VF = 0;
    }
    pc += 2;
}

void chip8::op8XY5(u16 opcode) {
    if (VY > VX) {
        VF = 1;
    }
    else {
        VF = 0;
    }
    VX -= VY;
    pc += 2;
}

void chip8::op8XY6(u16 opcode) {
    VF = VX & 0x1;
    VX >>= 1;
    pc += 2;
}

void chip8::op8XY7(u16 opcode) {
    if (VX > VY) {
        VF = 0;
    }
    else {
        VF = 1;
    }
    VX = VY - VX;
    pc += 2;
}

void chip8::op8XYE(u16 opcode) {
    VF = VX >> 7;
    VX <<= 1;
    pc += 2;
}

void chip8::op9XY0(u16 opcode) {
    if (VX != VY) {
        pc += 4;
    }
    else {
        pc += 2;
    }
}

void chip8::opANNN(u16 opcode) {
    i = NNN;
    pc += 2;
}

void chip8::opBNNN(u16 opcode) {
    pc = NNN + V0;
}

void chip8::opCXNN(u16 opcode) {
    VX = (rand() % (0xff + 1)) & NN;
    pc += 2;
}

void chip8::opDXYN(u16 opcode) {
    // TODO: draw a sprite
}

void chip8::opEX9E(u16 opcode) {
    if (input[VX]) {
        pc += 4;
    }
    else {
        pc += 2;
    }
}

void chip8::opEXA1(u16 opcode) {
    if (!input[VX]) {
        pc += 4;
    }
    else {
        pc += 2;
    }
}

void chip8::opFX07(u16 opcode) {
    VX = delay_timer;
}

void chip8::opFX0A(u16 opcode) {
    for (int i = 0xf; i >= 0; i--) {
        if (input[i]) {
            VX = input[i];
            pc += 2;
            return;
        }
    }
}

void chip8::opFX15(u16 opcode) {
    delay_timer = VX;
    pc += 2;
}

void chip8::opFX18(u16 opcode) {
    sound_timer = VX;
    pc += 2;
}

void chip8::opFX1E(u16 opcode) {
    i += VX;
    if (i > 0xfff) {
        VF = 1;
    }
    else {
        VF = 0;
    }
    pc += 2;
}

void chip8::opFX29(u16 opcode) {
    // set i to location of character in VX
    pc += 2;
}

void chip8::opFX33(u16 opcode) {
    mem[i] = VX / 100;
    mem[i+1] = (VX / 10) % 10;
    mem[i+2] = VX % 10;
    pc += 2;
}

void chip8::opFX55(u16 opcode) {
    for (int x = 0; x <= VX; x++) {
        mem[i] = v[x];
        i++;
    }
    pc += 2;
}
void chip8::opFX65(u16 opcode) {
    for (int x = 0; x <= VX; x++) {
        v[x] = mem[i];
        i++;
    }
    pc += 2;
}
#ifndef CHIP8_H
#define CHIP8_H

#include <inttypes.h>

#define u8 uint8_t
#define u16 uint16_t

class chip8 {
private:
    // Registers
    u16 pc;
    u16 i;
    u16 sp;
    u8 v[0xf];
    u8 delay_timer;
    u8 sound_timer;

    // Memory
    u8 mem[0x1000];
    u8 stack[0x30];

    // Input + Graphics
    u8 input[0x10];
    u8 graphics[0x30 * 0x20];

    // Opcodes
    void op0NNN();
    void op00E0();
    void op00EE();
    void op1NNN();
    void op2NNN();
    void op3XNN();
    void op4XNN();
    void op5XY0();
    void op6XNN();
    void op7XNN();
    void op8XY0();
    void op8XY1();
    void op8XY2();
    void op8XY3();
    void op8XY4();
    void op8XY5();
    void op8XY6();
    void op8XY7();
    void op8XYE();
    void op9XY0();
    void opANNN();
    void opBNNN();
    void opCXNN();
    void opDXYN();
    void opEX9E();
    void opEXA1();
    void opFX07();
    void opFX0A();
    void opFX15();
    void opFX18();
    void opFX1E();
    void opFX29();
    void opFX33();
    void opFX55();
    void opFX65();

public:
    chip8();
    void run();
};

#endif /* CHIP8_H */
#ifndef CHIP8_H
#define CHIP8_H

#include <cinttypes>
#include <random>
#include <ctime>

#define u8 uint8_t
#define u16 uint16_t

#define SIZE    0x1000

#define NNN     (opcode & 0x0fff)
#define NN      (opcode & 0x00ff)
#define VX      v[(opcode & 0x0f00) >> 8]
#define VY      v[(opcode & 0x00f0) >> 4]
#define VF      v[0xf]
#define V0      v[0]

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
    u8 mem[SIZE];
    u8 stack[0x30];

    // Input + Graphics
    u8 input[0x10];
    u8 graphics[0x30 * 0x20];

    bool running_;

    // Opcodes
    void op0NNN();
    void op00E0();
    void op00EE();
    void op1NNN(u16);
    void op2NNN(u16);
    void op3XNN(u16);
    void op4XNN(u16);
    void op5XY0(u16);
    void op6XNN(u16);
    void op7XNN(u16);
    void op8XY0(u16);
    void op8XY1(u16);
    void op8XY2(u16);
    void op8XY3(u16);
    void op8XY4(u16);
    void op8XY5(u16);
    void op8XY6(u16);
    void op8XY7(u16);
    void op8XYE(u16);
    void op9XY0(u16);
    void opANNN(u16);
    void opBNNN(u16);
    void opCXNN(u16);
    void opDXYN(u16);
    void opEX9E(u16);
    void opEXA1(u16);
    void opFX07(u16);
    void opFX0A(u16);
    void opFX15(u16);
    void opFX18(u16);
    void opFX1E(u16);
    void opFX29(u16);
    void opFX33(u16);
    void opFX55(u16);
    void opFX65(u16);

public:
    chip8();
    long getSize();
    void load(char*, long);
    bool running();
    void quit();
    void clearKeys();
    void setKey(u8);
    void cycle();
};

#endif /* CHIP8_H */
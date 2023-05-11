#include "chip8.h"
#include <cstdio>

// грубо говоря данный массив хранит в себе изображение цифр, 
// если их все выставить в ряд и поставить вместо 1 звездочки
unsigned char chip8_fontset[80] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


void Chip8::initialize() 
{
    // Initialize registers and memory once
    pc = RAM_BEGIN; // the begining of RAM (program in memory)
    opcode = 0;
    I = 0;
    sp = 0x0;

    // Clear display	
    for (int i = 0; i < DISPLAY_HEIGHT * DISPLAY_WIDTH; i++) 
        gfx[i] = 0x0;

    // Clear stack
    for (int i = 0; i < STACK_SIZE; i++) 
        stack[i] = 0x0;

    // Clear registers V0-VF
    for (int i = 0; i < REGISTERS_NUM; i++) 
        V[i] = 0x0;

    // Clear memory	
    for (int i = 0; i < MEM_SIZE; i++) 
        memory[i] = 0x0;

    // Load fontset
    for (int i = CHIPSET_FONTS_BUILTIN_BEGIN; i < CHIPSET_FONTS_BUILTIN_END; i++)
        memory[i] = chip8_fontset[i - CHIPSET_FONTS_BUILTIN_BEGIN];
}

void Chip8::loadGame(Programm p) 
{
    for (int i = 0; i < PROGRAMM_SIZE; i++)
        memory[i + RAM_BEGIN] = p.buffer[i];
}

bool Chip8::emulateCycle()
{
    // Fetch Opcode (вычислили код операции из памяти)
    opcode = (memory[pc] << 8) | memory[pc + 1];
    //printf("0x%x\n", opcode);

    // Decode Opcode
    // Execute Opcode
    decode_and_execute();

    // Update timers
    if (delay_timer > 0)
        delay_timer--;

    if (sound_timer > 0)
    {
        if (sound_timer == 1)
            std::cout << "BEEP!\n"; 
    }
    return ((unsigned int) pc < MEM_SIZE);

    
}

void Chip8::setKeys() {
    char v;
    std::cin >> v;
}
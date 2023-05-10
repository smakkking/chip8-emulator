#include "chip8.h"

void Chip8::initialize() 
{
    // Initialize registers and memory once
    pc = 0x200; // the begining of RAM (program in memory)
    opcode = 0;
    I = 0;
    sp = 0x0;

    // Clear display	
    for (int i = 0; i < DISPLAY_SIZE; i++) 
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

void Chip8::emulateCycle()
{
    // Fetch Opcode (вычислили код операции из памяти)
    opcode = (memory[pc] << 8) | memory[pc + 1];

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

    
}
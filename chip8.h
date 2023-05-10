#ifndef HEADER_1
#define HEADER_1

#include <string>
#include <iostream>

const unsigned int MEM_SIZE = 4096;
const unsigned int CHIPSET_FONTS_BUILTIN_BEGIN = 0x050;
const unsigned int CHIPSET_FONTS_BUILTIN_END = 0x0A0;
const unsigned int RAM_BEGIN = 0x200;

const unsigned int PROGRAMM_SIZE = 1024;

const unsigned int REGISTERS_NUM = 16;
const unsigned int DISPLAY_SIZE = 64 * 32;

const unsigned int STACK_SIZE = 16;
const unsigned int KEYS_SIZE = 16;

class Programm
{
    unsigned char buffer[PROGRAMM_SIZE];
    std::string name;
    friend class Chip8;
public:
    Programm(std::string n) 
    {
        name = n;
        for (int i = 0; i < PROGRAMM_SIZE; i++)
            buffer[i] = 0;
    }
};


class Chip8 
{
    unsigned short opcode; // takes operation codes

    unsigned char memory[MEM_SIZE]; // takes machine memory

    unsigned char V[REGISTERS_NUM]; // takes cpu registers

    unsigned short I; // index register, 
    unsigned short pc; // eip IA-32 analog 

    // memory map
    // 0x000-0x1FF - chip8 interpreter
    // 0x050-0x0A0 built-in 4x5 pixel font set (0-F digits) for output
    // 0x200-0xFFF - RAM
    // программа в памяти - это просто набор 2-байтных инструкций, идущих друг за другом

    unsigned char gfx[DISPLAY_SIZE]; // graphics
    unsigned char delay_timer; // interrupt analog
    unsigned char sound_timer; 

    unsigned short stack[STACK_SIZE]; // stack for functions
    unsigned short sp;

    unsigned char key[KEYS_SIZE];
    
public:
    bool drawFlag;

    void initialize(); // beginning init of cpu
    void loadGame(Programm p); // load game to the RAM
    void emulateCycle(); // model cycle of cpu
    void setKeys(); // user input
    void decode_and_execute();
};

#endif


#include "chip8.h"
#include <random>

void Chip8::decode_and_execute() 
{
    // decoding first letter of command
    switch (opcode & 0xF000) 
    {
        case 0x0000:
            switch(opcode & 0x000F)
            {

                case 0x0000:
                    // 0x00E0: Clears the screen
                break;

                case 0x000E:
                    // 0x00EE: Returns from subroutine
                    if (sp > 0)
                        pc = stack[--sp];
                    else
                        std::cout << "error: no subroutines!\n";
                break;
            }
        break;

        case 0x1000:
            /// 1NNN: goto NNN;
            pc = opcode & 0x0FFF;
        break;

        case 0x2000:
            //  0x2NNN - calls a subroutine at NNN
            stack[sp++] = pc;
            pc = opcode & 0x0FFF;
        break;

        case 0x3000:
            // 3XNN: if (Vx == NN) skip next comamnd
            if (V[(opcode & 0x0F00) >> 8] == opcode & 0x00FF)
                pc += 4;
            else
                pc += 2;
        break;

        case 0x4000:
            // 4XNN: if (Vx != NN) skip next comamnd
            if (V[(opcode & 0x0F00) >> 8] != opcode & 0x00FF)
                pc += 4;
            else
                pc += 2;
        break;

        case 0x5000:
            // 5XY0: if (Vx == Vy) skip next command
            if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
                pc += 4;
            else
                pc += 2;
        break;

        case 0x6000:
            // 6XNN: Vx = NN
            V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
            pc += 2;
        break;

        case 0x7000:
            // 7XNN: Vx == NN and CF is const
            V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
            pc += 2;
        break;

        case 0x8000:
            // 8XYN - математические операции
            unsigned char X = (opcode & 0x0F00) >> 8,
                        Y = (opcode & 0x00F0) >> 4;
            switch (opcode & 0x000F)
            {
                case 0x0000:
                    V[X] = V[Y];
                break;

                case 0x0001:
                    V[X] |= V[Y];
                break;

                case 0x0002:
                    V[X] &= V[Y];
                break;

                case 0x0003:
                    V[X] ^= V[Y];
                break;

                case 0x0004:
                    // важно отследить переполнение и поместить его в CF    
                    V[0XF] = V[X] > 255 - V[Y] ? 1 : 0;
                    V[X] += V[Y];
                break;

                case 0x0005:
                    V[0XF] = V[X] > V[Y] ? 1 : 0;
                    V[X] -= V[Y];
                break;

                case 0x0006:
                    V[0XF] = V[X] & 0b00000001;
                    V[X] >>= 1;
                break;

                case 0x0007:
                    V[0XF] = V[Y] > V[X] ? 1 : 0;
                    V[X] = V[Y] - V[X];
                break;

                case 0x000E:
                    V[0XF] = (V[X] & 0b10000000) >> 7;
                    V[X] <<= 1;
                break;
            }
            pc += 2;
                 
        break;

        case 0xA000:
            // ANNN: Sets I to the address NNN
            I = opcode & 0x0FFF;
            pc += 2;
        break;

        case 0xB000:
            // BNNN: Jumps to the address NNN plus V0. 
            pc = V[0] + opcode & 0x0FFF;
        break;

        case 0xC000:
            // CXNN: VX = rand() & NN
            unsigned char X = (opcode & 0x0F00) >> 8;
            V[X] = (rand() % 256) & (opcode & 0x00FF);
            pc += 2;
        break;

        case 0xF000:
            unsigned char X = (opcode & 0x0F00) >> 8;
            switch (opcode & 0x00FF) 
            {
                case 0x0033:
                    memory[I] = V[X] / 100;
                    memory[I + 1] = (V[X] / 10) % 10;
                    memory[I + 2] = V[X] % 10;
                    pc += 2;
                break;
            }
        break;


        default:
            std::cout << "unknown operation! " << opcode << std::endl;
    }
}
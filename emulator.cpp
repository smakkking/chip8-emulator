#include "chip8.h"
#include <GL/glut.h>

void draw_graphics(Chip8 *chip)
{
    for (int i = 0; i < DISPLAY_HEIGHT; i++)
    {
        for (int j = 0; j < DISPLAY_WIDTH; j++)
            if (chip->gfx[i * DISPLAY_WIDTH + j])
                std::cout << "*";
            else
                std::cout << " ";
        std::cout << std::endl;
    }
    chip->drawFlag = false;
}



int main(int argc, char **argv) 
{
    Chip8 *myChip = new Chip8;
    // we need to know how to start init glut
    // setupGraphics();
    // setupInput();

    unsigned char buff[PROGRAMM_SIZE] = {
        0x60, 0x00,
        0xF0, 0x29,
        0xD0, 0x05,
        0x00, 0xE0,

        0x60, 0x01,
        0xF0, 0x29,
        0xD0, 0x05,
        0x00, 0xE0,

        0x60, 0x02,
        0xF0, 0x29,
        0xD0, 0x05,
        0x00, 0xE0,

    };

    myChip->initialize();
    myChip->loadGame(Programm("packman", buff));

    for (;myChip->emulateCycle();) 
    { 
        if (myChip->drawFlag) {
            
            // there we draw the screen if it needed
            draw_graphics(myChip);
        }

        //myChip->setKeys(); // user input
    }

    delete myChip;
    return 0;
}


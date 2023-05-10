#include "chip8.h"
#include <GL/glut.h>

Chip8 myChip;

int main(int argc, char **argv) 
{
    // we need to know how to start init glut
    // setupGraphics();
    // setupInput();

    myChip.initialize();
    myChip.loadGame(Programm("packman"));

    for (;;) 
    {
        myChip.emulateCycle();
        if (myChip.drawFlag) {
            // there we draw the screen if it needed
            // drawGraphics()
        }

        myChip.setKeys(); // user input
    }
}
#ifndef _MENU_H_
#define _MENU_H_

#include "draw.h"
#include "file.h"

//random world generator... To improve
void initWorld(uint8_t *world);

//Main menu... What else to say ?
//buffer is a screen buffer
//exit is a boolean : if set to 1, exit without launching the game
//world is the cube world
//playerPos is player's coordinates, angle X and Z are camera rotation
//savePath is the path of the save file
void mainMenu(void *buffer,char *exit,uint8_t *world,pos *playerPos,float *angleX,float *angleZ,char *savePath);

//The "New world" action of the main menu
//menu is a boolean : if set to 0, launch the game
//world is the cube world
//playerPos is player's coordinates, angle X and Z are camera rotation
void menuNewWorld(char *menu,uint8_t *world,pos *playerPos,float *angleX,float *angleZ);

//The "Load world" action of the main menu
//buffer is a screen buffer
//menu is a boolean : if set to 0, launch the game
//world is the cube world
//playerPos is player's coordinates, angle X and Z are camera rotation
//savePath is the path of the save file
int menuLoadWorld(void *buffer,char *menu,uint8_t *world,pos *playerPos,float *angleX,float *angleZ,char *savePath);

#endif

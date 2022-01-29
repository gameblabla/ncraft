#ifndef _DRAW_H_
#define _DRAW_H_

#include "buffer.h"
#include "3D.h"

#define CHAR_HEIGHT 12
#define CHAR_WIDTH 8

//draw a little cursor in the middle of the screen
void drawCursor(void *buffer);

//draw a triangle in the top right corner of the screen showing the selected type of cube
void drawCubeIndicator(void *buffer,int color);

//Clipped triangle filling
void drawTriangle(void *buffer,int color,int x1,int y1,int x2,int y2,int x3,int y3);

//Test if a cube is on the screen. (used by drawCube)
int isCubeOnScreen(int *pos);

//A simple progress bar
void drawProgressBar(void *buffer,int percent);

//Draws a character on the buffer (only used by drawString)
void drawChar(void *buffer,uint8_t character,int color,int x,int y);

//Draws a string on the buffer
void drawString(void *buffer,char *str,int color,int x,int y);
void drawStringCenter(void *buffer,char *str,int color,int y);

//Cube drawing
//vertices should be a table of size 3*8    {x1,y1,z1, x2,y2,z2,...}
//pos should be a table of size 2*8    {x1,y1, x2,y2,...}
//faces should be a table of size 4*6    {v1,v2,v3,v4, v1,v2,v5,v6,...}
//colors should be a table of size 1*6    {c1, c2, c3,...}
void drawCube(void *buffer,float *vertices,int *pos,int *faces,int *colors);

#endif

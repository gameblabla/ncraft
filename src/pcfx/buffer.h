#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "utils.h"

//display a buffer on the screen
void bufDisplay(void *buffer);
//Fill a buffer with a color
void bufClear(void *buffer);
//(non-clipped) Set a pixel
void bufSetPixel(void *buffer,unsigned int x, unsigned int y,int color);
//(clipped) Set a pixel
void securedBufSetPixel(void *buffer,unsigned int x, unsigned int y,int color);
//Clipped horizontal line
void bufHorizLine(void *buffer,int x,int y,int x2, int color);


#endif


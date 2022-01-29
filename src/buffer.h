#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "utils.h"

#define SCREEN_BASE_ADDRESS sdl_screen->pixels
#ifdef _16BPP
#define SCREEN_BYTES_SIZE (320*240)*2
#else
#define SCREEN_BYTES_SIZE (320*240)
#endif

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


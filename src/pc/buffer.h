#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "utils.h"

#define SCREEN_BASE_ADDRESS sdl_screen->pixels
#ifdef _16BPP
#define SCREEN_BYTES_SIZE (SCREEN_GAME_WIDTH*SCREEN_GAME_HEIGHT)*2
#else
#define SCREEN_BYTES_SIZE (SCREEN_GAME_WIDTH*SCREEN_GAME_HEIGHT)
#endif

//display a buffer on the screen
void bufDisplay(void *buffer);
#define bufClear(a) memset(a,0xFF,SCREEN_BYTES_SIZE);
//(non-clipped) Set a pixel
#ifdef _16BPP
#define bufSetPixel(buffer,x,y,color) *((uint16_t*)buffer + x + y * SCREEN_GAME_WIDTH) = color;
#else
#define bufSetPixel(buffer,x,y,color) *((uint8_t*)buffer + x + y * SCREEN_GAME_WIDTH) = color;
#endif
//(clipped) Set a pixel
void securedBufSetPixel(void *buffer,unsigned int x, unsigned int y,int color);
//Clipped horizontal line
void bufHorizLine(void *buffer,int x,int y,int x2, int color);


#endif


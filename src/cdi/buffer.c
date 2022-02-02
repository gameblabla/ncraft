#include "buffer.h"
#include "graphics.h"
#include "input.h"
#include "video.h"


void Init_display()
{
	initVideo();
	initGraphics();
	initInput();
	
	while(1)
	{
		swapImageBuffer();
	}
}

void bufDisplay(void *buffer)
{
	int i;
	((void)buffer);
	
	swapImageBuffer();
}

void securedBufSetPixel(void *buffer,unsigned int x, unsigned int y,int color)
{
	//if (x<SCREEN_GAME_WIDTH && y<SCREEN_GAME_HEIGHT)
	{
		bufSetPixel(buffer,x,y,color);
	}
}

void bufHorizLine(void *buffer,int x,int y,int x2, int color)
{
	int i;
	if (x>x2)
	{
		invertVars(&x,&x2);
	}
	if(x2>=0 && x<SCREEN_GAME_WIDTH && y>=0 && y<SCREEN_GAME_HEIGHT)
	{
		if(x<0)
		  x=0;
		if(x2>SCREEN_GAME_WIDTH-1)
		  x2=SCREEN_GAME_WIDTH-1;
		for(i=x;i<=x2;i++)
		{
			bufSetPixel(buffer,i,y,color);
		}
	}
}


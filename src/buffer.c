#include "buffer.h"

int has_colors = 1;
SDL_Surface* sdl_screen;
Uint32 start;

#define FPS_VIDEO 60
const float real_FPS = 1000/FPS_VIDEO;

void Init_display()
{
	SDL_Init( SDL_INIT_VIDEO );
	SDL_ShowCursor(0);
	sdl_screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
	has_colors = 1;
	start = SDL_GetTicks();
}

void bufDisplay(void *buffer)
{
	Uint8 *keystate = SDL_GetKeyState(NULL);
	SDL_Event event;
	
	if (keystate[SDLK_ESCAPE]) return 0;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				printf("Exit\n");
				exit(0);
				break;
			}
		}
	}
	memcpy(SCREEN_BASE_ADDRESS,buffer,SCREEN_BYTES_SIZE);
	SDL_Flip(sdl_screen);
	if(real_FPS > SDL_GetTicks()-start) SDL_Delay(real_FPS-(SDL_GetTicks()-start));
	start = SDL_GetTicks();
}

void bufClear(void *buffer)
{
    memset(buffer,0xFF,SCREEN_BYTES_SIZE);
}

void bufSetPixel(void *buffer,unsigned int x, unsigned int y,int color)
{
    *((unsigned short*)buffer + x + y * 320) = color;
}

void securedBufSetPixel(void *buffer,unsigned int x, unsigned int y,int color)
{
  if(x<320 && y<240)
  {
    bufSetPixel(buffer,x,y,color);
  }
}

void bufHorizLine(void *buffer,int x,int y,int x2, int color)
{
	int width=0,i=0;
	if(x>x2)
		invertVars(&x,&x2);
	if(x2>=0 && x<320 && y>=0 && y<240)
	{
		if(x<0)
		  x=0;
		if(x2>319)
		  x2=319;
		for(i=x;i<=x2;i++)
		{
		*(volatile unsigned short*)(buffer+i*2+y*640)=color;
		}
	}
}


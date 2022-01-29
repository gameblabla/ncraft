#include "buffer.h"

SDL_Surface* sdl_screen;
Uint32 start;

#define FPS_VIDEO 60
const float real_FPS = 1000/FPS_VIDEO;

void Init_display()
{
	SDL_Init( SDL_INIT_VIDEO );
	SDL_ShowCursor(0);
	#ifdef _16BPP
	sdl_screen = SDL_SetVideoMode(SCREEN_GAME_WIDTH, SCREEN_GAME_HEIGHT, 16, SDL_SWSURFACE);
	#else
	sdl_screen = SDL_SetVideoMode(SCREEN_GAME_WIDTH, SCREEN_GAME_HEIGHT, 8, SDL_SWSURFACE);
	#endif
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
	#ifdef _16BPP
		*((unsigned short*)buffer + x + y * SCREEN_GAME_WIDTH) = color;
	#else
		*((unsigned char*)buffer + x + y * SCREEN_GAME_WIDTH) = color;
	#endif
}

void securedBufSetPixel(void *buffer,unsigned int x, unsigned int y,int color)
{
	if (x<SCREEN_GAME_WIDTH && y<SCREEN_GAME_HEIGHT)
	{
		bufSetPixel(buffer,x,y,color);
	}
}

void bufHorizLine(void *buffer,int x,int y,int x2, int color)
{
	int width=0,i=0;
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
			#ifdef _16BPP
				*(volatile unsigned char*)(buffer+(i*2)+y*(SCREEN_GAME_WIDTH*2))=color;
			#else
				*(volatile unsigned char*)(buffer+i+y*SCREEN_GAME_WIDTH)=color;
			#endif
		}
	}
}


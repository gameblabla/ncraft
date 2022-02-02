#include <stdint.h>


int isKeyPressed(int key)
{
	//if(paddata & (1 << key)) return 1;
	return 0;
}

int any_key_pressed(int key)
{
	((void)key);
	/*Uint8 *keystate = SDL_GetKeyState(NULL);
	if (keystate[key]) return 1;*/
	return 0;
}

void idle()
{
}

int wait_key_pressed()
{
	/*SDL_Event event;
	Uint8 *keystate;
	for(;;)
	{
		keystate = SDL_GetKeyState(NULL);
		if (keystate[key]) return 1;
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
	}*/
	return 0;
}

void show_msgbox(char* arr1, char* arr2)
{
	((void)arr1);
	((void)arr2);
}

void sleep_game(int sleep)
{
	((void)sleep);
}

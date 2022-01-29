#include <SDL/SDL.h>

int isKeyPressed(int key)
{
	Uint8 *keystate = SDL_GetKeyState(NULL);
	if (keystate[key]) return 1;
	return 0;
}

int any_key_pressed(int key)
{
	Uint8 *keystate = SDL_GetKeyState(NULL);
	if (keystate[key]) return 1;
	return 0;
}

void idle()
{
}

int wait_key_pressed(int key)
{
	SDL_Event event;
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
	}
}

void show_msgbox(char* arr1, char* arr2)
{
	
}

void sleep_game(int sleep)
{
}

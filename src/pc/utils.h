#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <stdint.h>
#include <SDL/SDL.h>

extern SDL_Surface* sdl_screen;
extern int isKeyPressed(int key);
extern void show_msgbox(char* arr1, char* arr2);

#define SCREEN_GAME_WIDTH 320
#define SCREEN_GAME_HEIGHT 240

#define SCREEN_BASE_ADDRESS sdl_screen->pixels
#ifdef _16BPP
#define SCREEN_BYTES_SIZE (SCREEN_GAME_WIDTH*SCREEN_GAME_HEIGHT)*2
#else
#define SCREEN_BYTES_SIZE (SCREEN_GAME_WIDTH*SCREEN_GAME_HEIGHT)
#endif

#define KEY_NSPIRE_ESC SDLK_ESCAPE
#define KEY_NSPIRE_UP SDLK_UP
#define KEY_NSPIRE_LEFT SDLK_LEFT
#define KEY_NSPIRE_RIGHT SDLK_RIGHT
#define KEY_NSPIRE_DOWN SDLK_DOWN
#define KEY_NSPIRE_TAB SDLK_LALT
#define KEY_NSPIRE_CTRL SDLK_LCTRL
#define KEY_NSPIRE_F 7
#define KEY_NSPIRE_8 8
#define KEY_NSPIRE_2 9
#define KEY_NSPIRE_5 10 
#define KEY_NSPIRE_6 11
#define KEY_NSPIRE_4 12
#define KEY_NSPIRE_PLUS 13
#define KEY_NSPIRE_MINUS 14
#define KEY_NSPIRE_ENTER SDLK_RETURN

#define CUBE_WORLD_X 101
#define CUBE_WORLD_Y 101
#define CUBE_WORLD_Z 40

#define CUBE_CHUNK_X 24
#define CUBE_CHUNK_Y 24
#define CUBE_CHUNK_Z 24

typedef struct
{
	float x,y,z;
}pos;


//invert two vars
void invertVars(int *v1,int *v2);
void invertTableElems(int *table,int e1,int e2);
void invertTablefloats(float *table,int e1,int e2);

//trigonometry utils
float cos(float angle);
float sin(float angle);
float angleCorrect(float angle);

//math utils
float floor(float n);
float sign(float n);
int random_game(int min, int max);
void startrandom_game();
int ceiling(int n,int max);

#endif

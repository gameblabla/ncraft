#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
extern int isKeyPressed(int key);
extern void show_msgbox(char* arr1, char* arr2);
extern void sleep_game(int sleep);
extern int wait_key_pressed();

#define SCREEN_GAME_WIDTH 256
#define SCREEN_GAME_HEIGHT 256

#ifdef _16BPP
#define SCREEN_BYTES_SIZE (SCREEN_GAME_WIDTH*SCREEN_GAME_HEIGHT)*2
extern unsigned short framebuffer[(SCREEN_GAME_WIDTH*SCREEN_GAME_HEIGHT)];
#else
#define SCREEN_BYTES_SIZE (SCREEN_GAME_WIDTH*SCREEN_GAME_HEIGHT)
extern unsigned char framebuffer[(SCREEN_GAME_WIDTH*SCREEN_GAME_HEIGHT)];
#endif

#define SCREEN_BASE_ADDRESS framebuffer

#define KEY_NSPIRE_ESC 6
#define KEY_NSPIRE_UP 8
#define KEY_NSPIRE_LEFT 11
#define KEY_NSPIRE_RIGHT 9
#define KEY_NSPIRE_DOWN 10
#define KEY_NSPIRE_TAB 1
#define KEY_NSPIRE_CTRL 0
#define KEY_NSPIRE_F 12
#define KEY_NSPIRE_8 2
#define KEY_NSPIRE_2 3
#define KEY_NSPIRE_5 4 
#define KEY_NSPIRE_6 5
#define KEY_NSPIRE_4 12
#define KEY_NSPIRE_PLUS 12
#define KEY_NSPIRE_MINUS 12
#define KEY_NSPIRE_ENTER 7

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
float cos_game(float angle);
float sin_game(float angle);
float angleCorrect(float angle);

//math utils
float floor_game(float n);
float sign(float n);
int random_game(int min, int max);
void startrandom_game();
int ceiling(int n,int max);

#endif

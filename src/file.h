#ifndef _FILE_H_
#define _FILE_H_

#include "cubeList.h"
#include "draw.h"

//Returns the first integer in a string
//int scanInt(char *str);

//Puts one line of the file in text
//void* readLine(FILE *filein, char *text);

//File browser (for another release ?)
//void listFiles(char **files,int *nbFiles);

//Load the world from the save file
char loadWorld(void *buffer,char *name,uint8_t *world,pos *playerPos,float *angleX,float *angleZ);

//Save the world in the save file
void saveWorld(void *buffer,char *name,uint8_t *world,pos playerPos,float angleX,float angleZ);

#endif

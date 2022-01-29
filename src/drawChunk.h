#ifndef _DRAW_CHUNK_H_
#define _DRAW_CHUNK_H_

#include "3D.h"
#include "draw.h"
#include "cubeList.h"


//HEAP SORT UTIL -- CALLED BY sortCubePos()
//this function is a modified version of wikipedia's heap sort
//thanks wikipedia :)
void heap(float *dist,int *index,int i,int n);

//SORT ALL THE CUBES WHICH WILL BE DISPLAYED
//cubePos is an array which contains the coordinates of the center of each cube
//cubeList is the array which contains the color of each cube
//size is the number of cubes
void sortCubePos(float *cubePos,uint8_t *cubeList,int size);
void sortChunkIndexes(float *dist,int *indexes,int size);

//RETURN 0 IF A CUBE ISNT VISIBLE
//chunk/world is a "cubemap" array
//CubeX, CubeY and CubeZ are the coordinates of the cube in the chunk
//index is the index of the cube in the chunk
//playerPos is the player's coordinates
int isCubeVisibleInChunk(uint8_t *chunk,int cubeX,int cubeY,int cubeZ,int index);
//Note that these two functions are slightly different. I didn't merge them for speed issues.
int isCubeVisibleInWorld(uint8_t *world,int cubeX,int cubeY,int cubeZ,int index,pos playerPos);

//COMPUTE CUBES POS AND CUBES WHICH WILL BE DISPLAYED
//chunk is a "cubemap" array
//cubePos is the array where the pos of each cube will be stored
//cubeList is the array where the color of each cube will be stored
//size is the place where the number of displayed cubes will be stored
//x and z rotation is the camera
//playerPos is the player's coordinates
void computeCubeWorldChunk(uint8_t *chunk,float *cubePos,uint8_t *cubeList,int *size,float xRotation,float zRotation,pos playerPos);

//RENDER THE FULL WORLD CHUNK PER CHUNK
//world is a "cubemap" array
//cubePos is the array where the pos of each cube will be stored
//cubeList is the array where the color of each cube will be stored
//size is the place where the number of displayed cubes will be stored
//x and z rotation is the camera
//playerPos is the player's coordinates
void renderFullWorld(void *buffer,uint8_t *world,float *cubePos,uint8_t *cubeList,float xRotation,float zRotation,pos playerPos);

//DRAW COMPUTED CUBES
//cubePos is an array which contains coordinates of the center of all the cubes {x1,y1,z1, x2,y2,z2,...}
//cubeList is an array which contains the color of each cube
//size is the number of cubes
//x and z rotation is the camera
void drawCubeList(void *buffer,float *cubePos,uint8_t *cubeList,int size,float xRotation,float zRotation);

#endif

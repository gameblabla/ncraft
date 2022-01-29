#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include "buffer.h"
#include "draw.h"
#include "3D.h"
#include "drawChunk.h"

//GET A CUBE INDEX DEFINED BY ITS POS
//x,y,z are coordinates
//warning ! the coordinates are in the chunk, NOT in the world. So 0,0,0 is player's feet pos.
//basically, 0,0,0 is the cube where the player stands on.
int getCubeIndex(float x,float y,float z);

//GET A CUBE DEFINED BY ITS POS
//Basically a shortcut for cubeChunk[getCubeIndex(x,y,z)]
//cubeChunk is the displayed chunk
//x,y,z are coordinates
int getCube(uint8_t *cubeChunk,float x,float y,float z);

//GET THE CUBE POINTED BY THE CAMERA
//chunk is the displayed chunk
//angleX and angleZ are camera rotation
//playerPos is the player's coordinates
//lastCube will be set to the index of last cube hit by the ray, if not NULL
int rayCast(uint8_t *chunk,float angleX,float angleZ,pos playerPos,int *lastCube);

//REMOVE THE BLOCK POINTED BY THE PLAYER
//And put it in the inventory
//chunk is the displayed chunk
//world is the whole world
//angleX and angleZ are camera rotation
//playerPos is the player's coordinates
void removeBlock(uint8_t *world,uint8_t *chunk,float angleX,float angleZ,pos playerPos);

//ADD A BLOCK AT THE PLACE POINTED BY THE PLAYER
//chunk is the displayed chunk
//world is the whole world
//angleX and angleZ are camera rotation
//playerPos is the player's coordinates
//block is the type of the block to place
void addBlock(uint8_t *world,uint8_t *chunk,float angleX,float angleZ,pos playerPos,int block);

#endif

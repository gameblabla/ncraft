#ifndef _CUBE_LIST_H_
#define _CUBE_LIST_H_

#include "utils.h"

//RETURNS THE COLOR OF A TYPE OF CUBE
//index is the type of the cube
int getCubeColor(uint8_t index);

//RETURN A COLOR DARKER/LIGHTER THAN GIVEN
//color is the color to modify
//shade is the modification (>0 for a lighter color, <0 for a darker color)
int shadeColor(int color,int shade);

//RETURNS A CUBE INDEX IN THE WORLD FROM ITS INDEX IN THE CHUNK
//chunkIndex is its index in the chunk
//playerPos is player's position (in the world)
int getWorldIndexFromChunk(int chunkIndex, pos playerPos);

#endif

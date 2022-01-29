#include "cubeList.h"

//PC-FX hook up
const uint8_t cubeListGray[128]={
0, //air (0)
1, //bedrock (1)
5, //stone (2)
8, //dirt (3)
12, //grass (4)
14, //sand (5)
14, //diamond (6)
2, //coal (7)
12, //gold (8)
8, //iron (9)
5 //omniblue (10)
};

const uint16_t cubeListColor[128]={
0b0000000000000000, //air (0)
0b0001000010000010, //bedrock (1)
0b0111001110001110, //stone (2)
0b0101101000000010, //dirt (3)
0b0001010111000010, //grass (4)
0b1110111100110110, //sand (5)
0b1100011101111101, //diamond (6)
0b0010000100000100, //coal (7)
0b1110111011100010, //gold (8)
0b1001110001000011, //iron (9)
0b0001000010010001 //omniblue(10)
};



int shadeColor(int color,int shade)
{
  int newColor=0;
  #ifdef _16BPP
    newColor=ceiling(color/2048+shade*2,31)*2048+ceiling(color/32%64 +shade*4,63)*32+ceiling(color%32+shade*2,31);
    return (newColor>0) ? newColor : 0;
  #else
  return ceiling(color+shade,15);
  #endif
}



int getCubeColor(uint8_t index)
{
	#ifdef _16BPP
    if(index<128)
      return (int)cubeListColor[index];
    else
      return shadeColor((int)cubeListColor[256-index],1);
	#else
    if(index<128)
      return (int)cubeListGray[index];
    else
      return shadeColor((int)cubeListGray[256-index],1);
	#endif
}



int getWorldIndexFromChunk(int chunkIndex, pos playerPos)
{
  int xWorldPos,yWorldPos,zWorldPos,worldIndex;
  
  yWorldPos=chunkIndex%CUBE_CHUNK_Y;
  xWorldPos=((chunkIndex-yWorldPos)/CUBE_CHUNK_Y)%CUBE_CHUNK_X;
  zWorldPos=(chunkIndex-xWorldPos*CUBE_CHUNK_Y-yWorldPos)/(CUBE_CHUNK_X*CUBE_CHUNK_Y);
    
  xWorldPos+=((int)playerPos.x)/2-CUBE_CHUNK_X/2;
  yWorldPos+=((int)playerPos.y)/2-CUBE_CHUNK_Y/2;
  zWorldPos+=((int)playerPos.z)/2-CUBE_CHUNK_Z/2-1;
    
  worldIndex=CUBE_WORLD_X*CUBE_WORLD_Y*zWorldPos + CUBE_WORLD_Y*xWorldPos + yWorldPos;
  return worldIndex;
}


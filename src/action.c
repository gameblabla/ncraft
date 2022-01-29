#include "actions.h"


//GET A CUBE DEFINED BY ITS POS
//cubeChunk is a "cubemap" array
//x,y,z are coordinates
//warning ! the coordinates are in the chunk, NOT in the world. So 0,0,0 is player's feet pos.
//basically, 0,0,0 is the cube where the player stands on.
int getCubeIndex(float x,float y,float z)
{
  int index=0,temp=0;
  x+=CUBE_CHUNK_X;
  y+=CUBE_CHUNK_Y;
  z+=CUBE_CHUNK_Z-2.0;
  if(x>0 && y>0 && z>0 && x/2.0<CUBE_CHUNK_X && y/2.0<CUBE_CHUNK_Y && z/2.0<CUBE_CHUNK_Z)
  {
    x=x/2.0;
    y=y/2.0;
    z=z/2.0;
    temp=(int)z;
    index=temp*CUBE_CHUNK_X*CUBE_CHUNK_Y;
    temp=(int)x;
    index+=temp*CUBE_CHUNK_Y;
    temp=(int)y;
    index+=temp;
  }
  if(index>=0 && index<CUBE_CHUNK_Z*CUBE_CHUNK_X*CUBE_CHUNK_Y)
    return index;
  else
    return -1;
}

//SHORTCUT
int getCube(uint8_t *cubeChunk,float x,float y,float z)
{
  int index=getCubeIndex(x,y,z);
  if(index!=-1)
    return cubeChunk[index];
  else
    return 0;
}

//GETS INDEX OF THE CUBE POINTED BY THE PLAYER, IN THE CHUNK
int rayCast(uint8_t *chunk,float angleX,float angleZ,pos playerPos,int *lastCube)
{
  float xcoef,ycoef,zcoef;
  float xPos,yPos,zPos;
  int i,collision,chunkIndex,worldIndex;
  
  xcoef=cos(angleZ-90.0)*cos(angleX);
  ycoef=sin(angleZ+90.0)*cos(angleX);
  zcoef=-sin(angleX);
  
  xPos=playerPos.x-floor(playerPos.x/2)*2.0;
  yPos=playerPos.y-floor(playerPos.y/2)*2.0;
  zPos=playerPos.z-floor(playerPos.z/2)*2.0;
  
  chunkIndex=-1;
  worldIndex=-1;
  i=0;
  collision=0;
  
  while(i<800 && collision==0)
  {
    i++;
    xPos+=xcoef/20;
    yPos+=ycoef/20;
    zPos+=zcoef/20;
    chunkIndex=getCubeIndex(xPos,yPos,zPos+4);
    if(chunkIndex>0)
    {
      if(chunk[chunkIndex]>0)
      {
        collision=1;
        if(lastCube!=NULL)
          *lastCube=getCubeIndex(xPos-xcoef/20,yPos-ycoef/20,zPos-zcoef/20+4);
      }
    }
  }
  //now, let's get worldIndex with chunkIndex...
  if(collision==1)
  {
    worldIndex=getWorldIndexFromChunk(chunkIndex,playerPos);
    if(lastCube!=NULL)
      *lastCube=getWorldIndexFromChunk(*lastCube,playerPos);
  }

  return worldIndex;
}


//REMOVE A BLOCK
void removeBlock(uint8_t *world,uint8_t *chunk,float angleX,float angleZ,pos playerPos)
{
  int index=rayCast(chunk,angleX,angleZ,playerPos,NULL);
  if(index>=0)
  {
    if(world[index]!=1)//bedrock
      world[index]=0;
  }
}

//ADD A BLOCK
void addBlock(uint8_t *world,uint8_t *chunk,float angleX,float angleZ,pos playerPos,int block)
{
  int newCubeIndex=-1;
  rayCast(chunk,angleX,angleZ,playerPos,&newCubeIndex);
  if(newCubeIndex>0 && newCubeIndex<CUBE_WORLD_X*CUBE_WORLD_Y*CUBE_WORLD_Z)
    world[newCubeIndex]=block;
}

  

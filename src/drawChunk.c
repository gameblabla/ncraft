#include <string.h>
#include "drawChunk.h"



void heap(float *dist,int *index,int i,int n)
{
  int k=i;
  int j=2*k;
  while(j<=n)
  {
    if(j<n && dist[j]>dist[j+1])
    {
      j++;
    }
    if(dist[k]>dist[j])
    {
      invertTablefloats(dist,k,j);
      invertTableElems(index,k,j);
      k=j;
      j=2*k;
    }
    else
    {
      break;
    }
  }
}




void sortCubePos(float *cubePos,uint8_t *cubeList,int size)
{  
  int i=0;
  float *dist=malloc(size*sizeof(float));
  int *index=malloc(size*sizeof(int));
  
  //calculates distance of each cube
  for(i=0;i<size;i++)
  {
    dist[i]=cubePos[i*3]*cubePos[i*3]+cubePos[i*3+1]*cubePos[i*3+1]+cubePos[i*3+2]*cubePos[i*3+2];
    index[i]=i;
  }
  
  //heap sort
  for(i=(size+1)/2-1;i>=0;i--)
  {
    heap(dist,index,i,size-1);
  }
  for(i=size-1;i>=1;i--)
  {
    invertTablefloats(dist,i,0);
    invertTableElems(index,i,0);
    heap(dist,index,0,i-1);
  }
  
  //sort cubes with given indexes
  float *cubePosImg=malloc(size*3*sizeof(float));
  memcpy(cubePosImg,cubePos,size*3*sizeof(float));
  
  uint8_t *cubeListImg=malloc(size*sizeof(uint8_t));
  memcpy(cubeListImg,cubeList,size*sizeof(uint8_t));
  
  for(i=0;i<size;i++)
  {
    cubePos[i*3]=cubePosImg[index[i]*3];
    cubePos[i*3+1]=cubePosImg[index[i]*3+1];
    cubePos[i*3+2]=cubePosImg[index[i]*3+2];
    cubeList[i]=cubeListImg[index[i]];
  }
  
  free(dist);
  free(index);
  free(cubePosImg);
  free(cubeListImg);
}

void sortChunkIndexes(float *dist,int *indexes,int size)
{
  int i=0;
  //heap sort
  for(i=(size+1)/2-1;i>=0;i--)
  {
    heap(dist,indexes,i,size-1);
  }
  for(i=size-1;i>=1;i--)
  {
    invertTablefloats(dist,i,0);
    invertTableElems(indexes,i,0);
    heap(dist,indexes,0,i-1);
  }
}



int isCubeVisibleInChunk(uint8_t *chunk,int cubeX,int cubeY,int cubeZ,int index)
{
  int visible=0;
  if(cubeZ>=CUBE_CHUNK_Z/2)
    visible+=(chunk[index-CUBE_CHUNK_X*CUBE_CHUNK_X]==0) ? 1 : 0;
  if(cubeZ<=CUBE_CHUNK_Z/2)
    visible+=(chunk[index+CUBE_CHUNK_X*CUBE_CHUNK_Y]==0) ? 1 : 0;
  if(cubeX>=CUBE_CHUNK_X/2)
    visible+=(chunk[index-CUBE_CHUNK_Y]==0) ? 1 : 0;
  if(cubeX<=CUBE_CHUNK_X/2)
    visible+=(chunk[index+CUBE_CHUNK_Y]==0) ? 1 : 0;
  if(cubeY>=CUBE_CHUNK_Y/2)
    visible+=(chunk[index-1]==0) ? 1 : 0;
  if(cubeY<=CUBE_CHUNK_Y/2)
    visible+=(chunk[index+1]==0) ? 1 : 0;
  return visible;
}



int isCubeVisibleInWorld(uint8_t *world,int cubeX,int cubeY,int cubeZ,int index,pos playerPos)
{
  int visible=0;
  playerPos.x=(int)playerPos.x/2; playerPos.y=(int)playerPos.y/2; playerPos.z=(int)playerPos.z/2;
  
  if(cubeZ>=playerPos.z)
    visible+=(world[index-CUBE_WORLD_X*CUBE_WORLD_Y]==0) ? 1 : 0;
  if(cubeZ<=playerPos.z)
    visible+=(world[index+CUBE_WORLD_X*CUBE_WORLD_Y]==0) ? 1 : 0;
  if(cubeX>=playerPos.x)
    visible+=(world[index-CUBE_WORLD_Y]==0) ? 1 : 0;
  if(cubeX<=playerPos.x)
    visible+=(world[index+CUBE_WORLD_Y]==0) ? 1 : 0;
  if(cubeY>=playerPos.y)
    visible+=(world[index-1]==0) ? 1 : 0;
  if(cubeY<=playerPos.y)
    visible+=(world[index+1]==0) ? 1 : 0;
  return visible;
}




void computeCubeWorldChunk(uint8_t *chunk,float *cubePos,uint8_t *cubeList,int *size,float xRotation,float zRotation,pos playerPos)
{
  int i=0,j=0,k=0; //iterators
  int index=0,n=0,displayed=0; //utils
  
  playerPos.x-=floor_game(playerPos.x/2.0f)*2.0f-(float)CUBE_CHUNK_X;
  playerPos.y-=floor_game(playerPos.y/2.0f)*2.0f-(float)CUBE_CHUNK_Y;
  playerPos.z-=floor_game(playerPos.z/2.0f)*2.0f-(float)CUBE_CHUNK_Z-2.0f;
  
  //loop to see all cubes
  for(i=0;i<CUBE_CHUNK_Z;i++)
  {
    for(j=0;j<CUBE_CHUNK_X;j++)
    {
      for(k=0;k<CUBE_CHUNK_Y;k++)
      {
        //optimization of cubes display
        index=i*CUBE_CHUNK_Y*CUBE_CHUNK_X+j*CUBE_CHUNK_Y+k;
        displayed=isCubeVisibleInChunk(chunk,j,k,i,index);
        
        if(chunk[index]!=0 && displayed)
        {
          cubePos[n*3]=(float)j*2.0f+1.0f;
          cubePos[n*3+1]=(float)k*2.0f+1.0f;
          cubePos[n*3+2]=(float)i*2.0f+1.0f;
          cubeList[n]=chunk[index];
          n=n+1;
        }

      }
    }
  }
  translate(cubePos,n,-playerPos.x,-playerPos.y,-playerPos.z);
  rotateZ(cubePos,n,zRotation);
  rotateX(cubePos,n,xRotation);
  sortCubePos(cubePos,cubeList,n);
  *size=n;
}




void renderFullWorld(void *buffer,uint8_t *world,float *cubePos,uint8_t *cubeList,float xRotation,float zRotation,pos playerPos)
{
  int i=0,j=0,k=0,c=0,currentChunk=0; //iterators
  int index=0,n=0,displayed=0; //utils
  int nbChunksX=CUBE_WORLD_X/CUBE_CHUNK_X+1;
  int nbChunksY=CUBE_WORLD_Y/CUBE_CHUNK_Y+1;
  
  //associate a number and a distance to each chunk
  int chunkIndexes[nbChunksX*nbChunksY];
  float chunkDist[nbChunksX*nbChunksY];
  for(i=0;i<nbChunksX*nbChunksY;i++)
  {
    chunkIndexes[i]=i;
    j=i/nbChunksX;
    k=i%nbChunksY;
    chunkDist[i]=(playerPos.x-((float)j*2+1)*CUBE_CHUNK_X)*(playerPos.x-((float)j*2+1)*CUBE_CHUNK_X)+(playerPos.y-((float)k*2+1)*CUBE_CHUNK_Y)*(playerPos.y-((float)k*2+1)*CUBE_CHUNK_Y);
  }
  sortChunkIndexes(chunkDist,chunkIndexes,nbChunksX*nbChunksY);
 
  //loop to see all chunks
  for(c=0;c<nbChunksX*nbChunksY;c++)
  {
    currentChunk=chunkIndexes[c];
    n=0;
    //loop to see all cubes
    for(i=0;i<CUBE_WORLD_Z;i++)
    {
      for(j=currentChunk/nbChunksY*CUBE_CHUNK_Y;j<currentChunk/nbChunksY*CUBE_CHUNK_Y+CUBE_CHUNK_X;j++)
      {
        for(k=currentChunk%nbChunksY*CUBE_CHUNK_Y;k<currentChunk%nbChunksY*CUBE_CHUNK_Y+CUBE_CHUNK_Y;k++)
        {
          //optimization of cubes display
          if(j>=0 && j<CUBE_WORLD_X && k>=0 && k<CUBE_WORLD_Y)
          {
            index=i*CUBE_WORLD_Y*CUBE_WORLD_X+j*CUBE_WORLD_Y+k;
            displayed=isCubeVisibleInWorld(world,j,k,i,index,playerPos);
          }
          else
            displayed=0;
          
          if(world[index]!=0 && displayed)
          {
            cubePos[n*3]=(float)j*2.0f+1.0f;
            cubePos[n*3+1]=(float)k*2.0f+1.0f;
            cubePos[n*3+2]=(float)i*2.0f+1.0f;
            cubeList[n]=(index%2==0)? world[index] : 256-world[index];
            n=n+1;
          }
        }
      }
    }
    translate(cubePos,n,-playerPos.x,-playerPos.y,-playerPos.z);
    rotateZ(cubePos,n,zRotation);
    rotateX(cubePos,n,xRotation);
    sortCubePos(cubePos,cubeList,n);
    
    drawCubeList(buffer,cubePos,cubeList,n,xRotation,zRotation);
    
    //progress bar
    drawProgressBar(SCREEN_BASE_ADDRESS,c*100/(nbChunksX*nbChunksY-2));
    
    bufDisplay(SCREEN_BASE_ADDRESS);
  }
  bufDisplay(SCREEN_BASE_ADDRESS);
}




void drawCubeList(void *buffer,float *cubePos,uint8_t *cubeList,int size,float xRotation,float zRotation)
{
  //one cube -- to translate to each pos of cubePos
  float cubeVertices[8*3]={1.0,1.0,1.0,  1.0,1.0,-1.0,  1.0,-1.0,1.0,  1.0,-1.0,-1.0,  -1.0,1.0,1.0,  -1.0,1.0,-1.0,  -1.0,-1.0,1.0,  -1.0,-1.0,-1.0};
  float cubeVerticesImg[8*3]={0.0};
  
  int cubeFaces[6*4]={1,2,4,3,  1,5,6,2,  1,3,7,5,  8,7,3,4,  8,7,5,6,  8,4,2,6};
  int colors[6]={2,4,6,8,10,12};
  int verticesPos[8*2]={0};
  int i=0;
  
  rotateZ(cubeVertices,8,zRotation);
  rotateX(cubeVertices,8,xRotation);
  
  //draw all cubes
  for(i=0;i<size;i++)
  {
    memcpy(cubeVerticesImg,cubeVertices,24*sizeof(float));
    
    translate(cubeVerticesImg,8,cubePos[i*3],cubePos[i*3+1],cubePos[i*3+2]);
    
    colors[0]=(int)(getCubeColor(cubeList[i]));
    colors[1]=shadeColor(colors[0],1);
    colors[2]=shadeColor(colors[0],-1);
    colors[3]=shadeColor(colors[0],1);
    colors[4]=colors[0];
    colors[5]=shadeColor(colors[0],-1);
    
    computeVertices(cubeVerticesImg,verticesPos,8);
    if(verticesPos[0]!=-10000)
      drawCube(buffer,cubeVerticesImg,verticesPos,cubeFaces,colors);
  }
}

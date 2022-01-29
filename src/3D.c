#include "3D.h"

//#define FOV 50.0f
#define FOV 25.0f

void computeVertices(float *vertices,int *pos,int size)
{
  int i;
  float temp;
  for(i=0;i<size;i++)
  {
    if(vertices[i*3+1]>0.0f)
    {
      temp=(float)OFFSET*vertices[i*3]/vertices[i*3+1]*FOV+(SCREEN_GAME_WIDTH/2);
      pos[i*2]=(int)temp;
      temp=(float)-OFFSET*vertices[i*3+2]/vertices[i*3+1]*FOV+(SCREEN_GAME_HEIGHT/2);
      pos[i*2+1]=(int)temp;
    }
    else
    {
      pos[0]=-10000;
      pos[i*2]=-10000;
      pos[i*2+1]=-10000;
    }
  }
}

void translate(float *vertices,int size,float x,float y,float z)
{
  int i;
  for(i=0;i<size;i++)
  {
    vertices[i*3]+=x;
    vertices[i*3+1]+=y;
    vertices[i*3+2]+=z;
  }
}

void scale(float *vertices,int size,float x,float y,float z)
{
  int i;
  for(i=0;i<size;i++)
  {
    vertices[i*3]*=x;
    vertices[i*3+1]*=y;
    vertices[i*3+2]*=z;
  }
}

void rotateX(float *vertices,int size,float angle)
{
  float c=cos_game(angle),s=sin_game(angle);
  float matrix[9]={1.0f,0.0f,0.0f,0.0f,c,-1.0f*s,0.0f,s,c};
  float vector[3];
  int i;
  for(i=0;i<size;i++)
  {
    vector[0]=vertices[i*3];
    vector[1]=vertices[i*3+1];
    vector[2]=vertices[i*3+2];
    multiplyMatrix(vector,matrix);
    vertices[i*3]=vector[0];
    vertices[i*3+1]=vector[1];
    vertices[i*3+2]=vector[2];
  }
}

void rotateY(float *vertices,int size,float angle)
{
  float c=cos_game(angle),s=sin_game(angle);
  float matrix[9]={c,0.0f,s,0.0f,1.0f,0.0f,-1.0f*s,0.0f,c};
  float vector[3];
  int i;
  for(i=0;i<size;i++)
  {
    vector[0]=vertices[i*3];
    vector[1]=vertices[i*3+1];
    vector[2]=vertices[i*3+2];
    multiplyMatrix(vector,matrix);
    vertices[i*3]=vector[0];
    vertices[i*3+1]=vector[1];
    vertices[i*3+2]=vector[2];
  }
}

void rotateZ(float *vertices,int size,float angle)
{
  float c=cos_game(angle),s=sin_game(angle);
  float matrix[9]={c,-1*s,0,s,c,0,0,0,1};
  float vector[3];
  int i;
  for(i=0;i<size;i++)
  {
    vector[0]=vertices[i*3];
    vector[1]=vertices[i*3+1];
    vector[2]=vertices[i*3+2];
    multiplyMatrix(vector,matrix);
    vertices[i*3]=vector[0];
    vertices[i*3+1]=vector[1];
    vertices[i*3+2]=vector[2];
  }
}

void multiplyMatrix(float *vector,float *matrix)
{
  float v0=vector[0];
  float v1=vector[1];
  float v2=vector[2];
  vector[0]=v0*matrix[0]+v1*matrix[1]+v2*matrix[2];
  vector[1]=v0*matrix[3]+v1*matrix[4]+v2*matrix[5];
  vector[2]=v0*matrix[6]+v1*matrix[7]+v2*matrix[8];
}

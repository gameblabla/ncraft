#ifndef _3D_H_
#define _3D_H_

#include "buffer.h"

#define OFFSET 10.0

//For all these functions :
//size should be the number of vertices of a mesh
//vertices should be a table of size 3*size    {x1,y1,z1, x2,y2,z2,...}
//pos should be a table of size 2*size       {x1,y1, x2,y2,...}

//calculates the position of given vertices on the screen. The position is stored in pos.
void computeVertices(float *vertices,int *pos,int size);

//translates vertices
void translate(float *vertices,int size,float x,float y,float z);

//scales vertices
void scale(float *vertices,int size,float x,float y,float z);

//rotates vertices
void rotateX(float *vertices,int size,float angle);
void rotateY(float *vertices,int size,float angle);
void rotateZ(float *vertices,int size,float angle);

//multiply a matrix and a vector
void multiplyMatrix(float *vector,float *matrix);

#endif

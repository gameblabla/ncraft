#include "buffer.h"
#include "draw.h"
#include "3D.h"
#include "drawChunk.h"
#include "actions.h"
#include "menu.h"


//LOADS THE CHUNK TO DISPLAY
void loadChunk(uint8_t *world,uint8_t *chunk,pos playerPos)
{  
  int x,y,z,i,j,k;
  int xmin,ymin,zmin;
  int xmax,ymax,zmax;
  int index=0;
  
  x=(int)floor(playerPos.x/2.0);
  y=(int)floor(playerPos.y/2.0);
  z=(int)floor(playerPos.z/2.0)-1;
  
  xmin=(x<CUBE_CHUNK_X/2) ? 0 : x-CUBE_CHUNK_X/2;
  ymin=(y<CUBE_CHUNK_Y/2) ? 0 : y-CUBE_CHUNK_Y/2;
  zmin=(z<CUBE_CHUNK_Z/2) ? 0 : z-CUBE_CHUNK_Z/2;
  
  xmax=(x+CUBE_CHUNK_X/2>=CUBE_WORLD_X) ? CUBE_WORLD_X : x+CUBE_CHUNK_X/2;
  ymax=(y+CUBE_CHUNK_Y/2>=CUBE_WORLD_Y) ? CUBE_WORLD_Y : y+CUBE_CHUNK_Y/2;
  zmax=(z+CUBE_CHUNK_Z/2>=CUBE_WORLD_Z) ? CUBE_WORLD_Z : z+CUBE_CHUNK_Z/2;
  
  memset(chunk,0,CUBE_CHUNK_X*CUBE_CHUNK_Y*CUBE_CHUNK_Z*sizeof(uint8_t));
  
  for(i=zmin-z+CUBE_CHUNK_Z/2;i<CUBE_CHUNK_Z/2+zmax-z;i++)
  {
    for(j=xmin-x+CUBE_CHUNK_X/2;j<CUBE_CHUNK_X/2+xmax-x;j++)
    {
      for(k=ymin-y+CUBE_CHUNK_Y/2;k<CUBE_CHUNK_Y/2+ymax-y;k++) /*TO DO:use memcpy*/
      {
        index=(i-CUBE_CHUNK_Z/2+z)*CUBE_WORLD_Y*CUBE_WORLD_X+(j-CUBE_CHUNK_X/2+x)*CUBE_WORLD_Y+k-CUBE_CHUNK_Y/2+y;
        chunk[i*CUBE_CHUNK_Y*CUBE_CHUNK_X+j*CUBE_CHUNK_Y+k]=(index%2==0) ? (world[index]) : (256-world[index]);
      }
    }
  }
}


//TRIES TO REACH A NEW POSITION
//and updates if success
void goToPos(uint8_t *chunk,float xPos,float yPos,pos *playerPos)
{
  float newXPos,newYPos;
  newXPos=xPos+playerPos->x-floor(playerPos->x/2)*2;
  newYPos=yPos+playerPos->y-floor(playerPos->y/2)*2;
  //make sure that the player does not go beyond the world's edge
  if(playerPos->x+xPos>0 && playerPos->x+xPos<2*CUBE_WORLD_X && playerPos->y+yPos>0 && playerPos->y+yPos<2*CUBE_WORLD_Y-1)
  {
    //collision tests
    if(getCube(chunk,newXPos,newYPos,4)==0)
    {
      if(getCube(chunk,newXPos,newYPos,2)==0)
      {
        playerPos->x+=xPos;
        playerPos->y+=yPos;
      }
      else if(getCube(chunk,newXPos,newYPos,6)==0)
      {
        playerPos->x+=xPos;
        playerPos->y+=yPos;
        playerPos->z+=2;
      }
    }
  }
}

void correctPosition(uint8_t *chunk,pos *playerPos)
{
  if(getCube(chunk,0,0,0)!=0 && ((playerPos->z+0.5)-floor((playerPos->z+0.5)/2)*2)>0.2)
   {playerPos->z=2+floor(playerPos->z/2)*2;}
}




////// MAIN GAME FUNCTION //////

void play_nCraft(void *buffer,uint8_t *world,pos *playerPosition,float *Xangle,float *Zangle)
{
  //player's position, rotation...
  //to avoid using pointers during the main function
  pos playerPos;
  playerPos.x=playerPosition->x;
  playerPos.y=playerPosition->y;
  playerPos.z=playerPosition->z;
  float angleX=*Xangle;
  float angleZ=*Zangle;
  
  //bools
  char exit=0,firstDisplay=0;
  char falling=1,repeatTab=0,repeatCtrl=0,fullRender=0;
  
  //utils
  uint8_t *chunk=malloc(CUBE_CHUNK_X*CUBE_CHUNK_Y*CUBE_CHUNK_Z*sizeof(uint8_t)); //cube world chunk (kind of a 3D array)
  uint8_t *cubeList=malloc(CUBE_CHUNK_X*CUBE_CHUNK_Y*CUBE_WORLD_Z*sizeof(uint8_t)); //type of all displayed cubes
  float *cubePos=malloc(CUBE_CHUNK_X*CUBE_CHUNK_Y*CUBE_WORLD_Z*3*sizeof(float)); //pos of the cubes to display
  int size=0; //number of displayed cubes
  
  //inventory ?
  int selectedCube=3;
  
  bufClear(buffer);
  bufDisplay(buffer);
  
  //render loop
  while(!exit)
  {
    //wait for key pressed
    /*while(!any_key_pressed() && firstDisplay==1 && falling==0)
    {
      idle();
      repeatTab=0;
      repeatCtrl=0;
    }*/

    //timers update
    //time=*(volatile uint16_t*)timerAddr;
    firstDisplay=1;
    
    //key detection
    if(isKeyPressed(KEY_NSPIRE_ESC))
      exit=1;
      
    if(isKeyPressed(KEY_NSPIRE_UP) && angleX>-80.0)
      angleX-=5.0;
    if(isKeyPressed(KEY_NSPIRE_DOWN) && angleX<80.0)
      angleX+=5.0;
    if(isKeyPressed(KEY_NSPIRE_RIGHT))
      angleZ+=5.0;
    if(isKeyPressed(KEY_NSPIRE_LEFT))
      angleZ-=5.0;
      
    if(isKeyPressed(KEY_NSPIRE_TAB) && repeatTab==0)
    {
      removeBlock(world,chunk,angleX,angleZ,playerPos);
      repeatTab=1;//avoid destroying several blocks in a row
    }
    if(!isKeyPressed(KEY_NSPIRE_TAB))
      repeatTab=0;
    if(isKeyPressed(KEY_NSPIRE_CTRL) && repeatCtrl==0)
    {
      addBlock(world,chunk,angleX,angleZ,playerPos,selectedCube);
      repeatCtrl=1;//avoid placing too much blocks in a row
    }
    if(!isKeyPressed(KEY_NSPIRE_CTRL))
      repeatCtrl=0;
      
    if(isKeyPressed(KEY_NSPIRE_F))
      fullRender=1;
    
      
    if(isKeyPressed(KEY_NSPIRE_8)) //forward
      goToPos(chunk,cos(angleZ-90.0)/1.5,sin(angleZ+90.0)/1.5,&playerPos);
    if(isKeyPressed(KEY_NSPIRE_2) || isKeyPressed(KEY_NSPIRE_5)) //backward
      goToPos(chunk,-cos(angleZ-90.0)/2,-sin(angleZ+90.0)/2,&playerPos);
    if(isKeyPressed(KEY_NSPIRE_6)) //right straff
      goToPos(chunk,cos(angleZ)/1.5,sin(angleZ+180.0)/1.5,&playerPos);
    if(isKeyPressed(KEY_NSPIRE_4)) //left straff
      goToPos(chunk,cos(angleZ-180.0)/1.5,sin(angleZ)/1.5,&playerPos);
      
    if(isKeyPressed(KEY_NSPIRE_PLUS))
      selectedCube=selectedCube%10+1;
    if(isKeyPressed(KEY_NSPIRE_MINUS))
      selectedCube=(selectedCube+8)%10+1;
    
    //gravity
    if(getCube(chunk,0,0,0)==0)
    {
      playerPos.z-=0.5;
      falling=1;
    }
    else
    {
      falling=0;
    }
    correctPosition(chunk,&playerPos);
    
      
    //draw
    bufClear(buffer);
    loadChunk(world,chunk,playerPos);
    if(fullRender)
    {
      renderFullWorld(buffer,world,cubePos,cubeList,angleX,angleZ,playerPos);
      fullRender=0;
      wait_key_pressed();
    }
    else
    {
      computeCubeWorldChunk(chunk,cubePos,cubeList,&size,angleX,angleZ,playerPos);
      drawCubeList(buffer,cubePos,cubeList,size,angleX,angleZ);
      drawCursor(buffer);
      drawCubeIndicator(buffer,getCubeColor(selectedCube));
      bufDisplay(buffer);
    }
  }
  
  //update pointers
  playerPosition->x=playerPos.x;
  playerPosition->y=playerPos.y;
  playerPosition->z=playerPos.z;
  *Xangle=angleX;
  *Zangle=angleZ;
  
  //free
  free(cubeList);
  free(chunk);
  free(cubePos);
}


////////////////////////
///////   MAIN   ///////
////////////////////////

extern void Init_display();

int main(int argc,char *argv[])
{
  if(argc<1)
    return 0;  
    
	Init_display();
  
  //initialization
  startrandom_game();
  
  //screen buffer
  void *buffer=malloc(SCREEN_BYTES_SIZE);
  //The cube world. Huge array
  uint8_t *world=malloc(CUBE_WORLD_X*CUBE_WORLD_Y*CUBE_WORLD_Z*sizeof(uint8_t));
  //boolean
  char exit=0;
  //path of the save file
  char savePath[200]="";
  snprintf(savePath, sizeof(savePath), "nCraft.save");
  
  
  //position & camera rotation
  pos playerPos;
  playerPos.x=101.0;
  playerPos.y=101.0;
  playerPos.z=50.1;
  float angleX=5.0,angleZ=10.0;
  
  
  //menu
  mainMenu(buffer,&exit,world,&playerPos,&angleX,&angleZ,savePath);

  //THE GAME
  if(!exit)
  {
    play_nCraft(buffer,world,&playerPos,&angleX,&angleZ);
    saveWorld(buffer,savePath,world,playerPos,angleX,angleZ);
  }

  free(world);
  free(buffer);
  return 0;
}

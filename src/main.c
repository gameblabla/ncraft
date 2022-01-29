#include "buffer.h"
#include "draw.h"
#include "3D.h"
#include "drawChunk.h"
#include "actions.h"
#include "menu.h"

uint8_t world[CUBE_WORLD_X*CUBE_WORLD_Y*CUBE_WORLD_Z];

//LOADS THE CHUNK TO DISPLAY

void loadChunk(uint8_t *world,uint8_t *chunk,pos playerPos)
{  
  int x,y,z,i,j,k;
  int xmin,ymin,zmin;
  int xmax,ymax,zmax;
  int index=0;
  
  x=(int)floor_game(playerPos.x/2.0f);
  y=(int)floor_game(playerPos.y/2.0f);
  z=(int)floor_game(playerPos.z/2.0f)-1;
  
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
      for(k=ymin-y+CUBE_CHUNK_Y/2;k<CUBE_CHUNK_Y/2+ymax-y;k++)
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
  newXPos=xPos+playerPos->x-floor_game(playerPos->x/2)*2;
  newYPos=yPos+playerPos->y-floor_game(playerPos->y/2)*2;
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
  if(getCube(chunk,0,0,0)!=0 && ((playerPos->z+0.5f)-floor_game((playerPos->z+0.5f)/2)*2)>0.2f)
   {playerPos->z=2+floor_game(playerPos->z/2)*2;}
}


////// MAIN GAME FUNCTION //////


void play_nCraft(void *buffer,uint8_t *world,pos *playerPosition,float *Xangle,float *Zangle)
{
  float angleX=*Xangle;
  float angleZ=*Zangle;
  
  //bools
  char exit=0;
  char repeatTab=0,repeatCtrl=0,fullRender=0;
  
  //utils
  uint8_t *chunk=malloc(CUBE_CHUNK_X*CUBE_CHUNK_Y*CUBE_CHUNK_Z*sizeof(uint8_t)); //cube world chunk (kind of a 3D array)
  uint8_t *cubeList=malloc(CUBE_CHUNK_X*CUBE_CHUNK_Y*CUBE_WORLD_Z*sizeof(uint8_t)); //type of all displayed cubes
  float *cubePos=malloc(CUBE_CHUNK_X*CUBE_CHUNK_Y*CUBE_WORLD_Z*3*sizeof(float)); //pos of the cubes to display
  int size=0; //number of displayed cubes
  

  int selectedCube=3;
  
  //inventory ?
	
  //player's position, rotation...
  //to avoid using pointers during the main function
  pos playerPos;
  playerPos.x=playerPosition->x;
  playerPos.y=playerPosition->y;
  playerPos.z=playerPosition->z;

  
  bufClear(buffer);
  bufDisplay(buffer);
  
  //render loop
  while(!exit)
  {
    //wait for key pressed
    //while(!any_key_pressed() && firstDisplay==1 && falling==0)
    //{
    //  idle();
    //  repeatTab=0;
   //   repeatCtrl=0;
   // }

    //timers update
    //time=*(volatile uint16_t*)timerAddr;
    
    //key detection
    #ifndef PCFX
    if(isKeyPressed(KEY_NSPIRE_ESC))
      exit=1;
    #endif
      
    if(isKeyPressed(KEY_NSPIRE_UP) && angleX>-80.0f)
      angleX-=5.0f;
    if(isKeyPressed(KEY_NSPIRE_DOWN) && angleX<80.0f)
      angleX+=5.0f;
    if(isKeyPressed(KEY_NSPIRE_RIGHT))
      angleZ+=5.0f;
    if(isKeyPressed(KEY_NSPIRE_LEFT))
      angleZ-=5.0f;
      
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
      goToPos(chunk,cos_game(angleZ-90.0f)/1.5,sin_game(angleZ+90.0f)/1.5f,&playerPos);
    if(isKeyPressed(KEY_NSPIRE_2) || isKeyPressed(KEY_NSPIRE_5)) //backward
      goToPos(chunk,-cos_game(angleZ-90.0f)/2,-sin_game(angleZ+90.0f)/2,&playerPos);
    if(isKeyPressed(KEY_NSPIRE_6)) //right straff
      goToPos(chunk,cos_game(angleZ)/1.5f,sin_game(angleZ+180.0f)/1.5f,&playerPos);
    if(isKeyPressed(KEY_NSPIRE_4)) //left straff
      goToPos(chunk,cos_game(angleZ-180.0f)/1.5,sin_game(angleZ)/1.5f,&playerPos);
      
    if(isKeyPressed(KEY_NSPIRE_PLUS))
      selectedCube=selectedCube%10+1;
    if(isKeyPressed(KEY_NSPIRE_MINUS))
      selectedCube=(selectedCube+8)%10+1;
    
    //gravity
    if(getCube(chunk,0,0,0)==0)
    {
      playerPos.z-=0.5f;
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

int main()
{
	char exit=0;
	float angleX=5.0f,angleZ=10.0f;
	pos playerPos;
	
	Init_display();
	
	//initialization
	startrandom_game();

	//The cube world. Huge array
	
	//path of the save file
	//position & camera rotation
	//menu
	#ifndef NOMENU
	char savePath[16]="";
	mainMenu(SCREEN_BASE_ADDRESS,&exit,world,&playerPos,&angleX,&angleZ,savePath);
	#else
	initWorld(world);
	#endif
	
	playerPos.x=101.0f;
	playerPos.y=101.0f;
	playerPos.z=50.1f;
	
	//THE GAME
	if(!exit)
	{
		play_nCraft(SCREEN_BASE_ADDRESS,world,&playerPos,&angleX,&angleZ);
		//saveWorld(SCREEN_BASE_ADDRESS,savePath,world,playerPos,angleX,angleZ);
	}

	//free(world);
	//free(buffer);
	return 0;
}

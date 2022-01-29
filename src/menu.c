#include "menu.h"


//RANDOM WORLD GENERATOR
void initWorld(uint8_t *world)
{
  int i=0,j=0,rnd=0,height=0;
  memset(world,0,CUBE_WORLD_X*CUBE_WORLD_Y*CUBE_WORLD_Z*sizeof(uint8_t));
  memset(world,1,CUBE_WORLD_X*CUBE_WORLD_Y*sizeof(uint8_t)); //floor 0 (bedrock)
  memset(world+CUBE_WORLD_X*CUBE_WORLD_Y*19,3,CUBE_WORLD_X*CUBE_WORLD_Y*sizeof(uint8_t)); //floor 19 (dirt)
  for(i=0;i<CUBE_WORLD_X*CUBE_WORLD_Y;i++)
  {
    //floor 1 (diamond)
    rnd=random_game(0,100);
    world[i+CUBE_WORLD_X*CUBE_WORLD_Y]=(rnd<5) ? 6 : 2;
    rnd=random_game(0,100);
    world[i+CUBE_WORLD_X*CUBE_WORLD_Y*2]=(rnd<3) ? 6 : 2;
    //floor 3 to 6 (gold)
    for(j=0;j<4;j++)
    {
      rnd=random_game(0,100);
      world[i+CUBE_WORLD_X*CUBE_WORLD_Y*(j+3)]=(rnd<5-j) ? 8 : 2;
    }
    //floor 7 to 12 (iron)
    for(j=7;j<=12;j++)
    {
      rnd=random_game(0,100);
      world[i+CUBE_WORLD_X*CUBE_WORLD_Y*j]=(rnd<5) ? 9 : 2;
    }
    //floor 13 to 18 (coal)
    for(j=13;j<=18;j++)
    {
      rnd=random_game(0,100);
      world[i+CUBE_WORLD_X*CUBE_WORLD_Y*j]=(rnd<5) ? 7 : 2;
    }
    //terrain
    height=floor(sin(i%CUBE_WORLD_X*30)*0.49+cos(i/CUBE_WORLD_Y*30)*0.49+sin(i%CUBE_WORLD_X*10+80)*0.49+cos(i/CUBE_WORLD_Y*10+65)*0.49+3);
    for(j=20;j<=19+height-1;j++)
    {
      world[i+CUBE_WORLD_X*CUBE_WORLD_Y*j]=3;
    }
    world[i+CUBE_WORLD_X*CUBE_WORLD_Y*(19+height)]=4;
  }//TO DO:desert, sea, moutain
}


void mainMenu(void *buffer,char *exit,uint8_t *world,pos *playerPos,float *angleX,float *angleZ,char *savePath)
{
  char menu=1;
  char firstDisplay=0;
  int cursor=0;
  int test=1;
  int white=(has_colors) ? 0xFFFF : 0xF;
  int grey=(has_colors) ? 0b0111001110001110 : 0x9;
  int blue=(has_colors) ? 0b0100001101111101 : 0xF;
  
  if(isKeyPressed(KEY_NSPIRE_ENTER))
    sleep_game(500); //avoid passing the menu when clicking enter to launch the game
  
  while(menu)
  {
    /*while(!any_key_pressed() && firstDisplay==1)
    {
      idle();
    }*/
    
    firstDisplay=1;
    
    if(isKeyPressed(KEY_NSPIRE_UP))
    {
      cursor=(cursor+2)%3;
    }
    if(isKeyPressed(KEY_NSPIRE_DOWN))
      cursor=(cursor+1)%3;
    if(isKeyPressed(KEY_NSPIRE_ENTER))
    {
      if(cursor==0)
        menuNewWorld(&menu,world,playerPos,angleX,angleZ);
      else if(cursor==1)
        test=menuLoadWorld(buffer,&menu,world,playerPos,angleX,angleZ,savePath);
    }
    if(isKeyPressed(KEY_NSPIRE_ESC))
    {
      menu=0;
      *exit=1;
    }
    if(test==0)
      *exit=1;
    
    memset(buffer,0,SCREEN_BYTES_SIZE);
    drawStringCenter(buffer,"nCraft alpha",blue,10);
    drawStringCenter(buffer,"Create new world",(cursor==0) ? white : grey,100);
    drawStringCenter(buffer,"Load world",(cursor==1) ? white : grey,130);
    drawStringCenter(buffer,"Settings",(cursor==2) ? white : grey,160);
    drawStringCenter(buffer,"Created by Chockosta (Loic Pujet)",grey,225);
    
    bufDisplay(buffer);
    if(menu)
      sleep_game(200);
  }
}


void menuNewWorld(char *menu,uint8_t *world,pos *playerPos,float *angleX,float *angleZ)
{
  initWorld(world);
  
  playerPos->x=101.0;
  playerPos->y=101.0;
  playerPos->z=50.1;
  *angleX=5.0;
  *angleZ=10.0;
  
  *menu=0;
}

int menuLoadWorld(void *buffer,char *menu,uint8_t *world,pos *playerPos,float *angleX,float *angleZ,char *savePath)
{
  int test=0;
  test=loadWorld(buffer,savePath,world,playerPos,angleX,angleZ);
  *menu=0;
  return test;
}



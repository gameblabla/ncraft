#include "file.h"


int scanInt(char *str)
{
  int start=0;
  int i=0;
  int number=0;
  
  while((str[start]<'0' || str[start]>'9'))
  {
    start++;
  }
  i=start;
  while(str[i]>='0' && str[i]<='9')
  {
    number*=10;
    number+=str[i]-'0';
    i++;
  }
  return number;
}



void* readLine(FILE *filein, char *text)
{
  do {
    if(fgets(text,512,filein)==NULL)
      return NULL;
  }while((text[0]=='/') || (text[0]=='\n'));
  return 0;
}

/*
void listFiles(char **files,int *nbFiles)
{
  
}
*/

char loadWorld(void *buffer,char *name,uint8_t *world,pos *playerPos,float *angleX,float *angleZ)
{
  #if 0
  //"loading chunks" screen
  memset(buffer,0,SCREEN_BYTES_SIZE);
  drawStringCenter(buffer,"Loading chunks",(has_colors) ? 0xFFFF : 0xF,100);
  
  FILE *worldFile=NULL;
  worldFile=fopen(name,"r");
  
  int i,j,k,l,m; //iterators
  char line[512];
  char value[5];
  
  if(worldFile==NULL)
  {
    sleep_game(500);
    show_msgbox("Error","No existing world.\nPlease create one.");
    return 0;
  }
  else
  {
    readLine(worldFile,line);
    if(strstr(line,"NCW1")==NULL)
    {
      fclose(worldFile);
      return 0;
    }
    else
    {
      //position
      readLine(worldFile,line);
      playerPos->x=(float)scanInt(line);
      readLine(worldFile,line);
      playerPos->y=(float)scanInt(line);
      readLine(worldFile,line);
      playerPos->z=(float)scanInt(line);
      
      //rotation
      readLine(worldFile,line);
      *angleX=(float)scanInt(line);
      readLine(worldFile,line);
      *angleZ=(float)scanInt(line);
      
      //correct
      playerPos->x/=1000; playerPos->y/=1000; playerPos->z/=1000;
      *angleX/=1000; *angleZ/=1000;
      
      //cube world
      for(i=0;i<CUBE_WORLD_Z;i++)
      {
        for(j=0;j<CUBE_WORLD_X;j++)
        {
          readLine(worldFile,line);
          l=0;
          
          for(k=0;k<CUBE_WORLD_Y;k++)
          {
            value[0]=' '; value[1]=' '; value[2]=' '; value[3]=' '; value[4]='\0';
            m=0;
            while(line[l]!=' ' && m<5)
            {
              value[m]=line[l];
              l++;
              m++;
            }
            l++;
            world[i*CUBE_WORLD_X*CUBE_WORLD_Y+j*CUBE_WORLD_Y+k]=scanInt(value);
          }
        }
        drawProgressBar(buffer,100*i/CUBE_WORLD_Z);
        bufDisplay(buffer);
      }
      fclose(worldFile);
      return 1;
    }
  }
  #endif
}


void saveWorld(void *buffer,char *name,uint8_t *world,pos playerPos,float angleX,float angleZ)
{
	#if 0
  //"saving chunks" screen
  memset(buffer,0,SCREEN_BYTES_SIZE);
  drawStringCenter(buffer,"Saving chunks",(has_colors) ? 0xFFFF : 0xF,100);
      
  int i,j,k;
  FILE *worldFile=NULL;
  worldFile=fopen(name,"w+");
  
  if(worldFile!=NULL)
  {
    fprintf(worldFile,"NCW1\n"); //magic number (nCraft world, version 1)
    
    //players pos, camera rotation
    //(multiplied by 1000 because I only can use integers) 
    playerPos.x*=1000; playerPos.y*=1000; playerPos.z*=1000;
    angleX*=1000; angleZ*=1000;
    fprintf(worldFile,"%d\n",(int)playerPos.x);
    fprintf(worldFile,"%d\n",(int)playerPos.y);
    fprintf(worldFile,"%d\n",(int)playerPos.z);
    fprintf(worldFile,"%d\n",(int)angleX);
    fprintf(worldFile,"%d\n",(int)angleZ);
    
    //world
    for(i=0;i<CUBE_WORLD_Z;i++)
    {
      for(j=0;j<CUBE_WORLD_X;j++)
      {
        for(k=0;k<CUBE_WORLD_Y;k++)
        {
          fprintf(worldFile,"%d ",world[i*CUBE_WORLD_X*CUBE_WORLD_Y+j*CUBE_WORLD_Y+k]);
        }
        fprintf(worldFile,"\n");
      }
      drawProgressBar(buffer,100*i/CUBE_WORLD_Z);
      bufDisplay(buffer);
    }
    fclose(worldFile);
  }
  else
  {
    sleep_game(500);
    show_msgbox("Error","Unable to open save file.\nIf it exists, desinstall ndless\nand suppress it. Then reinstall\nndless. Sorry.");  
  }
  #endif
}



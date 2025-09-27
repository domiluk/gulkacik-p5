#include <io.h>
#include "dlfont.h"

long done, info;
struct _finddata_t f;
BITMAP *active;

typedef struct _flee
{
char name[20];
char real_name[60];   
int longer;     
}FLEE;

typedef struct _levelbrowser
{
 int x, y;
 int nof;   
 int fw;
 int active;
 FLEE flee[400];      
}LB;

LB *init_lb(char *path, int x, int y)
{
 int i;
 int k;
 
 LB *lb;
 lb = (LB*)malloc(sizeof(LB));
 
 lb->x = x;
 lb->y = y;
 lb->nof = 0;
 lb->fw = 0;
 lb->active = 0;
 i = 0;
 
 info = _findfirst(path, &f);
 //for(k = 0; k < strlen(f.name)-4; k++)lb->flee[0].name[k] = f.name[k];
 strcpy(lb->flee[0].real_name,f.name);
 strcpy(lb->flee[0].name,f.name);
 lb->flee[0].name[strlen(f.name)] = '\0';
 lb->flee[0].name[strlen(f.name)-1] = '\0';
 lb->flee[0].name[strlen(f.name)-2] = '\0';
 lb->flee[0].name[strlen(f.name)-3] = '\0';
 lb->flee[0].name[strlen(f.name)-4] = '\0';
 //for(k = 0; k < strlen(f.name); k++)lb->flee[0].real_name[k] = f.name[k];
 printf("searching in path> %s\n", path);
 i++;
 printf("orgbba> %s <<\n", lb->flee[0].name);
 
 lb->nof++;
 while (1)
 {
  done = _findnext(info,&f);
  if (done) break;
  
  //for(k = 0; k < strlen(f.name); k++)lb->flee[i].name[k] = f.name[k];
  //for(k = 0; k < strlen(f.name); k++)lb->flee[i].real_name[k] = f.name[k];
 strcpy(lb->flee[i].real_name, f.name);
 strcpy(lb->flee[i].name, f.name);
 lb->flee[i].name[strlen(f.name)] = '\0';
 lb->flee[i].name[strlen(f.name)-1] = '\0';
 lb->flee[i].name[strlen(f.name)-2] = '\0';
 lb->flee[i].name[strlen(f.name)-3] = '\0';
 lb->flee[i].name[strlen(f.name)-4] = '\0';
 
  
  printf("org> %s <<\n",lb->flee[i].name);
  i++;
  lb->nof++; 
 }     
 
 return lb;            
}

int draw_lb(BITMAP *bmp, LB *lb)
{
 
 int i;
 
 for(i = lb->fw; i < lb->fw+7; i++)
 {
  if(i == lb->active)write_by_hand_red(bmp, lb->flee[i].name, lb->x + 10, lb->y+(i-lb->fw)*30); 
  else write_by_hand(bmp, lb->flee[i].name, lb->x + 10, lb->y+(i-lb->fw)*30);
  
  
  if(mir(lb->x, lb->y+(i-lb->fw)*30, lb->x+120, lb->y+(i-lb->fw)*30+30, 1))
  {
   lb->active = i;              
  }
 }
 
 if(mir(435, 220, 468, 254, 1))
 {
  if(lb->fw > 0)lb->fw--;
  rest(100);            
 }
 
 if(mir(430, 407, 466, 436, 1))
 {
  if(lb->fw+7 < lb->nof)lb->fw++;
  rest(100);             
 }
 //draw_sprite(bmp, active, lb->x+5, lb->y+2);
 
 return 1;    
}




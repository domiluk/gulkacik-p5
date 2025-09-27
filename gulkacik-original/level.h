#include <allegro.h>
#include <winalleg.h>
#include <winsock2.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define FIELD_SIZE 60
#define biela 0xffffff
#ifndef LEVEL_H
#define LEVEL_H

BITMAP *normal_brick[13], *water_field[5], *grass_field[5], *qm[4], *symbol_brick[30], *reverse, *diebrick, *bg;
BITMAP *laser_h_off, *laser_h_on, *laser_v_off, *laser_v_on, *arrow[4], *teleport, *teleport2, *endlevel, *intermezzo;
int curlevel = 0, splscr = 1, menu;

char levelname[10][15] = {"levely/01.gud", "levely/02.gud", "levely/03.gud", "levely/04.gud", "levely/05.gud", "levely/06.gud", "levely/07.gud", "levely/08.gud", "levely/09.gud", "levely/10.gud"};
char im_fname[] = "graphics/im1.bmp";

typedef struct _qm
{
 int value;
 int flip;
 int x;
 int y;
 int done;
 //struct _qm *next;       
}QM;//QUESTIONMARK

typedef struct _tp
{
 int x;
 int y;
 int x2;
 int y2;
}TP;//TELEPORT

typedef struct _lsr
{
 int type;
 int x;
 int y;
 int on;
}LASER;//LASER

typedef struct _level
{
 int w, h;
 int info[100][100];
 int qma;
 int tpa;
 int la;
 int elx, ely;
 int canend;
 int winner;
 float bx, by;
 QM qm[10];
 TP tp[5];
 LASER **lsr;
 BITMAP *bmp;
 BITMAP *alpha;
}LEVEL;

LEVEL *lvl;

LASER **init_lasers(int amount)
{
 LASER **ret;
 ret = (LASER**)malloc(sizeof(LASER*)*amount);
 int i;
 for(i = 0; i < amount; i++)
 {
  ret[i] = (LASER*)malloc(sizeof(LASER));
 }
 return ret;
}

QM *init_qm(int value, int x, int y)
{
 QM *q;
 q = (QM*)malloc(sizeof(QM));
 
 q->value = value;
 q->flip = 0;
 q->x = x;
 q->y = y;
 
 //q->next = NULL;
 
 return q;                 
}

int stick_qm_to_level(QM *q, LEVEL *l)
{
 //q->next = l->qm->next;
 //l->qm->next = q;
 
 return 1;   
}


int load_level(LEVEL *l, char *filename)
{
 FILE *ll;
 int x, y;
 //QM *q;
 int i, j, k;
 
 i = 0;
 j = 0;
 k = 0;
 ll = fopen(filename, "r");
 fscanf(ll, "%d %d %d %d %d %f %f", &l->w, &l->h, &l->qma, &l->tpa, &l->la, &l->bx, &l->by);
 l->lsr = init_lasers(l->la);
 l->winner = 0;
 //l->qm = (QM*)malloc(sizeof(QM)*l->qma);
 //l->qm = (QM*)malloc(sizeof(int)*l->qma);
 
  for(y = 0; y < l->h; y++)
  {
   for(x = 0; x < l->w; x++)
   {
    fscanf(ll, "%d", &l->info[x][y]);
    printf("%d ",l->info[x][y]); 
    
    if(l->info[x][y] == 100)
    {
     l->elx = x;
     l->ely = y;
     l->canend = 0;
    }
    
    if(l->info[x][y] == 40 || l->info[x][y] == 41 || l->info[x][y] == 42 || l->info[x][y] == 43)
    {
     l->lsr[j]->type = l->info[x][y];
     l->lsr[j]->x = x;
     l->lsr[j]->y = y;
     if(l->info[x][y] == 40 || l->info[x][y] == 42)
      l->lsr[j]->on = 1;
     else
      l->lsr[j]->on = 0;
     printf("LASER:%d:", l->lsr[j]->on);
     j++;
    }
    
    if(l->info[x][y] == 6)
    {
     l->tp[i].x = x;
     l->tp[i].y = y;
     i++;
    }
    
    if(l->info[x][y] == 10 || l->info[x][y] == 11 || l->info[x][y] == 12 || l->info[x][y] == 13 || l->info[x][y] == 14)
    {
     l->qm[k].value = l->info[x][y];
     l->qm[k].x = x;              
     l->qm[k].y = y;
     l->qm[k].flip = 0;
     l->qm[k].done = 0;
     k++;
    }
         
   }
   printf("\n");
  }
  printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",l->qm[0].value, l->qm[1].value, l->qm[2].value, l->qm[3].value, l->qm[4].value, l->qm[5].value, l->qm[6].value, l->qm[7].value, l->qm[8].value, l->qm[9].value);
  for(i = 0; i < l->tpa; i++)
  {
   fscanf(ll, "%d %d", &l->tp[i].x2, &l->tp[i].y2);
  }
  
  fclose(ll);
  return 1;   
}

BITMAP *level_to_bmp(LEVEL *l, int alpha)
{
 int x, y, tp = 0;
 BITMAP *b;
 if(alpha == 1)b = create_bitmap(l->w, l->h);
 else b = create_bitmap(l->w*FIELD_SIZE, l->h*FIELD_SIZE);
 if(alpha == 1) clear_to_color(b, 0);
 else{
  for(x = -15; x < b->w; x += bg->w)
  for(y = -9; y < b->h; y += bg->h)
  {
   draw_sprite(b, bg, x, y);
  }
 }
 for(x = 0; x < l->w; x++)
 for(y = 0; y < l->h; y++)
 {
  switch(l->info[x][y])
  {
   case 0:
    if(alpha == 1)putpixel(b, x, y, biela); 
    else draw_sprite(b, normal_brick[rand() % 13], x*FIELD_SIZE, y*FIELD_SIZE);   
   break;
   case 1:
    if(alpha == 1)putpixel(b, x, y, makecol(128, 128, 128));
    else draw_sprite(b, water_field[0], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 2:
    if(alpha == 1)putpixel(b, x, y, makecol(128, 128, 128));
    else draw_sprite(b, water_field[1], x*FIELD_SIZE, y*FIELD_SIZE);    
   break; 
   case 3:
    if(alpha == 1)putpixel(b, x, y, makecol(128, 128, 128));
    else draw_sprite(b, water_field[2], x*FIELD_SIZE, y*FIELD_SIZE);    
   break;
   case 4:
    if(alpha == 1)putpixel(b, x, y, makecol(128, 128, 128));
    else draw_sprite(b, water_field[3], x*FIELD_SIZE, y*FIELD_SIZE);    
   break; 
   case 5:
    if(alpha == 1)putpixel(b, x, y, makecol(128, 128, 128));
    else draw_sprite(b, water_field[4], x*FIELD_SIZE, y*FIELD_SIZE);    
   break;
   case 6:
    
   break;
   case 7:
    if(alpha == 1)putpixel(b, x, y, makecol(210,210,210));
    else draw_sprite(b, reverse, x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 9:
    if(alpha == 1)putpixel(b, x, y, makecol(220, 220, 220));
    else draw_sprite(b, diebrick, x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   
   case 10:
    if(alpha == 1)putpixel(b, x, y, makecol(10, 10, 10));
    else draw_sprite(b, qm[rand()%3], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 11:
    if(alpha == 1)putpixel(b, x, y, makecol(11, 11, 11));
    else draw_sprite(b, qm[rand()%3], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 12:
    if(alpha == 1)putpixel(b, x, y, makecol(12, 12, 12));
    else draw_sprite(b, qm[rand()%3], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 13:
    if(alpha == 1)putpixel(b, x, y, makecol(13, 13, 13));
    else draw_sprite(b, qm[rand()%3], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 14:
    if(alpha == 1)putpixel(b, x, y, makecol(14, 14, 14));
    else draw_sprite(b, qm[rand()%3], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
     
   case 20:
    if(alpha == 1)putpixel(b, x, y, makecol(200, 200, 200));
    else draw_sprite(b, grass_field[0], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 21:
    if(alpha == 1)putpixel(b, x, y, makecol(200, 200, 200));
    else draw_sprite(b, grass_field[1], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 22:
    if(alpha == 1)putpixel(b, x, y, makecol(200, 200, 200));
    else draw_sprite(b, grass_field[2], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 23:
    if(alpha == 1)putpixel(b, x, y, makecol(200, 200, 200));
    else draw_sprite(b, grass_field[3], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 24:
    if(alpha == 1)putpixel(b, x, y, makecol(200, 200, 200));
    else draw_sprite(b, grass_field[4], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 30:
    if(alpha == 1)
    {
     putpixel(b, x, y, makecol(230+tp,230+tp,230+tp));
     tp++;
    }
    else draw_sprite(b, teleport, x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 31:
    if(alpha == 1)
    {
     putpixel(b, x, y, makecol(230+tp,230+tp,230+tp));
     tp++;
    }
    else draw_sprite(b, teleport, x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 32:
    if(alpha == 1)
    {
     putpixel(b, x, y, makecol(230+tp,230+tp,230+tp));
     tp++;
    }
    else draw_sprite(b, teleport, x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 40://hor_on
    if(alpha == 1)
    {
     putpixel(b, x-1, y, biela);
     putpixel(b, x, y, makecol(240,240,240));
     putpixel(b, x+1, y, biela);
    }
    else draw_sprite(b, laser_h_on, (x-1)*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 41://hor_off
    if(alpha == 1)
    {
     putpixel(b, x-1, y, biela);
     //putpixel(b, x, y, makecol(240,240,240));
     putpixel(b, x+1, y, biela);
    }
    else draw_sprite(b, laser_h_off, (x-1)*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 42://ver_on
    if(alpha == 1)
    {
     putpixel(b, x, y-1, biela);
     putpixel(b, x, y, makecol(240,240,240));
     putpixel(b, x, y+1, biela);
    }
    else draw_sprite(b, laser_v_on, x*FIELD_SIZE, (y-1)*FIELD_SIZE);
   break;
   case 43://ver_off
    if(alpha == 1)
    {
     putpixel(b, x, y-1, biela);
     //putpixel(b, x, y, makecol(240,240,240));
     putpixel(b, x, y+1, biela);
    }
    else draw_sprite(b, laser_v_off, x*FIELD_SIZE, (y-1)*FIELD_SIZE);
   break;
   case 50:
    if(alpha == 1)putpixel(b, x, y, makecol(150, 150, 150));
    else draw_sprite(b, arrow[0], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 51:
    if(alpha == 1)putpixel(b, x, y, makecol(151, 151, 151));
    else draw_sprite(b, arrow[1], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 52:
    if(alpha == 1)putpixel(b, x, y, makecol(152, 152, 152));
    else draw_sprite(b, arrow[2], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 53:
    if(alpha == 1)putpixel(b, x, y, makecol(153, 153, 153));
    else draw_sprite(b, arrow[3], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 100:
    if(alpha == 1)putpixel(b, x, y, makecol(50, 100, 150));
   break;
  }
 }
  
 int f;
 for(f = 0; f < l->tpa; f++)
 {
  if(alpha == 0)
   draw_sprite(b, teleport2, l->tp[f].x2 * FIELD_SIZE, l->tp[f].y2 * FIELD_SIZE);
 }
 
 return b;       
}

LEVEL *init_level(char *filename)
{
 LEVEL *l;
 l = (LEVEL*)malloc(sizeof(LEVEL));
 load_level(l, filename);
 l->bmp = level_to_bmp(l, 0);
 l->alpha = level_to_bmp(l, 1);
 
 return l; 
}
#endif

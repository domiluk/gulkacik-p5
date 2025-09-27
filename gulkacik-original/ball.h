#define FIELD_SIZE 60

#include "level.h"

/*
TO DO - reakcie s QM treba asi prerobit.. to sa takto neda.. to uplne bugu.. game-featruje...
*/

int drawx1 = 0, drawy1 = 0;
int drawx2 = 0, drawy2 = 0;

int bll2_is_up = 0, bll2_is_down = 0, bll2_is_left = 0, bll2_is_right = 0;

int mode;
int turned;
int st;
int wwt;
volatile int bt = 0;
int lt = 0, gd, gwwt;
int first, last;

double gr_maxspeed = 1.0;
double gr_incspeed = 0.04;
double w_incvector = 0.005;
double bl_maxspeed = 3.0;
double bl_xspeed   = 0.04;
double bl_yspeed   = 0.04;
double bl_slowdn   = 0.01;
int pgud = 5;


SAMPLE *smp_normal, *smp_die, *smp_water, *smp_grass, *smp_teleport, *smp_symbol;
SAMPLE *h_teleport[3], *h_die, *h_level[3], *h_revers[2];


int pageupdn()
{
	if(key[KEY_PGUP] && pgud < 10)
	{
		gr_maxspeed  *= 2;
		gr_incspeed  *= 2;
		w_incvector  *= 2;
		bl_maxspeed  *= 2;
		bl_xspeed    *= 2;
		bl_yspeed    *= 2;
		bl_slowdn    *= 2;
		pgud += 1;
		key[KEY_PGUP] = FALSE;
	}
	if(key[KEY_PGDN] && pgud > 0)
	{
		gr_maxspeed  /= 2;
		gr_incspeed  /= 2;
		w_incvector  /= 2;
		bl_maxspeed  /= 2;
		bl_xspeed    /= 2;
		bl_yspeed    /= 2;
		bl_slowdn				/= 2;
		pgud -= 1;
		key[KEY_PGDN] = FALSE;
	}
}

void increase_time(void)
{
 bt++;
 printf("<>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
}
END_OF_FUNCTION(increase_time)

/*void inc_lt()
{
 lt++;
 if()
}*/

int one_man_show()
{
	if(mode == 10 || mode == 11)
	 return 1;
	else return 0;
}

void smth()
{
 lvl->qm[gd].flip = 0;
 lvl->qm[wwt].flip = 0;
 draw_sprite(lvl->bmp, qm[0], lvl->qm[gd].x*FIELD_SIZE, lvl->qm[gd].y*FIELD_SIZE);
 draw_sprite(lvl->bmp, qm[0], lvl->qm[wwt].x*FIELD_SIZE, lvl->qm[wwt].y*FIELD_SIZE);
 remove_int(smth);
 printf("idem\n");
}

typedef struct _ball
{
 float x, y, vx, vy;
 float maxspeed, yspeed, xspeed;
 BITMAP *bmp, *alpha;
 int reverse;   
 int qma;
 int lives;
 int siw;
 int points;
 int tmppts;
 int inwater;
 int ongrass;
}BALL;

BALL *bll, *bll2;

void smth2a()
{
 int a = getpixel(bll->alpha, (bll->x+bll->vx) / FIELD_SIZE, (bll->y+bll->vy) / FIELD_SIZE);
 int i;
 for(i = 0; i < lvl->tpa; i++)
 {
  if(a == makecol(230+i,230+i,230+i))
  {
   bll->x = lvl->tp[i].x2 * FIELD_SIZE + 15;
   bll->y = lvl->tp[i].y2 * FIELD_SIZE + 15;
   bll->vx = 0;
   bll->vy = 0;
   play_sample(h_teleport[rand()%3], 255, 128, 1000, FALSE);
  }
 }
 remove_int(smth2a);
}

void smth2b()
{
 int a = getpixel(bll2->alpha, (bll2->x+bll2->vx) / FIELD_SIZE, (bll2->y+bll2->vy) / FIELD_SIZE);
 int i;
 for(i = 0; i < lvl->tpa; i++)
 {
  if(a == makecol(230+i,230+i,230+i))
  {
   bll2->x = lvl->tp[i].x2 * FIELD_SIZE + 15;
   bll2->y = lvl->tp[i].y2 * FIELD_SIZE + 15;
   bll2->vx = 0;
   bll2->vy = 0;
   play_sample(h_teleport[rand()%3], 255, 128, 1000, FALSE);
  }
 }
 remove_int(smth2b);
}

void blick_laser()
{
 int i = 0;
 for(i = 0; i < lvl->la; i++)
 {
  if(lvl->lsr[i]->on == 1)
  {
   putpixel(bll->alpha, lvl->lsr[i]->x, lvl->lsr[i]->y, 0);
   if(!one_man_show())
   {
	   putpixel(bll2->alpha, lvl->lsr[i]->x, lvl->lsr[i]->y, 0);
			}
   if(lvl->lsr[i]->type == 40 || lvl->lsr[i]->type == 41)
    draw_sprite(lvl->bmp, laser_h_off, (lvl->lsr[i]->x-1)*FIELD_SIZE, lvl->lsr[i]->y*FIELD_SIZE);
   else
    draw_sprite(lvl->bmp, laser_v_off, lvl->lsr[i]->x*FIELD_SIZE, (lvl->lsr[i]->y-1)*FIELD_SIZE);
   lvl->lsr[i]->on = 0;
  }
  else
  {
   putpixel(bll->alpha, lvl->lsr[i]->x, lvl->lsr[i]->y, makecol(240,240,240));
   if(!one_man_show())
   {
   	putpixel(bll2->alpha, lvl->lsr[i]->x, lvl->lsr[i]->y, makecol(240,240,240));
			}
   if(lvl->lsr[i]->type == 40 || lvl->lsr[i]->type == 41)
    draw_sprite(lvl->bmp, laser_h_on, (lvl->lsr[i]->x-1)*FIELD_SIZE, lvl->lsr[i]->y*FIELD_SIZE);
   else
    draw_sprite(lvl->bmp, laser_v_on, lvl->lsr[i]->x*FIELD_SIZE, (lvl->lsr[i]->y-1)*FIELD_SIZE);
   lvl->lsr[i]->on = 1;
  }
 }
}

void decrease_reverse1()
{
 if(bll->reverse > 0)
 bll->reverse--;
 else remove_int(decrease_reverse1);
}

void decrease_reverse2()
{
 if(bll2->reverse > 0)
 bll2->reverse--;
 else remove_int(decrease_reverse2);
}

void manage_grass(BALL *b)
{
 if(getpixel(b->alpha, (b->x+b->vx) / FIELD_SIZE, (b->y+b->vy) / FIELD_SIZE) == makecol(200,200,200))
 {
  if(b->ongrass == 0)
  {
   b->ongrass = 1;
   play_sample(smp_grass, 255, 128, 1000, TRUE);
  }
  if(b->maxspeed > gr_maxspeed/*2.0*/)b->maxspeed -= gr_incspeed/*0.daco menej ako 5*/;
  else if(b->maxspeed < gr_maxspeed/*2.0*/)b->maxspeed = gr_maxspeed;
 }
 else
 {
  if(b->ongrass == 1)
  {
   b->ongrass = 0;
   stop_sample(smp_grass);
  }
  if(b->maxspeed < bl_maxspeed/*5.0*/)b->maxspeed += gr_incspeed/*5.0*/;
  else if(b->maxspeed > bl_maxspeed)b->maxspeed = bl_maxspeed;
 }
}

void manage_water_bll()
{
 if(getpixel(bll->alpha, (bll->x+bll->vx) / FIELD_SIZE, (bll->y+bll->vy) / FIELD_SIZE) == makecol(128,128,128))
 {
  if(bll->inwater == 0)
  {
   play_sample(smp_water, 255, 128, 1000, TRUE);
   bll->inwater = 1;
  }
  if(bll->siw < 3)
  {
   bll->siw++;
  }
  else
  {
   bll->siw = 0;
   if(bll->lives > 0)
    bll->lives--;
   bll->x = lvl->bx;
   bll->y = lvl->by;
   bll->vx = 0;
   bll->vy = 0;
  }
 }
 else
 {
  if(bll->inwater == 1)
  {
   stop_sample(smp_water);
   bll->inwater = 0;
  }
  bll->siw = 0;
 }
}

void manage_water_bll2()
{
 if(getpixel(bll2->alpha, (bll2->x+bll2->vx) / FIELD_SIZE, (bll2->y+bll2->vy) / FIELD_SIZE) == makecol(128,128,128))
 {
  if(bll2->inwater == 0)
  {
   play_sample(smp_water, 255, 128, 1000, TRUE);
   bll2->inwater = 1;
  }
  if(bll2->siw < 3)
  {
   bll2->siw++;
  }
  else
  {
   bll2->siw = 0;
   if(bll2->lives > 0)
    bll2->lives--;
   bll2->x = lvl->bx;
   bll2->y = lvl->by;
   bll2->vx = 0;
   bll2->vy = 0;
  }
 }
 else
 {
  if(bll2->inwater == 1)
  {
   stop_sample(smp_water);
   bll2->inwater = 0;
  }
  bll2->siw = 0;
 }
}


BALL *init_ball(char *filename, BITMAP *a, int qma, float x, float y)
{
 BALL *ball;
 ball = (BALL*)malloc(sizeof(BALL));
 
 ball->bmp = load_bitmap(filename, NULL);
 ball->alpha = create_bitmap(a->w, a->h);
 draw_sprite(ball->alpha, a, 0, 0);
 
 ball->x = x;
 ball->y = y;
 ball->vx = 0.0;
 ball->vy = 0.0;
 ball->maxspeed = bl_maxspeed; //5.0
 ball->xspeed = bl_xspeed; //0.001
 ball->yspeed = bl_yspeed; //0.001
 ball->reverse = 0;
 ball->qma = qma;
 ball->siw = 0;
 ball->lives = 3;
 ball->points = 0;
 ball->tmppts = 0;
 ball->inwater = 0;
 ball->ongrass = 0;
 
 return ball;     
}


int get_input_keyboard(BALL *b, int which)
{
 if(which == 5)
 {
  if(key[KEY_UP] && b->vy < b->maxspeed && b->vy > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vy-=b->yspeed;
   else
    b->vy+=b->yspeed;
   key[KEY_DOWN] = FALSE;
  }
  if(key[KEY_DOWN] && b->vy < b->maxspeed && b->vy > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vy+=b->yspeed;
   else
    b->vy-=b->yspeed;
   key[KEY_UP] = FALSE;
  } 
  if(key[KEY_A] && b->vx < b->maxspeed && b->vx > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vx-=b->xspeed;
   else
    b->vx+=b->xspeed;
   key[KEY_D] = FALSE;             
  }
  if(key[KEY_D] && b->vx < b->maxspeed && b->vx > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vx+=b->xspeed;
   else
    b->vx-=b->xspeed;
   key[KEY_A] = FALSE;               
  }
 }
 
 
 else if(which == 0)
 {
  if(key[KEY_UP] && b->vy < b->maxspeed && b->vy > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vy-=b->yspeed;
   else
    b->vy+=b->yspeed;
   key[KEY_DOWN] = FALSE;
  }
  if(key[KEY_DOWN] && b->vy < b->maxspeed && b->vy > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vy+=b->yspeed;
   else
    b->vy-=b->yspeed;
   key[KEY_UP] = FALSE;
  } 
  if(key[KEY_LEFT] && b->vx < b->maxspeed && b->vx > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vx-=b->xspeed;
   else
    b->vx+=b->xspeed;
   key[KEY_RIGHT] = FALSE;             
  }
  if(key[KEY_RIGHT] && b->vx < b->maxspeed && b->vx > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vx+=b->xspeed;
   else
    b->vx-=b->xspeed;
   key[KEY_LEFT] = FALSE;               
  }
 }
 else
 {
  if(key[KEY_W] && b->vy < b->maxspeed && b->vy > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vy-=b->yspeed;
   else
    b->vy+=b->yspeed;
   key[KEY_S] = FALSE;
  }
  if(key[KEY_S] && b->vy < b->maxspeed && b->vy > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vy+=b->yspeed;
   else
    b->vy-=b->yspeed;
   key[KEY_W] = FALSE;
  } 
  if(key[KEY_A] && b->vx < b->maxspeed && b->vx > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vx-=b->xspeed;
   else
    b->vx+=b->xspeed;
   key[KEY_D] = FALSE;             
  }
  if(key[KEY_D] && b->vx < b->maxspeed && b->vx > -b->maxspeed)
  {
   if(b->reverse == 0)
    b->vx+=b->xspeed;
   else
    b->vx-=b->xspeed;
   key[KEY_A] = FALSE;               
  }
 }
  /*if(b->vx > b->maxspeed) b->vx = b->maxspeed;
  if(b->vy > b->maxspeed) b->vy = b->maxspeed;
  if(b->vx < -b->maxspeed) b->vx = -b->maxspeed;
  if(b->vy < -b->maxspeed) b->vy = -b->maxspeed;*/
  if(b->vx > b->maxspeed) b->vx -= bl_slowdn;
  if(b->vy > b->maxspeed) b->vy -= bl_slowdn;
  if(b->vx < -b->maxspeed) b->vx += bl_slowdn;
  if(b->vy < -b->maxspeed) b->vy += bl_slowdn;
  //printf("%f,, %f\n", b->vx, b->vy);
 
 return 1;    
}

int get_input_mouse(BALL *b)
{
 int x, y;
 
 get_mouse_mickeys(&x, &y);
 //printf("<%d %d>", x, y);
 if(x == 0 && y == 0)
 {
      
 }
 else
 {
  b->vx = x/1;
  b->vy = y/1;
 }
 return 1;    
}


//pozdravujeme maja
int move_ya_body(BALL *b)
{
 int a1, a2, a3, a4, a5, a6, a7, a8;
 int a;
 int c;
 int d;
 int i;
 int flag;
 float bx, by;

 b->x += b->vx;
 b->y += b->vy;
 
 bx = b->vx+b->x;
 by = b->vy+b->y;
 //a1 = getpixel(b->alpha, bx/FIELD_SIZE, by/FIELD_SIZE);
 //a2 = getpixel(b->alpha, (bx+b->bmp->w/2)/FIELD_SIZE, by/FIELD_SIZE);
 //a3 = getpixel(b->alpha, (bx+b->bmp->w)/FIELD_SIZE, by/FIELD_SIZE);
 //a4 = getpixel(b->alpha, (bx+b->bmp->w)/FIELD_SIZE, (by+b->bmp->h/2)/FIELD_SIZE);
 //a5 = getpixel(b->alpha, (bx+b->bmp->w)/FIELD_SIZE, (by+b->bmp->h)/FIELD_SIZE);
 //a6 = getpixel(b->alpha, (bx+b->bmp->w/2)/FIELD_SIZE, (by+b->bmp->h)/FIELD_SIZE);
 //a7 = getpixel(b->alpha, bx/FIELD_SIZE, (by+b->bmp->h)/FIELD_SIZE);
 //a8 = getpixel(b->alpha, bx/FIELD_SIZE, (by+b->bmp->h/2)/FIELD_SIZE);
 
 
 /*if(a3 == biela && a4 == biela && a5 == biela)
  b->vx *= -1;
 else if(a5 == biela && a6 == biela && a7 == biela)
  b->vy *= -1;
 else if(a7 == biela && a8 == biela && a1 == biela)
  b->vx *= -1;
 else if(a1 == biela && a2 == biela && a3 == biela)
  b->vy *= -1;
 else if(a1 == biela && a3 == 0)
  b->vy *= -1;
 else if(a5 == biela && a7 == 0)
  b->vy *= -1;
 else if(a7 == biela && a1 == 0)
  b->vx *= -1;*/
  /*if(a2 == biela)
 {
  b->vy *= -1;
 }
 else if(a4 == biela)
 {
  b->vx *= -1;
 }
 else if(a6 == biela)
 {
  b->vy *= -1;
 }
 else if(a8 == biela)
 {
  b->vx *= -1;
 }
 /*else if(a1 == biela && a7 == biela)
  b->vx *= -1;
 else if(a1 == biela && a3 == biela)
  b->vy *= -1;
 else if(a3 == biela && a5 == biela)
  b->vx *= -1;
 else if(a5 == biela && a7 == biela)
  b->vy *= -1;
 else if(a1 == biela && a2 == 0 && a8 == 0)
 {
  b->vx *= -1;
  b->vy *= -1;
 }
 else if(a3 == biela && a2 == 0 && a4 == 0)
 {
  b->vx *= -1;
  b->vy *= -1;
 }
 else if(a5 == biela && a4 == 0 && a6 == 0)
 {
  b->vx *= -1;
  b->vy *= -1;
 }
  if(a7 == biela && a6 == 0 && a8 == 0)
 {
  b->vx *= -1;
  b->vy *= -1;
 }*/
 
 if(b->vx < 0)b->vx+=b->xspeed/3;
 else b->vx-=b->xspeed/3;
 
 if(b->vy < 0)b->vy+=b->yspeed/3;
 else b->vy-=b-> yspeed/3;
 
 
 for(a = 1; a < b->bmp->w-1; a++)
 {
  
  a1 = getpixel(b->alpha, (b->x+b->vx+a) / FIELD_SIZE, (b->y+b->vy) / FIELD_SIZE);
  a2 = getpixel(b->alpha, (b->x+b->vx+a) / FIELD_SIZE, (b->y+b->vy+b->bmp->h)/ FIELD_SIZE);
    
  if(a1 == biela)  
  {
   b->vy *= -1;
   play_sample(smp_normal, 255, 128, 1000, FALSE);
   /*f(b->reverse == 0)
    
    key[KEY_UP] = FALSE;
   else
    key[KEY_DOWN] = FALSE;*/
  }
  if(a2 == biela)
  {
   play_sample(smp_normal, 255, 128, 1000, FALSE);
   b->vy *= -1;
   /*if(b->reverse == 0)
    key[KEY_DOWN] = FALSE;
   else key[KEY_UP] = FALSE;*/
  }
  if(lvl->canend == 1)
  {
   if(a1 == makecol(50,100,150) || a2 == makecol(50,100,150))
   {
    if(lvl->winner == 0)
    {
					b->points += 3;
					printf("Niekto dosiel do ciela, dal som mu tri body.\n");
					if(one_man_show())
					{
						lvl->winner = 1;
					}
					else
					{
						if(bll->points > bll2->points)
						{
							lvl->winner = 1;
							printf("Kokos, vyhral to Gulkacik!\n");
						}
						else if(bll->points < bll2->points)
						{
							lvl->winner = 2;
							printf("Kokos, vyhrala to Gulicka!\n");
						}
						else if(bll->points == bll2->points)
						{
							if(b == bll)
							{
								lvl->winner = 1;
								printf("Kokos, mal som problem sa rozhodnut, ale nakoniec to vyhral Gulkacik!\n");
							}
							else if(b == bll2)
							{
								lvl->winner = 2;
								printf("Kokos, mal som problem sa rozhodnut, ale nakoniec to vyhrala Gulicka!\n");
							}
						}
					}
    }
   }
  }
  for(i = 0; i < 4; i++)
  {
   if(a1 == makecol(150+i, 150+i, 150+i) || a2 == makecol(150+i,150+i,150+i))
   {
    switch(i)
    {
     case 0:
      b->vy -= w_incvector;
     break;
     case 1:
      b->vx += w_incvector;
     break;
     case 2:
      b->vy += w_incvector;
     break;
     case 3:
      b->vx -= w_incvector;
     break;
    }
   }
  }
  for(i = 0; i < lvl->la; i++)
  {
   if(a1 == makecol(240,240,240) || a2 == makecol(240,240,240))
   {
    if(b->lives > 0)
     b->lives--;
    b->x = lvl->bx;
    b->y = lvl->by;
    b->vx = 0;
    b->vy = 0;
    play_sample(smp_die, 255, 128, 1000, FALSE);
    play_sample(h_die, 255, 128, 1000, FALSE);
   }
  }
  for(i = 0; i < lvl->tpa; i++)
  {
   if(a1 == makecol(230+i,230+i,230+i) || a2 == makecol(230+i,230+i,230+i))
   {
    if(b == bll)
     install_int(smth2a,1000);
    else
     install_int(smth2b,1000);
    play_sample(smp_teleport, 255, 128, 1000, FALSE);
   }
  }
  if(a1 == makecol(220,220,220) || a2 == makecol(220,220,220))
  {
   play_sample(smp_die, 255, 128, 1000, FALSE);
   if(b->lives > 0)
    b->lives--;
   b->x = lvl->bx;
   b->y = lvl->by;
   b->vx = 0;
   b->vy = 0;
   play_sample(h_die, 255, 128, 1000, FALSE);
  }
  if(a1 == makecol(210,210,210) || a2 == makecol(210,210,210))
  {
   b->vy *= -1;/*
   if(key[KEY_UP] && b->reverse == 0) key[KEY_]
   if(key[KEY_UP] && b->reverse > 0) key[KEY_UP] = FALSE;
   else if(key[KEY_DOWN] && b->reverse > 0) key[KEY_DOWN] = FALSE;*/
   if(key[KEY_UP]) key[KEY_UP] = FALSE;
   else if(key[KEY_DOWN]) key[KEY_DOWN] = FALSE;
   b->reverse = 5;
   if(b == bll)
    install_int(decrease_reverse1, 1000);
   else
    install_int(decrease_reverse2, 1000);
   play_sample(h_revers[rand()%2], 255, 128, 1000, FALSE);
  }
  for(c = 10; c < 15; c++)
  {
   if(a1 == makecol(c, c, c))
   {
    for(d = 0; d < b->qma*2; d++)
    {
     
     if(lvl->qm[d].x == (int)((b->x+b->vx)/FIELD_SIZE) && lvl->qm[d].y == (int)((b->y+b->vy)/FIELD_SIZE) && lvl->qm[d].done == 0)
     {
      /*printf("narazil som do %d, bwahaha up\n", d);
      lvl->qm[d].flip = 1;
      blit(symbol_brick[lvl->qm[d].value-10], lvl->bmp, 0, 0, lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE, FIELD_SIZE, FIELD_SIZE);
      */
      if(st == 0)
      {
							if(b == bll)
								first = 1;
							else if(b == bll2)
							 first = 2;
       turned = lvl->qm[d].value;
       wwt = d;
       st++;
       
       printf("<<turned %d wwt %d st %d>>\n",turned, wwt, st);
       
       lvl->qm[d].flip = 1;
      
       blit(symbol_brick[lvl->qm[d].value-10], lvl->bmp, 0, 0, lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE, FIELD_SIZE, FIELD_SIZE);
       play_sample(smp_symbol, 255, 128, 1000, FALSE);
      } 
      else if(st == 1)
      {
       if(turned == lvl->qm[d].value && wwt != d)
       {
								if(b == bll)
									last = 1;
								else if(b == bll2)
								 last = 2;
								if(first == last) //prve dal ten isty co druhe
								{
									b->points += 3;
									printf("Pridal som tri body gulke %d.\n", last);
								}
								else if(last == 1) //prve dal 2, druhe 1
								{
									b->points += 1;
									bll2->points += 2;
									printf("Pridal som jeden bod gulke %d a dva body gulke %d.\n", last, first);
								}
								else if(last == 2) //prve dal 1, druhe 2
								{
									b->points += 1;
									bll->points += 2;
									printf("Pridal som jeden bod gulke %d a dva body gulke %d.\n", last, first);
								}
        printf("fokin kab %d %d\n", d, lvl->qm[d].value-5);
        st = turned = 0;
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[wwt].value-5], lvl->qm[wwt].x*FIELD_SIZE, lvl->qm[wwt].y*FIELD_SIZE);
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[d].value-5], lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE);
        //blit(lvl->bmp, screen, 0, 0, 0, 0, 800,600);
        lvl->qm[d].flip = 1;
        lvl->qm[d].done = 1;
        lvl->qm[wwt].done = 1;
        play_sample(smp_symbol, 255, 128, 1000, FALSE);
       }
       else if(wwt != d)
       {
        st = turned = 0;
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[d].value-10], lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE);
        //blit(lvl->bmp, screen, 0, 0, 0, 0, 800,600);
        
        printf("p:%d, %d", d, wwt);
        flag = 1;
        
        gd = d;
        gwwt = wwt;
        wwt = 0;
        install_int(smth, 500);
        play_sample(smp_symbol, 255, 128, 1000, FALSE);
       }     
      }
      break;            
     }      
    }
    b->vy *= -1;
    key[KEY_UP] = FALSE;      
   }
   
   
   if(a2 == makecol(c, c, c))
   {
    for(d = 0; d < b->qma*2; d++)
    {
     
     if(lvl->qm[d].x == (int)((b->x+b->vx)/FIELD_SIZE) && lvl->qm[d].y-1 == (int)((b->y+b->vy)/FIELD_SIZE) && lvl->qm[d].done == 0)
     {
      /*intf("narazil som do %d, bwahaha down\n", d);
      lvl->qm[d].flip = 1;
      blit(symbol_brick[lvl->qm[d].value-10], lvl->bmp, 0, 0, lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE, FIELD_SIZE, FIELD_SIZE);
      */
      if(st == 0)
      {
							if(b == bll)
								first = 1;
							else if(b == bll2)
							 first = 2;
       turned = lvl->qm[d].value;
       wwt = d;
       st++;
       
       printf("<<%d %d %d>>",turned, wwt, st);
       
       lvl->qm[d].flip = 1;
      
       blit(symbol_brick[lvl->qm[d].value-10], lvl->bmp, 0, 0, lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE, FIELD_SIZE, FIELD_SIZE);
       play_sample(smp_symbol, 255, 128, 1000, FALSE);
      } 
      else if(st == 1)
      {
       if(turned == lvl->qm[d].value && wwt != d)
       {
								if(b == bll)
									last = 1;
								else if(b == bll2)
								 last = 2;
								if(first == last) //prve dal ten isty co druhe
								{
									b->points += 3;
									printf("Pridal som tri body gulke %d.\n", last);
								}
								else if(last == 1) //prve dal 2, druhe 1
								{
									b->points += 1;
									bll2->points += 2;
									printf("Pridal som jeden bod gulke %d a dva body gulke %d.\n", last, first);
								}
								else if(last == 2) //prve dal 1, druhe 2
								{
									b->points += 1;
									bll->points += 2;
									printf("Pridal som jeden bod gulke %d a dva body gulke %d.\n", last, first);
								}
        printf("fokin kab %d %d\n", d, lvl->qm[d].value-5);
        st = turned = 0;
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[wwt].value-5], lvl->qm[wwt].x*FIELD_SIZE, lvl->qm[wwt].y*FIELD_SIZE);
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[d].value-5], lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE);
        //blit(lvl->bmp, screen, 0, 0, 0, 0, 800,600);
        lvl->qm[d].flip = 1;
        lvl->qm[d].done = 1;
        lvl->qm[wwt].done = 1;
        play_sample(smp_symbol, 255, 128, 1000, FALSE);
       }
       else if(wwt != d)
       {
        st = turned = 0;
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[d].value-10], lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE);
        //blit(lvl->bmp, screen, 0, 0, 0, 0, 800,600);
        
        printf("p:%d, %d", d, wwt);
        flag = 1;
        
        gd = d;
        gwwt = wwt;
        install_int(smth, 500);
        play_sample(smp_symbol, 255, 128, 1000, FALSE);
       }     
      }
      break;           
     }      
    }
    b->vy *= -1;
    key[KEY_DOWN] = FALSE;      
   }  
  }  
 }
 
 for(a = 1; a < b->bmp->h-1; a++)
 {
  a1 = getpixel(b->alpha, (b->x+b->vx) / FIELD_SIZE, (b->y+b->vy+a) / FIELD_SIZE);
  a2 = getpixel(b->alpha, (b->x+b->vx+b->bmp->w) / FIELD_SIZE, (b->y+b->vy+a) / FIELD_SIZE);
   
  if(a1 == biela)
  {
   play_sample(smp_normal, 255, 128, 1000, FALSE);
    b->vx *= -1;
    /*if(b->reverse == 0)
     key[KEY_LEFT] = FALSE;
    else key[KEY_RIGHT] = FALSE;*/
  }
  if(a2 == biela)
  {
   play_sample(smp_normal, 255, 128, 1000, FALSE);
    b->vx *= -1;
    /*if(b->reverse == 0)
     key[KEY_RIGHT] = FALSE;
    else key[KEY_LEFT] = FALSE;*/
  }
  
  if(lvl->canend == 1)
  {
   if(a1 == makecol(50,100,150) || a2 == makecol(50,100,150))
   {
    if(lvl->winner == 0)
    {
					b->points += 3;
					printf("Niekto dosiel do ciela, dal som mu tri body.\n");
					if(one_man_show())
					{
						lvl->winner = 1;
					}
					else
					{
						if(bll->points > bll2->points)
						{
							lvl->winner = 1;
							printf("Kokos, vyhral to Gulkacik!\n");
						}
						else if(bll->points < bll2->points)
						{
							lvl->winner = 2;
							printf("Kokos, vyhrala to Gulicka!\n");
						}
						else if(bll->points == bll2->points)
						{
							if(b == bll)
							{
								lvl->winner = 1;
								printf("Kokos, mal som problem sa rozhodnut, ale nakoniec to vyhral Gulkacik!\n");
							}
							else if(b == bll2)
							{
								lvl->winner = 2;
								printf("Kokos, mal som problem sa rozhodnut, ale nakoniec to vyhrala Gulicka!\n");
							}
						}
					}
    }
   }
  }
  for(i = 0; i < 4; i++)
  {
   if(a1 == makecol(150+i, 150+i, 150+i) || a2 == makecol(150+i,150+i,150+i))
   {
    switch(i)
    {
     case 0:
      b->vy -= w_incvector;
     break;
     case 1:
      b->vx += w_incvector;
     break;
     case 2:
      b->vy += w_incvector;
     break;
     case 3:
      b->vx -= w_incvector;
     break;
    }
   }
  }
  for(i = 0; i < lvl->la; i++)
  {
   if(a1 == makecol(240,240,240) || a2 == makecol(240,240,240))
   {
   if(b->lives > 0)
    b->lives--;
   b->x = lvl->bx;
   b->y = lvl->by;
   b->vx = 0;
   b->vy = 0;
   play_sample(smp_die, 255, 128, 1000, FALSE);
   play_sample(h_die, 255, 128, 1000, FALSE);
   }
  }
  for(i = 0; i < lvl->tpa; i++)
  {
   if(a1 == makecol(230+i,230+i,230+i) || a2 == makecol(230+i,230+i,230+i))
   {
    if(b == bll)
     install_int(smth2a,1000);
    else
     install_int(smth2b,1000);
    play_sample(smp_teleport, 255, 128, 1000, FALSE);
   }
  }
  if(a1 == makecol(220,220,220) || a2 == makecol(220,220,220))
  {
   play_sample(smp_die, 255, 128, 1000, FALSE);
   if(b->lives > 0)
    b->lives--;
   b->x = lvl->bx;
   b->y = lvl->by;
   b->vx = 0;
   b->vy = 0;
   play_sample(h_die, 255, 128, 1000, FALSE);
  }
  if(a1 == makecol(210,210,210) || a2 == makecol(210,210,210))
  {
   b->vx *= -1;
   if(key[KEY_LEFT] && b->reverse > 0) key[KEY_LEFT] = FALSE;
   else if(key[KEY_RIGHT] && b->reverse > 0) key[KEY_RIGHT] = FALSE;
   b->reverse = 5;
   if(b == bll)
    install_int(decrease_reverse1, 1000);
   else
    install_int(decrease_reverse2, 1000);
   play_sample(h_revers[rand()%2], 255, 128, 1000, FALSE);
  }
  for(c = 10; c < b->qma+10; c++)
  {
   if(a1 == makecol(c, c, c))
   {
    for(d = 0; d < b->qma*2; d++)
    {
     
     if(lvl->qm[d].x == (int)((b->x+b->vx)/FIELD_SIZE) && lvl->qm[d].y == (int)((b->y+b->vy)/FIELD_SIZE) && lvl->qm[d].done == 0)
     {
      if(st == 0)
      {
							if(b == bll)
								first = 1;
							else if(b == bll2)
							 first = 2;
       turned = lvl->qm[d].value;
       wwt = d;
       st++;
       
       printf("<<%d %d %d>>",turned, wwt, st);
       
       lvl->qm[d].flip = 1;
      
       blit(symbol_brick[lvl->qm[d].value-10], lvl->bmp, 0, 0, lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE, FIELD_SIZE, FIELD_SIZE);
       play_sample(smp_symbol, 255, 128, 1000, FALSE);
      } 
      else if(st == 1)
      {
       if(turned == lvl->qm[d].value && wwt != d)
       {
								if(b == bll)
									last = 1;
								else if(b == bll2)
								 last = 2;
								if(first == last) //prve dal ten isty co druhe
								{
									b->points += 3;
									printf("Pridal som tri body gulke %d.\n", last);
								}
								else if(last == 1) //prve dal 2, druhe 1
								{
									b->points += 1;
									bll2->points += 2;
									printf("Pridal som jeden bod gulke %d a dva body gulke %d.\n", last, first);
								}
								else if(last == 2) //prve dal 1, druhe 2
								{
									b->points += 1;
									bll->points += 2;
									printf("Pridal som jeden bod gulke %d a dva body gulke %d.\n", last, first);
								}
        printf("fokin kab %d %d\n", d, lvl->qm[d].value-5);
        st = turned = 0;
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[wwt].value-5], lvl->qm[wwt].x*FIELD_SIZE, lvl->qm[wwt].y*FIELD_SIZE);
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[d].value-5], lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE);
        //blit(lvl->bmp, screen, 0, 0, 0, 0, 800,600);
        lvl->qm[d].flip = 1;
        lvl->qm[d].done = 1;
        lvl->qm[wwt].done = 1;
        play_sample(smp_symbol, 255, 128, 1000, FALSE);
       }
       else if(wwt != d)
       {
        st = turned = 0;
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[d].value-10], lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE);
        //blit(lvl->bmp, screen, 0, 0, 0, 0, 800,600);
        
        printf("p:%d, %d", d, wwt);
        flag = 1;
        
        gd = d;
        gwwt = wwt;
        play_sample(smp_symbol, 255, 128, 1000, FALSE);
        install_int(smth, 500);
       }     
      }
      break;               
     }      
    }
    b->vx *= -1;
    key[KEY_LEFT] = FALSE;      
   }
   
   
   if(a2 == makecol(c, c, c))
   {
    for(d = 0; d < b->qma*2; d++)
    {
     
     if(lvl->qm[d].x-1 == (int)((b->x+b->vx)/FIELD_SIZE) && lvl->qm[d].y == (int)((b->y+b->vy)/FIELD_SIZE) && lvl->qm[d].done == 0)
     {
      if(st == 0)
      {
							if(b == bll)
								first = 1;
							else if(b == bll2)
							 first = 2;
       turned = lvl->qm[d].value;
       wwt = d;
       st++;
       
       printf("<<%d %d %d>>",turned, wwt, st);
       
       lvl->qm[d].flip = 1;
      
       blit(symbol_brick[lvl->qm[d].value-10], lvl->bmp, 0, 0, lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE, FIELD_SIZE, FIELD_SIZE);
        play_sample(smp_symbol, 255, 128, 1000, FALSE);
      } 
      else if(st == 1)
      {
       if(turned == lvl->qm[d].value && wwt != d)
       {
								if(b == bll)
									last = 1;
								else if(b == bll2)
								 last = 2;
								if(first == last) //prve dal ten isty co druhe
								{
									b->points += 3;
									printf("Pridal som tri body gulke %d.\n", last);
								}
								else if(last == 1) //prve dal 2, druhe 1
								{
									b->points += 1;
									bll2->points += 2;
									printf("Pridal som jeden bod gulke %d a dva body gulke %d.\n", last, first);
								}
								else if(last == 2) //prve dal 1, druhe 2
								{
									b->points += 1;
									bll->points += 2;
									printf("Pridal som jeden bod gulke %d a dva body gulke %d.\n", last, first);
								}
        printf("fokin kab %d %d\n", d, lvl->qm[d].value-5);
        st = turned = 0;
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[wwt].value-5], lvl->qm[wwt].x*FIELD_SIZE, lvl->qm[wwt].y*FIELD_SIZE);
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[d].value-5], lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE);
        //blit(lvl->bmp, screen, 0, 0, 0, 0, 800,600);
        lvl->qm[d].flip = 1;
        lvl->qm[d].done = 1;
        lvl->qm[wwt].done = 1;
        play_sample(smp_symbol, 255, 128, 1000, FALSE);
       }
       else if(wwt != d)
       {
        st = turned = 0;
        draw_sprite(lvl->bmp, symbol_brick[lvl->qm[d].value-10], lvl->qm[d].x*FIELD_SIZE, lvl->qm[d].y*FIELD_SIZE);
        //blit(lvl->bmp, screen, 0, 0, 0, 0, 800,600);
        
        printf("p:%d, %d", d, wwt);
        flag = 1;
        
        gd = d;
        gwwt = wwt;
        play_sample(smp_symbol, 255, 128, 1000, FALSE);
        install_int(smth, 500);
       }     
      }
      break;               
     }      
    }
    b->vx *= -1;
    key[KEY_RIGHT] = FALSE;      
   }  
  }  
 }
 /*if(getpixel(b->alpha, (b->x+b->vx+b->bmp->w/2) / FIELD_SIZE, (b->y+b->vy) / FIELD_SIZE) == 0xffffff && !key[KEY_DOWN])
    b->vy *= -1;
 if(getpixel(b->alpha, (b->x+b->vx+b->bmp->w/2) / FIELD_SIZE, (b->y+b->vy+b->bmp->h) / FIELD_SIZE) == 0xffffff && !key[KEY_UP])
    b->vy *= -1;
 if(getpixel(b->alpha, (b->x+b->vx) / FIELD_SIZE, (b->y+b->vy+b->bmp->h) / FIELD_SIZE) == 0xffffff && !key[KEY_RIGHT])
  {
    b->vx *= -1;
  }
  if(getpixel(b->alpha, (b->x+b->vx+b->bmp->w) / FIELD_SIZE, (b->y+b->vy+b->bmp->h) / FIELD_SIZE) == 0xffffff && !key[KEY_LEFT])
  {
    b->vx *= -1;
  }*/
 
 return 1;    
}



int bounce_balls(BALL *b1, BALL *b2)
{
 float tempvx, tempvy;
 float tx = abs(b1->x - b2->x);
 float ty = abs(b1->y - b2->y);
 float c = sqrt((tx*tx) + (ty*ty));
 if(c < 30)
 {
  tempvx = b1->vx;
  tempvy = b1->vy;
  b1->vx = b2->vx;
  b1->vy = b2->vy;
  b2->vx = tempvx;
  b2->vy = tempvy;
 }
 return 1;
}

int draw_ball(BALL *b, BITMAP *bmp, int splitscreen, int s)
{
 if(splitscreen == 0)
  draw_sprite(bmp, b->bmp, b->x-(float)drawx1, b->y-(float)drawy1);
 else
 {
  if(b == bll)
  {
   if(s == 1)
    draw_sprite(bmp, b->bmp, b->x-(float)drawx1, b->y-(float)drawy1);
   else
    draw_sprite(bmp, b->bmp, b->x-(float)drawx2, b->y-(float)drawy2);
  }
  else
  {
   if(s == 1)
    draw_sprite(bmp, b->bmp, b->x-(float)drawx2, b->y-(float)drawy2);
   else
    draw_sprite(bmp, b->bmp, b->x-(float)drawx1, b->y-(float)drawy1);
  }
 }
 return 1;    
}

int fake_wsad()
{
 printf("WSAD: %d%d%d%d\n", bll2_is_up, bll2_is_down, bll2_is_left, bll2_is_right);
 if(bll2_is_up == 1)
  key[KEY_W] = TRUE;
 else
  key[KEY_W] = FALSE;
  
 if(bll2_is_down == 1)
  key[KEY_S] = TRUE;
 else
  key[KEY_S] = FALSE;
  
 if(bll2_is_left == 1)
  key[KEY_A] = TRUE;
 else
  key[KEY_A] = FALSE;
  
 if(bll2_is_right == 1)
  key[KEY_D] = TRUE;
 else
  key[KEY_D] = FALSE;
}

int manage_my_ball()
{
 if(key[KEY_UP])
  bll2_is_up = 48 + 1;
 else
  bll2_is_up = 48 + 0;
  
 if(key[KEY_DOWN])
  bll2_is_down = 48 + 1;
 else
  bll2_is_down = 48 + 0;
  
 if(key[KEY_LEFT])
  bll2_is_left = 48 + 1;
 else
  bll2_is_left = 48 + 0;
  
 if(key[KEY_RIGHT])
  bll2_is_right = 48 + 1;
 else
  bll2_is_right = 48 + 0;
}

int manage_remote_ball(BALL *b, BITMAP *bmp)
{
	draw_ball(b, bmp, 0, 1);
	return 1;
}

int manage_ball(BALL *b, BITMAP *bmp, BITMAP *bmp2, int splitscreen)
{
 if(mode == 20)
 {
  get_input_keyboard(b, 5);
 }
 else if(mode == 19)
 {
  if(b == bll)
   get_input_keyboard(b, 0);
  else 
   get_input_keyboard(b, 1);
 }
 else
 {
  if(splitscreen == 1)
  {
   if(b == bll)
    get_input_keyboard(b, 0);
   else 
    get_input_keyboard(b, 1);
  }
  else if(b == bll)
   get_input_keyboard(b, 0);
 }
 
  
 //get_input_mouse(b);
 
 move_ya_body(b);
 
 draw_ball(b, bmp, splitscreen, 1);
 if(bmp2 != NULL)
  draw_ball(b, bmp2, splitscreen, 2);
 int i, j = 0;
 for(i = 0; i < lvl->qma*2; i++)
 {
  if(lvl->qm[i].done)
   j++;
 }
 if(j == lvl->qma*2)
 {
  draw_sprite(lvl->bmp, endlevel, lvl->elx*FIELD_SIZE, lvl->ely*FIELD_SIZE);
  lvl->canend = 1;
 }
 
 return 1; 
}

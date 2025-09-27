#include "levelbrowser.h"

typedef struct _ipbox
{
 char ip[100];
 int cur;
 int x, y;       
}IPBOX;

IPBOX *init_ipbox(int x, int y)
{
 IPBOX *box;
 box = (IPBOX*)malloc(sizeof(IPBOX));
 
 box->x = x;
 box->y = y;
 box->cur = 0;
 
 return box;      
}

int manage_input(IPBOX *box)
{
 if(box->cur < 15)
 {
 if(key[KEY_0_PAD])
 {
  box->ip[box->cur] = '0';
  box->cur++;
  key[KEY_0_PAD] = FALSE;               
 } 
  if(key[KEY_1_PAD])
 {
  box->ip[box->cur] = '1';
  box->cur++;
  key[KEY_1_PAD] = FALSE;               
 }
  if(key[KEY_2_PAD])
 {
  box->ip[box->cur] = '2';
  box->cur++;
  key[KEY_2_PAD] = FALSE;               
 }
  if(key[KEY_3_PAD])
 {
  box->ip[box->cur] = '3';
  box->cur++;
  key[KEY_3_PAD] = FALSE;               
 }
  if(key[KEY_4_PAD])
 {
  box->ip[box->cur] = '4';
  box->cur++;
  key[KEY_4_PAD] = FALSE;               
 }
  if(key[KEY_5_PAD])
 {
  box->ip[box->cur] = '5';
  box->cur++;
  key[KEY_5_PAD] = FALSE;               
 }
  if(key[KEY_6_PAD])
 {
  box->ip[box->cur] = '6';
  box->cur++;
  key[KEY_6_PAD] = FALSE;               
 }
  if(key[KEY_7_PAD])
 {
  box->ip[box->cur] = '7';
  box->cur++;
  key[KEY_7_PAD] = FALSE;               
 }
  if(key[KEY_8_PAD])
 {
  box->ip[box->cur] = '8';
  box->cur++;
  key[KEY_8_PAD] = FALSE;               
 }
  if(key[KEY_9_PAD])
 {
  box->ip[box->cur] = '9';
  box->cur++;
  key[KEY_9_PAD] = FALSE;               
 }   

 if(key[KEY_STOP])
 {
  box->ip[box->cur] = '.';
  box->cur++;
  key[KEY_STOP] = FALSE;               
 }
}
 
  if(key[KEY_BACKSPACE] && box->cur > 0)
 {
  box->ip[box->cur-1] = '\0';
  box->cur--;
  key[KEY_BACKSPACE] = FALSE;               
 }
 
 return 1;
}

int draw_ipbox(BITMAP *bmp, IPBOX *box)
{
 write_by_hand(bmp, box->ip, box->x, box->y);
 manage_input(box);
    
 return 1;    
}

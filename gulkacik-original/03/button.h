//butty just moooove yaaa bodyyyyy     ~~~
#include "engine.h"



//spravene buttonu
BUTTON* init_button(int x, int y, int w, int h, char *text, int font_height ,BITMAP *bmp, int light_on, int switch_on)
{
  //registracia noveho a alokacia ;)
  BUTTON *btn;
  btn = (BUTTON*)malloc(sizeof(BUTTON));
  
  //kopirovanie udajov
  btn->x = x;
  btn->y = y;
  btn->w = w;
  btn->h = h;        
  
  btn->text = text;
  btn->font_height = font_height;
  
  btn->light_on = light_on;
  btn->switch_on = switch_on;
  btn->visible = 1;
  
  btn->bmp = create_bitmap(btn->w,btn->h);
  
  if(bmp == NULL){    //ked nieje bitmapa
    clear_to_color(btn->bmp,0);
  }
  else {  //ked je
    blit(bmp,btn->bmp,0,0,0,0,btn->w,btn->h);
  }
  
  return btn;
}


//priradene buttona k nejakemu oknu
int stick_button_to_window(WIND *wnd, BUTTON *btn)
{
  btn->nextbutton = wnd->btns;
  wnd->btns = btn;
  wnd->btn_amount+=1;
  //wnd->btns->nextbutton = NULL;
  return 1;    
}


//vykreslenie vsetkych buttnov nejakeho okna na nejaku bitmapu!!! bwahahaha :D
int draw_buttons(WIND *wnd,BITMAP *bmp)
{
  int y, x, loop;
  loop = 0;
  BUTTON *butty;
  butty = (BUTTON*)malloc(sizeof(BUTTON));
  
  butty = wnd->btns;
  while(butty != NULL || loop != wnd->btn_amount)
  {
  
    loop++;
    //nastavenie velkosti fonta
    alfont_set_font_size(larabie,butty->font_height);
    //nakreslenie toho hlavneho obdlznika
    
    //rectfill(bmp,butty->x + wnd->x,butty->y + wnd->y,butty->x + butty->w + wnd->x,butty->y+butty->h + wnd->y,makecol(0,0,0));
    
    if(butty->visible)
    {
    blit(butty->bmp,bmp, 0,0, butty->x + wnd->x,butty->y + wnd->y, butty->w,butty->h);
    if(butty->switch_on)
    {
     rect(bmp,butty->x + wnd->x, butty->y + wnd->y, wnd->x+butty->x+butty->w,wnd->y+butty->y+butty->h,0xffffff);
     rect(bmp,butty->x + wnd->x+1, butty->y + wnd->y+1, wnd->x+butty->x+butty->w-1,wnd->y+butty->y+butty->h-1,0xaaaaaa);
     rect(bmp,butty->x + wnd->x+2, butty->y + wnd->y+2, wnd->x+butty->x+butty->w-2,wnd->y+butty->y+butty->h-2,0x555555);
    }
    
    butty->re = 255;
    butty->gr = 170;
    butty->bl = 0;
    //trapny if mouse over button
    if(mouse_x > butty->x + wnd->x && mouse_x < butty->x + butty->w + wnd->x && mouse_y > butty->y + wnd->y && mouse_y < butty->y+butty->h + wnd->y && wnd->active)
    {
      //pokial sa kliklo, KLIKLO, na ten button, co sa ma stat
      if(mouse_b & 1)
      {
        alfont_textprintf_centre_aa(bmp,larabie,butty->x + (butty->w/2)+wnd->x + 1,butty->y + wnd->y + 1,makecol(255,170,0),"%s",butty->text);
        butty->proc();
      }
      else alfont_textprintf_centre_aa(bmp,larabie,butty->x + (butty->w/2)+wnd->x,butty->y + wnd->y,makecol(255,170,0),"%s",butty->text);
      
      for(y = butty->y + wnd->y;y < butty->y + wnd->y + butty->h + 1;y++)
      {
        butty->re = 255;
        butty->gr = 170;
        butty->bl = 0;
        if(getpixel(bmp,butty->x + wnd->x-1,y) == makecol(100,100,100) && butty->light_on == 1)
        {
          for(x = butty->x + wnd->x;x > butty->x + wnd->x-butty->light;x--)
          {
            butty->re+=(float)(100-255)/butty->light;//(255-80)/100;
            butty->gr+=(float)(100-170)/butty->light;//(170-80)/100;
            butty->bl+=(float)(100-0)/butty->light;//(0-80)/100;
            if(butty->re > 255)butty->re=255;    if(butty->gr > 255)butty->gr=255;    if(butty->bl > 255)butty->bl=255;
            if(butty->re < 0)butty->re=0;    if(butty->gr < 0)butty->gr=0;    if(butty->bl < 0)butty->bl=0;
            putpixel(bmp,x-1,y,makecol((int)butty->re,(int)butty->gr,(int)butty->bl));      
          }   
          butty->re = 255;
          butty->gr = 170;
          butty->bl = 0;
          for(x = butty->x + wnd->x;x < butty->x + wnd->x+butty->light;x++)
          {
            butty->re+=(float)(100-255)/butty->light;//(255-80)/100;
            butty->gr+=(float)(100-170)/butty->light;//(170-80)/100;
            butty->bl+=(float)(100-0)/butty->light;//(0-80)/100;
            if(butty->re > 255)butty->re=255;    if(butty->gr > 255)butty->gr=255;    if(butty->bl > 255)butty->bl=255;
            if(butty->re < 0)butty->re=0;    if(butty->gr < 0)butty->gr=0;    if(butty->bl < 0)butty->bl=0;
            putpixel(bmp,x+butty->w+1,y,makecol((int)butty->re,(int)butty->gr,(int)butty->bl));      
          }//for x  
        }//if getpixel
        //else alfont_textprintf_centre_aa(bmp,larabie,butty->x + (butty->w/2)+wnd->x,butty->y + wnd->y,makecol(255,255,255),"%s %d",butty->text);
      }//for y
      if(butty->light < (butty->w/6)*2)butty->light+=5.2;
      //lightvect+=0.2;          
    }//if mouse over button
    else//pisanie toho fontu
    {
      if(butty->switch_on == 0)
      alfont_textprintf_centre_aa(bmp,larabie,butty->x + (butty->w/2)+wnd->x,butty->y + wnd->y,makecol(255,255,255),"%s",butty->text);
      else       alfont_textprintf_centre_aa(bmp,larabie,butty->x + (butty->w/2)+wnd->x,butty->y + wnd->y,makecol(255,170,0),"%s",butty->text);
     
      butty->light = 0.0;
    }
    //prejdenie na noveho butty
    butty = butty->nextbutton;
  }//while
}//if butty je visible
  free(butty);
  return 1;    
}


int set_button_action(BUTTON *btn, void(*proc)())
{
  btn->proc = proc;
  return 1;   
}

int ci;

int stick_unit_to_combo_list(CB_LIST *lst, CB_UNIT *unt)
{
 lst->units[lst->cpoio]->value = unt->value;
 lst->units[lst->cpoio]->text = unt->text;
 lst->cpoio++;
    
 return 1;
}

CB_UNIT* init_unit(char *text, int value)
{
 CB_UNIT *unt;
 
 unt = (CB_UNIT*)malloc(sizeof(CB_UNIT)); 
 
 
 unt->text = text;
 unt->value = value;

 return unt;      
}

CB_LIST* init_list(int x, int y)
{
 int xx;
 float rgb;
 rgb = 255.0;
 CB_LIST *lst;
 lst = (CB_LIST*)malloc(sizeof(CB_LIST));         
 lst ->cpoio    = 0;
 lst ->cpoi     = 0;
 lst ->x        = x;
 lst ->y        = y;
 lst ->rolled   = 0;
 lst ->slidebar = 0;
 
 lst->grad = create_bitmap(20,12);
 for(xx = 0;xx < lst->grad->w;xx++)
 {
  line(lst->grad,xx,0,xx,12,makecol(rgb,rgb,rgb));
  rgb-=(255/20);      
 }

 int i;
 
 for(i = 0;i < 25;i++)
 {
  lst->units[i] = (CB_UNIT*)malloc(sizeof(CB_UNIT));       
 }
 
 return lst;
}


bool draw_list(BITMAP *bmp,CB_LIST *lst, WIND *wnd)
{
  //if(mir(lst->x+wnd->x,lst->y+wnd->y,lst->x+wnd->x+50,lst->y+wnd->y+15+(lst->cpoio*12),1) == 0)lst->rolled = 0;
  
  //draw of skeleton
  alfont_set_font_size(larabie,20);
  rectfill(bmp,lst->x+wnd->x, lst->y+wnd->y, lst->x+wnd->x+50, lst->y+wnd->y + 15,0); 
  line(bmp,lst->x+wnd->x+35,lst->y+wnd->y,lst->x+wnd->x+35,lst->y+wnd->y+15,makecol(100,100,100));
  
  //cool v butty
  if(mir(lst->x+wnd->x+40,lst->y+wnd->y,lst->x+wnd->x+50,lst->y+wnd->y+15,1))
  {
   alfont_textprintf_aa(bmp,larabie,lst->x+wnd->x+40,lst->y+wnd->y-3,0xff9600,"v");
   lst->rolled = 1;
   
   while(mouse_b & 1)
   {
    vsync(); 
    rectfill(screen,lst->x+36+wnd->x,lst->y+wnd->y,lst->x+wnd->x+50,lst->y+wnd->y+15,0); 
    alfont_textprintf_aa(screen,larabie,lst->x+wnd->x+40,lst->y+wnd->y-3,0xff9600,"v");
   }
   //mouse_b = 0;
   rest(100);
  }
  else alfont_textprintf_aa(bmp,larabie,lst->x+wnd->x+39,lst->y+wnd->y-4,0xffffff,"v");
  
  //chosen one :D
  alfont_set_font_size(larabie,17);
  alfont_textprintf_right_aa(bmp,larabie,lst->x+wnd->x+34,lst->y+wnd->y,0xff9600,"%s",lst->units[lst->cpoi]->text);
  
  alfont_set_font_size(larabie,16);
  
  //drawing of rolka
  if(lst->rolled == 1)
  {
   //more than size
   if(lst->cpoio > 6)
   {
    if(key[KEY_PLUS_PAD]  && lst->slidebar < lst->cpoio-6){lst->slidebar++;key[KEY_PLUS_PAD] = FALSE;}
    if(key[KEY_MINUS_PAD] && lst->slidebar > 0){lst->slidebar--;key[KEY_MINUS_PAD] = FALSE;}
    rectfill(bmp,lst->x+wnd->x+35,lst->y+wnd->y+15,lst->x+wnd->x+50,lst->y+wnd->y+15+72,0);
    
    //upper arrow
    if(mir(lst->x+wnd->x+35,lst->y+wnd->y+15,lst->x+wnd->x+50,lst->y+wnd->y+30,1))
    {
     line(bmp,lst->x+wnd->x+37+2,lst->y+wnd->y+28-1,lst->x+wnd->x+46+2,lst->y+wnd->y+28-1,0xffffff);                                                                              
     line(bmp,lst->x+wnd->x+38+2,lst->y+wnd->y+27-1,lst->x+wnd->x+45+2,lst->y+wnd->y+27-1,0xdddddd);                                                                              
     line(bmp,lst->x+wnd->x+39+2,lst->y+wnd->y+26-1,lst->x+wnd->x+44+2,lst->y+wnd->y+26-1,0xbbbbbb);                                                                              
     line(bmp,lst->x+wnd->x+40+2,lst->y+wnd->y+25-1,lst->x+wnd->x+43+2,lst->y+wnd->y+25-1,0x999999);
     line(bmp,lst->x+wnd->x+41+2,lst->y+wnd->y+24-1,lst->x+wnd->x+42+2,lst->y+wnd->y+24-1,0x777777);
     if(lst->slidebar > 0)
     {
      lst->slidebar--;
      rest(75);
      while(mouse_b & 1)
      {
       //rest(75);
       mouse_b = 0;
       if(lst->slidebar > 0)lst->slidebar--;              
      }
     }
    }
    else
    {
     line(bmp,lst->x+wnd->x+37+1,lst->y+wnd->y+28-2,lst->x+wnd->x+46+1,lst->y+wnd->y+28-2,0xffffff);                                                                              
     line(bmp,lst->x+wnd->x+38+1,lst->y+wnd->y+27-2,lst->x+wnd->x+45+1,lst->y+wnd->y+27-2,0xdddddd);                                                                              
     line(bmp,lst->x+wnd->x+39+1,lst->y+wnd->y+26-2,lst->x+wnd->x+44+1,lst->y+wnd->y+26-2,0xbbbbbb);                                                                              
     line(bmp,lst->x+wnd->x+40+1,lst->y+wnd->y+25-2,lst->x+wnd->x+43+1,lst->y+wnd->y+25-2,0x999999);
     line(bmp,lst->x+wnd->x+41+1,lst->y+wnd->y+24-2,lst->x+wnd->x+42+1,lst->y+wnd->y+24-2,0x777777);
    }
    
    //lower arrow
    if(mir(lst->x+wnd->x+35,lst->y+wnd->y+72,lst->x+wnd->x+50,lst->y+wnd->y+72+15,1))
    {
     line(bmp,lst->x+wnd->x+37+2,lst->y+wnd->y+77-1+4,lst->x+wnd->x+46+2,lst->y+wnd->y+77-1+4,0xffffff);                                                                              
     line(bmp,lst->x+wnd->x+38+2,lst->y+wnd->y+78-1+4,lst->x+wnd->x+45+2,lst->y+wnd->y+78-1+4,0xdddddd);                                                                              
     line(bmp,lst->x+wnd->x+39+2,lst->y+wnd->y+79-1+4,lst->x+wnd->x+44+2,lst->y+wnd->y+79-1+4,0xbbbbbb);                                                                              
     line(bmp,lst->x+wnd->x+40+2,lst->y+wnd->y+80-1+4,lst->x+wnd->x+43+2,lst->y+wnd->y+80-1+4,0x999999);
     line(bmp,lst->x+wnd->x+41+2,lst->y+wnd->y+81-1+4,lst->x+wnd->x+42+2,lst->y+wnd->y+81-1+4,0x777777);
     if(lst->slidebar < lst->cpoio-6)
     {
      lst->slidebar++;
      rest(90);
      while(mouse_b & 1)
      {
       //rest(90);
       mouse_b = 0;
       if(lst->slidebar < lst->cpoio-6)lst->slidebar++;              
      }
     }
    }
    else
    {
     line(bmp,lst->x+wnd->x+37+1,lst->y+wnd->y+77-2+4,lst->x+wnd->x+46+1,lst->y+wnd->y+77-2+4,0xffffff);                                                                              
     line(bmp,lst->x+wnd->x+38+1,lst->y+wnd->y+78-2+4,lst->x+wnd->x+45+1,lst->y+wnd->y+78-2+4,0xdddddd);                                                                              
     line(bmp,lst->x+wnd->x+39+1,lst->y+wnd->y+79-2+4,lst->x+wnd->x+44+1,lst->y+wnd->y+79-2+4,0xbbbbbb);                                                                              
     line(bmp,lst->x+wnd->x+40+1,lst->y+wnd->y+80-2+4,lst->x+wnd->x+43+1,lst->y+wnd->y+80-2+4,0x999999);
     line(bmp,lst->x+wnd->x+41+1,lst->y+wnd->y+81-2+4,lst->x+wnd->x+42+1,lst->y+wnd->y+81-2+4,0x777777);
    }
    
    rectfill(bmp,lst->x+wnd->x,lst->y+wnd->y + 15,wnd->x+lst->x+35,lst->y+wnd->y + 15 + (6*12),0);
    for(ci = lst->slidebar;ci < lst->slidebar+6;ci++)
    {
     if(mir(lst->x+wnd->x, lst->y+wnd->y+15+((ci-lst->slidebar)*12), lst->x+wnd->x+35, lst->y+wnd->y+15+((ci-lst->slidebar)*12)+11,0))
     {
      draw_sprite(bmp,lst->grad,lst->x+wnd->x,lst->y+15+wnd->y + ((ci-lst->slidebar)*12));
      rect(bmp,lst->x+wnd->x,lst->y+wnd->y+15+((ci-lst->slidebar)*12),lst->x+wnd->x+35,lst->y+wnd->y+15+((ci-lst->slidebar)*12)+12,0xffffff); 
      alfont_textprintf_right_aa(bmp,larabie,lst->x+wnd->x+35,lst->y+wnd->y+15+((ci-lst->slidebar)*12)-1,0xff9600,"%s",lst->units[ci]->text);       
      if(mouse_b & 1)
      {
       lst->cpoi = ci;
       lst->rolled = 0;
       rest(80);
      }// if mouse
     }//if mir 
     else
     {
      alfont_textprintf_right_aa(bmp,larabie,lst->x+wnd->x+35,lst->y+wnd->y+15+((ci-lst->slidebar)*12)-1,0xffffff,"%s",lst->units[ci]->text);       
     }//else mir     
    }//for ci     
   }//if > 6
   else //if =< 6
   {
    //if(mir(lst->x+wnd->x,lst->y+wnd->y,lst->x+wnd->x+50,lst->y+wnd->y+15+(lst->cpoio*12),1) == 0)lst->rolled = 0;
   
    rectfill(bmp,lst->x+wnd->x,lst->y+wnd->y + 15,wnd->x+lst->x+50,lst->y+wnd->y + 15 + (lst->cpoio*12),0);    
   
    for(ci = 0;ci < lst->cpoio;ci++)
    {
     if(mir(lst->x+wnd->x, lst->y+wnd->y+15+(ci*12), lst->x+wnd->x+50, lst->y+wnd->y+15+(ci*12)+11,0))
     {
      draw_sprite(bmp,lst->grad,lst->x+wnd->x,lst->y+15+wnd->y + (ci*12));
      rect(bmp,lst->x+wnd->x,lst->y+wnd->y+15+((ci)*12),lst->x+wnd->x+50,lst->y+wnd->y+15+((ci)*12)+12,0xffffff); 
      alfont_textprintf_right_aa(bmp,larabie,lst->x+wnd->x+50,lst->y+wnd->y+15+(ci*12)-1,0xff9600,"%s",lst->units[ci]->text);       
      if(mouse_b & 1)
      {
       lst->cpoi = ci;
       lst->rolled = 0;
       rest(80);
      }
     }
     else
     alfont_textprintf_right_aa(bmp,larabie,lst->x+wnd->x+50,lst->y+wnd->y+15+(ci*12)-1,0xffffff,"%s",lst->units[ci]->text);       
    }
   
   }
   
                  
  }
  
  return true; 
}



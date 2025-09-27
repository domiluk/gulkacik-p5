//features list
// small and big Alpha
// Del, BCKSPC, Space, Enter
// Numerical characters
// vertical scroll

//todo list
// Special Characters


int insert_etwas = 0;
int mzlog = 0;
const char endchar = '\0';
TEXTBOX *init_textbox(int x, int y, int w, int h, int ml, char *start_text)
{
 TEXTBOX *tbox;
 tbox = (TEXTBOX*)malloc(sizeof(TEXTBOX));
 tbox->x = x;
 tbox->y = y;
 tbox->w = w;
 tbox->h = h;
 tbox->fy = 3;

 //if(ml == 1)
 tbox->bmp = create_bitmap(w+1, h*5+1);
 tbox->maxchar = 512;
 if(ml == 0)tbox->maxchar = 16;
 tbox->blick = 0.0;
 tbox->multiline = ml; 
 tbox->active = 0;
 tbox->achar = 0;
 tbox->amtchar = strlen(start_text);
 strcpy(tbox->text,start_text);
 //strcat(tbox->text, endchar);
 //tbox->text[0] = 'x';
 //tbox->text[1] = '\0';

 return tbox;        
}

int i;
int l;
int move_right(TEXTBOX *tbox)
{
 int k;
 
  for(k = tbox->amtchar;k > tbox->achar;k--)
  {
   tbox->text[k] = tbox->text[k-1];
  }    
 
 return 1;
}

int manage_textbox(TEXTBOX *tbox)
{
    
 for(i = 1;i < 27;i++)
 {
  if(key[i] && tbox->amtchar < tbox->maxchar)
  {
   move_right(tbox);
   if(key[KEY_LSHIFT] || key[KEY_RSHIFT])tbox->text[tbox->achar] = i+64;
   else tbox->text[tbox->achar] = i+96;  
   tbox->achar++;
   tbox->amtchar++;
   insert_etwas = 1;
   key[i] = FALSE;        
  }
 } 
 
 for(i = 37; i < 47;i++)
 {
  if(key[i]&& tbox->amtchar < tbox->maxchar)
  {
   move_right(tbox);
   tbox->text[tbox->achar] = i+11;
   tbox->achar++;
   tbox->amtchar++;
   insert_etwas = 1;
   key[i] = FALSE;          
  }      
 }
 
 
 
  //< and ,                  
  if(key[KEY_COMMA] && tbox->amtchar < tbox->maxchar)
  {
   move_right(tbox);
   if(key[KEY_LSHIFT] || key[KEY_RSHIFT])tbox->text[tbox->achar] = '<';
   else tbox->text[tbox->achar] = ',';
   tbox->achar++;
   tbox->amtchar++;
   insert_etwas = 1;
   key[KEY_COMMA] = FALSE;                      
  }
  
  //> and .
  if(key[KEY_STOP] && tbox->amtchar < tbox->maxchar)
  {
   move_right(tbox);
   if(key[KEY_LSHIFT] || key[KEY_RSHIFT])tbox->text[tbox->achar] = '>';
   else tbox->text[tbox->achar] = '.';
   tbox->achar++;
   tbox->amtchar++;
   insert_etwas = 1;
   key[KEY_STOP] = FALSE;                 
  }
  
  //? and /
  if(key[KEY_SLASH] && tbox->amtchar < tbox->maxchar)
  {
   move_right(tbox);
   if(key[KEY_LSHIFT] || key[KEY_RSHIFT])tbox->text[tbox->achar] = '?';
   else tbox->text[tbox->achar] = '/';
   tbox->achar++;
   tbox->amtchar++;
   insert_etwas = 1;
   key[KEY_SLASH] = FALSE;                 
  }
  
  //: and ;
  if(key[KEY_SEMICOLON] && tbox->amtchar < tbox->maxchar)
  {
   move_right(tbox);
   if(key[KEY_LSHIFT] || key[KEY_RSHIFT])tbox->text[tbox->achar] = ':';
   else tbox->text[tbox->achar] = ';';
   tbox->achar++;
   tbox->amtchar++;
   insert_etwas = 1;
   key[KEY_SEMICOLON] = FALSE;                 
  }
  
  //' and "
  if(key[KEY_QUOTE] && tbox->amtchar < tbox->maxchar)
  {
   move_right(tbox);
   if(key[KEY_LSHIFT] || key[KEY_RSHIFT])tbox->text[tbox->achar] = 39;
   else tbox->text[tbox->achar] = 34;
   tbox->achar++;
   tbox->amtchar++;
   insert_etwas = 1;
   key[KEY_QUOTE] = FALSE;                 
  }
  
  //{ and [
  if(key[KEY_OPENBRACE] && tbox->amtchar < tbox->maxchar)
  {
   move_right(tbox);
   if(key[KEY_LSHIFT] || key[KEY_RSHIFT])tbox->text[tbox->achar] = '{';
   else tbox->text[tbox->achar] = '[';
   tbox->achar++;
   tbox->amtchar++;
   insert_etwas = 1;
   key[KEY_OPENBRACE] = FALSE;                        
  }
  
  //} and ]
  if(key[KEY_CLOSEBRACE] && tbox->amtchar < tbox->maxchar)
  {
   move_right(tbox);
   if(key[KEY_LSHIFT] || key[KEY_RSHIFT])tbox->text[tbox->achar] = '}';
   else tbox->text[tbox->achar] = ']';
   tbox->achar++;
   tbox->amtchar++;
   insert_etwas = 1;
   key[KEY_CLOSEBRACE] = FALSE;                        
  }
  
  //+ and =
  if(key[KEY_EQUALS] && tbox->amtchar < tbox->maxchar)
  {
   move_right(tbox);
   if(key[KEY_LSHIFT] || key[KEY_RSHIFT])tbox->text[tbox->achar] = '+';
   else tbox->text[tbox->achar] = '=';
   tbox->achar++;
   tbox->amtchar++;
   insert_etwas = 1;
   key[KEY_EQUALS] = FALSE;                        
  }
  

  
  
 if(key[KEY_RIGHT] && tbox->achar < tbox->amtchar)//to minus jedna tam je koli '\0' aby bol null terminated
 {
  tbox->achar++;
  key[KEY_RIGHT] = FALSE;                   
 }      
 
 if(key[KEY_LEFT] && tbox->achar > 0)
 {
  tbox->achar--;
  key[KEY_LEFT] = FALSE;                   
 }
 
 if(key[KEY_SPACE] && tbox->amtchar < tbox->maxchar)
 {
  move_right(tbox);
  tbox->text[tbox->achar] = ' ';
  tbox->achar++;
  tbox->amtchar++;
  key[KEY_SPACE] = FALSE;                  
 }
 
 if(key[KEY_ENTER] && tbox->multiline == 1)
 {
  move_right(tbox);
  tbox->text[tbox->achar] = '\n';
  tbox->achar++;
  tbox->amtchar++;
  key[KEY_ENTER] = FALSE;                  
 }
 
  if(key[KEY_BACKSPACE] && tbox->achar > 0)
  {
   tbox->achar--;
   for(l = tbox->achar;l < tbox->amtchar-1;l++)
   {
    tbox->text[l] = tbox->text[l+1];            
   }
   //tbox->text[tbox->amtchar] = '\0';
   tbox->amtchar--;
   key[KEY_BACKSPACE] = FALSE;             
  }
  
  if(key[KEY_DEL] && tbox->achar < tbox->amtchar)
  {
   for(l = tbox->achar;l < tbox->amtchar-1;l++)
   {
    tbox->text[l] = tbox->text[l+1];            
   }    
   tbox->text[tbox->amtchar] = '\0';               
   tbox->amtchar--;
   key[KEY_DEL] = FALSE;
  }
  
  //if(tbox->multiline == 0 && insert_etwas == 1)tbox->achar = tbox->amtchar;
  
 return 1;    
}

int k;

int draw_textbox(BITMAP *bmp, TEXTBOX *tbox, WIND *wnd)
{
 int x, y;
 char str[2];
 //rectfill(bmp, tbox->x+wnd->x, tbox->y+wnd->y, tbox->x+tbox->w+wnd->x, tbox->y+tbox->y+wnd->y, 0);
 clear_to_color(tbox->bmp, 0);
 
 alfont_set_font_size(larabie,15);
 if(tbox->multiline == 0)
 rectfill(bmp, tbox->x+wnd->x, tbox->y+wnd->y, tbox->x+tbox->w+wnd->x, tbox->y+tbox->h+wnd->y, 0);
 if(mouse_b & 1)tbox->active = 0;
 if(mir(tbox->x+wnd->x, tbox->y+wnd->y, tbox->x+tbox->w+wnd->x+15, tbox->y+tbox->h+wnd->y, 1))tbox->active = 1;
 
 if(tbox->active == 1)manage_textbox(tbox);
 
 //x = tbox->x+wnd->x+5;
 //y = tbox->y+wnd->y+5; 
 //if(tbox->multiline == 1)
 //{
 x = y = 5;
 
 if(tbox->amtchar == 0 && tbox->active)
 if(tbox->multiline == 1)
 line(tbox->bmp, x-1, y, x-1, y+14, 0xff9600);          else
    line(bmp, x-1+wnd->x+tbox->x, y+wnd->y+tbox->y-3, x-1+wnd->x+tbox->x, y+14+wnd->y+tbox->y-3, 0xff9600);
 
 if(tbox->text[0] != '\0' && tbox->text[0] != '\n')
 {
  if(tbox->multiline == 1)alfont_textprintf_aa(tbox->bmp, larabie, x, y, 0xffffff, "%c", tbox->text[0]);
   else alfont_textprintf_aa(bmp, larabie, x+wnd->x+tbox->x, y+wnd->y+tbox->y-4, 0xffffff, "%c", tbox->text[0]);
   
  str[0] = tbox->text[0];
  str[1] = '\0';
  if(tbox->amtchar == 0)rectfill(bmp, tbox->x+wnd->x, tbox->y+wnd->y, tbox->x+tbox->w+wnd->x, tbox->y+tbox->h+wnd->y, 0);
  if(tbox->achar == 0 && tbox->active && tbox->blick >= 0.5)
  {
    if(tbox->multiline == 1)
    line(tbox->bmp, x-1, y, x-1, y+14, 0xff9600);          
    else
    line(bmp, x-1+wnd->x+tbox->x, y+wnd->y+tbox->y-3, x-1+wnd->x+tbox->x, y+14+wnd->y+tbox->y-3, 0xff9600);
  }
  
  tbox->blick+=0.04;
  if(tbox->blick > 1.0)tbox->blick = 0.0;
  
  x+=alfont_text_length(larabie,str);
  for(i = 1;i<tbox->amtchar;i++)
  {
   
   if(tbox->achar == i && tbox->active && tbox->blick >= 0.5)
   {
    if(tbox->multiline == 1)
    line(tbox->bmp, x-1, y, x-1, y+14, 0xff9600);          
    else
    line(bmp, x-1+wnd->x+tbox->x, y+wnd->y+tbox->y-3, x-1+wnd->x+tbox->x, y+14+wnd->y+tbox->y-3, 0xff9600);
   }
   
   //if((x - wnd->x - tbox->x)+6 > tbox->w || tbox->text[i] == '\n')
   if((x+6 > tbox->w || tbox->text[i] == '\n') && tbox->multiline == 1)
   {
    //x = tbox->x+wnd->x+5;
    x = 5;
    y += 10;//alfont_text_heigth(larabie);
    if(tbox->text[i] == '\n')i++;
    //for(;tbox->text[i] != '\n';i++){}
   }
   
   if(y+7-tbox->fy > tbox->h/2 && insert_etwas == 1)//printf("have to scroll");//
   tbox->fy+=10;
   
   if(tbox->multiline == 1)alfont_textprintf_aa(tbox->bmp, larabie, x, y, 0xffffff, "%c", tbox->text[i]);
   else alfont_textprintf_aa(bmp, larabie, x+wnd->x+tbox->x, y+wnd->y+tbox->y-4, 0xffffff, "%c", tbox->text[i]);
   
   str[0] = tbox->text[i];
   str[1] = '\0';
   x+=alfont_text_length(larabie,str)+1;
     
  }
  
  
  if(i+1 == tbox->amtchar && tbox->active == 1 && tbox->blick >= 0.5)
  {
    if(tbox->multiline == 1)
    line(tbox->bmp, x-1, y, x-1, y+14, 0xff9600);          
    else
    line(bmp, x-1+wnd->x+tbox->x, y+wnd->y+tbox->y-3, x-1+wnd->x+tbox->x, y+14+wnd->y+tbox->y-3, 0xff9600);
  }
  if(tbox->achar+1 == tbox->amtchar && tbox->active == 1 && tbox->blick >= 0.5)
  {
    if(tbox->multiline == 1)
    line(tbox->bmp, x-1, y, x-1, y+14, 0xff9600);          
    else
    line(bmp, x-1+wnd->x+tbox->x, y+wnd->y+tbox->y-3, x-1+wnd->x+tbox->x, y+14+wnd->y+tbox->y-3, 0xff9600);
  }
  
  
 }
 else
 {
  tbox->blick+=0.04;
  if(tbox->blick > 1.0)tbox->blick = 0.0;
  
  if(tbox->active == 1 && tbox->blick >= 0.5)
  {
   if(tbox->multiline == 1)
   line(tbox->bmp, x-1, y, x-1, y+14, 0xff9600);          
   else
   line(bmp, x-1+wnd->x+tbox->x, y+wnd->y+tbox->y-3, x-1+wnd->x+tbox->x, y+14+wnd->y+tbox->y-3, 0xff9600);
  }
 }
 
 if(tbox->amtchar <= 0)clear_to_color(tbox->bmp, 0);//rectfill(bmp, tbox->x+wnd->x, tbox->y+wnd->y, tbox->x+tbox->w+wnd->x, tbox->y+tbox->y+wnd->y, 0);
 
 if(tbox->multiline == 1)blit(tbox->bmp, bmp, 0, tbox->fy, wnd->x+tbox->x, wnd->y+tbox->y, tbox->w+1, tbox->h/2 + 1);
 //else blit(tbox->bmp, bmp, )
 
 if(key[KEY_PLUS_PAD]) //&& tbox->fy + tbox->h/2 < tbox->h*5);
 {
  key[KEY_PLUS_PAD] = FALSE;
  if((tbox->fy + (tbox->h/2)) < tbox->h*5)tbox->fy+=3;
  //printf("%d\n",tbox->fy);
 }
 
 if(key[KEY_MINUS_PAD])// && tbox->fy > 0);
 {
  key[KEY_MINUS_PAD] = FALSE;
  if(tbox->fy > 3)tbox->fy-=3;
 }/**/
 
 
 //rectfill(bmp, tbox->x+wnd->x+wnd->w, tbox->y+wnd->y, tbox->x+tbox->w+wnd->x-15, tbox->y+(tbox->h/2)+wnd->y, 0);
 if(tbox->multiline == 1)
 {
 rectfill(bmp, tbox->x+tbox->w+wnd->x, tbox->y+wnd->y, tbox->x+tbox->w+wnd->x+15,tbox->y+wnd->y+tbox->h/2,0);
 if(mir(tbox->x+tbox->w+wnd->x, tbox->y+wnd->y, tbox->x+tbox->w+wnd->x+15,tbox->y+wnd->y+15,1))
 {
   line(bmp,tbox->x+tbox->w+wnd->x+4+2,tbox->y+wnd->y+0-1+5,
            tbox->x+tbox->w+wnd->x+5+2,tbox->y+wnd->y+0-1+5,0x777777);                                                                              
   
   line(bmp,tbox->x+tbox->w+wnd->x+3+2,tbox->y+wnd->y+1-1+5,
            tbox->x+tbox->w+wnd->x+6+2,tbox->y+wnd->y+1-1+5,0x999999);                                                                              
   
   line(bmp,tbox->x+tbox->w+wnd->x+2+2,tbox->y+wnd->y+2-1+5,
            tbox->x+tbox->w+wnd->x+7+2,tbox->y+wnd->y+2-1+5,0xbbbbbb);                                                                              
   
   line(bmp,tbox->x+tbox->w+wnd->x+1+2,tbox->y+wnd->y+3-1+5,
            tbox->x+tbox->w+wnd->x+8+2,tbox->y+wnd->y+3-1+5,0xdddddd);
   
   line(bmp,tbox->x+tbox->w+wnd->x+0+2,tbox->y+wnd->y+4-1+5,
            tbox->x+tbox->w+wnd->x+9+2,tbox->y+wnd->y+4-1+5,0xffffff);
            
            if(tbox->fy > 3)tbox->fy-=3;
            rest(50);
 }
 else
 {
  //putpixel(bmp, tbox->x+tbox->w+wnd->x+4+1,tbox->y+wnd->y+0+2,0xffffff);
  line(bmp,tbox->x+tbox->w+wnd->x+4+1,tbox->y+wnd->y+0-2+5,
           tbox->x+tbox->w+wnd->x+5+1,tbox->y+wnd->y+0-2+5,0x777777);                                                                              
  
  line(bmp,tbox->x+tbox->w+wnd->x+3+1,tbox->y+wnd->y+1-2+5,
           tbox->x+tbox->w+wnd->x+6+1,tbox->y+wnd->y+1-2+5,0x999999);                                                                              
  
  line(bmp,tbox->x+tbox->w+wnd->x+2+1,tbox->y+wnd->y+2-2+5,
           tbox->x+tbox->w+wnd->x+7+1,tbox->y+wnd->y+2-2+5,0xbbbbbb);                                                                              
  
  line(bmp,tbox->x+tbox->w+wnd->x+1+1,tbox->y+wnd->y+3-2+5,
           tbox->x+tbox->w+wnd->x+8+1,tbox->y+wnd->y+3-2+5,0xdddddd);
  
  line(bmp,tbox->x+tbox->w+wnd->x+0+1,tbox->y+wnd->y+4-2+5,
           tbox->x+tbox->w+wnd->x+9+1,tbox->y+wnd->y+4-2+5,0xffffff);
 } 
 /////////////////////down//////////////////////////////////////////////////////
 if(mir(tbox->x+wnd->x+tbox->w, tbox->y+wnd->y+wnd->h/2 - 20, 
        tbox->x+wnd->x+tbox->w + 15, tbox->y+wnd->y+wnd->h/2-5, 1))
 {
   line(bmp,tbox->x+tbox->w+wnd->x+4+2,tbox->y+wnd->y+4-6+(tbox->h/2),
            tbox->x+tbox->w+wnd->x+5+2,tbox->y+wnd->y+4-6+(tbox->h/2),0xffffff);                                                                              
   
   line(bmp,tbox->x+tbox->w+wnd->x+3+2,tbox->y+wnd->y+3-6+(tbox->h/2),
            tbox->x+tbox->w+wnd->x+6+2,tbox->y+wnd->y+3-6+(tbox->h/2),0xdddddd);                                                                              
   
   line(bmp,tbox->x+tbox->w+wnd->x+2+2,tbox->y+wnd->y+2-6+(tbox->h/2),
            tbox->x+tbox->w+wnd->x+7+2,tbox->y+wnd->y+2-6+(tbox->h/2),0xbbbbbb);                                                                              
   
   line(bmp,tbox->x+tbox->w+wnd->x+1+2,tbox->y+wnd->y+1-6+(tbox->h/2),
            tbox->x+tbox->w+wnd->x+8+2,tbox->y+wnd->y+1-6+(tbox->h/2),0x999999);
   
   line(bmp,tbox->x+tbox->w+wnd->x+0+2,tbox->y+wnd->y+0-6+(tbox->h/2),
            tbox->x+tbox->w+wnd->x+9+2,tbox->y+wnd->y+0-6+(tbox->h/2),0x777777);       
 if((tbox->fy + (tbox->h/2)) < tbox->h*5)tbox->fy+=3;
 rest(50);
 }                  
 else{
     line(bmp,tbox->x+tbox->w+wnd->x+4+1,tbox->y+wnd->y+4-7+(tbox->h/2),
              tbox->x+tbox->w+wnd->x+5+1,tbox->y+wnd->y+4-7+(tbox->h/2),0xffffff);                                                                              
   
     line(bmp,tbox->x+tbox->w+wnd->x+3+1,tbox->y+wnd->y+3-7+(tbox->h/2),
              tbox->x+tbox->w+wnd->x+6+1,tbox->y+wnd->y+3-7+(tbox->h/2),0xdddddd);                                                                              
   
     line(bmp,tbox->x+tbox->w+wnd->x+2+1,tbox->y+wnd->y+2-7+(tbox->h/2),
              tbox->x+tbox->w+wnd->x+7+1,tbox->y+wnd->y+2-7+(tbox->h/2),0xbbbbbb);                                                                              
   
     line(bmp,tbox->x+tbox->w+wnd->x+1+1,tbox->y+wnd->y+1-7+(tbox->h/2),
              tbox->x+tbox->w+wnd->x+8+1,tbox->y+wnd->y+1-7+(tbox->h/2),0x999999);
   
     line(bmp,tbox->x+tbox->w+wnd->x+0+1,tbox->y+wnd->y+0-7+(tbox->h/2),
              tbox->x+tbox->w+wnd->x+9+1,tbox->y+wnd->y+0-7+(tbox->h/2),0x777777);       
   }            
 
 if(tbox->active == 1)
 {
  rect(bmp, tbox->x-1+wnd->x, tbox->y-1+wnd->y, tbox->x+tbox->w+1+wnd->x+15, tbox->y+tbox->y+1+wnd->y, 0xff9600);    
  rect(bmp, tbox->x-1+wnd->x, tbox->y-1+wnd->y, tbox->x+tbox->w+1+wnd->x-3, tbox->y+tbox->y+1+wnd->y, 0xff9600);
  rect(bmp, tbox->x-2+wnd->x, tbox->y-2+wnd->y, tbox->x+tbox->w+1+wnd->x+14, tbox->y+tbox->y+2+wnd->y, 0xff9600);
  //line()
  //rect(bmp, tbox->x-3+wnd->x, tbox->y-3+wnd->y, tbox->x+tbox->w+3+wnd->x, tbox->y+tbox->y+3+wnd->y, 0xff9600);                 
 }
 else
 {
  rect(bmp, tbox->x-1+wnd->x, tbox->y-1+wnd->y, tbox->x+tbox->w+1+wnd->x+15, tbox->y+tbox->y+1+wnd->y, 0xffffff);    
  rect(bmp, tbox->x-1+wnd->x, tbox->y-1+wnd->y, tbox->x+tbox->w+1+wnd->x-3, tbox->y+tbox->y+1+wnd->y, 0xffffff);
 }    
 tbox->fy += (mzlog-mouse_z)*3;
 if(tbox->fy < 3)tbox->fy = 3;
 mzlog = mouse_z;
 //printf("%d", mzlog-mouse_z);
 insert_etwas = 0;
 }
 else
 {
  if(tbox->active == 1)
  {
   rect(bmp, tbox->x-1+wnd->x, tbox->y-1+wnd->y, tbox->x+tbox->w+1+wnd->x, tbox->y+tbox->h+1+wnd->y, 0xff9600);                    
   rect(bmp, tbox->x-2+wnd->x, tbox->y-2+wnd->y, tbox->x+tbox->w+2+wnd->x, tbox->y+tbox->h+2+wnd->y, 0xff9600);                    
  }
  else rect(bmp, tbox->x-1+wnd->x, tbox->y-1+wnd->y, tbox->x+tbox->w+1+wnd->x, tbox->y+tbox->h+1+wnd->y, 0xffffff);
  
 }
 /*}
 else //textbox zjavne nieje multiline ;)
 {
  if(tbox->active == 1)
  {
   rect(bmp, tbox->x-1+wnd->x, tbox->y-1+wnd->y, tbox->x+tbox->w+1+wnd->x, tbox->y+tbox->h+1+wnd->y, 0xff9600);                    
   rect(bmp, tbox->x-2+wnd->x, tbox->y-2+wnd->y, tbox->x+tbox->w+2+wnd->x, tbox->y+tbox->h+2+wnd->y, 0xff9600);                    
  }
  else rect(bmp, tbox->x-1+wnd->x, tbox->y-1+wnd->y, tbox->x+tbox->w+1+wnd->x, tbox->y+tbox->h+1+wnd->y, 0xffffff);
  rectfill(bmp, tbox->x+wnd->x, tbox->y+wnd->y, tbox->x+tbox->w+wnd->x, tbox->y+tbox->h+wnd->y, 0);
  
  x = wnd->x+tbox->x-tbox->w;
  
  for(i = 0; i < tbox->amtchar;i++)
  {
   alfont_textprintf_aa(bmp, larabie, x+tbox->w, tbox->y+wnd->y, 0xffffff, "%c", tbox->text[i]);      
   if(tbox->achar == i && tbox->active == 1 && tbox->blick >= 0.5)
   {
    line(bmp, tbox->x+wnd->x-1+x-tbox->x, tbox->y+wnd->y, tbox->x+wnd->x-1+x-tbox->x, tbox->y+wnd->y+14, 0xff9600);               
   }
   str[0] = tbox->text[i];
   str[1] = '\0';
   x+=alfont_text_length(larabie,str)+1;
  }  
  
  
  tbox->blick+=0.04;
  if(tbox->blick >= 1.0)tbox->blick = 0.0;
  
  //alfont_textprintf_right(bmp, larabie, wnd->x+tbox->x+tbox->w, tbox->y+wnd->y, 0xffffff, "%s", tbox->text);
  
 }*/
 return 1;
}

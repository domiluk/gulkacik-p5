//Set texture 

bool draw_choose_color(BITMAP *bmp,int xx, int yy)
{
 //if(fill_mode == MODE_FILL_SIMPLE)
 //{
             
 //}
 
 
 //result blitout :D
 rect(bmp,xx + 70-1,yy+200+15+2,xx+70+30+1,yy+215+15+4,makecol(0,0,0));
 rectfill(bmp,xx + 70,yy+200+15+3,xx+70+30,yy+215+15+3,makecol(getpixledr,getpixledg,getpixledb));
  
 //border
 rectfill(bmp, xx-2,yy-2,xx+203,yy+203,0);
 blit(qgrad,bmp,0,0,xx,yy,200,200);
 rectfill(bmp, xx+202, yy-2, xx+275, yy+51, 0);
 
 //border 3, wandh 15
 rectfill(bmp, xx+206, yy,   xx+218, yy+12, 0xff0000);
 rectfill(bmp, xx+206+18, yy,   xx+218+18, yy+12, 0x00ff00);
 rectfill(bmp, xx+206+18+18, yy,   xx+218+18+18, yy+12, 0x0000ff);
 rectfill(bmp, xx+206+18+18+18, yy,   xx+218+18+18+18, yy+12, 0x333333);
 
 rectfill(bmp, xx+206, yy+18, xx+218, yy+12+18, 0x00ffff);
 rectfill(bmp, xx+206+18, yy+18, xx+218+18, yy+12+18, 0xff00ff);
 rectfill(bmp, xx+206+18+18, yy+18, xx+218+18+18, yy+12+18, 0xffff00);
 rectfill(bmp, xx+206+18+18+18, yy+18, xx+218+18+18+18, yy+30, 0x888888);
 
 rectfill(bmp, xx+206, yy+36, xx+218, yy+48, 0x7f0000);  
 rectfill(bmp, xx+206+18, yy+36, xx+218+18, yy+48, 0x007f00);
 rectfill(bmp, xx+206+18+18, yy+36, xx+218+18+18, yy+48, 0x00007f);
 rectfill(bmp, xx+206+18+18+18, yy+36, xx+218+18+18+18, yy+48, 0xdddddd);
 
 //seared
 if(mir(xx+206+set_texture_wnd->x, yy+set_texture_wnd->y,   xx+218+set_texture_wnd->x, yy+12+set_texture_wnd->y, 0))
 {
  rect(bmp, xx+205, yy-1,   xx+219, yy+13, 0xffffff);
  if(mouse_b & 1)
  {
   rr = 255;
   gg =   0;
   bb =   0;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //san francisco green
 if(mir(xx+206+set_texture_wnd->x+18, yy+set_texture_wnd->y,   xx+218+set_texture_wnd->x+18, yy+12+set_texture_wnd->y, 0))
 {
  rect(bmp, xx+205+18, yy-1,   xx+219+18, yy+13, 0xffffff);
  if(mouse_b & 1)
  {
   rr =   0;
   gg = 255;
   bb =   0;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //pneumatic blue
 if(mir(xx+206+set_texture_wnd->x+18+18, yy+set_texture_wnd->y,   xx+218+set_texture_wnd->x+18+18, yy+12+set_texture_wnd->y, 0))
 {
  rect(bmp, xx+205+18+18, yy-1,   xx+219+18+18, yy+13, 0xffffff);
  if(mouse_b & 1)
  {
   rr =   0;
   gg =   0;
   bb = 255;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //darkest white
 if(mir(xx+206+set_texture_wnd->x+18+18+18, yy+set_texture_wnd->y,   xx+218+set_texture_wnd->x+18+18+18, yy+12+set_texture_wnd->y, 0))
 {
  rect(bmp, xx+205+18+18+18, yy-1,   xx+219+18+18+18, yy+13, 0xffffff);
  if(mouse_b & 1)
  {
   rr = 0x33;
   gg = 0x33;
   bb = 0x33;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //alcalic blue
 if(mir(xx+206+set_texture_wnd->x, yy+set_texture_wnd->y+18,   xx+218+set_texture_wnd->x, yy+12+set_texture_wnd->y+18, 0))
 {
  rect(bmp, xx+205, yy-1+18,   xx+219, yy+13+18, 0xffffff);
  if(mouse_b & 1)
  {
   rr =   0;
   gg = 255;
   bb = 255;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //disgusting purple
 if(mir(xx+206+set_texture_wnd->x+18, yy+set_texture_wnd->y+18,   xx+218+set_texture_wnd->x+18, yy+12+set_texture_wnd->y+18, 0))
 {
  rect(bmp, xx+205+18, yy-1+18,   xx+219+18, yy+13+18, 0xffffff);
  if(mouse_b & 1)
  {
   rr = 255;
   gg =   0;
   bb = 255;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //amish yellow
 if(mir(xx+206+set_texture_wnd->x+18+18, yy+set_texture_wnd->y+18,   xx+218+set_texture_wnd->x+18+18, yy+12+set_texture_wnd->y+18, 0))
 {
  rect(bmp, xx+205+18+18, yy-1+18,   xx+219+18+18, yy+13+18, 0xffffff);
  if(mouse_b & 1)
  {
   rr = 255;
   gg = 255;
   bb =   0;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //darker white
 if(mir(xx+206+set_texture_wnd->x+18+18+18, yy+set_texture_wnd->y+18,   xx+218+set_texture_wnd->x+18+18+18, yy+12+set_texture_wnd->y+18, 0))
 {
  rect(bmp, xx+205+18+18+18, yy-1+18,   xx+219+18+18+18, yy+13+18, 0xffffff);
  if(mouse_b & 1)
  {
   rr = 0x88;
   gg = 0x88;
   bb = 0x88;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //urban red
 if(mir(xx+206+set_texture_wnd->x, yy+set_texture_wnd->y+18+18,   xx+218+set_texture_wnd->x, yy+12+set_texture_wnd->y+18+18, 0))
 {
  rect(bmp, xx+205, yy-1+18+18,   xx+219, yy+13+18+18, 0xffffff);
  if(mouse_b & 1)
  {
   rr = 0x7f;
   gg =    0;
   bb =    0;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //Uncle Sam's Green
 if(mir(xx+206+set_texture_wnd->x+18, yy+set_texture_wnd->y+18+18,   xx+218+set_texture_wnd->x+18, yy+12+set_texture_wnd->y+18+18, 0))
 {
  rect(bmp, xx+205+18, yy-1+18+18,   xx+219+18, yy+13+18+18, 0xffffff);
  if(mouse_b & 1)
  {
   rr =    0;
   gg = 0x7f;
   bb =    0;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //SDKU  - Blue is goooood
 if(mir(xx+206+set_texture_wnd->x+18+18, yy+set_texture_wnd->y+18+18,   xx+218+set_texture_wnd->x+18+18, yy+12+set_texture_wnd->y+18+18, 0))
 {
  rect(bmp, xx+205+18+18, yy-1+18+18,   xx+219+18+18, yy+13+18+18, 0xffffff);
  if(mouse_b & 1)
  {
   rr =    0;
   gg =    0;
   bb = 0x7f;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 //lightest white
 if(mir(xx+206+set_texture_wnd->x+18+18+18, yy+set_texture_wnd->y+18+18,   xx+218+set_texture_wnd->x+18+18+18, yy+12+set_texture_wnd->y+18+18, 0))
 {
  rect(bmp, xx+205+18+18+18, yy-1+18+18,   xx+219+18+18+18, yy+13+18+18, 0xffffff);
  if(mouse_b & 1)
  {
   rr = 0xdd;
   gg = 0xdd;
   bb = 0xdd;
   rest(75);
   make_qgrad();
   getpx = xx;                          
   getpy = yy;
   getpixledr = getr(getpixel(qgrad,0,0));
   getpixledg = getg(getpixel(qgrad,0,0));
   getpixledb = getb(getpixel(qgrad,0,0));
  }
 }
 
 
 //getpixled x 'n' y
 

//todo getpixel
if(mir(set_texture_wnd->x + 10,set_texture_wnd->y + 50,set_texture_wnd->x + 210, set_texture_wnd->y + 250,1))
{
 getpx = mouse_x - set_texture_wnd->x;                          
 getpy = mouse_y - set_texture_wnd->y;
 getpixledr = getr(getpixel(set_texture_wnd->bmp,getpx,getpy));
 getpixledg = getg(getpixel(set_texture_wnd->bmp,getpx,getpy));
 getpixledb = getb(getpixel(set_texture_wnd->bmp,getpx,getpy));
}
circle(bmp,getpx,getpy,3,0);
//todo change main clr


rectfill(bmp,270,110,326,130,0);
rectfill(bmp,270,140,326,160,0);
rectfill(bmp,270,170,326,190,0);
alfont_textprintf_right_aa(bmp,larabie,310,113,0xff9600,"%2.0f",rr);
alfont_textprintf_right_aa(bmp,larabie,310,143,0xff9600,"%2.0f",gg);
alfont_textprintf_right_aa(bmp,larabie,310,173,0xff9600,"%2.0f",bb);
line(bmp,311,110,311,130,makecol(120,120,120));
line(bmp,311,140,311,160,makecol(120,120,120));
line(bmp,311,170,311,190,makecol(120,120,120));

line(bmp,311,120,326,120,makecol(120,120,120));
line(bmp,311,150,326,150,makecol(120,120,120));
line(bmp,311,180,326,180,makecol(120,120,120));

rectfill(bmp,330,110,380,130,makecol(rr,0,0));
rectfill(bmp,330,140,380,160,makecol(0,gg,0));
rectfill(bmp,330,170,380,190,makecol(0,0,bb));

alfont_textprintf_aa(bmp,larabie,316-1,107-1,0xffffff,"+");
alfont_textprintf_aa(bmp,larabie,316-1,137-1,0xffffff,"+");
alfont_textprintf_aa(bmp,larabie,316-1,167-1,0xffffff,"+");

alfont_textprintf_aa(bmp,larabie,318,117,0xffffff,"-");
alfont_textprintf_aa(bmp,larabie,318,147,0xffffff,"-");
alfont_textprintf_aa(bmp,larabie,318,177,0xffffff,"-");

//if red plus
if(mir(311+set_texture_wnd->x,110+set_texture_wnd->y,326+set_texture_wnd->x,120+set_texture_wnd->y,1) && rr < 255)
{
 rr++;
 alfont_textprintf(screen,larabie,316+set_texture_wnd->x-1,107+set_texture_wnd->y-1,0xff9600,"+");
 rest(75); 
 //pokial luser32 necha stlacenu mys na tom metabuttone co sa ma stat...
 while(mir(311+set_texture_wnd->x,110+set_texture_wnd->y,326+set_texture_wnd->x,120+set_texture_wnd->y,1) && rr < 255)
 {
  rr++;
  rest(25);
  alfont_textprintf(screen,larabie,316+set_texture_wnd->x-1,107+set_texture_wnd->y-1,0xff9600,"+");
  rectfill(screen,270+set_texture_wnd->x,110+set_texture_wnd->y,310+set_texture_wnd->x,130+set_texture_wnd->y,0);                                                                                                         
  alfont_textprintf_right_aa(screen,larabie,310+set_texture_wnd->x,113+set_texture_wnd->y-1,0xff9600,"%2.0f",rr);
  rectfill(screen,330+set_texture_wnd->x,110+set_texture_wnd->y,380+set_texture_wnd->x,130+set_texture_wnd->y,makecol(rr,0,0));
 }//while
 //teraz to nanovo prepocita ten qgradient...
 make_qgrad();
 circle(set_texture_wnd->bmp, getpx, getpy, 3, 0);
}//if
//-/-/-/-/-/-/-/-/-/-/-/-//-/-/-/-/--/-/-/-/-/-/--/-/-/-/-/-/-/-//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//-/-/-/-/

//if red minus
if(mir(311+set_texture_wnd->x,120+set_texture_wnd->y,326+set_texture_wnd->x,130+set_texture_wnd->y,1) && rr > 0)
{
 rr--;
 rest(75); 
 //pokial luser32 necha stlacenu mys na tom metabuttone co sa ma stat...
 while(mir(311+set_texture_wnd->x,120+set_texture_wnd->y,326+set_texture_wnd->x,130+set_texture_wnd->y,1) && rr > 0)
 {
  rr--;
  rest(25);
  alfont_textprintf(screen,larabie,316+set_texture_wnd->x+2,107+set_texture_wnd->y+10,0xff9600,"-");
  rectfill(screen,270+set_texture_wnd->x,110+set_texture_wnd->y,310+set_texture_wnd->x,130+set_texture_wnd->y,0);                                                                                                         
  alfont_textprintf_right_aa(screen,larabie,310+set_texture_wnd->x,113+set_texture_wnd->y+1,0xff9600,"%2.0f",rr);
  rectfill(screen,330+set_texture_wnd->x,110+set_texture_wnd->y,380+set_texture_wnd->x,130+set_texture_wnd->y,makecol(rr,0,0));
 }//while
 //teraz to nanovo prepocita ten qgradient...
 make_qgrad();
}//if

//GREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEN
/////////////////////////////////////////////////////////////////////////////////////
//if green plus
if(mir(311+set_texture_wnd->x,140+set_texture_wnd->y,326+set_texture_wnd->x,150+set_texture_wnd->y,1) && gg < 255)
{
 gg++;
 alfont_textprintf(screen,larabie,316+set_texture_wnd->x-1,107+set_texture_wnd->y+30-1,0xff9600,"+");
 rest(75); 
 //pokial luser32 necha stlacenu mys na tom metabuttone co sa ma stat...
 while(mir(311+set_texture_wnd->x,140+set_texture_wnd->y,326+set_texture_wnd->x,150+set_texture_wnd->y,1) && gg < 255)
 {
  gg++;
  rest(25);
  alfont_textprintf(screen,larabie,316+set_texture_wnd->x-1,107+set_texture_wnd->y+30-1,0xff9600,"+");
  rectfill(screen,270+set_texture_wnd->x,140+set_texture_wnd->y,310+set_texture_wnd->x,160+set_texture_wnd->y,0);                                                                                                         
  alfont_textprintf_right_aa(screen,larabie,310+set_texture_wnd->x,113+set_texture_wnd->y+30,0xff9600,"%2.0f",gg);
  rectfill(screen,330+set_texture_wnd->x,140+set_texture_wnd->y,380+set_texture_wnd->x,160+set_texture_wnd->y,makecol(0,gg,0));
 }//while
 //teraz to nanovo prepocita ten qgradient...
 make_qgrad();
 getpx = 10;
 getpy = 50;
 circle(set_texture_wnd->bmp, getpx, getpy, 3, 0);
}//if

//if green minusz :D
if(mir(311+set_texture_wnd->x,150+set_texture_wnd->y,326+set_texture_wnd->x,160+set_texture_wnd->y,1) && gg > 0)
{
 gg--;
 alfont_textprintf(screen,larabie,316+set_texture_wnd->x+2,107+set_texture_wnd->y+30+10,0xff9600,"-");
 rest(75); 
 //pokial luser32 necha stlacenu mys na tom metabuttone co sa ma stat...
 while(mir(311+set_texture_wnd->x,150+set_texture_wnd->y,326+set_texture_wnd->x,160+set_texture_wnd->y,1) && gg > 0)
 {
  gg--;
  rest(25);
  alfont_textprintf(screen,larabie,316+set_texture_wnd->x+2,107+set_texture_wnd->y+30+10,0xff9600,"-");
  rectfill(screen,270+set_texture_wnd->x,140+set_texture_wnd->y,310+set_texture_wnd->x,160+set_texture_wnd->y,0);                                                                                                         
  alfont_textprintf_right_aa(screen,larabie,310+set_texture_wnd->x,113+set_texture_wnd->y+30,0xff9600,"%2.0f",gg);
  rectfill(screen,330+set_texture_wnd->x,140+set_texture_wnd->y,380+set_texture_wnd->x,160+set_texture_wnd->y,makecol(0,gg,0));
 }//while
 //teraz to nanovo prepocita ten qgradient...
 make_qgrad();
 getpx = 10;
 getpy = 50;
 circle(set_texture_wnd->bmp, getpx, getpy, 3, 0);
}//if
//BLUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
//if blue plusz :D (pre nechapaveho citatela  -  madaguayorszagh notació)
if(mir(311+set_texture_wnd->x,170+set_texture_wnd->y,326+set_texture_wnd->x,180+set_texture_wnd->y,1) && bb < 255)
{
 bb++;
 alfont_textprintf(screen,larabie,316+set_texture_wnd->x-1,107+set_texture_wnd->y+30+30-1,0xff9600,"+");
 rest(75); 
 //pokial luser32 necha stlacenu mys na tom metabuttone co sa ma stat...
 while(mir(311+set_texture_wnd->x,170+set_texture_wnd->y,326+set_texture_wnd->x,180+set_texture_wnd->y,1) && bb < 255)
 {
  bb++;
  rest(25);
  alfont_textprintf(screen,larabie,316+set_texture_wnd->x-1,107+set_texture_wnd->y+30+30-1,0xff9600,"+");
  rectfill(screen,270+set_texture_wnd->x,170+set_texture_wnd->y,310+set_texture_wnd->x,190+set_texture_wnd->y,0);                                                                                                         
  alfont_textprintf_right_aa(screen,larabie,310+set_texture_wnd->x,113+set_texture_wnd->y+30+30,0xff9600,"%2.0f",bb);
  rectfill(screen,330+set_texture_wnd->x,170+set_texture_wnd->y,380+set_texture_wnd->x,190+set_texture_wnd->y,makecol(0,0,bb));
 }//while
 //teraz to nanovo prepocita ten qgradient...
 make_qgrad();
 getpx = 10;
 getpy = 50;
 circle(set_texture_wnd->bmp, getpx, getpy, 3, 0);
}//if

//if blue minusz *TIRED* pri pisani tohto kodu je asi tak 23:00 a ja uz
//dost ze zaspavam...ja to zvladnem, nepoznam unavu, NEPOZNAM UNAVU
//N E P O Z N A M   U N A V U :)
if(mir(311+set_texture_wnd->x,180+set_texture_wnd->y,326+set_texture_wnd->x,190+set_texture_wnd->y,1) && bb > 0)
{
 bb--;
 alfont_textprintf(screen,larabie,316+set_texture_wnd->x+2,107+set_texture_wnd->y+30+30+10,0xff9600,"-");
 rest(75); 
 //pokial luser32 necha stlacenu mys na tom metabuttone co sa ma stat...
 while(mir(311+set_texture_wnd->x,180+set_texture_wnd->y,326+set_texture_wnd->x,190+set_texture_wnd->y,1) && bb > 0)
 {
  bb--;
  rest(25);
  alfont_textprintf(screen,larabie,316+set_texture_wnd->x+2,107+set_texture_wnd->y+30+10+30,0xff9600,"-");
  rectfill(screen,270+set_texture_wnd->x,170+set_texture_wnd->y,310+set_texture_wnd->x,190+set_texture_wnd->y,0);                                                                                                         
  alfont_textprintf_right_aa(screen,larabie,310+set_texture_wnd->x,113+set_texture_wnd->y+30+30,0xff9600,"%2.0f",bb);
  rectfill(screen,330+set_texture_wnd->x,170+set_texture_wnd->y,380+set_texture_wnd->x,190+set_texture_wnd->y,makecol(0,0,bb));
 }//while
 //teraz to nanovo prepocita ten qgradient...
 make_qgrad();
 getpx = 10;
 getpy = 50;
 circle(set_texture_wnd->bmp, getpx, getpy, 3, 0);
}//if



}//int


bool draw_choose_fill_mode(BITMAP *bmp)
{

rectfill(bmp,240,210,250,220,0);
rectfill(bmp,240,230,250,240,0);
rectfill(bmp,240,250,250,260,0);

if(fill_mode == MODE_FILL_SIMPLE)
{
 putpixel(bmp,245,215,0xffffff);
 rect(bmp,244,214,246,216,0xffffff);             
 rect(bmp,243,213,247,217,0xaaaaaa);             
 rect(bmp,242,212,248,218,0x555555);             
}

if(fill_mode == MODE_FILL_GRADIENT)
{
 putpixel(bmp,245,235,0xffffff);
 rect(bmp,244,234,246,236,0xffffff);             
 rect(bmp,243,233,247,237,0xaaaaaa);             
 rect(bmp,242,232,248,238,0x555555);             
}

if(fill_mode == MODE_FILL_PICTURE)
{
 putpixel(bmp,245,255,0xffffff);
 rect(bmp,244,254,246,256,0xffffff);             
 rect(bmp,243,253,247,257,0xaaaaaa);             
 rect(bmp,242,252,248,258,0x555555);             
}

if(mir(240+set_texture_wnd->x,210+set_texture_wnd->y,250+set_texture_wnd->x,220+set_texture_wnd->y,1))
{
 fill_mode = MODE_FILL_SIMPLE;
 //GTYPE->visible = 0;
 //set_texture_wnd->btns->nextbutton->nextbutton->visible = 0;
}
if(mir(240+set_texture_wnd->x,230+set_texture_wnd->y,250+set_texture_wnd->x,240+set_texture_wnd->y,1))
{
 fill_mode = MODE_FILL_GRADIENT;
 //set_texture_wnd->btns->nextbutton->nextbutton->visible = 0;
}
if(mir(240+set_texture_wnd->x,250+set_texture_wnd->y,250+set_texture_wnd->x,260+set_texture_wnd->y,1))
{
 fill_mode = MODE_FILL_PICTURE;
 //GTYPE->visible = 0;
}

//triangle(bmp, set_texture_wnd->x+getpx+10, set_texture_wnd->y+48, set_texture_wnd->x+getpx+8, set_texture_wnd->y+44, set_texture_wnd->x+getpx+12, set_texture_wnd->y+44, 0);
//rectfill(bmp, 10, 43, 210, 46, makecol(120,120,120));
if(mir(set_texture_wnd->x+10, set_texture_wnd->y+40, set_texture_wnd->x+209, set_texture_wnd->y+48,1))
{
 getpx = mouse_x - set_texture_wnd->x;
 getpixledr = getr(getpixel(qgrad,getpx-10,getpy));
 getpixledg = getg(getpixel(qgrad,getpx-10,getpy));
 getpixledb = getb(getpixel(qgrad,getpx-10,getpy));
}

if(mir(set_texture_wnd->x+1, set_texture_wnd->y+50, set_texture_wnd->x+8, set_texture_wnd->y+249,1))
{
 getpy = mouse_y - set_texture_wnd->y;
 getpixledr = getr(getpixel(qgrad,getpx,getpy-50));
 getpixledg = getg(getpixel(qgrad,getpx,getpy-50));
 getpixledb = getb(getpixel(qgrad,getpx,getpy-50));
}

draw_sprite(bmp,trix,0,43);
triangle(bmp, getpx, 48, getpx-2, 44, getpx+2, 44, 0);
draw_sprite(bmp,triy,3,43);
triangle(bmp, 7, getpy, 3, getpy-2, 3, getpy+2, 0);
return true;     
}


bool draw_set_texture(BITMAP *bmp)
{
    if(set_texture_wnd->visible)
    {
      draw_choose_color(set_texture_wnd->bmp,10,50);
      draw_choose_fill_mode(set_texture_wnd->bmp);
      draw_wind(set_texture_wnd, bmp);

      alfont_set_font_size(larabie,19);
      if(fill_mode == MODE_FILL_SIMPLE)alfont_textprintf_aa(bmp,larabie, 10+set_texture_wnd->x,50 - 24 + set_texture_wnd->y,0xffffff,"Simple Color Fill");  
      alfont_textprintf_aa(mb,larabie,10+set_texture_wnd->x,50+200+15+set_texture_wnd->y,makecol(255,255,255),"Result: ");
      alfont_textprintf_aa(mb,larabie,10+120+set_texture_wnd->x,50+217+set_texture_wnd->y,makecol(255,255,255), "%d, %d, %d",getpixledr,getpixledg, getpixledb);
      alfont_set_font_size(larabie,14);
      alfont_textprintf_aa(mb,larabie,230+set_texture_wnd->x,112+set_texture_wnd->y,0xffffff,"Red: ");
      alfont_textprintf_aa(mb,larabie,230+set_texture_wnd->x,142+set_texture_wnd->y,0xffffff,"Green: ");
      alfont_textprintf_aa(mb,larabie,230+set_texture_wnd->x,172+set_texture_wnd->y,0xffffff,"Blue: ");
      alfont_set_font_size(larabie,17);
      alfont_textprintf_aa(mb,larabie,255+set_texture_wnd->x,207+set_texture_wnd->y,0xffffff,"Simple Color Fill");
      alfont_textprintf_aa(mb,larabie,255+set_texture_wnd->x,227+set_texture_wnd->y,0xffffff,"Gradient Color Fill");
      alfont_textprintf_aa(mb,larabie,255+set_texture_wnd->x,247+set_texture_wnd->y,0xffffff,"Picture Fill");      
      
      draw_buttons(set_texture_wnd, bmp);
      manage_window(set_texture_wnd); 
    }     
}

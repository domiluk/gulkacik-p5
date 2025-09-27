#include <io.h>
#include <ctype.h>

N_UNIT* init_nunit(char *path, char *name)
{
N_UNIT *nnt;
int i;

nnt = (N_UNIT*)malloc(sizeof(N_UNIT));

for(i = 0; i < strlen(path);i++)
nnt->path[i] = path[i];

for(i = 0; i < strlen(name);i++)
nnt->name[i] = name[i];

return nnt;        
}

N_LIST *init_nlist(int x, int y)
{
int xx;
float rgb;
rgb = 255.0;       
 N_LIST *nlt;
 nlt = (N_LIST*)malloc(sizeof(N_LIST));         
 nlt ->cpoio    = 0;
 nlt ->cpoi     = 0;
 nlt ->x        = x;
 nlt ->y        = y;
 nlt ->rolled   = 0;
 nlt ->slidebar = 0;
 
 nlt->grad = create_bitmap(50,12);
 for(xx = 0;xx < nlt->grad->w;xx++)
 {
  line(nlt->grad,xx,0,xx,12,makecol(rgb,rgb,rgb));
  rgb-=(255/50);      
 }
 
 
 /*for(i = 0;i < 25;i++)
 {
  nst->units[i] = (N_UNIT*)malloc(sizeof(CB_UNIT));       
 }*/

 return nlt;
}

bool fill_the_list(N_LIST *nlt)
{
  int num = 0;
  char *cesta;
  int i, strl;
  
  cesta = getenv("WINDIR");
  strcat(cesta, "/Fonts/*.*");
  
  long done, info;
  struct _finddata_t f;
  
  info = _findfirst(cesta,&f);
  
  //printf("mam prve %s", f.name);
  //readkey();
  while (1)
  {
   done = _findnext(info,&f);
   if (done) break;
   if (num == 999) break;
   
   if(!(f.name[0] == '.' && f.name[1] == '.'))
   {
	  nlt->units[num] = init_nunit(cesta, f.name);
	  strl = strlen(cesta);
		//printf("%d", strl);
		
		/*nlt->units[num]->path[strlen(nlt->units[num]->path)] = '\0';
	  nlt->units[num]->path[strlen(nlt->units[num]->path)-1] = '\0';
	  nlt->units[num]->path[strlen(nlt->units[num]->path)-2] = '\0';
	  */
	  
	  
	  for(i = 0; i < strlen(f.name); i++)
	  {
		 nlt->units[num]->path[i + strl - 3] = f.name[i]; 			
	  }
	  
	  for(i = 0; i < strlen(f.name); i++)
	  {
		 nlt->units[num]->name[i] = f.name[i]; 			 			
		}
		//strcpy(nlt->units[num]->name, cesta);
		//strcat(nlt->units[num]->name, f.name);
		//strcpy(nlt->units[num]->path, cesta);
		//strcat(nlt->units[num]->path, f.name);
		//readkey();
		printf("\n %s %s", nlt->units[num]->path, nlt->units[num]->name);
		nlt->cpoio = num+1;
		num ++;						 
	 }
	}
	
  return true; 
}//bool



int draw_ninja(N_LIST *nlt, BITMAP *bmp, int x, int y)
{
  int i;
  
	if(mouse_b & 1 && !mir(x, y, x+150, y+15+12*6, 0))nlt->rolled = 0;
	
	//draw of skeleton
  alfont_set_font_size(larabie,20);
  rectfill(bmp,x, y, x+150, y + 15,0); 
  line(bmp,x+135,y,x+135,y+15,makecol(100,100,100));
  
  //cool v butty
  if(mir(x+140,y,x+150,y+15,1))
  {
   alfont_textprintf_aa(bmp,larabie,x+140,y-3,0xff9600,"v");
   nlt->rolled = 1;
   
   while(mouse_b & 1)
   {
    vsync(); 
    rectfill(screen,x+136,y,x+150,y+15,0); 
    alfont_textprintf_aa(screen,larabie,x+140,y-3,0xff9600,"v");
   }
   //mouse_b = 0;
   printf("clicked");
   
   rest(100);
  }
  else alfont_textprintf_aa(bmp,larabie,x+139,y-4,0xffffff,"v");
  
  //chosen one :D
  alfont_set_font_size(larabie,17);
  alfont_textprintf_right_aa(bmp,larabie,x+134,y,0xff9600,"%s",nlt->units[nlt->cpoi]->name);
  
  alfont_set_font_size(larabie,16);
  
  //drawing of rolka
  if(nlt->rolled == 1)
  {
	 //printf("ttttu som bol");
   //more than size
   if(nlt->cpoio > 6)
   {
		// printf("aj ttttu");
    if(key[KEY_PLUS_PAD]  && nlt->slidebar < nlt->cpoio-6){nlt->cpoio++;key[KEY_PLUS_PAD] = FALSE;}
    if(key[KEY_MINUS_PAD] && nlt->slidebar > 0){nlt->cpoio--;key[KEY_MINUS_PAD] = FALSE;}
    rectfill(bmp,x+135,y+15,x+150,y+15+72,0);
    
    //upper arrow
    if(mir(x+135,y+15,x+150,y+30,1))
    {
     line(bmp,x+137+2,y+28-1,x+146+2,y+28-1,0xffffff);                                                                              
     line(bmp,x+138+2,y+27-1,x+145+2,y+27-1,0xdddddd);                                                                              
     line(bmp,x+139+2,y+26-1,x+144+2,y+26-1,0xbbbbbb);                                                                              
     line(bmp,x+140+2,y+25-1,x+143+2,y+25-1,0x999999);
     line(bmp,x+141+2,y+24-1,x+142+2,y+24-1,0x777777);
     if(nlt->slidebar > 0)
     {
      nlt->slidebar--;
      rest(75);
      while(mouse_b & 1)
      {
       //rest(75);
       //mouse_b = 0;
       printf("wahahaa");
       if(nlt->slidebar > 0)nlt->slidebar--;              
      }
     }
    }
    else
    {
     line(bmp,x+137+1,y+28-2,x+146+1,y+28-2,0xffffff);                                                                              
     line(bmp,x+138+1,y+27-2,x+145+1,y+27-2,0xdddddd);                                                                              
     line(bmp,x+139+1,y+26-2,x+144+1,y+26-2,0xbbbbbb);                                                                              
     line(bmp,x+140+1,y+25-2,x+143+1,y+25-2,0x999999);
     line(bmp,x+141+1,y+24-2,x+142+1,y+24-2,0x777777);
    }
    
    //lower arrow
    if(mir(x+135,y+72,x+150,y+172+15,1))
    {
     line(bmp,x+137+2,y+77-1+4,x+146+2,y+77-1+4,0xffffff);                                                                              
     line(bmp,x+138+2,y+78-1+4,x+145+2,y+78-1+4,0xdddddd);                                                                              
     line(bmp,x+139+2,y+79-1+4,x+144+2,y+79-1+4,0xbbbbbb);                                                                              
     line(bmp,x+140+2,y+80-1+4,x+143+2,y+80-1+4,0x999999);
     line(bmp,x+141+2,y+81-1+4,x+142+2,y+81-1+4,0x777777);
     if(nlt->slidebar < nlt->cpoio-6)
     {
      nlt->slidebar++;
      rest(90);
      while(mouse_b & 1)
      {
       rest(75);
       //mouse_b = 0;
       
       printf("cpoio = %d, slidebar+6 = %d\n", nlt->cpoio, nlt->slidebar+6);
       
       rectfill(screen, x, y+15, x+ 135, y+15+12*6 +1, 0);
       
			 if(nlt->slidebar < nlt->cpoio-7)
			 for(i = nlt->slidebar; i < nlt->slidebar+6; i++)
			 {
			  if(i == nlt->cpoio-1)break;
				alfont_textprintf_right_aa(screen, larabie, x+135, y+15+(12*(i-nlt->slidebar))-1, 0xffffff, "%s", nlt->units[i]->name);
			 }	 
       if(nlt->slidebar < nlt->cpoio-7)nlt->slidebar++;              
      }
     }
    }
    else
    {
     line(bmp,x+137+1,y+77-2+4,x+146+1,y+77-2+4,0xffffff);                                                                              
     line(bmp,x+138+1,y+78-2+4,x+145+1,y+78-2+4,0xdddddd);                                                                              
     line(bmp,x+139+1,y+79-2+4,x+144+1,y+79-2+4,0xbbbbbb);                                                                              
     line(bmp,x+140+1,y+80-2+4,x+143+1,y+80-2+4,0x999999);
     line(bmp,x+141+1,y+81-2+4,x+142+1,y+81-2+4,0x777777);
    }
    
    rectfill(bmp,x ,y + 15,x+135,y + 15 + (6*12),0);
    for(ci = nlt->slidebar;ci < nlt->slidebar+6;ci++)
    {
     if(mir(x, y+15+((ci-nlt->slidebar)*12), x+135, y+15+((ci-nlt->slidebar)*12)+11,0))
     {
      draw_sprite(bmp,nlt->grad,x,y+15 + ((ci-nlt->slidebar)*12));
      rect(bmp,x,y+15+((ci-nlt->slidebar)*12),x+135,y+15+((ci-nlt->slidebar)*12)+12,0xffffff); 
      alfont_textprintf_right_aa(bmp,larabie,x+135,y+15+((ci-nlt->slidebar)*12)-1,0xff9600,"%s",nlt->units[ci]->name);       
      if(mouse_b & 1)
      {
       nlt->cpoi = ci;
       nlt->rolled = 0;
       rest(80);
      }// if mouse
     }//if mir 
     else
     {
      alfont_textprintf_right_aa(bmp,larabie,x+135,y+15+((ci-nlt->slidebar)*12)-1,0xffffff,"%s",nlt->units[ci]->name);       
     }//else mir     
    }//for ci     
   }//if > 6
   else //if =< 6
   {                    
    //if(mir(lst->x+wnd->x,lst->y+wnd->y,lst->x+wnd->x+50,lst->y+wnd->y+15+(lst->cpoio*12),1) == 0)lst->rolled = 0;
   
    rectfill(bmp,x,y + 15,x+150,y + 15 + (nlt->cpoio*12),0);    
   
    for(ci = 0;ci < nlt->cpoio;ci++)
    {
     if(mir(x, y+15+(ci*12), x+50, y+15+(ci*12)+11,0))
     {
      draw_sprite(bmp,nlt->grad,x,y+15+ (ci*12));
      rect(bmp,x,y+15+((ci)*12),x+150,y+15+((ci)*12)+12,0xffffff); 
      alfont_textprintf_right_aa(bmp,larabie,x+150,y+15+(ci*12)-1,0xff9600,"%s",nlt->units[ci]->name);       
      if(mouse_b & 1)
      {
       nlt->cpoi = ci;
       nlt->rolled = 0;
       rest(80);
      }
     }
     else
     alfont_textprintf_right_aa(bmp,larabie,x+150,y+15+(ci*12)-1,0xffffff,"%s",nlt->units[ci]->name);       
    }
   
   }
   
                  
  }
 
 return 1;
}

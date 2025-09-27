#define wfb 200
#define hfb 180
#include "engine.h"

long done, info;
struct _finddata_t f;
   
char nwe[512];
int a;
int baw;

int stick_textbox_to_filebrowser(FILEBROWSER *fb, TEXTBOX *tbox)
{
 fb->tbox = tbox;
 printf("aaaaaaaaaaaaaa %d %d", fb->tbox->x, tbox->x);
 return 1; 		
}

int stick_combo_list_to_filebrowser(FILEBROWSER *fb, CB_LIST *cblst)
{
 fb->cblst = cblst;
 return 1; 		
}

int init_dirr(FILEBROWSER *fb)
{
 int i;
 int k;
 info = _findfirst(fb->path,&f);
 
 for(i = 0; i != 100;i++)
 {
  for(k = strlen(fb->dir[i].name); k != 0; k--)
	fb->dir[i].name[k] = '\0';
	
	for(k = strlen(fb->dir[i].real_name); k != 0; k--)
	fb->dir[i].real_name[k] = '\0';
	
	fb->dir[i].name[0] = '\0';		
	fb->dir[i].real_name[0] = '\0';		 
 }
 fb->nod = 0;
 
 if(f.attrib == _A_SUBDIR || f.attrib == _A_HIDDEN || f.attrib == _A_SYSTEM)
  {
   //fb->dir[fb->nod]->name = f.name;
   for(i = 0;i < strlen(f.name) && i < 16; i++)
   {
    fb->dir[fb->nod].name[i] = f.name[i]; 
   }
   for(i = 0;i < strlen(f.name);i++)
   {
	  fb->dir[fb->nod].real_name[i] = f.name[i];			 
	 }
	 
   if(strlen(f.name) > 16)fb->dir[fb->nod].longer = 1;
   else fb->dir[fb->nod].longer = 0;
   printf("\n%s %d",fb->dir[fb->nod].name, fb->dir[fb->nod].longer);
   fb->nod++;
  }
 while (1)
 {
  done = _findnext(info,&f);
  if (done) break;
  if(f.attrib == _A_SUBDIR || f.attrib == _A_HIDDEN || f.attrib == _A_SYSTEM)
  {
   //fb->dir[fb->nod]->name = f.name;
   for(i = 0;i < strlen(f.name) && i < 16; i++)
   {
    fb->dir[fb->nod].name[i] = f.name[i]; 
   }
   for(i = 0;i < strlen(f.name);i++)
   {
	  fb->dir[fb->nod].real_name[i] = f.name[i];			 
	 }
   
	 if(strlen(f.name) > 16)   
	 {
	  fb->dir[fb->nod].longer = 1;
	  fb->dir[fb->nod].name[15] = '.';
	  fb->dir[fb->nod].name[16] = '.';
	  fb->dir[fb->nod].name[17] = '.';
	  fb->dir[fb->nod].name[18] = '\0';
	 }
	 
   else fb->dir[fb->nod].longer = 0;
   printf("\n%s %d",fb->dir[fb->nod].name, fb->dir[fb->nod].longer);
   fb->nod ++;
  }
 }
}


int init_flee(FILEBROWSER *fb)//, CB_LIST *lst)
{
 int i;
 int k;
 int format;
 format = fb->cblst->units[fb->cblst->cpoi]->value;
 format = 0;
 //format = 0;
 for(i = 0; i != 400;i++)
 {
  for(k = strlen(fb->fle[i].name); k != 0; k--)
	fb->fle[i].name[k] = '\0';
	
	for(k = strlen(fb->fle[i].real_name); k != 0; k--)
	fb->fle[i].real_name[k] = '\0';
	
	fb->fle[i].name[0] = '\0';		
	fb->fle[i].real_name[0] = '\0';		 
 }
 fb->nof = 0;
 
 
 ///printf("tunak som bol %d",strlen(fb->path)-3);
 //strncpy(nwe, fb->path, strlen(fb->path)-3);
 fb->nof = 0;
 //printf("%s", fb->path);
 /********
 for(i = 0; i < strlen(fb->path)-1;i++)
 {
  nwe[i] = fb->path[i];	 		 
 }
 //strcpy(nwe, fb->path);
 //printf("%s",nwe);
 if(format == 0)//VGP
 strcat(nwe, "vgp");
 if(format == 1)//BMP
 strcat(nwe, "bmp");
 ***********/
 
 for(i = 0; i < strlen(fb->path);i++)
 {
  nwe[i] = fb->path[i];	 		 
 }
 
 for(i = strlen(fb->path);;i--)
 {
  if(nwe[i] == '/')break;
	else nwe[i] = '\0';			 
 }
 if(format == 0)//VGP
 strcat(nwe, "*.gud");
 if(format == 1)//BMP
 strcat(nwe, "*.bmp");
 if(format == 2)//TGA
 strcat(nwe, "*.tga");
 if(format == 3)//PCX
 strcat(nwe, "*.pcx");
 if(format == 4)//GIF
 strcat(nwe, "*.gif");
 if(format == 5)//PNG
 strcat(nwe, "*.png");
 if(format == 6)//JPG
 strcat(nwe, "*.jpg");
 //printf("%s",nwe);
 info = _findfirst(nwe,&f);
 printf("<<<<<<<<<< %c %c >>>>>>>>>>>>", nwe[strlen(nwe)-2], nwe[strlen(nwe)-1]);
 if((format == 0 && f.name[strlen(f.name)-1] == 'd' && f.name[strlen(f.name)-2] == 'u')     || (format == 1 && f.name[strlen(f.name)-1] == 'p' && f.name[strlen(f.name)-2] == 'm')		 || (format == 2 && f.name[strlen(f.name)-1] == 'a' && f.name[strlen(f.name)-2] == 'g')     || (format == 3 && f.name[strlen(f.name)-1] == 'x' && f.name[strlen(f.name)-2] == 'c')     || (format == 4 && f.name[strlen(f.name)-1] == 'f' && f.name[strlen(f.name)-2] == 'i')     || (format == 5 && f.name[strlen(f.name)-1] == 'g' && f.name[strlen(f.name)-2] == 'n')     || (format == 6 && f.name[strlen(f.name)-1] == 'g' && f.name[strlen(f.name)-2] == 'p'))
 {
  for(i = 0;i < strlen(f.name) && i < 15; i++)
  {
   fb->fle[fb->nof].name[i] = f.name[i];
  }
  
  for(i = 0;i < strlen(f.name); i++)
  {
   fb->fle[fb->nof].real_name[i] = f.name[i];
  }
  //printf("FLEE %s\n", fb->fle[fb->nof].real_name);
  
  if(strlen(f.name) > 15)
	{
	 fb->fle[fb->nof].name[14] = '.';
	 if(format == 0)
	 {
	  fb->fle[fb->nof].name[15] = 'g';
		fb->fle[fb->nof].name[16] = 'u';
		fb->fle[fb->nof].name[17] = 'd';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }		
	 if(format == 1)
	 {
	  fb->fle[fb->nof].name[15] = 'b';
		fb->fle[fb->nof].name[16] = 'm';
		fb->fle[fb->nof].name[17] = 'p';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }	
	 if(format == 2)
	 {
	  fb->fle[fb->nof].name[15] = 't';
		fb->fle[fb->nof].name[16] = 'g';
		fb->fle[fb->nof].name[17] = 'a';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }	
	 if(format == 3)
	 {
	  fb->fle[fb->nof].name[15] = 'p';
		fb->fle[fb->nof].name[16] = 'c';
		fb->fle[fb->nof].name[17] = 'x';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }			
	 if(format == 4)
	 {
	  fb->fle[fb->nof].name[15] = 'g';
		fb->fle[fb->nof].name[16] = 'i';
		fb->fle[fb->nof].name[17] = 'f';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }
	 if(format == 5)
	 {
	  fb->fle[fb->nof].name[15] = 'p';
		fb->fle[fb->nof].name[16] = 'n';
		fb->fle[fb->nof].name[17] = 'g';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }
	 if(format == 6)
	 {
	  fb->fle[fb->nof].name[15] = 'j';
		fb->fle[fb->nof].name[16] = 'p';
		fb->fle[fb->nof].name[17] = 'g';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }
	 		
	 fb->fle[fb->nof].longer = 1;
  }
  
	else fb->fle[fb->nof].longer = 0;
  fb->nof++;
  //fb->nofiles = 0;
 }
 //else fb->nofiles = 1;
 
 if(fb->nof == 1)
 {
 while (1)
 {
  done = _findnext(info,&f);
  if (done) break;
   //fb->dir[fb->nod]->name = f.name;
   for(i = 0;i < strlen(f.name) && i < 16; i++)
   {
    fb->fle[fb->nof].name[i] = f.name[i]; 
   }
   for(i = 0;i < strlen(f.name); i++)
   {
    fb->fle[fb->nof].real_name[i] = f.name[i];
   }
   //printf("FLEE %s\n", fb->fle[fb->nof].real_name);
   if(strlen(f.name) > 15)
	 {
	  fb->fle[fb->nof].name[14] = '.';
	 if(format == 0)
	 {
	  fb->fle[fb->nof].name[15] = 'g';
		fb->fle[fb->nof].name[16] = 'u';
		fb->fle[fb->nof].name[17] = 'd';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }	
	 if(format == 1)
	 {
	  fb->fle[fb->nof].name[15] = 'b';
		fb->fle[fb->nof].name[16] = 'm';
		fb->fle[fb->nof].name[17] = 'p';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }			
	 if(format == 2)
	 {
	  fb->fle[fb->nof].name[15] = 't';
		fb->fle[fb->nof].name[16] = 'g';
		fb->fle[fb->nof].name[17] = 'a';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }	
	 if(format == 3)
	 {
	  fb->fle[fb->nof].name[15] = 'p';
		fb->fle[fb->nof].name[16] = 'c';
		fb->fle[fb->nof].name[17] = 'x';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }		
	 if(format == 4)
	 {
	  fb->fle[fb->nof].name[15] = 'g';
		fb->fle[fb->nof].name[16] = 'i';
		fb->fle[fb->nof].name[17] = 'f';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }
	 if(format == 5)
	 {
	  fb->fle[fb->nof].name[15] = 'p';
		fb->fle[fb->nof].name[16] = 'n';
		fb->fle[fb->nof].name[17] = 'g';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }
	 if(format == 6)
	 {
	  fb->fle[fb->nof].name[15] = 'j';
		fb->fle[fb->nof].name[16] = 'p';
		fb->fle[fb->nof].name[17] = 'g';
		fb->fle[fb->nof].name[18] = '\0';					 
	 }		
	 	
	 fb->fle[fb->nof].longer = 1;
  }
	 //else fb->fle[fb->nof].longer = 0;
   //printf("\n%s %d",fb->fle[fb->nof].name, fb->fle[fb->nof].longer);
   fb->nof++;
  
 }
}
 return 1;
 
}

FILEBROWSER *init_filebrowser(int x, int y, char *start_path, TEXTBOX *tbox, CB_LIST *cblst)
{
FILEBROWSER *fb;
fb = (FILEBROWSER*)malloc(sizeof(FILEBROWSER));
fb->x = x;
fb->y = y;
fb->fyd = 0;
fb->fyf = 0;
fb->nof = 0;
fb->nod = 0;
fb->refresh = 0;
fb->tbox = (TEXTBOX*)malloc(sizeof(TEXTBOX));
fb->cblst = (CB_LIST*)malloc(sizeof(CB_LIST));
stick_textbox_to_filebrowser(fb, tbox);printf("sticked");
stick_combo_list_to_filebrowser(fb, cblst);
//fb->path = start_path;
strcpy(fb->path,start_path);
strcat(fb->path,"*.*");

init_dirr(fb);
printf("brum");
//init_flee(fb, lllst);
init_flee(fb);//, 0);
printf("aj tu");
return fb;            
}

int draw_filebrowser(BITMAP *bmp, FILEBROWSER *fb, WIND *wnd)
{
 
 alfont_set_font_size(larabie, 17);
 
 int k;
 if(fb->refresh == 1)
 {
	init_flee(fb);
  fb->refresh = 0;
  for(k = strlen(fb->tbox->text); k > 0;k--)fb->tbox->text[k] = '\0';
	fb->tbox->achar = 0;
	fb->tbox->amtchar = 0;
	//printf("refreshing, man...just wait nigga..just wait...\n");								
 }
 
 
 
 if(key[KEY_D] && fb->fyd+9 < fb->nod)
 {
  key[KEY_D] = FALSE;
  fb->fyd++;
 }
 
 if(key[KEY_E] && fb->fyd > 0)
 {
  key[KEY_E] = FALSE;
  fb->fyd--;
 }
 
 int i;
 
 
 //dirs podklad
 //rect(bmp, fb->x+wnd->x-1, fb->y+wnd->y-1, fb->x+wnd->x+wfb+1, fb->y+wnd->y+hfb+1,0x888888);
 //rectfill(bmp, fb->x+wnd->x, fb->y+wnd->y, fb->x+wnd->x+wfb, fb->y+wnd->y+hfb,0x222222);
 
 //files podklad
 rect(bmp, fb->x+wnd->x-1+wfb+15, fb->y+wnd->y-1+20, fb->x+wnd->x+wfb+1+wfb+15, fb->y+wnd->y+hfb+1,0x888888);
 rectfill(bmp, fb->x+wnd->x+wfb+15, fb->y+wnd->y+20, fb->x+wnd->x+wfb+wfb+15, fb->y+wnd->y+hfb,0x222222);
 
 //rectfill(bmp, fb->x+wnd->x+wfb-15, fb->y+wnd->y+1,fb->x+wnd->x+wfb, fb->y+wnd->y-1 + hfb, 0);
 rectfill(bmp, fb->x+wnd->x+wfb+wfb, fb->y+wnd->y+21, fb->x+wnd->x+wfb+15+wfb, fb->y+wnd->y+hfb, 0);
 //dir up
 /*if(mir(fb->x+wnd->x+wfb-15, fb->y+wnd->y+1, fb->x+wnd->x+wfb, fb->y+wnd->y+16, 0))
 {
 	draw_sprite(bmp,arrup,fb->x+wnd->x+wfb-15+1,fb->y+wnd->y+1+1);	
	 if(mouse_b & 1 && fb->fyd > 0)	
	 {
	  fb->fyd--;
		rest(75);						
	 }											 
 }
 else draw_sprite(bmp,arrup,fb->x+wnd->x+wfb-15,fb->y+wnd->y+1);
 //dir down
 if(mir(fb->x+wnd->x+wfb-15, fb->y+wnd->y+1+hfb-15, fb->x+wnd->x+wfb, fb->y+wnd->y+16+hfb, 0))
 {
 	draw_sprite(bmp,arrdown,fb->x+wnd->x+wfb-15+1,fb->y+wnd->y+1+1+hfb-15);	
	 if(mouse_b & 1 && fb->fyd+9 < fb->nod)	
	 {
	  fb->fyd++;
		rest(75);						
	 }											 
 }*/
 //else draw_sprite(bmp,arrdown,fb->x+wnd->x+wfb-15,fb->y+wnd->y+1+hfb-15);	
 //fle up
 if(mir(fb->x+wnd->x+wfb+wfb, fb->y+wnd->y+1+20, fb->x+wnd->x+wfb+wfb+15, fb->y+wnd->y+16+20, 0))
 {
 	draw_sprite(bmp,arrup,fb->x+wnd->x+wfb+wfb+1,fb->y+wnd->y+1+1+20);	
	 if(mouse_b & 1 && fb->fyf > 0)	
	 {
	  fb->fyf--;
		rest(75);						
	 }											 
 }
 else draw_sprite(bmp,arrup,fb->x+wnd->x+wfb+wfb,fb->y+wnd->y+1+20);
 //fle down
 if(mir(fb->x+wnd->x+wfb+wfb, fb->y+wnd->y+1+hfb-15, fb->x+wnd->x+wfb+wfb+15, fb->y+wnd->y+1+hfb, 0))
 {
 	draw_sprite(bmp,arrdown,fb->x+wnd->x+wfb+wfb+1,fb->y+wnd->y+1+1+hfb-15);	
	 if(mouse_b & 1 && fb->fyf+8 < fb->nof)	
	 {
	  fb->fyf++;
		rest(75);						
	 }											 
 }
 else draw_sprite(bmp,arrdown,fb->x+wnd->x+wfb+wfb,fb->y+wnd->y+1+hfb-15);	

 
 /*for(i = 0;i < 9;i++)
 {
  if(mir(fb->x+wnd->x, fb->y+wnd->y+(i*20)+1,fb->x+wnd->x - 15 + wfb,fb->y+wnd->y+(i*20)+20,0) && fb->fyd+i < fb->nod)
  {
	 rectfill(bmp, fb->x+wnd->x, fb->y+wnd->y+(i*20), fb->x+wnd->x+wfb-15, fb->y+wnd->y+(i*20)+20,0x111111);
   alfont_textprintf_aa(bmp, larabie, fb->x+wnd->x+2, fb->y+wnd->y+(i*20) + 2, 0xff9600, "%s", fb->dir[fb->fyd+i].name);      
   if(mouse_b & 1)
   {
	  //nulovane po prvu somarinu
		for(baw = strlen(fb->path);;baw--)
	  {
		 if(fb->path[baw] == '/')break;
		 else fb->path[baw] = '\0'; 			
		}
		/*a = strlen(fb->path);
		for(baw = a; baw < a+strlen(fb->dir[i].name);baw++)
		{
		 fb->path[baw + a] = fb->dir[i].name[baw-a]; 						
		}*/
/*		strcat(fb->path, fb->dir[fb->fyd+i].real_name);
		strcat(fb->path, "/*.*"); 
		init_dirr(fb);
		init_flee(fb);//, 0);
		fb->fyd = 0;
		rest(100);
		printf("\n\n%s",fb->path);
		printf("\n%s",fb->dir[fb->fyd+i].name);
	 }
	}
  else alfont_textprintf_aa(bmp, larabie, fb->x+wnd->x+2, fb->y+wnd->y+(i*20)+2, 0xffffff, "%s", fb->dir[fb->fyd+i].name);      
 }*/
 
 for(i = 0;i < 8;i++)
 {
  if(mir(fb->x+wnd->x+wfb+15, fb->y+wnd->y+(i*20)+20, fb->x+wnd->x - 15 + wfb+15+wfb,fb->y+wnd->y+(i*20)+20+20,0) && fb->fyf+i < fb->nof)
  {
	 rectfill(bmp, fb->x+wnd->x+wfb+15, fb->y+wnd->y+(i*20)+20, fb->x+wnd->x - 15 + wfb+15+wfb,fb->y+wnd->y+(i*20)+20+20,0x111111); 														
	 alfont_textprintf_aa(bmp, larabie, fb->x+wnd->x+2+wfb+15, fb->y+wnd->y+(i*20) + 20+2, 0xff9600, "%s", fb->fle[fb->fyf+i].name);      
	 if(mouse_b & 1)
	 {
	  //printf("clicked / %s\n", fb->fle[fb->fyf+i].real_name);						
	  for(k = strlen(fb->tbox->text); k > 0;k--)fb->tbox->text[k] = '\0';
	  fb->tbox->achar = 0;
	  fb->tbox->amtchar = 0;
	  strcpy(fb->tbox->text, fb->fle[fb->fyf+i].real_name);
	  fb->tbox->amtchar = strlen(fb->fle[fb->fyf+i].real_name);
	 }
	}
	else alfont_textprintf_aa(bmp, larabie, fb->x+wnd->x+2+wfb+15, fb->y+wnd->y+(i*20) + 20+2, 0xffffff, "%s", fb->fle[fb->fyf+i].name);      
 }
 
 //C:/
 /*rectfill(bmp, fb->x+wnd->x+wfb+15, fb->y+wnd->y, fb->x+wnd->x+wfb+15+19, fb->y+wnd->y+19, 0);
 if(mir(fb->x+wnd->x+wfb+15, fb->y+wnd->y, fb->x+wnd->x+wfb+15+19, fb->y+wnd->y+19, 0))
 {
  alfont_textprintf_centre_aa(bmp, larabie, fb->x+wnd->x+wfb+15 + (19/2), fb->y+wnd->y + 2, 0xff9600, "C:/"); 														 
  if(mouse_b & 1)
  {
	 for(k = strlen(fb->path); k > 0;k--)fb->path[k] = '\0';
	 fb->path[0] = 'C';
	 fb->path[1] = ':';
	 fb->path[2] = '/';
	 fb->path[3] = '*';
	 fb->path[4] = '.';
	 fb->path[5] = '*';
	 fb->path[6] = '\0';
	 printf("%s", fb->path);
	 init_dirr(fb);
	 init_flee(fb); 
	 rest(75);					 
	}
 }
 else alfont_textprintf_centre_aa(bmp, larabie, fb->x+wnd->x+wfb+15 + (19/2), fb->y+wnd->y + 2, 0xffffff, "C:/");
 */
 
 /*
 int slno;
 //back
 rectfill(bmp, fb->x+wnd->x+wfb+wfb+15-19, fb->y+wnd->y, fb->x+wnd->x+wfb+wfb+15, fb->y+wnd->y+19, 0);
 if(mir(fb->x+wnd->x+wfb+wfb+15-19, fb->y+wnd->y, fb->x+wnd->x+wfb+wfb+15, fb->y+wnd->y+19, 0))
 {
  draw_sprite(bmp, arrback, fb->x+wnd->x+wfb+wfb+15-19+1, fb->y+wnd->y+1);
  slno = 0;
	if(!(fb->path[0] == 'C' && fb->path[1] == ':' && fb->path[2] == '/' && fb->path[3] == '*' && fb->path[4] == '.' && fb->path[5] == '*') && mouse_b & 1)
  {
	 for(k = strlen(fb->path);;k--)
	 {
	  if(fb->path[k] == '/')slno++;
	  if(slno == 2)break;			 
		fb->path[k] = '\0';
   }
	 strcat(fb->path, "*.*");
	 init_dirr(fb);
	 init_flee(fb); 		
	 rest(100);						 
	}
 }
 else draw_sprite(bmp, arrback, fb->x+wnd->x+wfb+wfb+15-19, fb->y+wnd->y);
 
 //newdir
 rectfill(bmp, fb->x+wnd->x+wfb+wfb+15-19-19, fb->y+wnd->y, fb->x+wnd->x+wfb+wfb+15-19, fb->y+wnd->y+19, 0);
 if(mir(fb->x+wnd->x+wfb+wfb+15-19-19, fb->y+wnd->y, fb->x+wnd->x+wfb+wfb+15-19, fb->y+wnd->y+19, 0))
 {
  draw_sprite(bmp, newdir, fb->x+wnd->x+wfb+wfb+15-19-19+1, fb->y+wnd->y+1);
  //folder_name_wnd->visible = 1; 		
	rest(100);						 
 }
 else draw_sprite(bmp, newdir, fb->x+wnd->x+wfb+wfb+15-19-19, fb->y+wnd->y);
 
 */
 
 if(fb->nof == 0)
 {
  alfont_textprintf_centre_aa(mb, larabie, fb->x+wnd->x+wfb+15+((wfb-15)/2), fb->y+wnd->y+50, 0xffffff, "No");								
  alfont_textprintf_centre_aa(mb, larabie, fb->x+wnd->x+wfb+15+((wfb-15)/2), fb->y+wnd->y+65, 0xffffff, "Files");
 }
 
 return 1;    
}

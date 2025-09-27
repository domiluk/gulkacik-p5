#include "engine.h"
#include "vgp.h"

void new_cell_act()
{
 new_wnd->visible = 1; 	 
}
void quit_cell_act()
{
 close_button_pressed = 1;
}
void ppp()
{
 printf("ppp"); 	 
}

void save_as_cell_act()
{
 //save_vgp("pokus.vgp", window);     
 save_as_wnd->visible = 1;
}

void open_cell_act()
{
 open_wnd->visible = 1;
 //open_vgp("pokus.vgp", window);     
}

//tunak uz take seriozne
void credits_action()
{
 credits_wnd->visible = 1; 	 
}

void visit_us_action()
{
 system("\"C:/Program Files/Internet Explorer/iexplore\" www.dlsoftware.net/vectoria"); 	 
 
}

/***************************************************************************************************/
void water_action()
{
 ldm = 1;     
}
void klasik_action()
{
 ldm = 0;     
}
void water1_action()
{
 ldm = 2;     
}
void water2_action()
{
 ldm = 3;     
}
void water3_action()
{
 ldm = 4;     
}
void water4_action()
{
 ldm = 5;     
}
void symbol1_action()
{
 ldm = 10;     
}
void symbol2_action()
{
 ldm = 11;     
}
void symbol3_action()
{
 ldm = 12;     
}
void symbol4_action()
{
 ldm = 13;     
}
void symbol5_action()
{
 ldm = 14;     
}
void start_action()
{
 ldm = -1;     
}
void ostat_koniec_action()
{
 ldm = -2;     
}
void trava_action()
{
 ldm = 20;     
}
void reverse_action()
{
 ldm = 7;     
}
void trava1_action()
{
 ldm = 21;     
}
void trava2_action()
{
 ldm = 22;     
}
void trava3_action()
{
 ldm = 23;     
}
void trava4_action()
{
 ldm = 24;     
}
void smrt_action()
{
 ldm = 9;     
}
void teleport_action()
{
 ldm = 6;     
}
void laser1_action()
{
 ldm = 40;     
}
void laser1b_action()
{
 ldm = 41;     
}
void laser2b_action()
{
 ldm = 43;     
}
void laser2_action()
{
 ldm = 42;     
}
void hore_action()
{
 ldm = 50;     
}
void doprava_action()
{
 ldm = 51;     
}
void dole_action()
{
 ldm = 52;     
}
void dolava_action()
{
 ldm = 53;     
}
UMH* init_umh(char *text, char scut, void(*proc)())
{
 UMH* umh;
 umh = (UMH*)malloc(sizeof(UMH));
 umh->text = text;
 umh->shortcut = scut;
 umh->shortcut = 'x';
 umh->proc = proc;	
 
 return umh;
}


CMH* init_cmh(char *text, char scut, void(*proc)())
{
 CMH* cmh;
 int i;
 char str[13];
 cmh = (CMH*)malloc(sizeof(CMH));
 cmh->text = text;
 cmh->mshortcut = scut;
 cmh->shortcut = 'x';
 cmh->proc = proc;	
 cmh->rolled = 0;
 cmh->rollable = 0;
 cmh->noumh = 0;
 cmh->au = 0;
 
 if(text[0] == scut)
 {
  str[0] = text[0];
  str[1] = '\0';
  cmh->slx = 0;
  cmh->elx = alfont_text_length(larabie, str);			
 }
 else
 {
  for(i = 0;i < strlen(text); i++)
  {
   if(text[i] == scut)break;
   if(text[i]+32 == scut)break; 	   
  }
  //printf("<%d>", i);
  strncpy(str,text,i);
  cmh->slx = alfont_text_length(larabie, str);
  str[0] = scut;
  str[1] = '\0';
  cmh->elx = cmh->slx + alfont_text_length(larabie, str);
 }
 
 return cmh;
}

SMH* init_smh(char *text, char scut, int x, int w)
{
 SMH* smh;
 int i;
 char str[10];
 
 smh = (SMH*)malloc(sizeof(SMH));
 smh->text = text;
 smh->shortcut = scut;
 
 smh->x = x;
 smh->w = w;	
 
 smh->nocmh = 0;
 smh->rolled = 0;
 smh->ac = 0;
 
 if(text[0] == scut)
 {
  str[0] = text[0];
  str[1] = '\0';
  smh->slx = 0;
  smh->elx = alfont_text_length(larabie, str);			
 }
 else
 {
  for(i = 0;i < strlen(text); i++)
  {
   if(text[i] == scut)break;
   if(text[i]+32 == scut)break; 	   
  }
  //printf("<%d>", i);
  strncpy(str,text,i);
  smh->slx = alfont_text_length(larabie, str);
  str[0] = scut;
  str[1] = '\0';
  smh->elx = smh->slx + alfont_text_length(larabie, str);
 }
 //printf(" %s %d %d\n", text, smh->slx, smh->elx);
 return smh;
}

MMH* init_mmh()
{
 MMH* mmh;
 int xx;
 float rgb;
 mmh = (MMH*)malloc(sizeof(MMH));
 mmh->nosmh = 0;
 mmh->grad = create_bitmap(70, 20);
 rgb = 34;
 for(xx = 0;xx < 70;xx++)
 {
  line(mmh->grad,xx,0,xx,20,makecol(rgb, rgb, rgb));//((int)rgb + 34)>255 ? 255 : ((int)rgb + 34),((int)rgb + 34)>255 ? 255 : ((int)rgb + 34),((int)rgb + 34)>255 ? 255 : ((int)rgb + 34)));
  rgb+=((255-34)/70);      
 }

 return mmh;
}

int add_scut_info(CMH *cmh, char scut)
{
cmh->shortcut = scut;
return 1; 	
}

int stick_umh_to_cmh(UMH *umh, CMH *cmh)
{
 cmh->umh[cmh->noumh] = umh;
 cmh->noumh++;
 return 1;
}

int stick_cmh_to_smh(CMH *cmh, SMH *smh)
{
smh->cmh[smh->nocmh]  = cmh;
smh->nocmh++;
return 1; 	
}

int stick_smh_to_mmh(SMH *smh, MMH *mmh)
{
smh->ord = mmh->nosmh;
mmh->smh[mmh->nosmh] = smh;
mmh->nosmh++;
return 1; 	
}

int draw_smh(MMH *mmh, SMH *smh, BITMAP *bmp)
{
 int i,  k,   l;
 int help_me = 0;
 
if(smh->rolled == 1)
{
 if(mir(smh->x, smh->ac*20 +21, smh->x +140, smh->ac*20 +41, 1) && smh->cmh[smh->ac]->rollable == 0)//printf("clicked on %s|%s", smh->text, smh->cmh[smh->ac]->text);
 {
   smh->rolled = 0;
   smh->cmh[smh->ac]->proc();
 }
 if(mir(smh->x, smh->ac*20 +21, smh->x +140, smh->ac*20 +41, 1) && smh->cmh[smh->ac]->rollable == 1)
 {
  //printf("klikol som na nonrollable cmh...");
  if(smh->cmh[smh->ac]->rolled == 0)
  {
   help_me = 1;
   smh->cmh[smh->ac]->rolled = 1;
  }
  else 
  {
   help_me = 0;//smh->cmh[smh->ac]->rolled = 0; 				
   smh->cmh[smh->ac]->rolled = 0; 
  }
 }
 
 if(mir(smh->x+140, smh->ac*20 + 21 + smh->cmh[smh->ac]->au*20, smh->x+280, smh->ac*20 + 41 + smh->cmh[smh->ac]->au*20, 1))
 {
  //printf("kliklo sa na unit!");
  mmh->smh[smh->ord]->cmh[mmh->smh[smh->ord]->ac]->umh[mmh->smh[smh->ord]->cmh[mmh->smh[smh->ord]->ac]->au]->proc(); 					
 }
} 
 /*if(!mir(smh->x, 21, smh->x+140, smh->nocmh*20 + 22, 0) && mouse_b & 1 && !mir(0,0,800,21,0))
 {
  if(smh->cmh[smh->ac]->rolled == 0)
  {
   smh->rolled = 0;
   //for(i = 0; i < mmh->)
   return 1;
  }
  else
  {
   if(!mir(smh->x+140,smh->ac*20 + smh->cmh[smh->ac]->au*20, smh->x + 280, smh->ac*20 + smh->cmh[smh->ac]->au*20 + 21, 0)) 	  
   {
    smh->rolled = 0;
    //for(i = 0; i < mmh->)
    return 1;
   }
  }
 }*/
 
 for(k = 0; k < smh->nocmh;k++)
 {
  if(smh->cmh[k]->shortcut != 'x' && key[KEY_RCONTROL] && key[smh->cmh[k]->shortcut - 64])
  {
   key[smh->cmh[k]->shortcut - 64] = FALSE;
   smh->ac = k;
   smh->rolled = 0;
   smh->cmh[k]->proc();
  }
  
  if(smh->cmh[k]->shortcut != 'x' && key[KEY_LCONTROL] && key[smh->cmh[k]->shortcut - 64])
  {
   key[smh->cmh[k]->shortcut - 64] = FALSE;
   smh->ac = k;
   smh->rolled = 0;
   smh->cmh[k]->proc();
  } 	   
  if(smh->cmh[k]->shortcut != 'x' && key[KEY_LCONTROL] && key[smh->cmh[k]->shortcut - 96])
  {
   key[smh->cmh[k]->shortcut - 96] = FALSE;
   smh->ac = k;
   smh->rolled = 0;
   smh->cmh[k]->proc();
  }
    if(smh->cmh[k]->shortcut != 'x' && key[KEY_RCONTROL] && key[smh->cmh[k]->shortcut - 96])
  {
   key[smh->cmh[k]->shortcut - 96] = FALSE;
   smh->ac = k;
   smh->rolled = 0;
   smh->cmh[k]->proc();
  }
 }
 
 if (key[KEY_ALT] && smh->rolled == 1)
 {
  for(k = 0; k < smh->nocmh;k++)
  {
   if(key[smh->cmh[k]->mshortcut - 64])
   {
    //smh->rolled = 0;
    smh->ac = k;
    if(smh->cmh[smh->ac]->rollable == 1)smh->cmh[smh->ac]->rolled = 1;
	//smh->cmh[k]->proc();
    key[smh->cmh[k]->mshortcut - 64] = FALSE;
   }
   if(key[smh->cmh[k]->mshortcut - 96])
   {
    //smh->rolled = 0;
    smh->ac = k;
	if(smh->cmh[smh->ac]->rollable == 1)smh->cmh[smh->ac]->rolled = 1;
	//smh->cmh[k]->proc();
    key[smh->cmh[k]->mshortcut - 96] = FALSE;
   }
   
  } 	  
 }
 
 else if(key[KEY_ALT] && key[smh->shortcut - 64] && smh->rolled == 0)
 {
  for(k = 0; k < mmh->nosmh;k++)mmh->smh[k]->rolled = 0;
  smh->rolled = 1;
  key[smh->shortcut - 64] = FALSE;
 }
 else if(key[KEY_ALT] && key[smh->shortcut - 96] && smh->rolled == 0)
 {
  for(k = 0; k < mmh->nosmh;k++)mmh->smh[k]->rolled = 0;
  smh->rolled = 1;
  key[smh->shortcut - 96] = FALSE;
 }
 /**************************************************************************************************/
 
 if(mir(smh->x, 0, smh->x+smh->w, 21, 0) == 1 || smh->rolled == 1) //|| smh->rolled)
 {
  mmh->as = smh->ord;
  rect(bmp,smh->x, 0, smh->x+smh->w, 21, 0xeeeeee);
  rectfill(bmp,smh->x+1, 1, smh->x+smh->w-1, 20, 0x444444);
  if(mouse_b & 1)
  {
   if(smh->rolled == 0)
   {
    for(k = 0; k < mmh->nosmh;k++)mmh->smh[k]->rolled = 0;
    smh->rolled = 1;
   }
   else smh->rolled = 0;
   rest(200);
  } 
 } 
 else rectfill(bmp,smh->x, 0, smh->x+smh->w, 21, 0x888888);
 

 if(mir(smh->x, smh->ac*20 +21, smh->x +140, smh->ac*20 +41, 1) && smh->cmh[smh->ac]->rollable == 1)
 {
  //printf("klikol som na nonrollable cmh...");
  if(smh->cmh[smh->ac]->rolled == 0)
  {
   smh->rolled = 1;//help_me = 1;
   smh->cmh[smh->ac]->rolled = 1;
  }
  else 
  {
   smh->rolled = 1;//help_me = 0;//smh->cmh[smh->ac]->rolled = 0; 				
   smh->cmh[smh->ac]->rolled = 0; 
  }
  rest(100);
 }
 
 if(smh->rolled)
 {
  for(i=0;i<smh->nocmh;i++)
  {
   if(mir(smh->x, 20*i + 23, smh->x+140, 20*i + 41, 0) || smh->ac == i)
   {
   	smh->ac = i;
    if(help_me == 1)smh->rolled = 1;
	if(smh->cmh[i]->rolled == 1)
	{
	 for(k = 0;k < smh->cmh[i]->noumh;k++)
	 {
      if(mir(smh->x+141,i*20 + 23 + k*20, smh->x+281,i*20 + 42 + k*20, 0))
      {
	   smh->cmh[i]->au = k;
	   /*if(mouse_b & 1)// && mir(smh->x+141,i*20 + 23 + k*20, smh->x+281,i*20 + 42 + k*20, 0))
	   {
	    smh->rolled = 0;
		smh->cmh[smh->ac]->rolled = 0;
		smh->cmh[smh->ac]->umh[smh->cmh[smh->ac]->au]->proc();			  
	   }
	   //else if(mouse_b & 1 && !mir(smh->x+141,i*20 + 23 + k*20, smh->x+281,i*20 + 42 + k*20, 0))smh->rolled = 0;
       */	  
	  }
	  
////////////////////////////////////////tunak som skoncil, robil som unit menu...     
	   if(smh->cmh[i]->au == k)
	   {
	    rectfill(bmp,smh->x+141,i*20 + 22 + k*20, smh->x+281,i*20 + 42 + k*20, 0x222222);
	    draw_sprite(bmp,mmh->grad,smh->x+281-mmh->grad->w,i*20 + 22 + k*20);
		alfont_textprintf_aa(bmp,larabie,smh->x+141,i*20 + 22 + k*20,0xff9600,"%s",smh->cmh[smh->ac]->umh[/*smh->cmh[smh->ac]->au*/k]->text);
	   }
	   else 
	   {
	    rectfill(bmp,smh->x+141,i*20 + 22 + k*20, smh->x+281,i*20 + 42 + k*20, 0x666666); 	   
	    alfont_textprintf_aa(bmp,larabie,smh->x+141,i*20 + 22 + k*20,0xffffff,"%s",smh->cmh[smh->ac]->umh[/*smh->cmh[smh->ac]->au*/k]->text);
	   }
	  } 			   
	}
	rectfill(bmp,smh->x, 20*i + 22, smh->x+140, 20*i + 42, 0x222222);
    draw_sprite(mb,mmh->grad,smh->x+140-mmh->grad->w, 20*i + 22);
	
	alfont_textprintf_aa(bmp,larabie, smh->x+6, 20*i+20+3, 0xff9600, "%s", smh->cmh[i]->text);
	if(key[KEY_ALT])line(bmp,smh->x+smh->cmh[i]->slx+6, 20*i +38, smh->x+smh->cmh[i]->elx+6, 20*i + 38, 0xff9600); 						   
    if(smh->cmh[i]->rollable == 1)alfont_textprintf_right_aa(bmp,larabie,smh->x+130, 20*i+23,0,">");
	if(smh->cmh[1]->shortcut != 'x')
	{
	 alfont_set_font_size(larabie,13);
	 alfont_textprintf_right_aa(bmp,larabie,smh->x+133, 20*i+26, 0, "Ctrl + %c", smh->cmh[i]->shortcut);
	 alfont_set_font_size(larabie,17);
    }
    //printf("tu som bol");
	/*if(mouse_b & 1 && smh->cmh[i]->rollable == 0)// && mir(smh->x, 20*i + 22, smh->x+140, 20*i + 42, 0))
    {
	 smh->cmh[i]->proc(); 		   
	 printf("clicked on %s|%s",smh->text, smh->cmh[i]->text);
	 smh->rolled = 0;
    }
    else if (mouse_b & 1 && smh->cmh[i]->rollable == 1)// && mir(smh->x, 20*i + 22, smh->x+140, 20*i + 42, 0))
    {
	 if(smh->cmh[i]->rolled == 0)smh->cmh[i]->rolled = 1;
	 else smh->cmh[i]->rolled = 0;
	 rest(200); 	 
    }/*else if(mouse_b & 1 && smh->cmh[smh->ac]->rolled == 0)
    {
	  smh->rolled = 0;	  
	   }*/
    
    if(smh->cmh[i]->rolled == 0)
    {
     for(l = 0; l < smh->nocmh;l++)
     {
	  smh->cmh[l]->rolled = 0; 	  
     }
    }
   }
   else
   {
    rectfill(bmp,smh->x, 20*i + 22, smh->x+140, 20*i + 42, 0x777777);
    alfont_textprintf_aa(bmp,larabie, smh->x+6, 20*i+20+3, 0xffffff, "%s", smh->cmh[i]->text);
	if(key[KEY_ALT])line(bmp,smh->x+smh->cmh[i]->slx+6, 20*i +38, smh->x+smh->cmh[i]->elx+6, 20*i + 38, 0xffffff);
	if(smh->cmh[1]->shortcut != 'x')
	{
	 alfont_set_font_size(larabie,13);
	 alfont_textprintf_right_aa(bmp,larabie,smh->x+133, 20*i+26, 0xffffff, "Ctrl + %c", smh->cmh[i]->shortcut);
     alfont_set_font_size(larabie,17);
	}
	if(smh->cmh[i]->rollable == 1)alfont_textprintf_right_aa(bmp,larabie,smh->x+130, 20*i+23,0xffffff,">");
	
   }
  }
 }
 
 
 alfont_textprintf_aa(bmp, larabie, smh->x+3, 4, 0xffffff, "%s",smh->text); 	
 //rect(bmp,smh->x, 0, smh->x+smh->w, 21, 0xff9600);
 if(key[KEY_ALT])line(bmp,smh->x + smh->slx+3, 18, smh->x + smh->elx+3, 18, 0xffffff);
 
 
 if(smh->rolled)
 {
  if(key[KEY_UP])
  {
   if(smh->cmh[smh->ac]->rolled == 0)
   {
    smh->ac--;
    key[KEY_UP] = FALSE;
   }
   else
   {
    smh->cmh[smh->ac]->au--;
	key[KEY_UP] = FALSE;	   
   }
  }
  
  if(key[KEY_DOWN])
  {
   if(smh->cmh[smh->ac]->rolled == 0)
   {
    smh->ac++;
    key[KEY_DOWN] = FALSE;
   }
   else
   {
    smh->cmh[smh->ac]->au++;
	key[KEY_DOWN] = FALSE;	   
   }
  }
 
  if(smh->ac == 0)smh->ac = smh->nocmh;
  if(smh->ac == smh->nocmh)smh->ac = 0;
  if(smh->ac == -1)smh->ac = 0;
  
  
  if(smh->cmh[smh->ac]->au == 0)smh->cmh[smh->ac]->au = smh->cmh[smh->ac]->noumh;
  if(smh->cmh[smh->ac]->au == smh->cmh[smh->ac]->noumh)smh->cmh[smh->ac]->au = 0;
  if(smh->cmh[smh->ac]->au == -1)smh->cmh[smh->ac]->au = 0;
  
  
  if(key[KEY_ENTER])
  {
   if(smh->cmh[smh->ac]->rolled == 0)
   {
    if(smh->cmh[smh->ac]->rollable == 1)smh->cmh[smh->ac]->rolled = 1;
    else
    {
	 smh->rolled = 0;
     key[KEY_ENTER] = FALSE;
     smh->cmh[smh->ac]->proc();
    }
   }
   else
   {
    smh->rolled = 0;
    smh->cmh[smh->ac]->rolled = 0;
	key[KEY_ENTER] = FALSE;
    smh->cmh[smh->ac]->umh[smh->cmh[smh->ac]->au]->proc();
    //smh->cmh[smh->ac]->rolled = 1;
   }
  }
  
  if(key[KEY_TAB])
  {
   /*if(smh->ord+1 > mmh->nosmh)
   {
    smh->rolled = 0;
    mmh->smh[0]->rolled = 1;				 
   } 				
   else
   {
    smh->rolled = 0;
	mmh->smh[smh->ord + 1]->rolled = 1;	   
   }*/
   mmh->as++;
   if(mmh->as == mmh->nosmh)
   {
    mmh->as=0;
    mmh->smh[0]->rolled = 1;
   }
   smh->rolled = 0;
   mmh->smh[mmh->as]->rolled = 1;  
   key[KEY_TAB] = FALSE;
   //printf("%d",mmh->as);
  }
  
  if(key[KEY_RIGHT] && smh->cmh[smh->ac]->rollable == 1)
  {
   smh->cmh[smh->ac]->rolled = 1;
   key[KEY_RIGHT] = FALSE;
  }
  
  if(key[KEY_LEFT] && smh->cmh[smh->ac]->rolled == 1)
  {
   smh->cmh[smh->ac]->rolled = 0;
   key[KEY_LEFT] = FALSE; 				   
  }
  
 }
 
 if(key[KEY_ESC])
 {
  smh->rolled = 0;
  key[KEY_ESC] = FALSE; 				 
 }
 
 if(help_me == 1)smh->rolled = 1;
 
 return 1;
}

int draw_mmh(MMH *mmh, BITMAP *bmp)
{
 int i;
 alfont_set_font_size(larabie,17);
 //vsync();
 rectfill(bmp,0,0,SCREEN_W,21,0x888888);
 for(i=0;i<mmh->nosmh;i++)draw_smh(mmh, mmh->smh[i], bmp);
 alfont_textprintf_aa(bmp,larabie,SCREEN_W-200, 3, 0xffffff, "DLX Games");
 //á 225
 //è 232
  //float rr = 0.0;
    //rr+=0.5;
    //circle(mb, cos(rr/360 * 2 * 3.14)*100, sin(rr/360 * 2 * 3.14)*100, 5, 0xff9600);
//printf("%f",cos(rr/360 * 2 * 3.14)*100);
 
 
 return 1; 	
}
/*
File - Menu
New - Odznova
Open - Otvor
Save - Zachovaj
Save As - Zachovaj ako
Quit - Koniec

About - O programe
Help - Pomoc
Visit Us - Web
Credits - Autori*/

int make_menu()
{
menu = init_mmh();
 	
 	upcell = init_smh("Menu",'M',0,40);
 	
    cell = init_cmh("Odznova",'O',new_cell_act);
    add_scut_info(cell,'N');
 	stick_cmh_to_smh(cell,upcell);
 	
    cell = init_cmh("Otvor",'t',open_cell_act);
 	add_scut_info(cell,'O');
    stick_cmh_to_smh(cell,upcell);
    
 	cell = init_cmh("Nahraj",'N',save_as_cell_act);
 	add_scut_info(cell,'S');
	stick_cmh_to_smh(cell,upcell);
	
 	cell = init_cmh("Nahraj ako...",'a',save_as_cell_act);
 	add_scut_info(cell,'A');
	stick_cmh_to_smh(cell,upcell);
	
	
 	cell = init_cmh("Koniec",'K',quit_cell_act);
 	add_scut_info(cell,'Q');
    stick_cmh_to_smh(cell,upcell);
	
	stick_smh_to_mmh(upcell,menu);
	
	//edit upcell
	upcell2 = init_smh("Pridaj",'P',41,40);
	
	cell = init_cmh("Kocka",'K',new_cell_act);
	//add_scut_info(cell, 'Z');
 	cell->rollable = 1;
 	
      unit = init_umh("Klasik",'l',klasik_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Revers",'r',reverse_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Smrt",'S',smrt_action);
      stick_umh_to_cmh(unit,cell);
     
    stick_cmh_to_smh(cell,upcell2);
 	
	cell = init_cmh("Voda",'V',new_cell_act);//tunak ma byt ina action
 	//add_scut_info(cell, 'Y');
    cell->rollable = 1;
    
      unit = init_umh("Jazero",'J',water_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Prechod 1",'1',water1_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Prechod 2",'2',water2_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Prechod 3",'3',water3_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Prechod 4",'4',water4_action);
      stick_umh_to_cmh(unit,cell);
    
    
    stick_cmh_to_smh(cell,upcell2);
 	
	 cell = init_cmh("Zelina",'Z',new_cell_act);//tunak ma byt ina action
 	//add_scut_info(cell, 'C');
    cell->rollable = 1;
    
      unit = init_umh("Plocha",'J',trava_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Prechod 1",'1',trava1_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Prechod 2",'2',trava2_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Prechod 3",'3',trava3_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Prechod 4",'4',trava4_action);
      stick_umh_to_cmh(unit,cell);
    
    
    stick_cmh_to_smh(cell,upcell2);
    
 	
	 cell = init_cmh("Pexeso",'P',new_cell_act);//tunak ma byt ina action
 	//add_scut_info(cell, 'V');
 	cell->rollable = 1;
 	
	  unit = init_umh("Symbol 1",'1',symbol1_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Symbol 2",'2',symbol2_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Symbol 3",'3',symbol3_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Symbol 4",'4',symbol4_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Symbol 5",'5',symbol5_action);
      stick_umh_to_cmh(unit,cell);
     
     stick_cmh_to_smh(cell,upcell2);
 	
	 cell = init_cmh("Lejzer",'O',new_cell_act);//tunak ma byt ina action
 	//add_scut_info(cell, 'X');
	 stick_cmh_to_smh(cell,upcell2);
	cell->rollable = 1;
 
      unit = init_umh("Lezaty 1",'1', laser1_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Lezaty 2",'2',laser1b_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Stojaty 1",'S',laser2_action);
      stick_umh_to_cmh(unit,cell); 
      unit = init_umh("Stojaty 2",'t',laser2b_action);
      stick_umh_to_cmh(unit,cell);   
      
	 cell = init_cmh("Vietor",'V',new_cell_act);//tunak ma byt ina action
 	//add_scut_info(cell, 'X');
	 stick_cmh_to_smh(cell,upcell2);
	cell->rollable = 1;
 
      unit = init_umh("Hore",'1', hore_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Doprava",'2',doprava_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Dole",'S',dole_action);
      stick_umh_to_cmh(unit,cell); 
      unit = init_umh("Dolava",'t',dolava_action);
      stick_umh_to_cmh(unit,cell);        
	
	cell = init_cmh("Ostatok",'O',new_cell_act);//tunak ma byt ina action
 	//add_scut_info(cell, 'X');
 	cell->rollable = 1;
 	
 	  unit = init_umh("Teleport",'T',teleport_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Start",'1',start_action);
      stick_umh_to_cmh(unit,cell);
      unit = init_umh("Koniec",'2',ostat_koniec_action);
      stick_umh_to_cmh(unit,cell);
      
	 stick_cmh_to_smh(cell,upcell2);
	
	
	stick_smh_to_mmh(upcell2,menu);
	
	//upcell3 = init_smh("Object",'O',82,55);
	
 /*	cell = init_cmh("Insert", 'I', new_cell_act);
	stick_cmh_to_smh(cell, upcell3);
	cell = init_cmh("Bring to", 'B', new_cell_act);
	cell->rollable = 1;
	unit = init_umh("Forward", 'F', new_cell_act);
	stick_umh_to_cmh(unit,cell);
	
	unit = init_umh("Backward", 'F', new_cell_act);
	
	stick_umh_to_cmh(unit,cell);
	stick_cmh_to_smh(cell,upcell3);
	stick_smh_to_mmh(upcell3,menu);
	
	/*upcell4 = init_smh("Project",'j',82+56,55);
	 cell = init_cmh("Color Tone",'C',new_cell_act);
	 cell->rollable = 1;
	  unit = init_umh("Sepia Tone",'S',new_cell_act);
	  stick_umh_to_cmh(unit,cell);
 	  unit = init_umh("Grayscale",'G',ppp);
	 stick_umh_to_cmh(unit,cell);
	
   stick_cmh_to_smh(cell,upcell4);
 	cell = init_cmh("Invert",'I',new_cell_act);
   stick_cmh_to_smh(cell,upcell4);
 	
 	
	//stick_cmh_to_smh(cell,upcell4);
	stick_smh_to_mmh(upcell4,menu);*/
	
	/*upcell45 = init_smh("Window", 'W', 82+56, 66);
	
	cell = init_cmh("Cascade", 'C', new_cell_act);
	stick_cmh_to_smh(cell, upcell45);
	cell = init_cmh("Tile", 'T', new_cell_act);
	stick_cmh_to_smh(cell, upcell45);
	
	/*cell = init_cmh("Help",'H',new_cell_act);
 	stick_cmh_to_smh(cell,upcell45);
 	cell = init_cmh("Visit Us...",'V',new_cell_act);//tunak ma byt ina action
 	stick_cmh_to_smh(cell,upcell45);
 	cell = init_cmh("Credits",'C',new_cell_act);//tunak ma byt ina action
 	stick_cmh_to_smh(cell,upcell45);*/
 	
	/*stick_smh_to_mmh(upcell45, menu);
	
*/	
	upcell5 = init_smh("O programe",'r',41+40+1,48*2 - 12);
	
	cell = init_cmh("Pomoc",'P',new_cell_act);
 	stick_cmh_to_smh(cell,upcell5);
 	cell = init_cmh("Web",'W',visit_us_action);
 	stick_cmh_to_smh(cell,upcell5);
 	cell = init_cmh("Autori",'A',credits_action);
 	stick_cmh_to_smh(cell,upcell5);
 	
	
	stick_smh_to_mmh(upcell5,menu);
	 	
return 1;
}

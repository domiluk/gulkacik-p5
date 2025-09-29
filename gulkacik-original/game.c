#include <allegro.h>
#include <winalleg.h>
#include <apeg.h>
#include <ogg/ogg.h>

#include <vorbis/codec.h>
#include <winsock2.h>
#include "ipbox.h"
#include "ws.h"
#include "ogg.h"


#include <stdio.h>

#define POLOMER 60

//hra 90/150  nastavenia su 90/240  autori 90/325  xko suradnice 670, 0



void darkness(BITMAP *bmp, int x1, int y1, int x2, int y2)
{
 int x, y, r, g, b, c;
 
 for(x = x1; x < x2; x++)
 for(y = y1; y < y2; y++)
 {
  c = getpixel(bmp, x, y);
  r = getr(c);     
  g = getr(c);
  b = getr(c); 
  
  if(r < 128)r = 128;
  if(g < 128)g = 128;
  if(b < 128)b = 128;
  putpixel(bmp, x, y, makecol(r-128, g-128, b-128));
 }
}

BITMAP *mb1,
    *mb2;
int q[10] = {3,3,3,3,3,3,3,3,3,3}, hlp;

BITMAP *mb, *main_menu, *main_hra, *main_aut, *main_nast, *main_xko, *ps_pripojit;
BITMAP *nastavenia, *sipka, *check_box, *pribeh, *volnahra, *lokalnahra;
BITMAP *autori, *zalozitserver, *pripojitsa, *slred, *slyellow, *slblue;
BITMAP *hra, *naozajukoncit, *nu_ano, *nu_nie, *nu_xko, *nacitatlevel, *nl_start;
BITMAP *pripojit, *zalozitsrv, *zs_pokracuj, *check1, *check2;
OGGFILE *gulkacik;
BITMAP *trhanec;
int koniec;
WSADATA wsaData;
char *my_ip;
LB *levbr;
IPBOX *ipbox;
int whattastart;
char wt[6];

int mp_mode = 1;
FILE *eff;
int fhudba = 520, fzvuk = 520, fbalans = 520;
int i = 0;

int mir(int x1, int y1, int x2, int y2, int bp)
{
  if(bp == 0){
    if(mouse_x >= x1 && mouse_x <= x2 && mouse_y >= y1 && mouse_y <= y2)
      return 1;
    else return 0;
  }
  else{
    if(mouse_x >= x1 && mouse_x <= x2 && mouse_y >= y1 && mouse_y <= y2 && mouse_b & bp)
      return 1;
    else return 0;
  }
}

int sketch_to_hra()
{
 int x, y;    
 fscanf(eff, "%d %d", &x, &y);     
 blit(hra, mb, x-POLOMER, y-POLOMER, x, y, POLOMER, POLOMER);
 
 if(x == -50)return 2;
 else return 1;
}

int count_mb(BITMAP *bmp, BALL *b, int *x, int *y)
{
 if(b->x > (bmp->w/2) && b->x < lvl->bmp->w-bmp->w/2)
  *x = b->x - bmp->w/2;
 else if(b->x < bmp->w/2)
  *x = 0;
 else
  *x = lvl->bmp->w-bmp->w;
 
 if(b->y > (bmp->h/2) && b->y < lvl->bmp->h-bmp->h/2)
  *y = b->y - bmp->h/2;
 else if(b->y < bmp->h/2)
  *y = 0;
 else
  *y = lvl->bmp->h-bmp->h;
 
 if(*x < 0) *x = 0;
 if(*y < 0) *y = 0;
}

char *get_my_ip()
{
 char ac[80];
 gethostname(ac, sizeof(ac));
 struct hostent *phe = gethostbyname(ac);
 struct in_addr addr;
 memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
 return inet_ntoa(addr);
}



int fulskrin_on = 1;

int main()
{
 allegro_init();
 set_color_depth(32);
 set_gfx_mode(2, 800, 600, 0, 0);
 
 install_keyboard();
 install_mouse(); 
 install_timer();
 install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);

 
 LOCK_VARIABLE(bt);
 LOCK_FUNCTION(increase_time);
 bt = 0;
 install_int(increase_time, 1000);
 
 WSAStartup(MAKEWORD(2, 2), &wsaData);    
 
 koniec = 0;
 mode = 0;
 
 set_display_switch_mode(SWITCH_BACKGROUND);
 
 srand(time(NULL));
 
 st = turned = 0;
 
 init_dl_font();
 
 
 smp_normal = load_sample("./sounds/normal.wav");
 smp_die = load_sample("./sounds/diebrick.wav");
 smp_water = load_sample("./sounds/water.wav");
 smp_grass = load_sample("./sounds/grass.wav");
 smp_teleport = load_sample("./sounds/teleport.wav");
 smp_symbol = load_sample("./sounds/symbol.wav");
 h_die = load_sample("./sounds/h_die.wav");
 h_teleport[0] = load_sample("./sounds/h_teleport.wav");
 h_teleport[1] = load_sample("./sounds/h_teleport2.wav");
 h_teleport[2] = load_sample("./sounds/h_teleport3.wav");
 h_level[0] = load_sample("./sounds/h_level.wav");
 h_level[1] = load_sample("./sounds/h_level2.wav");
 h_level[2] = load_sample("./sounds/h_level3.wav");
 h_revers[0] = load_sample("./sounds/h_revers.wav");
 h_revers[1] = load_sample("./sounds/h_revers2.wav");
 
 gulkacik = open_ogg_file("gulkacik.ogg");
 
 printf("All sounds loaded");
 
 mb = create_bitmap(800, 600);
 main_menu = load_bitmap("main_menu.bmp", NULL);
 main_xko = load_bitmap("xko.bmp", NULL);
 main_aut = load_bitmap("menudlx_aut.bmp", NULL);
 main_hra = load_bitmap("menudlx_hra.bmp", NULL);
 main_nast = load_bitmap("menudlx_nast.bmp", NULL);
 hra = load_bitmap("hra.bmp", NULL);
 autori = load_bitmap("autori.bmp", NULL);
 nastavenia = load_bitmap("nastavenia.bmp", NULL);
 sipka = load_bitmap("sipka.bmp", NULL);
 check_box = load_bitmap("checkbox.bmp", NULL);
 pribeh = load_bitmap("pribeh.bmp", NULL);
 volnahra = load_bitmap("volnahra.bmp", NULL);
 lokalnahra = load_bitmap("lokalnahra.bmp", NULL);
 zalozitserver = load_bitmap("zalozitserver.bmp", NULL);
 pripojitsa = load_bitmap("pripojitsa.bmp", NULL);
 slred = load_bitmap("slred.bmp", NULL);
 slblue = load_bitmap("slblue.bmp", NULL);
 slyellow = load_bitmap("slyellow.bmp", NULL);
 naozajukoncit = load_bitmap("naozajukoncit.bmp", NULL);
 nu_ano = load_bitmap("nu_ano.bmp", NULL);
 nu_nie = load_bitmap("nu_nie.bmp", NULL);
 nu_xko = load_bitmap("nu_xko.bmp", NULL);
 nacitatlevel = load_bitmap("nacitatlevel.bmp", NULL);
 nl_start = load_bitmap("nl_start.bmp", NULL);
 pripojit = load_bitmap("pripojit.bmp", NULL);
 active = load_bitmap("red_aa.bmp", NULL);
 ps_pripojit = load_bitmap("ps_pripojit.bmp", NULL);
 nl_start = load_bitmap("nl_start.bmp", NULL);
 zalozitsrv = load_bitmap("zalozitsrv.bmp", NULL);
 zs_pokracuj = load_bitmap("zs_pokracuj.bmp", NULL);
 check1 = load_bitmap("check1.bmp", NULL);
 check2 = load_bitmap("check2.bmp", NULL);
 normal_brick[0] = load_bitmap("graphics/kocka01.bmp", NULL);
 normal_brick[1] = load_bitmap("graphics/kocka02.bmp", NULL);
 normal_brick[2] = load_bitmap("graphics/kocka03.bmp", NULL);
 normal_brick[3] = load_bitmap("graphics/kocka04.bmp", NULL);
 normal_brick[4] = load_bitmap("graphics/kocka05.bmp", NULL);
 normal_brick[5] = load_bitmap("graphics/kocka06.bmp", NULL);
 normal_brick[6] = load_bitmap("graphics/kocka07.bmp", NULL);
 normal_brick[7] = load_bitmap("graphics/kocka08.bmp", NULL);
 normal_brick[8] = load_bitmap("graphics/kocka09.bmp", NULL);
 normal_brick[9] = load_bitmap("graphics/kocka10.bmp", NULL);
 normal_brick[10] = load_bitmap("graphics/kocka11.bmp", NULL);
 normal_brick[11] = load_bitmap("graphics/kocka12.bmp", NULL);
 normal_brick[12] = load_bitmap("graphics/kocka13.bmp", NULL);
 water_field[0] = load_bitmap("graphics/water.bmp", NULL); 
 water_field[1] = load_bitmap("graphics/water1.bmp", NULL);
 water_field[2] = load_bitmap("graphics/water2.bmp", NULL);
 water_field[3] = load_bitmap("graphics/water3.bmp", NULL);
 water_field[4] = load_bitmap("graphics/water4.bmp", NULL);
 qm[0] = load_bitmap("graphics/otaznik01.bmp", NULL);
 qm[1] = load_bitmap("graphics/otaznik02.bmp", NULL);
 qm[2] = load_bitmap("graphics/otaznik03.bmp", NULL);
 qm[3] = load_bitmap("graphics/otaznik04.bmp", NULL);
 symbol_brick[0] = load_bitmap("graphics/sym_ciara01.bmp", NULL);
 symbol_brick[1] = load_bitmap("graphics/sym_koso01.bmp", NULL);
 symbol_brick[2] = load_bitmap("graphics/sym_kruh01.bmp", NULL);
 symbol_brick[3] = load_bitmap("graphics/sym_plusko01.bmp", NULL);
 symbol_brick[4] = load_bitmap("graphics/sym_trojuholnik01.bmp", NULL);
 symbol_brick[5] = load_bitmap("graphics/sym_ciara01c.bmp", NULL);
 symbol_brick[6] = load_bitmap("graphics/sym_koso01c.bmp", NULL);
 symbol_brick[7] = load_bitmap("graphics/sym_kruh01c.bmp", NULL);
 symbol_brick[8] = load_bitmap("graphics/sym_plusko01c.bmp", NULL);
 symbol_brick[9] = load_bitmap("graphics/sym_trojuholnik01c.bmp", NULL);
 grass_field[0] = load_bitmap("graphics/trava.bmp", NULL);
 grass_field[1] = load_bitmap("graphics/trava1.bmp", NULL);
 grass_field[2] = load_bitmap("graphics/trava2.bmp", NULL);
 grass_field[3] = load_bitmap("graphics/trava3.bmp", NULL);
 grass_field[4] = load_bitmap("graphics/trava4.bmp", NULL);
 arrow[0] = load_bitmap("graphics/sipka_hore.bmp", NULL);
 arrow[1] = load_bitmap("graphics/sipka_doprava.bmp", NULL);
 arrow[2] = load_bitmap("graphics/sipka_dole.bmp", NULL);
 arrow[3] = load_bitmap("graphics/sipka_dolava.bmp", NULL);
 reverse = qm[0];
 diebrick = load_bitmap("graphics/diebrick.bmp", NULL);
 teleport = load_bitmap("graphics/teleport.bmp", NULL);
 teleport2 = load_bitmap("graphics/teleport2.bmp", NULL);
 laser_h_off = load_bitmap("graphics/laser_hor_vyp.bmp", NULL);
 laser_h_on = load_bitmap("graphics/laser_hor_zap.bmp", NULL);
 laser_v_off = load_bitmap("graphics/laser_ver_vyp.bmp", NULL);
 laser_v_on = load_bitmap("graphics/laser_ver_zap.bmp", NULL);
 endlevel = load_bitmap("graphics/diera.bmp", NULL);
 bg = load_bitmap("graphics/bg.bmp", NULL);
 trhanec = load_bitmap("trhanec.bmp", NULL);
 
 
 
 my_ip = get_my_ip();
 
 levbr = init_lb("./levels/*.gud", 206, 218);
 ipbox = init_ipbox(306, 258);
 
 
 //eff = fopen("data.eff", "r");
 
 system("rm game.o");
 
 
 
 apeg_play_mpg("dlx01.ogg", screen, 0, keypressed); 
 
 play_ogg_file(gulkacik, BUFSZ, 255, 128);   
 while(koniec == 0)
 {
  if(poll_ogg_file(gulkacik) == ALOGG_POLL_PLAYJUSTFINISHED)
  {
   printf("KKS END\n");
   
   close_ogg_file(gulkacik);
   gulkacik = open_ogg_file("gulkacik.ogg");
   play_ogg_file(gulkacik, BUFSZ, 255, 128);
  }
  if(key[KEY_V])mode = 10;
  
  //naozajukoncit    ano=200/350 nie=440/370 xko=x570/160
  
  if(mode == -1)
  {
   show_mouse(NULL);
   blit(naozajukoncit, mb, 0, 0, 0, 0, 800, 600);
   
   if(key[KEY_ESC])mode = 0;
   
   if(mir(200, 350, 200+nu_ano->w, 350+nu_ano->h, 0))
   {
    blit(nu_ano, mb, 0, 0, 200, 350, nu_ano->w, nu_ano->h);
    if(mouse_b & 1)koniec = 1;            
   }
   
   if(mir(440, 370, 440+nu_nie->w, 370+nu_nie->h, 0))
   {
    blit(nu_nie, mb, 0, 0, 440, 370, nu_nie->w, nu_nie->h);
    if(mouse_b & 1)mode = 0;            
   }
   
   if(mir(570, 160, 570+nu_xko->w, 160+nu_xko->h, 0))
   {
    blit(nu_xko, mb, 0, 0, 570, 160, nu_xko->w, nu_xko->h);
    if(mouse_b & 1)mode = 0;            
   }
   
   show_mouse(mb);
   blit(mb, screen, 0, 0, 0, 0, 800, 600);        
  }
  
  //nacitatlevel 480 380
  if(mode == -2)
  {
   show_mouse(NULL);
   blit(nacitatlevel, mb, 0, 0, 0, 0, 800, 600);
   
   if(key[KEY_ESC])mode = 1;
   
   if(mir(570, 160, 570+nu_xko->w, 160+nu_xko->h, 0))
   {
    blit(nu_xko, mb, 0, 0, 570, 160, nu_xko->w, nu_xko->h);
    if(mouse_b & 1)mode = 1;            
   }
   
   if(mir(480, 380, 480+nl_start->w, 380+nl_start->h, 0))
   {
    blit(nl_start, mb, 0, 0, 480, 380, nl_start->w, nl_start->h);
    
    if(mouse_b & 1)
    {
     if(whattastart == -1)mode = 10; //volna hra
     if(whattastart == -2)mode = 12; //lokalka 
     if(whattastart == -3)mode = 19; //vs server
     if(whattastart == -4)mode = 20; //coop server               
    }
   }
   
   draw_lb(mb, levbr);
   show_mouse(mb);
   blit(mb, screen, 0, 0, 0, 0, 800, 600);        
  }
  
    //pripojit [13:25:39] 410_385
  if(mode == -3)
  {
   show_mouse(NULL);
   blit(pripojit, mb, 0, 0, 0, 0, 800, 600);
   
   if(key[KEY_ESC])mode = 1;
   
   if(mir(570, 160, 570+nu_xko->w, 160+nu_xko->h, 0))
   {
    blit(nu_xko, mb, 0, 0, 570, 160, nu_xko->w, nu_xko->h);
    if(mouse_b & 1)mode = 1;            
   }
   
   if(mir(410, 385, 410+ps_pripojit->w, 385+ps_pripojit->h, 0))
   {
    blit(ps_pripojit, mb, 0, 0, 410, 385, ps_pripojit->w, ps_pripojit->h);
    if(mouse_b & 1)
    {
     mode = 13;            
     strncpy(ip, ipbox->ip, ipbox->cur);
     printf("IP> %s <php> %s\n", ip, ipbox->ip);
    } 
   }
   
   
   draw_ipbox(mb, ipbox);
   
   show_mouse(mb);
   blit(mb, screen, 0, 0, 0, 0, 800, 600);        
  }
  
  //zalozitsrv 400 / 420
  if(mode == -4)
  {
   show_mouse(NULL);
   blit(zalozitsrv, mb, 0, 0, 0, 0, 800, 600);
   
   if(key[KEY_ESC])mode = 1;
   
   if(mir(570, 160, 570+nu_xko->w, 160+nu_xko->h, 0))
   {
    blit(nu_xko, mb, 0, 0, 570, 160, nu_xko->w, nu_xko->h);
    if(mouse_b & 1)mode = 1;            
   }
   
   if(mir(400, 420, 400+zs_pokracuj->w, 420+zs_pokracuj->h, 0))
   {
    blit(zs_pokracuj, mb, 0, 0, 400, 420, zs_pokracuj->w, zs_pokracuj->h);
    if(mouse_b & 1)
    {
     mode = -2;            
     if(mp_mode == 1)whattastart = -3;
     else whattastart = -4;
    }
   }
   
   if(mp_mode == 1)blit(check1, mb, 0, 0, 225, 220, check1->w, check1->h);
   else  blit(check2, mb, 0, 0, 225, 270, check1->w, check1->h);  
   
   if(mir(225, 220, 225+check1->w, 220+check1->h, 1))mp_mode = 1;
   if(mir(225, 270, 225+check1->w, 270+check1->h, 1))mp_mode = 2;
   
   write_by_hand(mb, "20001", 415, 370);
   write_by_hand(mb, my_ip, 395, 334);
   
   show_mouse(mb);
   blit(mb, screen, 0, 0, 0, 0, 800, 600);        
  }
  
  
  //main
  if(mode == 0)
  {
   show_mouse(NULL);
   blit(main_menu, mb, 0, 0, 0, 0, 800, 600);
   
   //xko
   if(mir(670, 0, 670+main_xko->w,main_xko->h, 0))
   {
    blit(main_xko, mb, 0, 0, 670, 0, main_xko->w,main_xko->h);
    if(mouse_b & 1)mode = -1;            
   }
   
   //autori 90/325
   if(mir(90, 325, 90+main_aut->w,325+main_aut->h, 0))
   {
    blit(main_aut, mb, 0, 0, 90, 325, main_aut->w,main_aut->h);
    if(mouse_b & 1)
    {
     apeg_play_mpg("m2a.ogg", screen, 0, NULL);
     mode = 3;            
    } 
   }
   
   //hra 90/150
   if(mir(90, 150, 90+main_hra->w,150+main_hra->h, 0))
   {
    blit(main_hra, mb, 0, 0, 90, 150, main_hra->w,main_hra->h);
    if(mouse_b & 1)
    {

     mode = 1;            
     rest(120);
     /*while(sketch_to_hra() == 1)
     {
      printf("aha");
      blit(mb, screen, 0, 0, 0, 0, 800, 600);                    
     }*/
    } 
   }
   
   //nastavenia 90/240
   if(mir(90, 240, 90+main_nast->w,240+main_nast->h, 0))
   {
    blit(main_nast, mb, 0, 0, 90, 240, main_nast->w,main_nast->h);
    
     if(mouse_b & 1)mode = 2;            
   }
   
   show_mouse(mb);
   blit(mb, screen, 0, 0, 0, 0, 800, 600);                      
  }
  
  //hra pribeh.bmp 140/220,, volnahra.bmp 140/290,, lokalnahra.bmp 140/400
  if(mode == 1)
  {
   show_mouse(NULL);
   blit(hra, mb, 0, 0, 0, 0, 800, 600);
   
   
   if(mir(660, 0, 670+sipka->w,sipka->h, 0))
   {
    blit(sipka, mb, 0, 0, 660, 0, sipka->w,sipka->h);
    if(mouse_b & 1)
    {
     mode = 0;
     rest(300);            
    } 
   }
   
   //offtopic zalozitserver.bmp 140/450,, pripojitsa.bmp 140/510
   
   if(mir(140,220, 140+pribeh->w, 220+pribeh->h, 0))
   {
    blit(pribeh, mb, 0, 0, 140, 220, pribeh->w,pribeh->h);
    if(mouse_b & 1)
    {
     mode = 11;           
    }                
   }
   
   if(mir(140,290, 140+volnahra->w, 290+volnahra->h, 0))
   {
    blit(volnahra, mb, 0, 0, 140, 290, volnahra->w,volnahra->h);
    if(mouse_b & 1)
    {
     mode = -2;                
     whattastart = -1;
    }
   }
   
   if(mir(140,400, 140+lokalnahra->w, 400+lokalnahra->h, 0))
   {
    blit(lokalnahra, mb, 0, 0, 140, 400, lokalnahra->w,lokalnahra->h);
    if(mouse_b & 1)
    {
     mode = -2;                
     whattastart = -2;
    } 
   }
   
   if(mir(140,450, 140+zalozitserver->w, 450+zalozitserver->h, 0))
   {
    blit(zalozitserver, mb, 0, 0, 140, 450, zalozitserver->w,zalozitserver->h); 
    if(mouse_b & 1)
    {
     mode = -4;               
     rest(120);
    }
   }
   
   if(mir(140,510, 140+pripojitsa->w, 510+pripojitsa->h, 0))
   {
    blit(pripojitsa, mb, 0, 0, 140, 510, pripojitsa->w,pripojitsa->h); 
    if(mouse_b & 1)mode =-3;               
   }
   
   show_mouse(mb);
   blit(mb, screen, 0, 0, 0, 0, 800, 600);        
  }
  
    //autori
  if(mode == 3)
  {
   show_mouse(NULL);
   blit(autori, mb, 0, 0, 0, 0, 800, 600);
   
   
   if(mir(660, 0, 670+sipka->w,sipka->h, 0))
   {
    blit(sipka, mb, 0, 0, 660, 0, sipka->w,sipka->h);
    if(mouse_b & 1)
    {
     mode = 0;
     rest(300);            
    } 
   }
   
   show_mouse(mb);
   blit(mb, screen, 0, 0, 0, 0, 800, 600);        
  }
  
    //nastavenia checkbox.bmp 120/220
  if(mode == 2)
  {
   show_mouse(NULL);
   blit(nastavenia, mb, 0, 0, 0, 0, 800, 600);
   
   if(mir(660, 0, 670+sipka->w,sipka->h, 0))
   {
    blit(sipka, mb, 0, 0, 660, 0, sipka->w,sipka->h);
    if(mouse_b & 1)
    {
     mode = 0;
     rest(300);            
    } 
   }
   
   if(fulskrin_on == 1) draw_sprite(mb, check_box, 120, 220);
   
   if(mir(120, 220, 120+check_box->w, 220+check_box->h, 1))
   {
    if(fulskrin_on == 1)fulskrin_on = 0;
    else fulskrin_on = 1;
    
    rest(200);            
   }
  
   if(mir(fhudba, 360, fhudba+slred->w, 360+slred->h, 1))
   {
    show_mouse(NULL);
    blit(nastavenia, mb, 0, 0, 0, 0, 800, 600);
    
    if(fulskrin_on == 1) draw_sprite(mb, check_box, 120, 220);
    
    draw_sprite(mb,slred, fhudba, 360); 
    draw_sprite(mb,slyellow, fzvuk, 405);
    draw_sprite(mb,slblue, fbalans, 450);  
    
    fhudba = mouse_x-20;
    
    if(fhudba < 310)fhudba = 310;
    if(fhudba > 730)fhudba = 730;
    
    show_mouse(mb);
    blit(mb, screen, 0, 0, 0, 0, 800, 600);             
   } 
   
   
   if(mir(fzvuk, 405, fzvuk+slred->w, 405+slred->h, 1))
   {
    show_mouse(NULL);
    blit(nastavenia, mb, 0, 0, 0, 0, 800, 600);
    
    if(fulskrin_on == 1) draw_sprite(mb, check_box, 120, 220);
    
    draw_sprite(mb,slred, fhudba, 360); 
    draw_sprite(mb,slyellow, fzvuk, 405);
    draw_sprite(mb,slblue, fbalans, 450);  
    
    fzvuk = mouse_x-20;
    
    if(fzvuk < 310)fzvuk = 310;
    if(fzvuk > 730)fzvuk = 730;
    
    show_mouse(mb);
    blit(mb, screen, 0, 0, 0, 0, 800, 600);             
   }
   
   if(mir(fbalans, 450, fbalans+slred->w, 450+slred->h, 1))
   {
    show_mouse(NULL);
    blit(nastavenia, mb, 0, 0, 0, 0, 800, 600);
    
    if(fulskrin_on == 1) draw_sprite(mb, check_box, 120, 220);
    
    draw_sprite(mb,slred, fhudba, 360); 
    draw_sprite(mb,slyellow, fzvuk, 405);
    draw_sprite(mb,slblue, fbalans, 450);  
    
    fbalans = mouse_x-20;
    
    if(fbalans < 310)fbalans = 310;
    if(fbalans > 730)fbalans = 730;
    
    show_mouse(mb);
    blit(mb, screen, 0, 0, 0, 0, 800, 600);             
   }
   
  
   draw_sprite(mb,slred, fhudba, 360); 
   draw_sprite(mb,slyellow, fzvuk, 405);
   draw_sprite(mb,slblue, fbalans, 450);
   
   show_mouse(mb);
   blit(mb, screen, 0, 0, 0, 0, 800, 600);        
  }
  
  char meno_levela[32];
  //volna hra
  if(mode == 10)
  {
   strcpy(meno_levela, "./levels/");
   strcat(meno_levela, levbr->flee[levbr->active].real_name);
   splscr = 0;
    printf("pokusim sa nacitat> %s", meno_levela);
   lvl = init_level(meno_levela);//<- toto zmenis na init_level(nazov_levelu_ktory_bol_vybraty);

   bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
   //install_int(increase_time, 1000);
   bt = 0;
   install_int(manage_water_bll, 1000);
   install_int(blick_laser, 1500);
					 
   while(!key[KEY_ESC])
   {
    pageupdn();
	count_mb(mb, bll, &drawx1, &drawy1);
	blit(lvl->bmp, mb, drawx1, drawy1, 0, 0, mb->w, mb->h);
	manage_ball(bll, mb, NULL, 0);
	manage_grass(bll);
	textprintf(mb, font, 0,0, biela, "LEVEL %d PTS: %d TIME: %2d:%2d", curlevel+1, bll->points, bt/60, bt%60);
	draw_sprite(mb, trhanec, 0,0);	
    wt[0] = 48+((bt/60)/10);
    wt[1] = 48+((bt/60)%10);
    wt[2] = '.';
    wt[3] = 48+((bt%60)/10);
    wt[4] = 48+((bt%60)%10);
    wt[5] = '\0';
    printf("%d%d:%d%d\n", ((bt/60)/10), ((bt/60)%10), ((bt%60)/10), ((bt%60)%10));
    write_by_hand(mb, wt, 30,24);
    for(i = 0; i < bll->lives*25; i+=25)
    {
     stretch_sprite(mb, bll->bmp, 5+i, 55, 20, 20);
    }
	blit(mb, screen, 0,0,0,0,800,600);
	if(lvl->winner > 0)
	{
     key[KEY_ESC] = TRUE;
	}
   }//while
   stop_sample(smp_water);
   stop_sample(smp_grass);
   //remove_int(increase_time);
   remove_int(manage_water_bll);
   remove_int(blick_laser);
   mode = 0;        
  }
  //lokalna hra
  if(mode == 12)
  {
   curlevel = 0;
   splscr = 1;
   strcpy(meno_levela, "./levels/");
   strcat(meno_levela, levbr->flee[levbr->active].real_name);
   splscr = 0;
   printf("pokusim sa nacitat> %s", meno_levela);
   lvl = init_level(meno_levela);//<- toto zmenis na init_level(nazov_levelu_ktory_bol_vybraty);

   bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
   bll2 = init_ball("graphics/gulicka.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by+100);
   install_int(manage_water_bll, 1000);
   install_int(manage_water_bll2, 1000);
   install_int(blick_laser, 1500);
   mb1 = create_bitmap(SCREEN_W/2, SCREEN_H);
   mb2 = create_bitmap(SCREEN_W/2, SCREEN_H);

   while(!key[KEY_ESC])
   {
    pageupdn();
    count_mb(mb1, bll, &drawx1, &drawy1);
    count_mb(mb2, bll2, &drawx2, &drawy2);

    blit(lvl->bmp, mb1, drawx1, drawy1, 0,0, SCREEN_W/2, SCREEN_H);
    blit(lvl->bmp, mb2, drawx2, drawy2, 0,0, SCREEN_W/2, SCREEN_H);

    manage_ball(bll, mb1, mb2, 1);
    manage_ball(bll2, mb2, mb1, 1);
    bounce_balls(bll, bll2);
    manage_grass(bll);
    manage_grass(bll2);
    textprintf(mb2, font, 0,0, biela, "%2d:%2d", bll->points, bll2->points);
    textprintf(mb2, font, 0,8, biela, "%d:%d", bll->tmppts, bll2->tmppts);

    draw_sprite(mb2, trhanec, 0,0);
    for(i = 0; i < bll->lives*25; i+=25)
    {
     stretch_sprite(mb2, bll->bmp, 35+i, 25, 20, 20);
    }
    for(i = 0; i < bll2->lives*25; i+=25)
    {
     stretch_sprite(mb2, bll2->bmp, 5+i, 55, 20, 20);
    }

    blit(mb2, screen, 0,0,0,0,399,600);
    blit(mb1, screen, 0,0,400,0,400,600);
    if(lvl->winner > 0)
    {
     key[KEY_ESC] = TRUE;
     mode = 0;
    }
   }
   remove_int(manage_water_bll);
   remove_int(manage_water_bll2);
   remove_int(blick_laser);
   stop_sample(smp_water);
   stop_sample(smp_grass);
   mode = 0;
  }
  
  
  //vs server
  if(mode == 19)
  {
    printf("<<<M AKO MOMO>>>");
    init_server();
    curlevel = 0;
    splscr = 0;
    strcpy(meno_levela, "./levels/");
   strcat(meno_levela, levbr->flee[levbr->active].real_name);
   splscr = 0;
   printf("pokusim sa nacitat> %s", meno_levela);
   lvl = init_level(meno_levela);//<- toto zmenis na init_level(nazov_levelu_ktory_bol_vybraty);
    bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
    bll2 = init_ball("graphics/gulicka.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by+100);
    install_int(manage_water_bll, 1000);
    install_int(manage_water_bll2, 1000);
    install_int(blick_laser, 1500);
    //mb = create_bitmap(SCREEN_W, SCREEN_H);
    
    strcpy(gm, "1");
    dl_send(gm, CLIENT);
    printf("<><><><> %s", meno_levela);
    strcpy(gm, meno_levela);
    dl_send(gm, CLIENT);
    
    //strcpy(gm,"12345678901234567890123456789OK");
    //dl_send(gm, CLIENT);
    //dl_recv(rcv, CLIENT);
    //printf("PRIJAL SOM HLASKU: %s\n", rcv);
    
    while(!key[KEY_ESC])
    {
     count_mb(mb, bll, &drawx1, &drawy1);
    
     blit(lvl->bmp, mb, drawx1, drawy1, 0,0, SCREEN_W, SCREEN_H);
    
     //recv keys from client
     dl_recv(rcv, CLIENT);
     //decode it
     if(strcmp(rcv, "exit") == 0)
     {
      printf("EXIT MESSAGE RCVD");
      key[KEY_ESC] = TRUE;
     }
     else dl_decode_server(rcv);
     //manage it
     fake_wsad();
     manage_ball(bll, mb, NULL, 0);
     manage_ball(bll2, mb, NULL, 0);
     bounce_balls(bll, bll2);
     manage_grass(bll);
     manage_grass(bll2);
     //encode it
     dl_code(snd[0], bll->x, 0, 4);
     dl_code(snd[1], bll->y, 0, 4);
     dl_code(snd[2], bll2->x, 0, 4);
     dl_code(snd[3], bll2->y, 0, 4);
     dl_code(snd[4], bll->points, bll2->points, 2);
     make_values_qm(lvl);
     
     dl_code_qm(sndqm, qmval);
     make_great_msg(snd[0], snd[1], snd[2], snd[3], snd[4], sndqm);
     //send it all back
     dl_send(gm, CLIENT);
     //pixelize some text on the screen
     textprintf(mb, font, 0,0, biela, "%2d:%2d", bll->points, bll2->points);
     textprintf(mb, font, 0,8, biela, "%d:%d", bll->tmppts, bll2->tmppts);
     //now draw all that shit
     blit(mb, screen, 0,0,0,0,800,600);
    }
    
    strcpy(gm, "exitexitexitexitexitexitexit123");
    dl_send(gm, CLIENT);
    /*------------------
    NOVE!!! NEW!!!
    ------------------*/
    remove_int(manage_water_bll);
    remove_int(manage_water_bll2);
    remove_int(blick_laser);   
    mode = 0;      
  }
  
  
  
  //server coop
  if(mode == 20)
  {
    init_server();
    curlevel = 0;
    splscr = 0;
    strcpy(meno_levela, "./levels/");
   strcat(meno_levela, levbr->flee[levbr->active].real_name);
   splscr = 0;
   printf("pokusim sa nacitat> %s", meno_levela);
   lvl = init_level(meno_levela);//<- toto zmenis na init_level(nazov_levelu_ktory_bol_vybraty);
   
    bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
    bll2 = init_ball("graphics/gulicka.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by+100);
    install_int(manage_water_bll, 1000);
    install_int(blick_laser, 1500);
    //mb = create_bitmap(SCREEN_W, SCREEN_H);
    
    strcpy(gm, "2");
    dl_send(gm, CLIENT);
    printf("<><><><><> %s", meno_levela);
    strcpy(gm, meno_levela);
    dl_send(gm, CLIENT);
    
    //strcpy(gm,"12345678901234567890123456789OK");
    //dl_send(gm, CLIENT);
    //dl_recv(rcv, CLIENT);
    //printf("PRIJAL SOM HLASKU: %s\n", rcv);
    
    while(!key[KEY_ESC])
    {
     count_mb(mb, bll, &drawx1, &drawy1);
    
     blit(lvl->bmp, mb, drawx1, drawy1, 0,0, SCREEN_W, SCREEN_H);
    
     //recv keys from client
     dl_recv(rcv, CLIENT);
     //decode it
     if(strcmp(rcv, "exit") == 0)
     {
      printf("EXIT MESSAGE RCVD");
      key[KEY_ESC] = TRUE;
     }
     else dl_decode_server(rcv);
     //manage it
     fake_wsad();
     manage_ball(bll, mb, NULL, 0);
     manage_grass(bll);
       //encode it
     dl_code(snd[0], bll->x, 0, 4);
     dl_code(snd[1], bll->y, 0, 4);
     dl_code(snd[2], bll2->x, 0, 4);
     dl_code(snd[3], bll2->y, 0, 4);
     dl_code(snd[4], bll->points, bll2->points, 2);
     make_values_qm(lvl);
     
     dl_code_qm(sndqm, qmval);
     make_great_msg(snd[0], snd[1], snd[2], snd[3], snd[4], sndqm);
     //send it all back
     dl_send(gm, CLIENT);
     //pixelize some text on the screen here
     
     
     //now draw all that shit
     blit(mb, screen, 0,0,0,0,800,600);
    }
    
    strcpy(gm, "exitexitexitexitexitexitexit123");
    dl_send(gm, CLIENT);
    /*------------------
    NOVE!!! NEW!!!
    ------------------*/
    remove_int(manage_water_bll);
    remove_int(blick_laser); 
        mode = 0;       
  }
  
  
  
  //client 
  if(mode == 13)
  {
   init_client();
   
   recv(server, rcv, 2, 0);
   server_type = rcv[0]-48;
   printf(">>>>>>>SERVER TYPE: %d<<<<<<<<\n", server_type);
   strcpy(rcv,"\0");
   buf[0] = 'A';
   buf[1] = 'B';
   while(buf[0] != '\0' && buf[1] != '\0')
   {
    recv(server, buf, 2, 0);
    printf("buf:%s\n", buf, buf);
    strcat(rcv, buf);
    printf("a");
   }
   strcpy(meno_levela, rcv);
   printf(">>>>>>>MENO LEVELA: %s<<<<<<<\n", rcv);
	
    if(server_type == 1)//vs
      {
      //dl_recv(rcv, SERVER);
         curlevel = 0;
   splscr = 0;
   lvl = init_level(meno_levela);
   bll2 = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
   bll = init_ball("graphics/gulicka.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by+100);
   install_int(blick_laser, 1500);
   //mb = create_bitmap(SCREEN_W, SCREEN_H);
   
   //printf("PRIJAL SOM UVITACIU HLASKU: %s\n", rcv);
   //strcpy(snd[0], "Ahoj");
   //dl_send(snd[0], SERVER);
      while(!key[KEY_ESC])
      {
      //count pos of upper left corner of mb
       count_mb(mb, bll, &drawx1, &drawy1);
      //blit level bmp to mb
       blit(lvl->bmp, mb, drawx1, drawy1, 0,0, SCREEN_W, SCREEN_H);
    
      //check keys
       manage_my_ball();//bll, mb, NULL, 0
      //send keys
       snd[0][0] = bll2_is_up;
       snd[0][1] = bll2_is_down;
       snd[0][2] = bll2_is_left;
       snd[0][3] = bll2_is_right;
       snd[0][4] = '\0';
       dl_send(snd[0], SERVER);
      //recv data
       dl_recv(rcv, SERVER);
       if(strcmp(rcv, "exitexitexitexitexitexitexit123") == 0)
       {
        printf("EXIT MESSAGE RCVD");
        key[KEY_ESC] = TRUE;
       }
       else dl_decode_client(rcv);
      //manage ballz
       manage_remote_ball(bll, mb);
       manage_remote_ball(bll2, mb);
      //text output
       textprintf(mb, font, 0,0, biela, "HE %2d:%2d YOU", bll2->points, bll->points);
    
      //draw all that shit to screen
       blit(mb, screen, 0,0,0,0,800,600);
      }
        strcpy(snd[0], "exit");
        dl_send(snd[0], SERVER);
      }
      
    if(server_type == 2)//coop
      {
        //printf("ppp\n");
        //dl_recv(rcv, SERVER);
        printf("ppp\n");
        curlevel = 0;
        printf("ppp\n");
        splscr = 0;
        printf("ppp\n");
        lvl = init_level(meno_levela);
        printf("ppp\n");
        bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
        printf("ppp\n");
        bll2 = init_ball("graphics/gulicka.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by+100);
        printf("ppp\n");
        install_int(blick_laser, 1500);
        printf("ppp\n");
        //mb = create_bitmap(SCREEN_W, SCREEN_H);
        //printf("PRIJAL SOM UVITACIU HLASKU: %s\n", rcv);
        //printf("ppp\n");
        //strcpy(snd[0], "Ahoj");
        //dl_send(snd[0], SERVER);
        //printf("ppp\n");
        
        while(!key[KEY_ESC])
        {
         //count pos of upper left corner of mb
         count_mb(mb, bll, &drawx1, &drawy1);
         //blit level bmp to mb
         blit(lvl->bmp, mb, drawx1, drawy1, 0,0, SCREEN_W, SCREEN_H);
         
         //check keys
         manage_my_ball();//bll, mb, NULL, 0
         //send keys
         snd[0][0] = 48;
         snd[0][1] = 48;
         snd[0][2] = bll2_is_left;
         snd[0][3] = bll2_is_right;
         snd[0][4] = '\0';
         dl_send(snd[0], SERVER);
         //recv data
         dl_recv(rcv, SERVER);
         if(strcmp(rcv, "exitexitexitexitexitexitexit123") == 0)
         {
          printf("EXIT MESSAGE RCVD");
          key[KEY_ESC] = TRUE;
         }
         else dl_decode_client(rcv);
         //manage ballz
         manage_remote_ball(bll, mb);
         //text output here
         
         //draw all that shit to screen
         blit(mb, screen, 0,0,0,0,800,600);
        }
        strcpy(snd[0], "exit");
        dl_send(snd[0], SERVER);
      }  

  //NEWWWWW
   remove_int(blick_laser); 
       mode = 0;       
  }
  
  
  //rozpravka/pribeh
  if(mode == 11)
  {
   curlevel = 0;
   splscr = 0;
   lvl = init_level(levelname[curlevel]);
   bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);

  
   intermezzo = load_bitmap("graphics/im1.bmp", NULL);
   write_by_hand(intermezzo, "l*ska, ach t* l*ska. akur*t v ", 200, 100+120);
   write_by_hand(intermezzo, "de} gu~k*$ikovej a gu~;$kynej svatby", 200, 130+120);
   write_by_hand(intermezzo, "uniesol gu~;$ku zl& ihlan. z{fal&", 200, 160+120);
   write_by_hand(intermezzo, "gu~k*$ik sa vybral po radu za m{drym", 200, 190+120); 
   write_by_hand(intermezzo, "ujom gu~om. ten mu poradil ako zachr*ni%", 200, 220+120);
   write_by_hand(intermezzo, "gu~;$ku. ve~a #tastia", 200, 250+120);
 
   write_by_hand(intermezzo, "sta$ enter", 650, 600-60);

   blit(intermezzo, screen, 0,0,0,0,800,600);
   while(!key[KEY_ENTER]){}
   //install_int(increase_time, 1000);
   bt = 0;
   install_int(manage_water_bll, 1000);
   install_int(blick_laser, 1500);

   while(!key[KEY_ESC])
   {
    pageupdn();
    if(key[KEY_PLUS_PAD])
    {
     lvl->winner = 1;
     //curlevel++;
     printf("CURLEVEL> %d\n", curlevel);
     key[KEY_PLUS_PAD] = FALSE;                     
    }
    
    count_mb(mb, bll, &drawx1, &drawy1);

    blit(lvl->bmp, mb, drawx1, drawy1, 0, 0, mb->w, mb->h);
    manage_ball(bll, mb, NULL, 0);
    manage_grass(bll);
    //textprintf(mb, font, 0,0, biela, "LEVEL %d PTS: %d TIME: %2d:%2d", curlevel+1, bll->points, bt/60, bt%60);
	//if(key[KEY_D])darkness(mb, 10, 10, 200, 20);	
     
     draw_sprite(mb, trhanec, 0,0);	
     wt[0] = 48+((bt/60)/10);
     wt[1] = 48+((bt/60)%10);
     wt[2] = '.';
     wt[3] = 48+((bt%60)/10);
     wt[4] = 48+((bt%60)%10);
     wt[5] = '\0';
     printf("%d%d:%d%d\n", ((bt/60)/10), ((bt/60)%10), ((bt%60)/10), ((bt%60)%10));
     write_by_hand(mb, wt, 30,24);
     for(i = 0; i < bll->lives*25; i+=25)
     {
      stretch_sprite(mb, bll->bmp, 5+i, 55, 20, 20);
     }
    blit(mb, screen, 0,0,0,0,800,600);
    if(lvl->winner > 0)
    {
 //    remove_int(manage_water_bll);
     bll->x = 0;
     bll->y = 0;
     stop_sample(smp_water);
     stop_sample(smp_grass);
     play_sample(h_level[rand()%3], 255, 128, 1000, FALSE);
     curlevel++;
     //remove_int(increase_time);
     if(curlevel < 9)
     {
      im_fname[11] = 48 + curlevel+1;
      intermezzo = load_bitmap(im_fname, NULL);
     } 
     else
     {
      if(curlevel == 9)intermezzo = load_bitmap("./graphics/im10.bmp", NULL);
      if(curlevel == 10)intermezzo = load_bitmap("./graphics/im11.bmp", NULL);    
     }
     
     //gulkacik ma prvu skusku uspesne ze sebou... objavil sa vsak pred nim les. a kto sa boji nech nechodi do lesa
     if(curlevel == 1)
     {
      write_by_hand(intermezzo, "gu~k*$ik m* ", 20, 30+30+10);            
      write_by_hand(intermezzo, "prv{ sk{#ku ", 20, 30+30+30+10);
      write_by_hand(intermezzo, "{spe#ne za ", 20, 30+30+30+30+10);
      write_by_hand(intermezzo, "sebou... objavil  ", 20, 30+30+30+30+30+10);
      write_by_hand(intermezzo, "sa v#ak pred n(m", 20, 30+30+30+30+30+30+10);
      write_by_hand(intermezzo, "les... a kto sa boj(  ", 20, 30+30+30+30+30+30+30+10);
      write_by_hand(intermezzo, "nech nechod( do lesa", 20, 30+30+30+30+30+30+30+30+10);
     }
     
     if(curlevel == 2)
     {
      write_by_hand(intermezzo, "dezorientovan& gu~k*$ik uzrel svetlo na konci lesa", 20, 30+10);            
      write_by_hand(intermezzo, "av#ak to $o uvidel ho e#te viac zmietlo", 20, 30+30+10);
      write_by_hand(intermezzo, "pom;^te gu~k*$ikovi", 20, 30+30+30+10);
     }
     
     if(curlevel == 3)
     {
      write_by_hand(intermezzo, "r*zcestie m* u^ gu~k*$ik {spe#ne za sebou ", 20, 30+30+10);            
      write_by_hand(intermezzo, "n*# hrdina zac(til v;}u vody", 20, 30+30+30+10);
      write_by_hand(intermezzo, "pl*va% v#ak nevie, a po troch sekund*ch vo vode", 20, 30+30+30+30+10);
      write_by_hand(intermezzo, "sa chud*$ik gu~k*$ik utop(", 20, 30+30+30+30+30+10);
      write_by_hand(intermezzo, "dajte na}ho pros(m pozor", 20, 30+30+30+30+30+30+10);
     }
     
     if(curlevel == 4)
     {
      write_by_hand(intermezzo, "na ceste zachr*ni% gu~;$ku", 415, 200);            
      write_by_hand(intermezzo, "narazil na da~#iu prek*^ku", 435+10, 230);
      write_by_hand(intermezzo, "d*vajte pozor aby sa ", 450+30, 260);
      write_by_hand(intermezzo, "gu~k*$ik nezg{~al", 470+40, 290);
      write_by_hand(intermezzo, "dole na skaly", 490+50, 320);
     }
     
     if(curlevel == 5)
     {
      write_by_hand(intermezzo, "gu~k*$ik sa {spe#ne zg{~al z kopca. $ak* ho v#ak da~#ia ", 20, 30+10);            
      write_by_hand(intermezzo, "sk{#ka jeho l*sky...pom;^te mu prejs% cez mo$iare", 20, 30+30+10);
     }
     
     if(curlevel == 6)
     {
      write_by_hand(intermezzo, "a sme znovu na n(^ine. aj t* v#ak skr&va svoje n*strahy", 20, 30+10);            
      write_by_hand(intermezzo, "pokia~ gu~k*$ik padne do priepasti, niet mo^nosti odvr*ti%", 20, 30+30+10);            
      write_by_hand(intermezzo, "osud", 20, 30+30+30+10);
     }
     
     if(curlevel == 7)
     {
      write_by_hand(intermezzo, "priepasti a trhliny sme prekonali. zd* sa ^e je pred nami", 20, 30+10);            
      write_by_hand(intermezzo, "pokojn* l{ka. nieje tomu tak. f{kaj{ na nej siln) vetry", 20, 30+30+10);            
      write_by_hand(intermezzo, "dajte pozor aby gu~k*$ika neodf{klo do ve$n&ch lov(#%", 20, 30+30+30+10);
     }
     
     if(curlevel == 8)
     {
      write_by_hand(intermezzo, "zdia~ky gu~k*$ik zazrel ve^i$ky. bol to ihlanov pal*c.", 20, 10);            
      write_by_hand(intermezzo, "pomali$ky sa bl(^il a^ k&m sa neprig{~al ku dver*m", 20, 30+10);            
      write_by_hand(intermezzo, "vn{tri sa c(til ve~mi nepr(jemne. v#etko bolo tak) hranat).", 20, 30+30+10);
     }
     
     if(curlevel == 9)
     {
      write_by_hand(intermezzo, "zastal mu dych. rozb{#ilo sa mu srdce. bola to ona.", 20, 10);            
      write_by_hand(intermezzo, "chabo sa }u usmial. ", 20, 30+10);            
      write_by_hand(intermezzo, "$akali ho posledn) nastr*hy.", 20, 30+30+10);
      write_by_hand(intermezzo, "dotoho. nech vyhr* dobro nad zlom.",20, 30+30+30+10);
     }
     if(curlevel == 10)
     {
      write_by_hand(intermezzo, "koniec dobry. vsetko dobre", 210, 400);            
      write_by_hand(intermezzo, "ujo gu~o zosob*#il gu~k*$ika a  ", 190, 430);            
      write_by_hand(intermezzo, "gu~k;$ku. v#etci boli #tastn( a ^ili ", 170, 460);
      write_by_hand(intermezzo, "a^ k&m... ", 350, 490);
     }
     
     blit(intermezzo, screen, 0,0,0,0,800,600);
     while(!key[KEY_ENTER]){}
//     install_int(manage_water_bll, 1000);
     if(curlevel != 10)
     {
      lvl = init_level(levelname[curlevel]);
      bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
      //install_int(increase_time, 1000);
      bt = 0;
     }
    }
    if(curlevel == 10)
    {
     printf("*********************\n");
     printf("   ABSOLUT WINNER \n");
     printf(" DONE IN: %d S \n", bt);
     printf("*********************\n");
     mode = 0;
     key[KEY_ESC] = TRUE;
    }
   }//while
				  
   //remove_int(increase_time);
   remove_int(manage_water_bll);
   remove_int(blick_laser); 
   mode = 0;       
  }
  
  
 }
 
 return 0;
}END_OF_MAIN()

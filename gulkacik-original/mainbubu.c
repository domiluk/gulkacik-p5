#include "ws.h"

BITMAP *mb, *mb1, *mb2;
int q[10] = {3,3,3,3,3,3,3,3,3,3}, hlp;


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

int main()
{
 scanf("%d", &menu);
 if(menu == 9 || menu == 10)// 7-server vs, 8-server coop, 9-client vs, 10-client coop
 {
		printf("IP: ");
		scanf("%s", &ip);
	}
 allegro_init();
 set_color_depth(32);
 set_gfx_mode(2, 800, 600, 0, 0);
 
 
 install_keyboard();
 install_mouse();
 install_timer();
 
 set_display_switch_mode(SWITCH_BACKGROUND);
 
 srand(time(NULL));
 
 st = turned = 0;
 
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
 intermezzo = load_bitmap("graphics/im1.bmp", NULL);
 bg = load_bitmap("graphics/bg.bmp", NULL);
 printf("ppp\n");
 
 int h;
 //4-pribeh, 5-volna hra, 6-lokalna hra, 7-server vs, 8-server coop, 9-client vs, 10-client coop
 switch(menu)
 {
		 case 4://pribeh
						curlevel = 0;
						splscr = 0;
					 lvl = init_level(levelname[curlevel]);
					 bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
					 mb = create_bitmap(SCREEN_W, SCREEN_H);
					 blit(intermezzo, screen, 0,0,0,0,800,600);
					 while(!key[KEY_ENTER]){}
					 install_int(increase_time, 1000);
					 install_int(manage_water_bll, 1000);
					 install_int(blick_laser, 1500);
					 
					 while(!key[KEY_ESC])
				  {
				   count_mb(mb, bll, &drawx1, &drawy1);
				   
				   blit(lvl->bmp, mb, 0, 0, 0, 0, mb->w, mb->h);
				   manage_ball(bll, mb, NULL, 0);
				   manage_grass(bll);
				   textprintf(mb, font, 0,0, biela, "LEVEL %d PTS: %d TIME: %2d:%2d", curlevel+1, bll->points, bt/60, bt%60);
				   
				   blit(mb, screen, 0,0,0,0,800,600);
				   if(lvl->winner > 0)
				   {
				    curlevel++;
				    remove_int(increase_time);
				    im_fname[11] = 48 + curlevel;
				    intermezzo = load_bitmap(im_fname, NULL);
				    blit(intermezzo, screen, 0,0,0,0,800,600);
				    while(!key[KEY_ENTER]){}
				    if(curlevel != 10)
        {
         lvl = init_level(levelname[curlevel]);
				     bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
 				    install_int(increase_time, 1000);
        }
				   }
				   if(curlevel == 10)
				   {
				    printf("*********************\n");
				    printf("   ABSOLUT WINNER \n");
				    printf(" DONE IN: %d S \n", bt);
				    printf("*********************\n");
				    system("PAUSE");
				    key[KEY_ESC] = TRUE;
				   }
				  }//while
				  
			   remove_int(increase_time);
					 remove_int(manage_water_bll);
					 remove_int(blick_laser);
			break;
			case 5://volna hra
					 splscr = 0;
					 lvl = init_level(levelname[curlevel]);//<- toto zmenis na init_level(nazov_levelu_ktory_bol_vybraty);
					 bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
					 mb = create_bitmap(SCREEN_W, SCREEN_H);
					 install_int(increase_time, 1000);
					 install_int(manage_water_bll, 1000);
					 install_int(blick_laser, 1500);
					 
					 while(!key[KEY_ESC])
				    {
				   count_mb(mb, bll, &drawx1, &drawy1);
				   
				   blit(lvl->bmp, mb, 0, 0, 0, 0, mb->w, mb->h);
				   manage_ball(bll, mb, NULL, 0);
				   manage_grass(bll);
				   textprintf(mb, font, 0,0, biela, "LEVEL %d PTS: %d TIME: %2d:%2d", curlevel+1, bll->points, bt/60, bt%60);
				   
				   blit(mb, screen, 0,0,0,0,800,600);
				   if(lvl->winner > 0)
				   {
        key[KEY_ESC] = TRUE;
				   }
				  }//while
				  
			         remove_int(increase_time);
					 remove_int(manage_water_bll);
					 remove_int(blick_laser);
			break;
			case 6://lokalna hra
						curlevel = 0;
						splscr = 1;
						lvl = init_level(levelname[curlevel]);
						bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
					 bll2 = init_ball("graphics/gulicka.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by+100);
		 			install_int(manage_water_bll, 1000);
						install_int(manage_water_bll2, 1000);
					 install_int(blick_laser, 1500);
						mb1 = create_bitmap(SCREEN_W/2, SCREEN_H);
				  mb2 = create_bitmap(SCREEN_W/2, SCREEN_H);
				  
				  while(!key[KEY_ESC])
				  {
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
				   
				   blit(mb2, screen, 0,0,0,0,399,600);
				   blit(mb1, screen, 0,0,400,0,400,600);
				  }
			break;
			case 7://server vs
				  init_server();
				  curlevel = 0;
						splscr = 0;
						lvl = init_level(levelname[curlevel]);
						bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
					 bll2 = init_ball("graphics/gulicka.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by+100);
		 			install_int(manage_water_bll, 1000);
						install_int(manage_water_bll2, 1000);
					 install_int(blick_laser, 1500);
					 mb = create_bitmap(SCREEN_W, SCREEN_H);
				  /*printf("AHOJ\n");
				  
				  dl_code_base(snd[0], 100, 0, 4);
				  dl_code_base(snd[1], 100, 0, 4);
				  dl_code_base(snd[2], 200, 0, 4);
				  dl_code_base(snd[3], 200, 0, 4);
				  dl_code_base(snd[4], 1, 2, 2);
				  dl_code_qm(sndqm, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
				  make_great_msg(snd[0], snd[1], snd[2], snd[3], snd[4], sndqm);
				  printf("%s\n", gm);
				  dl_send(gm, CLIENT);*/
				  
				  strcpy(gm,"12345678901234567890123456789OK");
				  dl_send(gm, CLIENT);
				  dl_recv(rcv, CLIENT);
				  printf("PRIJAL SOM HLASKU: %s\n", rcv);
				  
				  while(!key[KEY_ESC])
				  {
							count_mb(mb, bll, &drawx1, &drawy1);
				   
				   blit(lvl->bmp, mb, drawx1, drawy1, 0,0, SCREEN_W, SCREEN_H);
				   
				   //recv keys from client
				   dl_recv(rcv, CLIENT);
				   //decode it
				   dl_decode_server(rcv);
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
				   /*for(hlp = 0; hlp < lvl->qma*2; hlp++)
				   {
        if(lvl->qm[hlp].done == 1)
         q[hlp] = lvl->qm[hlp].done;
        else
         q[hlp] = lvl->qm[hlp].flip;
       }*/
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
			break;
			case 8://server coop
				  init_server();
			break;
			case 9://client vs
						init_client();
						dl_recv(rcv, SERVER);
						curlevel = 0;
						splscr = 0;
						lvl = init_level(levelname[curlevel]);
						bll2 = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
					 bll = init_ball("graphics/gulicka.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by+100);
					 install_int(blick_laser, 1500);
					 mb = create_bitmap(SCREEN_W, SCREEN_H);
					 printf("PRIJAL SOM UVITACIU HLASKU: %s\n", rcv);
					 strcpy(snd[0], "Ahoj");
					 dl_send(snd[0], SERVER);
						
					 
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
				   dl_decode_client(rcv);
				   //manage ballz
				   manage_remote_ball(bll, mb);
				   manage_remote_ball(bll2, mb);
				   //text output
				   textprintf(mb, font, 0,0, biela, "HE %2d:%2d YOU", bll2->points, bll->points);
				   textprintf(mb, font, 0,8, biela, "%d:%d", bll2->tmppts, bll->tmppts);
				   
				   //draw all that shit to screen
				   blit(mb, screen, 0,0,0,0,800,600);
				  }
			break;
			case 10://client coop
				  init_client();
			break;
			default:
				printf("wrong number entered\n");
				system("PAUSE");
				return 1;
			break;
	}

 /*
 while(!key[KEY_ESC])
 {
  if(splscr == 1)
  {
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
   
   blit(mb2, screen, 0,0,0,0,399,600);
   blit(mb1, screen, 0,0,400,0,400,600);
  }
  else
  {
   count_mb(mb, bll, &drawx1, &drawy1);
   
   blit(lvl->bmp, mb, 0, 0, 0, 0, mb->w, mb->h);
   manage_ball(bll, mb, NULL, 0);
   manage_grass(bll);
   textprintf(mb, font, 0,0, biela, "LEVEL %d PTS: %d TIME: %2d:%2d", curlevel+1, bll->points, bt/60, bt%60);
   
   blit(mb, screen, 0,0,0,0,800,600);
   if(lvl->winner > 0)
   {
    curlevel++;
    remove_int(increase_time);
    blit(intermezzo, screen, 0,0,0,0,800,600);
    lvl = init_level(levelname[curlevel]);
    bll = init_ball("graphics/gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
    while(!key[KEY_ENTER]){}
    install_int(increase_time, 1000);
   }
   if(curlevel == 10)
   {
    printf("*********************\n");
    printf("   ABSOLUT WINNER \n");
    printf(" DONE IN: %d S \n", bt);
    printf("*********************\n");
    system("PAUSE");
    key[KEY_ESC] = TRUE;
   }
  }
   
  
  /*textprintf(mb, font, 0, 0, biela, "%d : %d fps: %d", bt / 60, bt % 60, fps);
  textprintf(mb, font, 0, 8, biela, "reverse: %d lives: %d siw: %d maxspeed: %f", bll->reverse, bll->lives, bll->siw, bll->maxspeed);
  textprintf(mb, font, 0, 16, biela, "vx:%-3.6f vy:%-3.6f", bll->vx, bll->vy);
  
  for(h = 0; h < lvl->qma*2; h++)
   textprintf(mb, font, 0,50+8*h, biela, "%d: %d", h, lvl->qm[h].flip);
  textprintf(mb, font, 0,150, biela, "turned: %d wwt: %d d: %d st: %d", turned, wwt, gd, st);
  
 }*/
 system("rm main.o");
 
 return 1;   
}
END_OF_MAIN()

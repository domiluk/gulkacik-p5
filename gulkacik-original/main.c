#include <allegro.h>
#include <stdio.h>

#include "level.h"
#include "ball.h"

BITMAP *mb;

int main()
{
 allegro_init();
 set_color_depth(32);
 set_gfx_mode(2, 800, 600, 0, 0);
 mb = create_bitmap(SCREEN_W, SCREEN_H);
 
 install_keyboard();
 install_mouse();
 install_timer();
 
 install_int(increase_time, 1000);
 install_int(manage_water, 1000);
 
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
 qm[0] = load_bitmap("graphics/qm1.bmp", NULL);
 symbol_brick[0] = load_bitmap("graphics/symbol1.bmp", NULL);
 symbol_brick[1] = load_bitmap("graphics/symbol2.bmp", NULL);
 symbol_brick[2] = load_bitmap("graphics/symbol3.bmp", NULL);
 
 printf("ppp");
 bg = load_bitmap("bg.bmp", NULL);
 
 lvl = init_level("level2.vgp");
 bll = init_ball("gulkacik.bmp", lvl->alpha, lvl->qma, lvl->bx, lvl->by);
 //printf("ppp\n");
// text_mode(-1);
 while(!key[KEY_ESC])
 {
  //draw_sprite(mb, lvl->bmp, 0, 0); 
  blit(lvl->bmp, mb, 0, 0, 0, 0, mb->w, mb->h);
  manage_ball(bll, mb);
  //circlefill(mb, mouse_x, mouse_y, 10, 0);
  textprintf_centre(mb, font, 400,10,biela, "%d:%d", bt/60, bt % 60);
  blit(mb, screen, 0,0,0,0,800,600);
 }
 system("rm main.o");
 
 return 1;   
}
END_OF_MAIN()

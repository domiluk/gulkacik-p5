#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "rotate.c"

#define POLOMER 60

BITMAP *mb;
FILE *output;


BITMAP *p_a, *p_b, *p_c, *p_d, *p_e, *p_f, *p_g, *p_h, *p_i, *p_j, *p_k, *p_l, *p_m, *p_n, *p_o, *p_p, *p_q, *p_r, *p_s, *p_t, *p_u, *p_v, *p_w, *p_z, *p_y, *p_x;
BITMAP *p_aa, *p_ch, *p_dh, *p_ee,*p_ii, *p_lh, *p_oo, *p_ooo, *p_sh, *p_th, *p_uu, *p_zh, *p_yy;
BITMAP *p_0, *p_1, *p_2, *p_3, *p_4, *p_5, *p_6, *p_7, *p_8, *p_9;

int init_dl_font()
{
 p_a = load_bitmap("./dlfont/a.bmp", NULL);    
 p_b = load_bitmap("./dlfont/b.bmp", NULL);
 p_c = load_bitmap("./dlfont/c.bmp", NULL);
 p_d = load_bitmap("./dlfont/d.bmp", NULL);
 p_e = load_bitmap("./dlfont/e.bmp", NULL);
 p_f = load_bitmap("./dlfont/f.bmp", NULL);
 p_g = load_bitmap("./dlfont/g.bmp", NULL);
 p_h = load_bitmap("./dlfont/h.bmp", NULL);
 p_i = load_bitmap("./dlfont/i.bmp", NULL);
 p_j = load_bitmap("./dlfont/j.bmp", NULL);
 p_k = load_bitmap("./dlfont/k.bmp", NULL);
 p_l = load_bitmap("./dlfont/l.bmp", NULL);
 p_m = load_bitmap("./dlfont/m.bmp", NULL);
 p_n = load_bitmap("./dlfont/n.bmp", NULL);
 p_o = load_bitmap("./dlfont/o.bmp", NULL);
 p_p = load_bitmap("./dlfont/p.bmp", NULL);
 p_q = load_bitmap("./dlfont/q.bmp", NULL);
 p_r = load_bitmap("./dlfont/r.bmp", NULL);
 p_s = load_bitmap("./dlfont/s.bmp", NULL);
 p_t = load_bitmap("./dlfont/t.bmp", NULL);
 p_u = load_bitmap("./dlfont/u.bmp", NULL);
 p_v = load_bitmap("./dlfont/v.bmp", NULL);
 p_w = load_bitmap("./dlfont/w.bmp", NULL);
 p_x = load_bitmap("./dlfont/x.bmp", NULL);
 p_y = load_bitmap("./dlfont/y.bmp", NULL);
 p_z = load_bitmap("./dlfont/z.bmp", NULL);
 p_aa = load_bitmap("./dlfont/aa.bmp", NULL);
 p_ch = load_bitmap("./dlfont/ch.bmp", NULL);
 p_dh = load_bitmap("./dlfont/dh.bmp", NULL);
 p_ee = load_bitmap("./dlfont/ee.bmp", NULL);
 p_ii = load_bitmap("./dlfont/ii.bmp", NULL);
 p_lh = load_bitmap("./dlfont/lh.bmp", NULL);
 p_oo = load_bitmap("./dlfont/oo.bmp", NULL);
 p_ooo = load_bitmap("./dlfont/ooo.bmp", NULL);
 p_sh = load_bitmap("./dlfont/sh.bmp", NULL);
 p_th = load_bitmap("./dlfont/th.bmp", NULL);
 p_uu = load_bitmap("./dlfont/uu.bmp", NULL);
 p_zh = load_bitmap("./dlfont/zh.bmp", NULL);
 p_yy = load_bitmap("./dlfont/yy.bmp", NULL);
 p_0 = load_bitmap("./dlfont/0.bmp", NULL);
 p_1 = load_bitmap("./dlfont/1.bmp", NULL);
 p_2 = load_bitmap("./dlfont/2.bmp", NULL);
 p_3 = load_bitmap("./dlfont/3.bmp", NULL);
 p_4 = load_bitmap("./dlfont/4.bmp", NULL);
 p_5 = load_bitmap("./dlfont/5.bmp", NULL);
 p_6 = load_bitmap("./dlfont/6.bmp", NULL);
 p_7 = load_bitmap("./dlfont/7.bmp", NULL);
 p_8 = load_bitmap("./dlfont/8.bmp", NULL);
 p_9 = load_bitmap("./dlfont/9.bmp", NULL);
 
 return 1;
}


int write_by_hand(BITMAP *bmp, char *text, int xx, int yy)
{
 int i;
 int x, y;
 
 x = xx;
 y = yy;
 
 //printf("tu som bol %d %c", strlen(text), text[0]);
 for(i = 0; i < strlen(text); i++)
 {
  if(text[i] == 'a')
  {
   draw_sprite(bmp, p_a, x, y);
   x+= p_a->w; 
  }
  
  if(text[i] == 'b')
  {
   draw_sprite(bmp, p_b, x, y); 
   x+= p_b->w;       
  }
  
  if(text[i] == 'c')
  {
   draw_sprite(bmp, p_c, x, y); 
   x+= p_c->w;       
  }
  
  if(text[i] == 'd')
  {
   draw_sprite(bmp, p_d, x, y); 
   x+= p_d->w;       
  }
  
  if(text[i] == 'e')
  {
   draw_sprite(bmp, p_e, x, y); 
   x+= p_e->w;       
  }
  
  if(text[i] == 'f')
  {
   draw_sprite(bmp, p_f, x, y); 
   x+= p_f->w;       
  }
  
  if(text[i] == 'g')
  {
   draw_sprite(bmp, p_g, x, y); 
   x+= p_f->w;       
  }
  
  if(text[i] == 'h')
  {
   draw_sprite(bmp, p_h, x, y); 
   x+= p_h->w;       
  }
  
  if(text[i] == 'i')
  {
   draw_sprite(bmp, p_i, x, y); 
   x+= p_i->w;       
  }
  
  if(text[i] == 'j')
  {
   draw_sprite(bmp, p_j, x, y); 
   x+= p_j->w;       
  }
  
  if(text[i] == 'k')
  {
   draw_sprite(bmp, p_k, x, y); 
   x+= p_k->w;       
  }
  
  if(text[i] == 'l')
  {
   draw_sprite(bmp, p_l, x, y); 
   x+= p_l->w;       
  }
  
  if(text[i] == 'm')
  {
   draw_sprite(bmp, p_m, x, y); 
   x+= p_m->w;       
  }
  
  if(text[i] == 'n')
  {
   draw_sprite(bmp, p_n, x, y); 
   x+= p_n->w;       
  }
  
  if(text[i] == 'o')
  {
   draw_sprite(bmp, p_o, x, y); 
   x+= p_o->w;       
  }
  
  if(text[i] == 'p')
  {
   draw_sprite(bmp, p_p, x, y); 
   x+= p_p->w;       
  }
  
  if(text[i] == 'q')
  {
   draw_sprite(bmp, p_q, x, y); 
   x+= p_q->w;       
  }
  
  if(text[i] == 'r')
  {
   draw_sprite(bmp, p_r, x, y); 
   x+= p_r->w;       
  }
  
  if(text[i] == 's')
  {
   draw_sprite(bmp, p_s, x, y); 
   x+= p_s->w;       
  }
  
  if(text[i] == 't')
  {
   draw_sprite(bmp, p_t, x, y); 
   x+= p_t->w;       
  }
  
  if(text[i] == 'u')
  {
   draw_sprite(bmp, p_u, x, y); 
   x+= p_u->w;       
  }
  
  if(text[i] == 'v')
  {
   draw_sprite(bmp, p_v, x, y); 
   x+= p_v->w;       
  }
  
  if(text[i] == 'w')
  {
   draw_sprite(bmp, p_w, x, y); 
   x+= p_w->w;       
  }
  
  if(text[i] == 'x')
  {
   draw_sprite(bmp, p_x, x, y); 
   x+= p_x->w;       
  }
  
  if(text[i] == 'y')
  {
   draw_sprite(bmp, p_y, x, y); 
   x+= p_y->w;       
  }
  
  if(text[i] == 'z')
  {
   draw_sprite(bmp, p_z, x, y); 
   x+= p_z->w;       
  }
  
  if(text[i] == ' ')
  {
   x+= 15;       
  }
  
  //aa
  if(text[i] == '*')
  {
   draw_sprite(bmp, p_aa, x, y); 
   x+= p_aa->w;       
  }
  //sh
  if(text[i] == '#')
  {
   draw_sprite(bmp, p_sh, x, y); 
   x+= p_sh->w;       
  }
  //yy
  if(text[i] == '&')
  {
   draw_sprite(bmp, p_yy, x, y); 
   x+= p_yy->w;       
  }
  //ch
  if(text[i] == '$')
  {
   draw_sprite(bmp, p_ch, x, y); 
   x+= p_ch->w;       
  }
  //th
  if(text[i] == '%')
  {
   draw_sprite(bmp, p_th, x, y); 
   x+= p_th->w;       
  }    
  //zh
  if(text[i] == '^')
  {
   draw_sprite(bmp, p_zh, x, y); 
   x+= p_zh->w;       
  }
  //ii
  if(text[i] == '(')
  {
   draw_sprite(bmp, p_ii, x, y); 
   x+= p_ii->w;       
  }
  //ee
  if(text[i] == ')')
  {
   draw_sprite(bmp, p_ee, x, y); 
   x+= p_ee->w;       
  }
  //oo
  if(text[i] == '@')
  {
   draw_sprite(bmp, p_oo, x, y); 
   x+= p_oo->w;       
  }
  //ooo
  if(text[i] == ';')
  {
   draw_sprite(bmp, p_ooo, x, y); 
   x+= p_ooo->w;       
  }
  //lh
  if(text[i] == '~')
  {
   draw_sprite(bmp, p_lh, x, y); 
   x+= p_lh->w;       
  }
  //uu
  if(text[i] == '{')
  {
   draw_sprite(bmp, p_uu, x, y); 
   x+= p_uu->w;       
  }
  if(text[i] == '0')
  {
   draw_sprite(bmp, p_0, x, y); 
   x+= p_0->w;       
  }
    if(text[i] == '1')
  {
   draw_sprite(bmp, p_1, x, y); 
   x+= p_1->w;       
  }
    if(text[i] == '2')
  {
   draw_sprite(bmp, p_2, x, y); 
   x+= p_2->w;       
  }
    if(text[i] == '3')
  {
   draw_sprite(bmp, p_3, x, y); 
   x+= p_3->w;       
  }
    if(text[i] == '4')
  {
   draw_sprite(bmp, p_4, x, y); 
   x+= p_4->w;       
  }
    if(text[i] == '5')
  {
   draw_sprite(bmp, p_5, x, y); 
   x+= p_5->w;       
  }
    if(text[i] == '6')
  {
   draw_sprite(bmp, p_6, x, y); 
   x+= p_6->w;       
  }
    if(text[i] == '7')
  {
   draw_sprite(bmp, p_7, x, y); 
   x+= p_7->w;       
  }
    if(text[i] == '8')
  {
   draw_sprite(bmp, p_8, x, y); 
   x+= p_8->w;       
  }
    if(text[i] == '9')
  {
   draw_sprite(bmp, p_9, x, y); 
   x+= p_9->w;       
  }
 }
 
 return 1;    
}
BITMAP *cur;
BITMAP *cur_rot;
float lx, ly;
float w, h;
float angle;

int main()
{
 allegro_init();
 set_color_depth(32);
 set_gfx_mode(2, 800, 600, 0, 0);
 
 install_keyboard();
 install_mouse();
 
 //output = fopen("data.eff", "w");
 
 mb = create_bitmap(800, 600);
 
 //init_dl_font();
 
 cur = load_bitmap("cur.bmp", NULL);
 cur_rot = load_bitmap("cur.bmp", NULL);
 angle = 0;
 
 
 clear_to_color(mb, 0xffffff);
 while(!key[KEY_ESC])
 {
  clear_to_color(mb, 0xffffff);
  lx = mouse_x;
  ly = mouse_y;
  rest(40);
  //write_by_hand(mb, "$o sa tak kuk*#", 20, 20);
  show_mouse(screen);
  /*if(ly != mouse_y)
  {
   w = lx-mouse_x;
   h = ly-mouse_y;
   
   angle = atan(w/h)*180/3.1415;     
   rotate(cur_rot, cur, angle);
   
   
   //printf("<%f %f>\n",, angle);
  }*/
  
  if(mouse_x != lx && mouse_y != ly)
  {
   angle = atan((mouse_x - lx) / (mouse_y - ly)) * 180.0 / 3.141592;
   rotate(cur_rot, cur, angle);
  }
  draw_sprite(mb, cur, mouse_x, mouse_y);
  //printf("%d %d \n", lx-mouse_x, ly-mouse_y);
  blit(mb, screen, 0, 0, 0, 0, 800, 600);
 }
 
 
}END_OF_MAIN()

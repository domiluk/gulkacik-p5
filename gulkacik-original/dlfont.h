
BITMAP *p_a, *p_b, *p_c, *p_d, *p_e, *p_f, *p_g, *p_h, *p_i, *p_j, *p_k, *p_l, *p_m, *p_n, *p_o, *p_p, *p_q, *p_r, *p_s, *p_t, *p_u, *p_v, *p_w, *p_z, *p_y, *p_x;
BITMAP *p_aa, *p_ch, *p_dh, *p_ee,*p_ii, *p_lh, *p_oo, *p_ooo, *p_sh, *p_th, *p_uu, *p_zh, *p_yy, *p_nh;
BITMAP *p_0, *p_1, *p_2, *p_3, *p_4, *p_5, *p_6, *p_7, *p_8, *p_9;

BITMAP *p_ar, *p_br, *p_cr, *p_dr, *p_er, *p_fr, *p_gr, *p_hr, *p_ir, *p_jr, *p_kr, *p_lr, *p_mr, *p_nr, *p_or, *p_pr, *p_qr, *p_rr, *p_sr, *p_tr, *p_ur, *p_vr, *p_wr, *p_zr, *p_yr, *p_xr;
BITMAP *p_aar, *p_chr, *p_dhr, *p_eer,*p_iir, *p_lhr, *p_oor, *p_ooor, *p_shr, *p_thr, *p_uur, *p_zhr, *p_yyr;
BITMAP *p_0r, *p_1r, *p_2r, *p_3r, *p_4r, *p_5r, *p_6r, *p_7r, *p_8r, *p_9r, *dot;

int letter_gone_red(BITMAP *bmp)
{
 int x, y, r, g, b, c;
 int rr, gg, bb;
 
 for(x = 0; x < bmp->w; x++)
 for(y = 0; y < bmp->h; y++)
 {
  if(getpixel(bmp, x, y) != 0xff00ff)
  {
   c = getpixel(bmp, x, y);
   r = getr(c);
   g = getg(c);
   b = getb(c);
   rr = r*0.4 + 255*0.6;
   putpixel(bmp, x, y, makecol(rr, g, b));                 
  }      
 }
 
 return 1;    
}


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
 p_nh = load_bitmap("./dlfont/nh.bmp", NULL);
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
 
 p_ar = load_bitmap("./dlfont/a.bmp", NULL);    
 p_br = load_bitmap("./dlfont/b.bmp", NULL);
 p_cr = load_bitmap("./dlfont/c.bmp", NULL);
 p_dr = load_bitmap("./dlfont/d.bmp", NULL);
 p_er = load_bitmap("./dlfont/e.bmp", NULL);
 p_fr = load_bitmap("./dlfont/f.bmp", NULL);
 p_gr = load_bitmap("./dlfont/g.bmp", NULL);
 p_hr = load_bitmap("./dlfont/h.bmp", NULL);
 p_ir = load_bitmap("./dlfont/i.bmp", NULL);
 p_jr = load_bitmap("./dlfont/j.bmp", NULL);
 p_kr = load_bitmap("./dlfont/k.bmp", NULL);
 p_lr = load_bitmap("./dlfont/l.bmp", NULL);
 p_mr = load_bitmap("./dlfont/m.bmp", NULL);
 p_nr = load_bitmap("./dlfont/n.bmp", NULL);
 p_or = load_bitmap("./dlfont/o.bmp", NULL);
 p_pr = load_bitmap("./dlfont/p.bmp", NULL);
 p_qr = load_bitmap("./dlfont/q.bmp", NULL);
 p_rr = load_bitmap("./dlfont/r.bmp", NULL);
 p_sr = load_bitmap("./dlfont/s.bmp", NULL);
 p_tr = load_bitmap("./dlfont/t.bmp", NULL);
 p_ur = load_bitmap("./dlfont/u.bmp", NULL);
 p_vr = load_bitmap("./dlfont/v.bmp", NULL);
 p_wr = load_bitmap("./dlfont/w.bmp", NULL);
 p_xr = load_bitmap("./dlfont/x.bmp", NULL);
 p_yr = load_bitmap("./dlfont/y.bmp", NULL);
 p_zr = load_bitmap("./dlfont/z.bmp", NULL);
 p_aar = load_bitmap("./dlfont/aa.bmp", NULL);
 p_chr = load_bitmap("./dlfont/ch.bmp", NULL);
 p_dhr = load_bitmap("./dlfont/dh.bmp", NULL);
 p_eer = load_bitmap("./dlfont/ee.bmp", NULL);
 p_iir = load_bitmap("./dlfont/ii.bmp", NULL);
 p_lhr = load_bitmap("./dlfont/lh.bmp", NULL);
 p_oor = load_bitmap("./dlfont/oo.bmp", NULL);
 p_ooor = load_bitmap("./dlfont/ooo.bmp", NULL);
 p_shr = load_bitmap("./dlfont/sh.bmp", NULL);
 p_thr = load_bitmap("./dlfont/th.bmp", NULL);
 p_uur = load_bitmap("./dlfont/uu.bmp", NULL);
 p_zhr = load_bitmap("./dlfont/zh.bmp", NULL);
 p_yyr = load_bitmap("./dlfont/yy.bmp", NULL);
 p_0r = load_bitmap("./dlfont/0.bmp", NULL);
 p_1r = load_bitmap("./dlfont/1.bmp", NULL);
 p_2r = load_bitmap("./dlfont/2.bmp", NULL);
 p_3r = load_bitmap("./dlfont/3.bmp", NULL);
 p_4r = load_bitmap("./dlfont/4.bmp", NULL);
 p_5r = load_bitmap("./dlfont/5.bmp", NULL);
 p_6r = load_bitmap("./dlfont/6.bmp", NULL);
 p_7r = load_bitmap("./dlfont/7.bmp", NULL);
 p_8r = load_bitmap("./dlfont/8.bmp", NULL);
 p_9r = load_bitmap("./dlfont/9.bmp", NULL);
 
 dot = load_bitmap("./dlfont/dot.bmp", NULL);
 
 letter_gone_red(p_aar);
 letter_gone_red(p_chr);
 letter_gone_red(p_dhr);
 letter_gone_red(p_eer);
 letter_gone_red(p_iir);
 letter_gone_red(p_lhr);
 letter_gone_red(p_oor);
 letter_gone_red(p_ooor);
 letter_gone_red(p_shr);
 letter_gone_red(p_thr);
 letter_gone_red(p_uur);
 letter_gone_red(p_zhr);
 letter_gone_red(p_yyr);
 
 letter_gone_red(p_0r);
 letter_gone_red(p_1r);
 letter_gone_red(p_2r);
 letter_gone_red(p_3r);
 letter_gone_red(p_4r);
 letter_gone_red(p_5r);
 letter_gone_red(p_6r);
 letter_gone_red(p_7r);
 letter_gone_red(p_8r);
 letter_gone_red(p_9r);
 
 letter_gone_red(p_ar);
 letter_gone_red(p_br);
 letter_gone_red(p_cr);
 letter_gone_red(p_dr);
 letter_gone_red(p_er);
 letter_gone_red(p_fr);
 letter_gone_red(p_gr);
 letter_gone_red(p_hr);
 letter_gone_red(p_ir);
 letter_gone_red(p_jr);
 letter_gone_red(p_kr);
 letter_gone_red(p_lr);
 letter_gone_red(p_mr);
 letter_gone_red(p_nr);
 letter_gone_red(p_or);
 letter_gone_red(p_pr);
 letter_gone_red(p_qr);
 letter_gone_red(p_rr);
 letter_gone_red(p_sr);
 letter_gone_red(p_tr);
 letter_gone_red(p_ur);
 letter_gone_red(p_vr);
 letter_gone_red(p_wr);
 letter_gone_red(p_xr);
 letter_gone_red(p_yr);
 letter_gone_red(p_zr);
 
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
  if(text[i] == '.')
  {
   draw_sprite(bmp, dot, x, y);
   x+= dot->w; 
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
  
  //nh
  if(text[i] == '}')
  {
   draw_sprite(bmp, p_nh, x, y); 
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
/********************************************************************************************************/

int write_by_hand_red(BITMAP *bmp, char *text, int xx, int yy)
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
   draw_sprite(bmp, p_ar, x, y);
   x+= p_a->w; 
  }
  
  if(text[i] == 'b')
  {
   draw_sprite(bmp, p_br, x, y); 
   x+= p_b->w;       
  }
  
  if(text[i] == 'c')
  {
   draw_sprite(bmp, p_cr, x, y); 
   x+= p_c->w;       
  }
  
  if(text[i] == 'd')
  {
   draw_sprite(bmp, p_dr, x, y); 
   x+= p_d->w;       
  }
  
  if(text[i] == 'e')
  {
   draw_sprite(bmp, p_er, x, y); 
   x+= p_e->w;       
  }
  
  if(text[i] == 'f')
  {
   draw_sprite(bmp, p_fr, x, y); 
   x+= p_f->w;       
  }
  
  if(text[i] == 'g')
  {
   draw_sprite(bmp, p_gr, x, y); 
   x+= p_f->w;       
  }
  
  if(text[i] == 'h')
  {
   draw_sprite(bmp, p_hr, x, y); 
   x+= p_h->w;       
  }
  
  if(text[i] == 'i')
  {
   draw_sprite(bmp, p_ir, x, y); 
   x+= p_i->w;       
  }
  
  if(text[i] == 'j')
  {
   draw_sprite(bmp, p_jr, x, y); 
   x+= p_j->w;       
  }
  
  if(text[i] == 'k')
  {
   draw_sprite(bmp, p_kr, x, y); 
   x+= p_k->w;       
  }
  
  if(text[i] == 'l')
  {
   draw_sprite(bmp, p_lr, x, y); 
   x+= p_l->w;       
  }
  
  if(text[i] == 'm')
  {
   draw_sprite(bmp, p_mr, x, y); 
   x+= p_m->w;       
  }
  
  if(text[i] == 'n')
  {
   draw_sprite(bmp, p_nr, x, y); 
   x+= p_n->w;       
  }
  
  if(text[i] == 'o')
  {
   draw_sprite(bmp, p_or, x, y); 
   x+= p_o->w;       
  }
  
  if(text[i] == 'p')
  {
   draw_sprite(bmp, p_pr, x, y); 
   x+= p_p->w;       
  }
  
  if(text[i] == 'q')
  {
   draw_sprite(bmp, p_qr, x, y); 
   x+= p_q->w;       
  }
  
  if(text[i] == 'r')
  {
   draw_sprite(bmp, p_rr, x, y); 
   x+= p_r->w;       
  }
  
  if(text[i] == 's')
  {
   draw_sprite(bmp, p_sr, x, y); 
   x+= p_s->w;       
  }
  
  if(text[i] == 't')
  {
   draw_sprite(bmp, p_tr, x, y); 
   x+= p_t->w;       
  }
  
  if(text[i] == 'u')
  {
   draw_sprite(bmp, p_ur, x, y); 
   x+= p_u->w;       
  }
  
  if(text[i] == 'v')
  {
   draw_sprite(bmp, p_vr, x, y); 
   x+= p_v->w;       
  }
  
  if(text[i] == 'w')
  {
   draw_sprite(bmp, p_wr, x, y); 
   x+= p_w->w;       
  }
  
  if(text[i] == 'x')
  {
   draw_sprite(bmp, p_xr, x, y); 
   x+= p_x->w;       
  }
  
  if(text[i] == 'y')
  {
   draw_sprite(bmp, p_yr, x, y); 
   x+= p_y->w;       
  }
  
  if(text[i] == 'z')
  {
   draw_sprite(bmp, p_zr, x, y); 
   x+= p_z->w;       
  }
  
  if(text[i] == ' ')
  {
   x+= 15;       
  }
  
  //aa
  if(text[i] == '*')
  {
   draw_sprite(bmp, p_aar, x, y); 
   x+= p_aa->w;       
  }
  //sh
  if(text[i] == '#')
  {
   draw_sprite(bmp, p_shr, x, y); 
   x+= p_sh->w;       
  }
  //yy
  if(text[i] == '&')
  {
   draw_sprite(bmp, p_yyr, x, y); 
   x+= p_yy->w;       
  }
  //ch
  if(text[i] == '$')
  {
   draw_sprite(bmp, p_chr, x, y); 
   x+= p_ch->w;       
  }
  //th
  if(text[i] == '%')
  {
   draw_sprite(bmp, p_thr, x, y); 
   x+= p_th->w;       
  }    
  //zh
  if(text[i] == '^')
  {
   draw_sprite(bmp, p_zhr, x, y); 
   x+= p_zh->w;       
  }
  //ii
  if(text[i] == '(')
  {
   draw_sprite(bmp, p_iir, x, y); 
   x+= p_ii->w;       
  }
  //ee
  if(text[i] == ')')
  {
   draw_sprite(bmp, p_eer, x, y); 
   x+= p_ee->w;       
  }
  //oo
  if(text[i] == '@')
  {
   draw_sprite(bmp, p_oor, x, y); 
   x+= p_oo->w;       
  }
  //ooo
  if(text[i] == ';')
  {
   draw_sprite(bmp, p_ooor, x, y); 
   x+= p_ooo->w;       
  }
  //lh
  if(text[i] == '~')
  {
   draw_sprite(bmp, p_lhr, x, y); 
   x+= p_lh->w;       
  }
  //uu
  if(text[i] == '{')
  {
   draw_sprite(bmp, p_uur, x, y); 
   x+= p_uu->w;       
  }
  if(text[i] == '0')
  {
   draw_sprite(bmp, p_0r, x, y); 
   x+= p_0->w;       
  }
    if(text[i] == '1')
  {
   draw_sprite(bmp, p_1r, x, y); 
   x+= p_1->w;       
  }
    if(text[i] == '2')
  {
   draw_sprite(bmp, p_2r, x, y); 
   x+= p_2->w;       
  }
    if(text[i] == '3')
  {
   draw_sprite(bmp, p_3r, x, y); 
   x+= p_3->w;       
  }
    if(text[i] == '4')
  {
   draw_sprite(bmp, p_4r, x, y); 
   x+= p_4->w;       
  }
    if(text[i] == '5')
  {
   draw_sprite(bmp, p_5r, x, y); 
   x+= p_5->w;       
  }
    if(text[i] == '6')
  {
   draw_sprite(bmp, p_6r, x, y); 
   x+= p_6->w;       
  }
    if(text[i] == '7')
  {
   draw_sprite(bmp, p_7r, x, y); 
   x+= p_7->w;       
  }
    if(text[i] == '8')
  {
   draw_sprite(bmp, p_8r, x, y); 
   x+= p_8->w;       
  }
    if(text[i] == '9')
  {
   draw_sprite(bmp, p_9r, x, y); 
   x+= p_9->w;       
  }
 }
 
 return 1;    
}

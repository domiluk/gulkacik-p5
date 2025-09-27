//tunak budu okna:
        //insert text
        //set texture
        //open file
        //save file
        //etc...
        
#include "engine.h"
//#include "numbox.h";
//#include "vgp.h"
        
int save_level(LEVEL *l, char *filename)
{
 FILE *ll;
 int x, y;
 int i;
 
 if(symbol_amount[0] == 2)l->qma++;
 if(symbol_amount[1] == 2)l->qma++;
 if(symbol_amount[2] == 2)l->qma++;
 if(symbol_amount[3] == 2)l->qma++;
 if(symbol_amount[4] == 2)l->qma++;
 
 ll = fopen(filename, "w");
 fprintf(ll, "%d %d %d %d %d %2.0f %2.0f ", l->w, l->h, l->qma, l->tela, l->la, l->bx, l->by);
 for(y = 0; y < l->h; y++)
  {
   for(x = 0; x < l->w; x++)
   {
    fprintf(ll, "%d ", l->info[x][y]);
    printf("%d ",l->info[x][y]); 
   }
   fprintf(ll, "\n");
  } 
 
 for(y = 0; y < l->h; y++)
  {
   for(x = 0; x < l->w; x++)
   {
    if(l->info[x][y] == 30)
    {
     if(l->tel[0].value == 30)fprintf(ll, " %d %d", l->tel[0].x, l->tel[0].y);  
     if(l->tel[1].value == 30)fprintf(ll, " %d %d", l->tel[1].x, l->tel[1].y);
     if(l->tel[2].value == 30)fprintf(ll, " %d %d", l->tel[2].x, l->tel[2].y);                    
    }
    if(l->info[x][y] == 31)
    {
     if(l->tel[0].value == 31)fprintf(ll, " %d %d", l->tel[0].x, l->tel[0].y);  
     if(l->tel[1].value == 31)fprintf(ll, " %d %d", l->tel[1].x, l->tel[1].y);
     if(l->tel[2].value == 31)fprintf(ll, " %d %d", l->tel[2].x, l->tel[2].y);                    
    }
    if(l->info[x][y] == 32)
    {
     if(l->tel[0].value == 32)fprintf(ll, " %d %d", l->tel[0].x, l->tel[0].y);  
     if(l->tel[1].value == 32)fprintf(ll, " %d %d", l->tel[1].x, l->tel[1].y);
     if(l->tel[2].value == 32)fprintf(ll, " %d %d", l->tel[2].x, l->tel[2].y);                    
    }
   }
   
  }  
  
  fprintf(ll, "%s", lvl->name);
 return 1;   
}        

int load_level(LEVEL *l, char *filename)
{
 FILE *ll;
 int x, y;
 //QM *q;
 int i;
 
 i = 0;
 ll = fopen(filename, "r");
 fscanf(ll, "%d %d %d %d %d %f %f", &l->w, &l->h, &l->qma, &l->tela, &l->la, &l->bx, &l->by);
 
 //l->qm = (QM*)malloc(sizeof(QM)*l->qma);
 //l->qm = (QM*)malloc(sizeof(int)*l->qma);
 
  for(y = 0; y < l->h; y++)
  {
   for(x = 0; x < l->w; x++)
   {
    fscanf(ll, "%d", &l->info[x][y]);
    printf("%d ",l->info[x][y]); 
    
    if(l->info[x][y] == 10 || l->info[x][y] == 11 || l->info[x][y] == 12)
    {
     l->qm[i].value = l->info[x][y];
     l->qm[i].x = x;              
     l->qm[i].y = y;
     l->qm[i].flip = 0;
     l->qm[i].done = 0;
     i++;
    }
         
   }
   printf("\n");
  }

  int zbytocnost, zbytocnost2;
  
  for(i = 0; i < l->tela; i++)
  {
   fscanf(ll, "%d %d", &zbytocnost, &zbytocnost2);      
  }
  
  //fgets(lvl->name, 512, ll);
  fscanf(ll, "%s", &lvl->name);
  return 1;   
}


LEVEL *init_level(int w, int h)
{
 int x, y;
 LEVEL *l;
 l = (LEVEL*)malloc(sizeof(LEVEL));
 
 l->w = w;
 l->h = h;
 l->qma = 0;
 l->tela = 0;
 
 for(x = 0; x < w; x++)
 for(y = 0; y < h; y++)
 {
  l->info[x][y] = 8;      
 }
 
 return l;      
}

BITMAP *level_to_bmp(LEVEL *l, int alpha)
{
 int x, y;
 int i = 0;
 BITMAP *b;
 if(alpha == 1)b = create_bitmap(l->w, l->h);
 else b = create_bitmap(l->w*FIELD_SIZE, l->h*FIELD_SIZE);
 
 printf(" i = %d\n\n", i);i++;
 
 if(alpha == 1) clear_to_color(b, 0);
 else{
  for(x = -15; x < b->w; x += bg->w)
  for(y = -9; y < b->h; y += bg->h)
  {
   draw_sprite(b, bg, x, y);
  }
 }
  printf("i = %d\n\n", i);i++;
  
 for(x = 0; x < l->w; x++)
 for(y = 0; y < l->h; y++)
 {
  switch(l->info[x][y])
  {
   case 0:
    if(alpha == 1)putpixel(b, x, y, 0xffffff); 
    else draw_sprite(b, normal_brick[rand() % 13], x*FIELD_SIZE, y*FIELD_SIZE);   
   break;
   case 1:
    if(alpha == 1)putpixel(b, x, y, makecol(128, 128, 128));
    else draw_sprite(b, water_field[0], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 2:
    if(alpha == 1)putpixel(b, x, y, makecol(128, 128, 128));
    else draw_sprite(b, water_field[1], x*FIELD_SIZE, y*FIELD_SIZE);    
   break; 
   case 3:
    if(alpha == 1)putpixel(b, x, y, makecol(128, 128, 128));
    else draw_sprite(b, water_field[2], x*FIELD_SIZE, y*FIELD_SIZE);    
   break;
   case 4:
    if(alpha == 1)putpixel(b, x, y, makecol(128, 128, 128));
    else draw_sprite(b, water_field[3], x*FIELD_SIZE, y*FIELD_SIZE);    
   break; 
   case 5:
    if(alpha == 1)putpixel(b, x, y, makecol(128, 128, 128));
    else draw_sprite(b, water_field[4], x*FIELD_SIZE, y*FIELD_SIZE);    
   break;
   case 7:
    draw_sprite(b, qm[0], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 9:
    draw_sprite(b, diebrick, x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 30:
    draw_sprite(b, teleport, x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 31:
    draw_sprite(b, teleport, x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 32:
    draw_sprite(b, teleport, x*FIELD_SIZE, y*FIELD_SIZE);
   break;      
   case 20:
    draw_sprite(b, trava[0], x*FIELD_SIZE, y*FIELD_SIZE);    
   break;
   case 21:
    draw_sprite(b, trava[1], x*FIELD_SIZE, y*FIELD_SIZE);    
   break;
   case 22:
    draw_sprite(b, trava[2], x*FIELD_SIZE, y*FIELD_SIZE);    
   break;
   case 23:
    draw_sprite(b, trava[3], x*FIELD_SIZE, y*FIELD_SIZE);    
   break;  
   case 24:
    draw_sprite(b, trava[4], x*FIELD_SIZE, y*FIELD_SIZE);    
   break; 
   case 40://hor_on
    draw_sprite(b, laser, (x-1)*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 41://ho_off
    draw_sprite(b, laser, (x-1)*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 42://ver_on
    draw_sprite(b, laser2, x*FIELD_SIZE, (y-1)*FIELD_SIZE);
   break;
   case 43://ver_off
    draw_sprite(b, laser2, x*FIELD_SIZE, (y-1)*FIELD_SIZE);
   break;  
   case 50://hor_on
    draw_sprite(b, arrow[0], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 51://ho_off
    draw_sprite(b, arrow[1], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 52://ver_on
    draw_sprite(b, arrow[2], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 53://ver_off
    draw_sprite(b, arrow[3], x*FIELD_SIZE, y*FIELD_SIZE);
   break; 
   
   case 10:
    if(alpha == 1)putpixel(b, x, y, makecol(10, 10, 10));
    else draw_sprite(b, symbol_brick[0], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 11:
    if(alpha == 1)putpixel(b, x, y, makecol(11, 11, 11));
    else draw_sprite(b, symbol_brick[1], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 12:
    if(alpha == 1)putpixel(b, x, y, makecol(12, 12, 12));
    else draw_sprite(b, symbol_brick[2], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 13:
    if(alpha == 1)putpixel(b, x, y, makecol(12, 12, 12));
    else draw_sprite(b, symbol_brick[3], x*FIELD_SIZE, y*FIELD_SIZE);
   break;
   case 14:
    if(alpha == 1)putpixel(b, x, y, makecol(12, 12, 12));
    else draw_sprite(b, symbol_brick[4], x*FIELD_SIZE, y*FIELD_SIZE);
   break;                       
  }
 }
 
 return b;       
}

LEVEL *init_level(char *filename)
{
 LEVEL *l;
 l = (LEVEL*)malloc(sizeof(LEVEL));
 load_level(l, filename);
 l->bmp = level_to_bmp(l, 0);
 l->alpha = level_to_bmp(l, 1);
 
 return l; 
}

int save_vgp(char *filename, WIND *wnd)
{
 FILE *vgp;
 vgp = fopen(filename, "w");
 if(vgp == NULL)printf("cannot create file");
 int loop = 0;
 OBJECT *oobj = (OBJECT*)malloc(sizeof(OBJECT));
 
 oobj = wnd->cnvs->lastobj;
 fprintf(vgp, "%d\n",wnd->cnvs->obj_amount);
 while(loop < wnd->cnvs->obj_amount)
  {
    //type
    fprintf(vgp, "%d\n", oobj->type);
    //printf("potadeto som sa dostal");
    //fill type
     
    //printf("potadeto som sa dostal");
    
    if(oobj->type == TYPE_INLINE_CIRC)
    {
     fprintf(vgp,"%d ", oobj->ic->fill_type);
     if(oobj->ic->fill_type == SIMPLE_COLOR)
     {
      //clr 1
      fprintf(vgp,"%d ", oobj->ic->clr1);                       
     }              
     
     if(oobj->ic->fill_type == GRADIENT_COLOR)
     {
      //clr 1 & clr 2
      fprintf(vgp,"%d ", oobj->ic->clr1);                       
      fprintf(vgp,"%d ", oobj->ic->clr2);                       
     }
     
     fprintf(vgp, "%d ", oobj->ic->x1);
     fprintf(vgp, "%d ", oobj->ic->y1);
     fprintf(vgp, "%d ", oobj->ic->r);
     fprintf(vgp, "%d ", oobj->ic->border_width);
     fprintf(vgp, "%d",  oobj->ic->border_clr);
    }//INLINE CIRC
    
    if(oobj->type == TYPE_INLINE_QUAD)
    {
     fprintf(vgp,"%d ", oobj->iq->fill_type);
     if(oobj->iq->fill_type == SIMPLE_COLOR)
     {
      //clr 1
      fprintf(vgp,"%d ", oobj->iq->clr1);                       
     }              
     
     if(oobj->iq->fill_type == GRADIENT_COLOR)
     {
      //clr 1 & clr 2
      fprintf(vgp,"%d ", oobj->iq->clr1);                       
      fprintf(vgp,"%d ", oobj->iq->clr2);                       
     }
     
     fprintf(vgp, "%d ", oobj->iq->x1);
     fprintf(vgp, "%d ", oobj->iq->y1);              
     fprintf(vgp, "%d ", oobj->iq->x2);
     fprintf(vgp, "%d ", oobj->iq->y2);
     fprintf(vgp, "%d ", oobj->iq->border_width);
     fprintf(vgp, "%d",  oobj->iq->border_clr);    
    }//INLINE QUAD
    
    if(oobj->type == TYPE_INLINE_RECT)
    {
     fprintf(vgp,"%d ", oobj->ir->fill_type);
     if(oobj->ir->fill_type == SIMPLE_COLOR)
     {
      //clr 1
      fprintf(vgp,"%d ", oobj->ir->clr1);                       
     }              
     
     if(oobj->ir->fill_type == GRADIENT_COLOR)
     {
      //clr 1 & clr 2
      fprintf(vgp,"%d ", oobj->ir->clr1);                       
      fprintf(vgp,"%d ", oobj->ir->clr2);                       
     }
     
     fprintf(vgp, "%d ", oobj->ir->x1);
     fprintf(vgp, "%d ", oobj->ir->y1);
     fprintf(vgp, "%d ", oobj->ir->w_and_h);
     fprintf(vgp, "%d ", oobj->ir->border_width);
     fprintf(vgp, "%d",  oobj->ir->border_clr);              
    }//INLINE RECT
    
    if(oobj->type == TYPE_INLINE_ELIP)
    {
     fprintf(vgp,"%d ", oobj->ie->fill_type);
     if(oobj->ie->fill_type == SIMPLE_COLOR)
     {
      //clr 1
      fprintf(vgp,"%d ", oobj->ie->clr1);                       
     }              
     
     if(oobj->ie->fill_type == GRADIENT_COLOR)
     {
      //clr 1 & clr 2
      fprintf(vgp,"%d ", oobj->ie->clr1);                       
      fprintf(vgp,"%d ", oobj->ie->clr2);                       
     }
     
     fprintf(vgp, "%d ", oobj->ie->x1);
     fprintf(vgp, "%d ", oobj->ie->y1);
     fprintf(vgp, "%d ", oobj->ie->rx);
     fprintf(vgp, "%d ", oobj->ie->ry);
     fprintf(vgp, "%d ", oobj->ie->border_width);
     fprintf(vgp, "%d",  oobj->ie->border_clr);              
    }//INLINE ELIP
    
    //OUTLINEEEEEEZ
    if(oobj->type == TYPE_OUTLINE_QUAD)
    {
     fprintf(vgp, "%d ", oobj->oq->clr1);                       
     fprintf(vgp, "%d ", oobj->oq->x1);
     fprintf(vgp, "%d ", oobj->oq->y1);
     fprintf(vgp, "%d ", oobj->oq->x2);
     fprintf(vgp, "%d ", oobj->oq->y2);
     fprintf(vgp, "%d",  oobj->oq->stroke);
    }//OUTLINE ELIP
    
    if(oobj->type == TYPE_OUTLINE_RECT)
    {
     fprintf(vgp, "%d ", oobj->ore->clr1);                       
     fprintf(vgp, "%d ", oobj->ore->x1);
     fprintf(vgp, "%d ", oobj->ore->y1);
     fprintf(vgp, "%d ", oobj->ore->w_and_h);
     fprintf(vgp, "%d",  oobj->ore->stroke);
    }//OUTLINE RECT
    
    if(oobj->type == TYPE_OUTLINE_CIRC)
    {
     fprintf(vgp, "%d ", oobj->oc->clr1);                       
     fprintf(vgp, "%d ", oobj->oc->x1);
     fprintf(vgp, "%d ", oobj->oc->y1);
     fprintf(vgp, "%d ", oobj->oc->r);
     fprintf(vgp, "%d",  oobj->oc->stroke);
    }//OUTLINE CIRC
    
    if(oobj->type == TYPE_OUTLINE_ELIP)
    {
     fprintf(vgp, "%d ", oobj->oe->clr1);                       
     fprintf(vgp, "%d ", oobj->oe->x1);
     fprintf(vgp, "%d ", oobj->oe->y1);
     fprintf(vgp, "%d ", oobj->oe->rx);
     fprintf(vgp, "%d ", oobj->oe->ry);
     fprintf(vgp, "%d",  oobj->oe->stroke);
    }//OUTLINE ELIP
    
    fprintf(vgp, "\n");
    if(oobj->prevobject != NULL)
       oobj = oobj->prevobject;
    loop++;
    printf("%d",loop);
  }
  fclose(vgp);
 return 1;    
}

int gggg;
//write me down FILENAME and I will open it in this WINDow...
int open_vgp(char *filename, WIND *wnd)
{
 int obj_amt;
 //possible attributes
 int stroke, fill_type, x1, x2, y1, y2, r, rx, ry, w_and_h, border_width, border_clr, clr1, clr2;
 int type;
 FILE *vgp;
 vgp = fopen(filename, "r");
 if(vgp == NULL)printf("cannot find file specified");
 
 OBJECT *obj;
 wnd->cnvs->obj = NULL;
 
 fscanf(vgp,"%d",&obj_amt);
 
 for(gggg = 0;gggg < obj_amt;gggg++)
 {
  fscanf(vgp,"%d", &type);
  
  if(type == TYPE_INLINE_QUAD)
  {
   fscanf(vgp,"%d",&fill_type);
   if(fill_type == SIMPLE_COLOR)
   {
    fscanf(vgp, "%d", &clr1);             
   }        
   if(fill_type == GRADIENT_COLOR)
   {
    fscanf(vgp,"%d", &clr1);
    fscanf(vgp,"%d", &clr2);             
   }
   fscanf(vgp, "%d", &x1);
   fscanf(vgp, "%d", &y1);
   fscanf(vgp, "%d", &x2);
   fscanf(vgp, "%d", &y2);
   fscanf(vgp, "%d", &border_width);
   fscanf(vgp, "%d", &border_clr);
   
   if(fill_type == SIMPLE_COLOR)
   obj = make_inline_quad(x1, y1, x2, y2, SIMPLE_COLOR, clr1, 0, border_clr, border_width);
   stick_object_to_canvas(wnd->cnvs,obj);
  }//TYPE_INLINE_QUAD     
  
  if(type == TYPE_INLINE_RECT)
  {
   fscanf(vgp,"%d",&fill_type);
   if(fill_type == SIMPLE_COLOR)
   {
    fscanf(vgp, "%d", &clr1);             
   }        
   if(fill_type == GRADIENT_COLOR)
   {
    fscanf(vgp,"%d", &clr1);
    fscanf(vgp,"%d", &clr2);             
   }
   fscanf(vgp, "%d", &x1);
   fscanf(vgp, "%d", &y1);
   fscanf(vgp, "%d", &w_and_h);
   fscanf(vgp, "%d", &border_width);
   fscanf(vgp, "%d", &border_clr);
   
   if(fill_type == SIMPLE_COLOR)
   obj = make_inline_rect(x1, y1, w_and_h, SIMPLE_COLOR, clr1, 0, border_clr, border_width);
   stick_object_to_canvas(wnd->cnvs,obj);
  }//TYPE_INLINE_RECT
  
  if(type == TYPE_INLINE_CIRC)
  {
   fscanf(vgp,"%d",&fill_type);
   if(fill_type == SIMPLE_COLOR)
   {
    fscanf(vgp, "%d", &clr1);             
   }        
   if(fill_type == GRADIENT_COLOR)
   {
    fscanf(vgp,"%d", &clr1);
    fscanf(vgp,"%d", &clr2);             
   }
   fscanf(vgp, "%d", &x1);
   fscanf(vgp, "%d", &y1);
   fscanf(vgp, "%d", &r);
   fscanf(vgp, "%d", &border_width);
   fscanf(vgp, "%d", &border_clr);
   
   if(fill_type == SIMPLE_COLOR)
   obj = make_inline_circ(x1, y1, r, SIMPLE_COLOR, clr1, 0, border_clr, border_width);
   stick_object_to_canvas(wnd->cnvs,obj);
  }//TYPE_INLINE_CIRC
  
  if(type == TYPE_INLINE_ELIP)
  {
   fscanf(vgp,"%d",&fill_type);
   if(fill_type == SIMPLE_COLOR)
   {
    fscanf(vgp, "%d", &clr1);             
   }        
   if(fill_type == GRADIENT_COLOR)
   {
    fscanf(vgp,"%d", &clr1);
    fscanf(vgp,"%d", &clr2);             
   }
   fscanf(vgp, "%d", &x1);
   fscanf(vgp, "%d", &y1);
   fscanf(vgp, "%d", &rx);
   fscanf(vgp, "%d", &ry);
   fscanf(vgp, "%d", &border_width);
   fscanf(vgp, "%d", &border_clr);
   
   if(fill_type == SIMPLE_COLOR)
   obj = make_inline_elip(x1, y1, rx, ry, SIMPLE_COLOR, clr1, 0, border_clr, border_width);
   stick_object_to_canvas(wnd->cnvs,obj);
  }//TYPE_INLINE_ELIP
  
  if(type == TYPE_OUTLINE_QUAD)
  {
   fscanf(vgp, "%d", &clr1);             
   fscanf(vgp, "%d", &x1);
   fscanf(vgp, "%d", &y1);
   fscanf(vgp, "%d", &x2);
   fscanf(vgp, "%d", &y2);
   fscanf(vgp, "%d", &stroke);
   
   obj = make_outline_quad(x1, y1, x2, y2, clr1, stroke);
   stick_object_to_canvas(wnd->cnvs,obj);
  }//TYPE_OUTLINE_QUAD
  
  if(type == TYPE_OUTLINE_RECT)
  {
   fscanf(vgp, "%d", &clr1);             
   fscanf(vgp, "%d", &x1);
   fscanf(vgp, "%d", &y1);
   fscanf(vgp, "%d", &w_and_h);
   fscanf(vgp, "%d", &stroke);
   
   obj = make_outline_rect(x1, y1, w_and_h, clr1, stroke);
   stick_object_to_canvas(wnd->cnvs,obj);
  }//TYPE_OUTLINE_RECT
  
  if(type == TYPE_OUTLINE_CIRC)
  {
   fscanf(vgp, "%d", &clr1);             
   fscanf(vgp, "%d", &x1);
   fscanf(vgp, "%d", &y1);
   fscanf(vgp, "%d", &r);
   fscanf(vgp, "%d", &stroke);
   
   obj = make_outline_circ(x1, y1, r, clr1, stroke);
   stick_object_to_canvas(wnd->cnvs,obj);
  }//TYPE_OUTLINE_ELIP
  
  if(type == TYPE_OUTLINE_ELIP)
  {
   fscanf(vgp, "%d", &clr1);             
   fscanf(vgp, "%d", &x1);
   fscanf(vgp, "%d", &y1);
   fscanf(vgp, "%d", &rx);
   fscanf(vgp, "%d", &ry);
   fscanf(vgp, "%d", &stroke);
   
   obj = make_outline_elip(x1, y1, rx, ry, clr1, stroke);
   stick_object_to_canvas(wnd->cnvs,obj);
  }//TYPE_OUTLINE_ELIP
   
 }
 wnd->cnvs->redraw = 1;
 fclose(vgp);
 //stick_canvas_to_window(wnd,cnv);
 return 1;     
}




//INSERT TEXT

void insert_text_ok_action()
{
  set_visibility(insert_text_wnd,0);
  move_button_action();   
}

void insert_text_cancel_action()
{
  set_visibility(insert_text_wnd,0);
  move_button_action();
}

//SET TEXTURE
void set_texture_ok_action()
{
  set_visibility(set_texture_wnd,0);
  c_red = rr = getpixledr;
  c_green = gg = getpixledg;
  c_blue = bb = getpixledb;
  make_qgrad();
}

void set_texture_cancel_action()
{
  set_visibility(set_texture_wnd,0);
}

//CREDITS
void credits_ok_action()
{
credits_wnd->visible = 0; 	 
}

//TYPE
void rectangle_action()
{
 rbtn->switch_on = 1;
 sbtn->switch_on = 0;
 cbtn->switch_on = 0;
 ebtn->switch_on = 0;
}

void square_action()
{
 rbtn->switch_on = 0;
 sbtn->switch_on = 1;
 cbtn->switch_on = 0;
 ebtn->switch_on = 0;     
}

void circle_action()
{
 rbtn->switch_on = 0;
 sbtn->switch_on = 0;
 cbtn->switch_on = 1;
 ebtn->switch_on = 0;     
}

void ellipse_action()
{
 rbtn->switch_on = 0;
 sbtn->switch_on = 0;
 cbtn->switch_on = 0;
 ebtn->switch_on = 1;     
}

void type_ok_action()
{
 if(rbtn->switch_on == 1)chsnprmtv = 0;
 if(sbtn->switch_on == 1)chsnprmtv = 2;
 if(cbtn->switch_on == 1)chsnprmtv = 1;
 if(ebtn->switch_on == 1)chsnprmtv = 3;
 
 type_wnd->visible = 0;
}

//SAVE AS
void save_as_ok_action()
{
 char filename[500];
 int prevmode;
 int format;
 format = fbsave->cblst->units[fbsave->cblst->cpoi]->value;
 BITMAP *wts1, *wts2;
 
 strcpy(filename, fbsave->path);
 filename[strlen(fbsave->path)] = '\0';
 filename[strlen(fbsave->path)-1] = '\0';
 filename[strlen(fbsave->path)-2] = '\0';
 filename[strlen(fbsave->path)-3] = '\0';
 //filename->path[strlen(fbsave->path)-4] = '\0';
 printf("%d", strlen(fbsave->path));
 strcat(filename, fbsave->tbox->text);
 printf("%s",filename);
 save_level(lvl, filename);//save_vgp(filename, window);
 if(fbsave->cblst->units[fbsave->cblst->cpoi]->value > 0 && fbsave->cblst->units[fbsave->cblst->cpoi]->value < 7)
 {
  wts1 = create_bitmap(window->cnvs->w, window->cnvs->h+40);
  wts2 = create_bitmap(window->cnvs->w, window->cnvs->h);
  prevmode = mode;
	mode = MODE_TOOL_MOVE;
	window->cnvs->redraw = 1;
	draw_canvas(window,wts1);
	//draw_sprite(screen,wts1, 0,0);
	blit(wts1, wts2, 0, 20, 0,0, window->cnvs->w, window->cnvs->h);
	//rest(4000);
	if(format == 1)
	save_bmp(filename, wts2, NULL);
	if(format == 2)
	save_tga(filename, wts2, NULL);
	if(format == 3)
	save_pcx(filename, wts2, NULL);
	if(format == 4)
	save_gif(filename, wts2, NULL);
	if(format == 5)
	save_png(filename, wts2, NULL);
	if(format == 6)
	save_jpg(filename, wts2, NULL);
		
	destroy_bitmap(wts1);
	destroy_bitmap(wts2);
	mode = prevmode;																										 
 }
 printf("Saved %s", filename);
 save_as_wnd->visible  = 0;     
}

void save_as_cancel_action()
{
 save_as_wnd->visible  = 0;     
}

//OPEN
void open_ok_action()
{
 char filename[500];
 strcpy(filename, fbopen->path);
 filename[strlen(fbopen->path)] = '\0';
 filename[strlen(fbopen->path)-1] = '\0';
 filename[strlen(fbopen->path)-2] = '\0';
 filename[strlen(fbopen->path)-3] = '\0';
 //filename->path[strlen(fbsave->path)-4] = '\0';
 printf("\n\n $$$ %d $$$", strlen(fbopen->path));
 strcat(filename, fbopen->tbox->text);
 printf("\n\n $$$$ %s $$$$",filename);
 //(fbopen->cblst->units[fbopen->cblst->cpoi]->value == 0)
 //{
  lvl = init_level(100, 100);
  printf("\np\n");
  load_level(lvl, filename);
    printf("\npp\n");
  //open_vgp(filename, window);
  lvl->bmp = level_to_bmp(lvl, 0);
    printf("\nppp\n");
  draw_sprite(lvl->bmp, gulkacik, lvl->bx, lvl->by);
    printf("\npppp\n");
  have_level = true;
  rest(300);
 //}
 printf("opened %s", filename);
 open_wnd->visible  = 0;     
}
void open_cancel_action()
{
 open_wnd->visible  = 0;     
}


//fm
void fm_ok_action()
{
 fm_wnd->visible = 0; 		 
}


//NEW
void new_ok_action()
{
 lvl = init_level(ww->value, hhh->value);
 printf("TU SOM");
 lvl->bmp = level_to_bmp(lvl, 0);
 printf("AJ TU");
 have_level = true; 
 new_wnd->visible = 0;
 //lvl->name = project_name->text;	 
 strcpy(lvl->name, project_name->text);
 rest(300);
}

void new_cancel_action()
{
 new_wnd->visible = 0; 		 
}


//MAKEs
int make_insert_text()
{
  //spravenie zakladneho okna
  //prepanajana to naco som tak poznamkoval??
  
  insert_text_wnd = make_wind(SCREEN_W/2-200,SCREEN_H/2-150,400,165,"Insert text",false,true,true);   
  
  BUTTON *btn;
  btn = init_button(285,31,50,21,"OK",20,NULL,1,0);
  set_button_action(btn,insert_text_ok_action);
  stick_button_to_window(insert_text_wnd,btn);
  
  btn = init_button(285,61,50,21,"Cancel",18,NULL,1,0);
  set_button_action(btn,insert_text_cancel_action);
  stick_button_to_window(insert_text_wnd,btn);
  
  alfont_set_font_size(larabie, 18);
  alfont_textprintf_aa(insert_text_wnd->bmp, larabie, 25, 55, 0xffffff, "Insert text:");
  ittbox = init_textbox(25,75,200,150,1,"Insert your text here");
  
  return 1;
}

int make_set_texture()
{
  set_texture_wnd = make_wind(100,100,400,300,"Set Texture",false,true,true);       
  trix = create_bitmap(215,5);
  blit(set_texture_wnd->bmp, trix, 0, 43, 0,0,215,5);
  triy = create_bitmap(5,215);
  blit(set_texture_wnd->bmp, triy, 2, 43, 0,0,5,215);
  
  BUTTON *butn;
  butn = init_button(314,31,50,21,"OK",20,NULL,1,0);
  set_button_action(butn,set_texture_ok_action);
  stick_button_to_window(set_texture_wnd,butn);
  
  butn = init_button(314,61,50,21,"Cancel",18,NULL,1,0);
  set_button_action(butn,set_texture_cancel_action);
  stick_button_to_window(set_texture_wnd,butn);
  
  GTYPE = init_button(284,270,45,17,"G-Type",15,NULL,1,0);
  set_button_action(GTYPE,set_texture_cancel_action);
  stick_button_to_window(set_texture_wnd,GTYPE);
  
  set_texture_wnd->active = true;
  
  return 1;
}

int make_credits()
{
 credits_wnd = make_wind(100, 120, 400, 300, "Autori", false, true, true);
 credits_wnd ->active = 1;
 
 BUTTON *btn;
 btn = init_button(200-25, 260, 50, 20, "OK", 20, NULL, 1, 0);
 set_button_action(btn, credits_ok_action);
 stick_button_to_window(credits_wnd, btn);
 //set_uformat(U_UTF8);
 int posun = 30;
 char dlhe_a = '\225';
 char dlo[] = "Daniel Lovsko";
 uinsert(dlo, 10, dlhe_a);
 
 alfont_set_font_size(larabie, 25);
 alfont_textprintf_aa(credits_wnd->bmp, larabie, 145, 75-posun, 0xffffff, "Programovanie");
 alfont_textprintf_aa(credits_wnd->bmp, larabie, 4,  145-posun, 0xffffff, "Dizajn");
 alfont_textprintf_aa(credits_wnd->bmp, larabie, 145,225-posun, 0xffffff, "Podakovanie");
 alfont_set_font_size(larabie, 20);
 alfont_textprintf_right_aa(credits_wnd->bmp,larabie, 325, 120-posun, 0xffffff, "Daniel Lovasko");
 alfont_textprintf_right_aa(credits_wnd->bmp,larabie, 125, 175-posun, 0xffffff, "Daniel Lovasko");
 //alfont_textprintf_right_aa(credits_wnd->bmp,larabie, 323, 140-posun, 0xffffff, "Dominik Lukac");
 alfont_set_font_size(larabie, 17);
 alfont_textprintf_right_aa(credits_wnd->bmp, larabie, 350, 250-posun, 0xffffff, "Marian Stano");
 alfont_textprintf_right_aa(credits_wnd->bmp, larabie, 350, 264-posun, 0xffffff, "Peter Mindek");
 alfont_textprintf_right_aa(credits_wnd->bmp, larabie, 350, 278-posun, 0xffffff, "Michal Szabados");
 alfont_textprintf_right_aa(credits_wnd->bmp, larabie, 350, 292-posun, 0xffffff, "Rastislav Tisovcik");
 return 1;  	
}

int make_type()
{
 type_wnd = make_wind(150,150,120,150, "Type", false, true, true);
 type_wnd->active = 1;
 
 BUTTON *btn;
 rbtn = init_button(60-25, 30, 50, 20, "Rectangle", 14, NULL, 0, 1);
 set_button_action(rbtn, rectangle_action);
 stick_button_to_window(type_wnd, rbtn);
 
 sbtn = init_button(60-25, 50, 50, 20, "Square", 17, NULL, 0, 0);
 set_button_action(sbtn, square_action);
 stick_button_to_window(type_wnd, sbtn);
 
 cbtn = init_button(60-25, 70, 50, 20, "Circle", 18, NULL, 0, 0);
 set_button_action(cbtn, circle_action);
 stick_button_to_window(type_wnd, cbtn);
 
 ebtn = init_button(60-25, 90, 50, 20, "Ellipse", 16, NULL, 0, 0);
 set_button_action(ebtn, ellipse_action);
 stick_button_to_window(type_wnd, ebtn);
 
 btn = init_button(60-25, 116, 50, 20, "OK", 20, NULL, 1, 0);
 set_button_action(btn, type_ok_action);
 stick_button_to_window(type_wnd, btn);
 
 return 1;    
}

int make_save_as()
{
 save_as_wnd = make_wind(100,120,400,300,"Nahraj ako...", true, true, true);
 save_as_wnd->active = 1;
 save_as_wnd->visible = 0;
 
 BUTTON *butn;
 butn = init_button(314,31,50,21,"OK",20,NULL,1,0);
 set_button_action(butn,save_as_ok_action);
 stick_button_to_window(save_as_wnd,butn);
 
 butn = init_button(314,61,50,21,"Nie",18,NULL,1,0);
 set_button_action(butn,save_as_cancel_action);
 stick_button_to_window(save_as_wnd,butn);
 
 formatt = init_list(50, 270);
 unitt = init_unit("GUD", 0);
 /*stick_unit_to_combo_list(formatt, unitt); 
 unitt = init_unit("BMP", 1);
 stick_unit_to_combo_list(formatt, unitt);
 unitt = init_unit("TGA", 2);
 stick_unit_to_combo_list(formatt, unitt);
 unitt = init_unit("PCX", 3);
 stick_unit_to_combo_list(formatt, unitt);
 unitt = init_unit("GIF", 4);
 stick_unit_to_combo_list(formatt, unitt); 
 unitt = init_unit("PNG", 5);
 stick_unit_to_combo_list(formatt, unitt);
 unitt = init_unit("JPG", 6);
 stick_unit_to_combo_list(formatt, unitt);*/
 
 fnametbox = init_textbox(50,250,198,15,0,"untitled.gud");
 
 //fbsave = init_filebrowser(25,50,"C:/Documents and Settings/lovasko1/Desktop/02/", formatt);
 
 //treba stickovat skor ako initovat fileho...
 
 fbsave = init_filebrowser(-167,50,"./", fnametbox, formatt);printf("sticked");
 //stick_textbox_to_filebrowser(fbsave, fnametbox);printf("sticked");
 //stick_combo_list_to_filebrowser(fbsave, formatt);
 
 printf("tu som");
 return 1;    
}

int make_fm()
{
 fm_wnd = make_wind(100,120,400,300,"Love is all around", true, true, true);
 fm_wnd->active = 1;
 fm_wnd->visible = 0;
  
 BUTTON *butn;
 butn = init_button(314,31,50,21,"OK",20,NULL,1,0);
 set_button_action(butn,fm_ok_action);
 stick_button_to_window(fm_wnd,butn);
 
 /*triangle(fm_wnd->bmp, 200-50, 120, 200+50,120, 200, 180, 0x990000);
 circlefill(fm_wnd->bmp, 200-25, 120, 25/2, 0x990000);	 		
 circlefill(fm_wnd->bmp, 200+25, 120, 25/2, 0x990000);
 */
 draw_sprite(fm_wnd->bmp, hb, 200-hb->w/2, 150-hb->h/2);
 
 alfont_textprintf_aa(fm_wnd->bmp, larabie, 50,50,makecol(255,255,255),"For someone who I love");
 alfont_textprintf_right_aa(fm_wnd->bmp, larabie, 280, 250, 0xffffff, "Dano");
 alfont_set_font_size(larabie, 50);
 alfont_textprintf_centre_aa(fm_wnd->bmp, larabie, 200, 110, 0xffffff, "Marry");
 return 1;
}

int make_open()
{
 open_wnd = make_wind(100,120,400,300,"Otvor", true, true, true);
 open_wnd->active = 1;
 open_wnd->visible = 0;
 
 BUTTON *butn;
 butn = init_button(314,31,50,21,"OK",20,NULL,1,0);
 set_button_action(butn,open_ok_action);
 stick_button_to_window(open_wnd,butn);
 
 butn = init_button(314,61,50,21,"Nie",18,NULL,1,0);
 set_button_action(butn,open_cancel_action);
 stick_button_to_window(open_wnd,butn);
 
 formatto = init_list(50, 270);
 //unitto = init_unit("VGP", 0);
 //stick_unit_to_combo_list(formatto, unitto);/* 
 /*unitt = init_unit("BMP", 1);
 stick_unit_to_combo_list(formatt, unitt);
 unitt = init_unit("TGA", 2);
 stick_unit_to_combo_list(formatt, unitt);
 unitt = init_unit("PCX", 3);
 stick_unit_to_combo_list(formatt, unitt); */
 
 fnametboxo = init_textbox(50,250,198,15,0,"untitled.gud");
 
 //fbsave = init_filebrowser(25,50,"C:/Documents and Settings/lovasko1/Desktop/02/", formatt);
 
 //treba stickovat skor ako initovat fileho...
 
 fbopen = init_filebrowser(-167,50,"./", fnametboxo, formatto);printf("sticked");
 //stick_textbox_to_filebrowser(fbsave, fnametbox);printf("sticked");
 //stick_combo_list_to_filebrowser(fbsave, formatt);
 
 printf("tu som open");
 return 1;    
}

int make_new()
{
 new_wnd = make_wind(100,120,350,100,"Odznova", true, true, true);
 new_wnd->active = 1;
 new_wnd->visible = 0;
 
 BUTTON *butn;
 butn = init_button(250+20,31,50,21,"OK",20,NULL,1,0);
 set_button_action(butn,new_ok_action);
 stick_button_to_window(new_wnd,butn);
 
 butn = init_button(250+20,61,50,21,"Nie",18,NULL,1,0);
 set_button_action(butn,new_cancel_action);
 stick_button_to_window(new_wnd,butn); 		
 
 ww = init_numbox(10.0, 0, 1.0, 100, 1);
 hhh = init_numbox(8.0, 0, 1.0, 100, 1);
 
 project_name = init_textbox(90,25,150,15,0,"Level 01");
 
 alfont_textprintf_right_aa(new_wnd->bmp, larabie, 45, 50, 0xffffff, "X:");
 alfont_textprintf_right_aa(new_wnd->bmp, larabie, 45, 75, 0xffffff, "Y:");
 alfont_textprintf_aa(new_wnd->bmp, larabie, 5,25,0xffffff, "Meno:");
  
 return 1;
}

int make_new_hlaska()
{
 new_hlaska = make_wind(100,120,350,100,"Pridaj hlasku", true, true, true);
 new_hlaska->active = 1;
 new_hlaska->visible = 1;
 
 BUTTON *butn;
 butn = init_button(250+20,31,50,21,"OK",20,NULL,1,0);
 set_button_action(butn,hlaska_ok_action);
 stick_button_to_window(new_hlaska,butn);
 
 butn = init_button(250+20,61,50,21,"Nie",18,NULL,1,0);
 set_button_action(butn,hlaska_cancel_action);
 stick_button_to_window(new_hlaska,butn); 
 
 return 1;   
}

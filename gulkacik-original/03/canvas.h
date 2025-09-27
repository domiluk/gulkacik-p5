//tu budu funkcie na platno a objekty na nom

#include "engine.h"
#include <math.h>


CANVAS* init_canvas(int x, int y, int w, int h)
{
  CANVAS *cnv;
  cnv = (CANVAS*)malloc(sizeof(CANVAS));
  
  cnv->x = x;
  cnv->y = y;
  cnv->w = w;
  cnv->h = h;
  cnv->bmp = create_bitmap(w,h);
  cnv->redraw = 1;
  clear_to_color(cnv->bmp,0xffffff);
  
  return cnv;        
}

int stick_object_to_canvas(CANVAS *cnv, OBJECT *obj)
{
  if(cnv->obj == NULL)
    cnv->lastobj = obj;
  else
    cnv->obj->prevobject = obj;
  obj->nextobject = cnv->obj;
  cnv->obj = obj;
  cnv->obj_amount++;
  return 1;
}

int draw_canvas(WIND *wnd, BITMAP *bmp)
{
  int loop = 0;
  OBJECT *oobj = (OBJECT*)malloc(sizeof(OBJECT));
  oobj = wnd->cnvs->lastobj;
  clear_to_color(wnd->cnvs->bmp, 0xffffff);
  while(loop < wnd->cnvs->obj_amount)
  {
    switch(oobj->type)
    {
      case TYPE_INLINE_QUAD:
        if(mode == MODE_TOOL_TRANSFORM)
        {
          invert_rect(wnd->cnvs->bmp, oobj->iq->x1-4, oobj->iq->y1-4, oobj->iq->x1-1, oobj->iq->y1-1, "a");
          invert_rect(wnd->cnvs->bmp, oobj->iq->x2+1, oobj->iq->y1-4, oobj->iq->x2+4, oobj->iq->y1-1, "b");
          invert_rect(wnd->cnvs->bmp, oobj->iq->x2+1, oobj->iq->y2+1, oobj->iq->x2+4, oobj->iq->y2+4, "c");
          invert_rect(wnd->cnvs->bmp, oobj->iq->x1-4, oobj->iq->y2+1, oobj->iq->x1-1, oobj->iq->y2+4, "d");
        }
        rectogon[0] = oobj->iq->x1; rectogon[1] = oobj->iq->y1;
        rectogon[2] = oobj->iq->x2; rectogon[3] = oobj->iq->y1;
        rectogon[4] = oobj->iq->x2; rectogon[5] = oobj->iq->y2;
        rectogon[6] = oobj->iq->x1; rectogon[7] = oobj->iq->y2;
        if(oobj->iq->fill_type == SIMPLE_COLOR)
          polygon(wnd->cnvs->bmp, 4, rectogon, oobj->iq->clr1);
      break;
      case TYPE_INLINE_CIRC:
        if(oobj->ic->fill_type == SIMPLE_COLOR)
          circlefill(wnd->cnvs->bmp, oobj->ic->x1, oobj->ic->y1, oobj->ic->r, oobj->ic->clr1);
      break;
      case TYPE_INLINE_RECT:
        rectfill(wnd->cnvs->bmp, oobj->ir->x1, oobj->ir->y1, oobj->ir->x1+oobj->ir->w_and_h, oobj->ir->y1+oobj->ir->w_and_h, oobj->ir->clr1);
      break;
      case TYPE_INLINE_ELIP:
        if(oobj->ie->fill_type == SIMPLE_COLOR)
          ellipsefill(wnd->cnvs->bmp, oobj->ie->x1, oobj->ie->y1, oobj->ie->rx, oobj->ie->ry, oobj->ie->clr1);
      break;
      case TYPE_OUTLINE_QUAD:
        line(wnd->cnvs->bmp, oobj->oq->x1, oobj->oq->y1, oobj->oq->x2, oobj->oq->y1, oobj->oq->clr1);
        line(wnd->cnvs->bmp, oobj->oq->x2, oobj->oq->y1, oobj->oq->x2, oobj->oq->y2, oobj->oq->clr1);
        line(wnd->cnvs->bmp, oobj->oq->x2, oobj->oq->y2, oobj->oq->x1, oobj->oq->y2, oobj->oq->clr1);
        line(wnd->cnvs->bmp, oobj->oq->x1, oobj->oq->y2, oobj->oq->x1, oobj->oq->y1, oobj->oq->clr1);
      break;
      case TYPE_OUTLINE_CIRC:
        circle(wnd->cnvs->bmp, oobj->oc->x1, oobj->oc->y1, oobj->oc->r, oobj->oc->clr1);
      break;
      case TYPE_OUTLINE_RECT:
        rect(wnd->cnvs->bmp, oobj->ore->x1, oobj->ore->y1, oobj->ore->x1+oobj->ore->w_and_h, oobj->ore->y1+oobj->ore->w_and_h, oobj->ore->clr1);
      break;
      case TYPE_OUTLINE_ELIP:
        ellipse(wnd->cnvs->bmp, oobj->oe->x1, oobj->oe->y1, oobj->oe->rx, oobj->oe->ry, oobj->oe->clr1);
      break;
    }
    if(oobj->prevobject != NULL)
      oobj = oobj->prevobject;
    loop++;
  }
  blit(wnd->cnvs->bmp,bmp, 0,0, wnd->cnvs->x,wnd->cnvs->y, wnd->cnvs->w,wnd->cnvs->h);
  return 1;
}


int stick_canvas_to_window(WIND *wnd, CANVAS *cnv)
{
  wnd->cnvs = cnv;
  return 1;    
}

int mouse_over_cnv(WIND *wnd)
{
  if(mouse_x > wnd->cnvs->x+wnd->x && mouse_x < wnd->cnvs->x+wnd->cnvs->w+wnd->x && mouse_y > wnd->cnvs->y+wnd->y && mouse_y < wnd->cnvs->y+wnd->cnvs->h+wnd->y)
    return 1;
  else return 0;
}

int mouse_over_obj(OBJECT *obj, WIND *wnd)
{
  int ret = 0;
  if(obj != NULL)
  {
    switch(obj->type)
    {
      case TYPE_INLINE_QUAD:
        if(mir(obj->iq->x1+wnd->x+2, obj->iq->y1+wnd->y+20, obj->iq->x2+wnd->x+2, obj->iq->y2+wnd->y+20, 0))
          ret = 1;
      break;
      case TYPE_INLINE_CIRC:
      {
        float dist = sqrt(((mouse_x-wnd->x-2-obj->ic->x1)*(mouse_x-wnd->x-2-obj->ic->x1)) + ((mouse_y-wnd->y-20-obj->ic->y1)*(mouse_y-wnd->y-20-obj->ic->y1)));
        if((int)dist <= obj->ic->r)
          ret = 1;
      }
      break;
      case TYPE_INLINE_RECT:
        if(mir(wnd->x+2+obj->ir->x1, wnd->y+20+obj->ir->y1, wnd->x+2+obj->ir->x1 + obj->ir->w_and_h, wnd->y+20+obj->ir->y1 + obj->ir->w_and_h, 0))
        {
          ret = 1;
        }
      break;
      case TYPE_INLINE_ELIP:
      {
        float rov1 = ((float)(mouse_x-wnd->x-2-obj->ie->x1) / obj->ie->rx) * ((float)(mouse_x-wnd->x-2-obj->ie->x1) / obj->ie->rx);
        float rov2 = ((float)(obj->ie->y1-mouse_y+wnd->y+20) / obj->ie->ry) * ((float)(obj->ie->y1-mouse_y+wnd->y+20) / obj->ie->ry);
        if (rov1 + rov2 < 1.0)
          ret = 1;
      }
      break;
      case TYPE_OUTLINE_QUAD:
        if(mir(obj->oq->x1+wnd->x+2, obj->oq->y1+wnd->y+20, obj->oq->x2+wnd->x+2, obj->oq->y2+wnd->y+20,0) &&
          !mir(obj->oq->x1+wnd->x+2+1, obj->oq->y1+wnd->y+20+1, obj->oq->x2+wnd->x+2-1, obj->oq->y2+wnd->y+19,0))
          ret = 1;
      break;
      case TYPE_OUTLINE_CIRC:
      {
        float dist = sqrt(((mouse_x-wnd->x-2-obj->oc->x1)*(mouse_x-wnd->x-2-obj->oc->x1)) + ((mouse_y-wnd->y-20-obj->oc->y1)*(mouse_y-wnd->y-20-obj->oc->y1)));
        if((int)dist == obj->oc->r)
          ret = 1;
      }
      break;
      case TYPE_OUTLINE_RECT:
        if(mir(obj->ore->x1+wnd->x+2, obj->ore->y1+wnd->y+20, obj->ore->x1+wnd->x+2+obj->ore->w_and_h, obj->ore->y1+wnd->y+20+obj->ore->w_and_h,0) &&
          !mir(obj->ore->x1+wnd->x+2+1, obj->ore->y1+wnd->y+20+1, obj->ore->x1+wnd->x+2+obj->ore->w_and_h-1, obj->ore->y1+wnd->y+19+obj->ore->w_and_h,0))
          ret = 1;
      break;
      case TYPE_OUTLINE_ELIP:
      {
        float rov1 = ((float)(mouse_x-wnd->x-2-obj->oe->x1) / obj->oe->rx) * ((float)(mouse_x-wnd->x-2-obj->oe->x1) / obj->oe->rx);
        float rov2 = ((float)(obj->oe->y1-mouse_y+wnd->y+20) / obj->oe->ry) * ((float)(obj->oe->y1-mouse_y+wnd->y+20) / obj->oe->ry);
        if (rov1 + rov2 > 0.9 && rov1 + rov2 < 1.1)
          ret = 1;
      }
      break;
      default: ret = 0;
      break;
    }
  }
  return ret;
}

int manage_canvas(WIND *wnd)
{
  int tmpx, tmpy, endx, endy, tmpx2, tmpy2;
  int x, y;
  
  if(key[KEY_0_PAD]) chsnprmtv = 0;
  if(key[KEY_1_PAD]) chsnprmtv = 1;
  if(key[KEY_2_PAD]) chsnprmtv = 2;
  if(key[KEY_3_PAD]) chsnprmtv = 3;
  
  switch(mode)
  {
    case MODE_TOOL_TRANSFORM:
    {
      int loop = 0;
      OBJECT *oobj = (OBJECT*)malloc(sizeof(OBJECT));
      oobj = wnd->cnvs->obj;
      while(loop < wnd->cnvs->obj_amount)
      {
        switch(oobj->type)
        {
          case TYPE_INLINE_QUAD: //TRANSFORMOVANIE INLINE QUADU - obdlzniku
            //AK SCALUJES LAVY HORNY ROH
            if(mir(wnd->x+2+oobj->iq->x1-4, wnd->y+20+oobj->iq->y1-4, wnd->x+2+oobj->iq->x1-1, wnd->y+20+oobj->iq->y1-1, 1))
            {
              blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
              while(mouse_b & 1)
              {
                blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
                if(mouse_over_cnv(wnd)){
                  if(key[KEY_X]){ //AK JE POCAS SCALOVANIA STLACENE X
                    rectfill(mb,wnd->x+2+oobj->iq->x2,wnd->y+19+oobj->iq->y2,mouse_x,wnd->y+20+oobj->iq->y1,oobj->iq->clr1);
                    endx = mouse_x-wnd->x-2;
                    endy = oobj->iq->y1;
                  }
                  else if(key[KEY_Y]){ //AK JE POCAS SCALOVANIA STLACENE Y
                    rectfill(mb,wnd->x+2+oobj->iq->x2,wnd->y+19+oobj->iq->y2,wnd->x+2+oobj->iq->x1,mouse_y,oobj->iq->clr1);
                    endx = oobj->iq->x1;
                    endy = mouse_y-wnd->y-20;
                  }
                  else{ //AK POCAS SCALOVANIA NENI STLACENE NIC
                    rectfill(mb,wnd->x+2+oobj->iq->x2,wnd->y+19+oobj->iq->y2,mouse_x,mouse_y,oobj->iq->clr1);
                    endx = mouse_x-wnd->x-2;
                    endy = mouse_y-wnd->y-20;
                  }
                }
                line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
                line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
                blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
              }
              if(mouse_over_cnv(wnd))
              {
                if(endx < oobj->iq->x2 && endy < oobj->iq->y2){
                  oobj->iq->x1 = endx;
                  oobj->iq->y1 = endy;
                }
                if(endx >= oobj->iq->x2 && endy < oobj->iq->y2){
                  oobj->iq->x1 = oobj->iq->x2;
                  oobj->iq->y1 = endy;
                  oobj->iq->x2 = endx;
                }
                if(endx < oobj->iq->x2 && endy >= oobj->iq->y2){
                  oobj->iq->x1 = endx;
                  oobj->iq->y1 = oobj->iq->y2-1;
                  oobj->iq->y2 = endy+1;
                }
                if(endx >= oobj->iq->x2 && endy >= oobj->iq->y2){
                  oobj->iq->x1 = oobj->iq->x2;
                  oobj->iq->y1 = oobj->iq->y2-1;
                  oobj->iq->x2 = endx;
                  oobj->iq->y2 = endy+1;
                }
                wnd->cnvs->redraw = 1;
              }
            }
            
            //AK SCALUJES PRAVY HORNY ROH
            if(mir(wnd->x+2+oobj->iq->x2+1, wnd->y+20+oobj->iq->y1-4, wnd->x+2+oobj->iq->x2+4, wnd->y+20+oobj->iq->y1-1, 1))
            {
              blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
              while(mouse_b & 1)
              {
                blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
                if(mouse_over_cnv(wnd)){
                  if(key[KEY_X]){ //AK JE POCAS SCALOVANIA STLACENE X
                    rectfill(mb,wnd->x+2+oobj->iq->x1,wnd->y+19+oobj->iq->y2,mouse_x,wnd->y+20+oobj->iq->y1,oobj->iq->clr1);
                    endx = mouse_x-wnd->x-2;
                    endy = oobj->iq->y1;
                  }
                  else if(key[KEY_Y]){ //AK JE POCAS SCALOVANIA STLACENE Y
                    rectfill(mb,wnd->x+2+oobj->iq->x1,wnd->y+19+oobj->iq->y2,wnd->x+2+oobj->iq->x2,mouse_y,oobj->iq->clr1);
                    endx = oobj->iq->x2;
                    endy = mouse_y-wnd->y-20;
                  }
                  else{ //AK POCAS SCALOVANIA NENI STLACENE NIC
                    rectfill(mb,wnd->x+2+oobj->iq->x1,wnd->y+19+oobj->iq->y2,mouse_x,mouse_y,oobj->iq->clr1);
                    endx = mouse_x-wnd->x-2;
                    endy = mouse_y-wnd->y-20;
                  }
                }
                line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
                line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
                blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
              }
              if(mouse_over_cnv(wnd))
              {
                if(endx < oobj->iq->x1 && endy < oobj->iq->y2){
                  oobj->iq->x2 = oobj->iq->x1;
                  oobj->iq->x1 = endx;
                  oobj->iq->y1 = endy;
                }
                else if(endx >= oobj->iq->x1 && endy < oobj->iq->y2){
                  oobj->iq->y1 = endy;
                  oobj->iq->x2 = endx;
                }
                else if(endx < oobj->iq->x1 && endy >= oobj->iq->y2){
                  oobj->iq->x2 = oobj->iq->x1;
                  oobj->iq->x1 = endx;
                  oobj->iq->y1 = oobj->iq->y2-1;
                  oobj->iq->y2 = endy+1;
                }
                else if(endx >= oobj->iq->x1 && endy >= oobj->iq->y2){
                  oobj->iq->y1 = oobj->iq->y2-1;
                  oobj->iq->x2 = endx;
                  oobj->iq->y2 = endy+1;
                }
                wnd->cnvs->redraw = 1;
              }
            }
            
            //AK SCALUJES PRAVY DOLNY ROH
            if(mir(wnd->x+2+oobj->iq->x2+1, wnd->y+20+oobj->iq->y2+1, wnd->x+2+oobj->iq->x2+4, wnd->y+20+oobj->iq->y2+4, 1))
            {
              blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
              while(mouse_b & 1)
              {
                blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
                if(mouse_over_cnv(wnd)){
                  if(key[KEY_X]){ //AK JE POCAS SCALOVANIA STLACENE X
                    rectfill(mb,wnd->x+2+oobj->iq->x1,wnd->y+20+oobj->iq->y1,mouse_x,wnd->y+19+oobj->iq->y2,oobj->iq->clr1);
                    endx = mouse_x-wnd->x-2;
                    endy = oobj->iq->y2;
                  }
                  else if(key[KEY_Y]){ //AK JE POCAS SCALOVANIA STLACENE Y
                    rectfill(mb,wnd->x+2+oobj->iq->x1,wnd->y+19+oobj->iq->y1,wnd->x+2+oobj->iq->x2,mouse_y,oobj->iq->clr1);
                    endx = oobj->iq->x2;
                    endy = mouse_y-wnd->y-20;
                  }
                  else{ //AK POCAS SCALOVANIA NENI STLACENE NIC
                    rectfill(mb,wnd->x+2+oobj->iq->x1,wnd->y+20+oobj->iq->y1,mouse_x,mouse_y,oobj->iq->clr1);
                    endx = mouse_x-wnd->x-2;
                    endy = mouse_y-wnd->y-20;
                  }
                }
                line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
                line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
                blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
              }
              if(mouse_over_cnv(wnd))
              {
                if(endx < oobj->iq->x1 && endy < oobj->iq->y1){
                  oobj->iq->x2 = oobj->iq->x1;
                  oobj->iq->y2 = oobj->iq->y1;
                  oobj->iq->x1 = endx;
                  oobj->iq->y1 = endy;
                }
                else if(endx >= oobj->iq->x1 && endy < oobj->iq->y1){
                  oobj->iq->y2 = oobj->iq->y1;
                  oobj->iq->y1 = endy;
                  oobj->iq->x2 = endx;
                }
                else if(endx < oobj->iq->x1 && endy >= oobj->iq->y1){
                  oobj->iq->x2 = oobj->iq->x1;
                  oobj->iq->x1 = endx;
                  oobj->iq->y2 = endy+1;
                }
                else if(endx >= oobj->iq->x1 && endy >= oobj->iq->y1){
                  oobj->iq->x2 = endx;
                  oobj->iq->y2 = endy+1;
                }
                wnd->cnvs->redraw = 1;
              }
            }
            
            //AK SCALUJES LAVY DOLNY ROH
            if(mir(wnd->x+2+oobj->iq->x1-4, wnd->y+20+oobj->iq->y2+1, wnd->x+2+oobj->iq->x1-1, wnd->y+20+oobj->iq->y2+4, 1))
            {
              blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
              while(mouse_b & 1)
              {
                blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
                if(mouse_over_cnv(wnd)){
                  if(key[KEY_X]){ //AK JE POCAS SCALOVANIA STLACENE X
                    rectfill(mb,wnd->x+2+oobj->iq->x2,wnd->y+20+oobj->iq->y1,mouse_x,wnd->y+19+oobj->iq->y2,oobj->iq->clr1);
                    endx = mouse_x-wnd->x-2;
                    endy = oobj->iq->y2;
                  }
                  else if(key[KEY_Y]){ //AK JE POCAS SCALOVANIA STLACENE Y
                    rectfill(mb,wnd->x+2+oobj->iq->x1,wnd->y+20+oobj->iq->y1,wnd->x+2+oobj->iq->x2,mouse_y,oobj->iq->clr1);
                    endx = oobj->iq->x1;
                    endy = mouse_y-wnd->y-20;
                  }
                  else{ //AK POCAS SCALOVANIA NENI STLACENE NIC
                    rectfill(mb,wnd->x+2+oobj->iq->x2,wnd->y+20+oobj->iq->y1,mouse_x,mouse_y,oobj->iq->clr1);
                    endx = mouse_x-wnd->x-2;
                    endy = mouse_y-wnd->y-20;
                  }
                }
                line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
                line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
                blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
              }
              if(mouse_over_cnv(wnd))
              {
                if(endx < oobj->iq->x2 && endy < oobj->iq->y1){
                  oobj->iq->y2 = oobj->iq->y1;
                  oobj->iq->x1 = endx;
                  oobj->iq->y1 = endy;
                }
                else if(endx >= oobj->iq->x2 && endy < oobj->iq->y1){
                  oobj->iq->x1 = oobj->iq->x2;
                  oobj->iq->y2 = oobj->iq->y1;
                  oobj->iq->y1 = endy;
                  oobj->iq->x2 = endx;
                }
                else if(endx < oobj->iq->x2 && endy >= oobj->iq->y1){
                  oobj->iq->x1 = endx;
                  oobj->iq->y2 = endy+1;
                }
                else if(endx >= oobj->iq->x2 && endy >= oobj->iq->y1){
                  oobj->iq->x1 = oobj->iq->x2;
                  oobj->iq->x2 = endx;
                  oobj->iq->y2 = endy+1;
                }
                wnd->cnvs->redraw = 1;
              }
            }
            
            //if(mir(wnd->x+oobj->iq->x1-4, oobj->iq->y1-4, oobj->iq->x1-1, oobj->iq->y1-1,))
          break;
        }
        if(oobj->nextobject != NULL)
          oobj = oobj->nextobject;
        loop++;
      }
    }
    break;
    case MODE_TOOL_MOVE:
    {
      int loop = 0;
      OBJECT *oobj = (OBJECT*)malloc(sizeof(OBJECT));
      oobj = wnd->cnvs->obj;
      while(loop < wnd->cnvs->obj_amount)
      {
        if(mouse_over_obj(oobj, wnd) && mouse_b & 1)
        {
          switch(oobj->type)
          {
            case TYPE_INLINE_QUAD:
              tmpx = mouse_x - oobj->iq->x1;
              tmpy = mouse_y - oobj->iq->y1;
              tmpx2 = oobj->iq->x2 - mouse_x;
              tmpy2 = oobj->iq->y2 - mouse_y;
              while(mouse_b & 1 && mouse_over_cnv(wnd))
              {
                oobj->iq->x1 = mouse_x - tmpx;
                oobj->iq->y1 = mouse_y - tmpy;
                oobj->iq->x2 = mouse_x + tmpx2;
                oobj->iq->y2 = mouse_y + tmpy2;
                draw_canvas(wnd, wnd->bmp);
                draw_wind(wnd, mb);
                blit(mb,screen,0,0,0,0,SCREEN_W,SCREEN_H);
              }
              wnd->cnvs->redraw = 1;
            break;
            case TYPE_INLINE_CIRC:
              tmpx = mouse_x - oobj->ic->x1;
              tmpy = mouse_y - oobj->ic->y1;
              while(mouse_b & 1 && mouse_over_cnv(wnd))
              {
                oobj->ic->x1 = mouse_x - tmpx;
                oobj->ic->y1 = mouse_y - tmpy;
                draw_canvas(wnd, wnd->bmp);
                draw_wind(wnd, mb);
                blit(mb, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
              }
              wnd->cnvs->redraw = 1;
            break;
            case TYPE_INLINE_RECT:
              tmpx = mouse_x - oobj->ir->x1;
              tmpy = mouse_y - oobj->ir->y1;
              while(mouse_b & 1 && mouse_over_cnv(wnd))
              {
                oobj->ir->x1 = mouse_x - tmpx;
                oobj->ir->y1 = mouse_y - tmpy;
                draw_canvas(wnd, wnd->bmp);
                draw_wind(wnd, mb);
                blit(mb,screen,0,0,0,0,SCREEN_W,SCREEN_H);
              }
              wnd->cnvs->redraw = 1;
            break;
            case TYPE_INLINE_ELIP:
              tmpx = mouse_x - oobj->ie->x1;
              tmpy = mouse_y - oobj->ie->y1;
              while(mouse_b & 1 && mouse_over_cnv(wnd))
              {
                oobj->ie->x1 = mouse_x - tmpx;
                oobj->ie->y1 = mouse_y - tmpy;
                draw_canvas(wnd, wnd->bmp);
                draw_wind(wnd, mb);
                blit(mb, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
              }
              wnd->cnvs->redraw = 1;
            break;
            case TYPE_OUTLINE_QUAD:
              tmpx = mouse_x - oobj->oq->x1;
              tmpy = mouse_y - oobj->oq->y1;
              tmpx2 = oobj->oq->x2 - mouse_x;
              tmpy2 = oobj->oq->y2 - mouse_y;
              while(mouse_b & 1 && mouse_over_cnv(wnd))
              {
                oobj->oq->x1 = mouse_x - tmpx;
                oobj->oq->y1 = mouse_y - tmpy;
                oobj->oq->x2 = mouse_x + tmpx2;
                oobj->oq->y2 = mouse_y + tmpy2;
                draw_canvas(wnd, wnd->bmp);
                draw_wind(wnd, mb);
                blit(mb,screen,0,0,0,0,SCREEN_W,SCREEN_H);
              }
              wnd->cnvs->redraw = 1;
            break;
            case TYPE_OUTLINE_CIRC:
              tmpx = mouse_x - oobj->oc->x1;
              tmpy = mouse_y - oobj->oc->y1;
              while(mouse_b & 1 && mouse_over_cnv(wnd))
              {
                oobj->oc->x1 = mouse_x - tmpx;
                oobj->oc->y1 = mouse_y - tmpy;
                draw_canvas(wnd, wnd->bmp);
                draw_wind(wnd, mb);
                blit(mb, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
              }
              wnd->cnvs->redraw = 1;
            break;
            case TYPE_OUTLINE_RECT:
              tmpx = mouse_x - oobj->ore->x1;
              tmpy = mouse_y - oobj->ore->y1;
              while(mouse_b & 1 && mouse_over_cnv(wnd))
              {
                oobj->ore->x1 = mouse_x - tmpx;
                oobj->ore->y1 = mouse_y - tmpy;
                draw_canvas(wnd, wnd->bmp);
                draw_wind(wnd, mb);
                blit(mb,screen,0,0,0,0,SCREEN_W,SCREEN_H);
              }
              wnd->cnvs->redraw = 1;
            break;
            case TYPE_OUTLINE_ELIP:
              tmpx = mouse_x - oobj->oe->x1;
              tmpy = mouse_y - oobj->oe->y1;
              while(mouse_b & 1 && mouse_over_cnv(wnd))
              {
                oobj->oe->x1 = mouse_x - tmpx;
                oobj->oe->y1 = mouse_y - tmpy;
                draw_canvas(wnd, wnd->bmp);
                draw_wind(wnd, mb);
                blit(mb, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
              }
              wnd->cnvs->redraw = 1;
            break;
          }
          
        }
        if(oobj->nextobject != NULL)
          oobj = oobj->nextobject;
        loop++;
      }//while
    }//case
    break;
    
    case MODE_DRAW_INLINE:
      if(mouse_over_cnv(wnd) && mouse_b & 1){
        switch(chsnprmtv)
        {
          case 0: //INLINE QUAD
            blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
            tmpx = mouse_x-wnd->x-2;
            tmpy = mouse_y-wnd->y-20;
            while(mouse_b & 1)
            {
              blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
              if(mouse_over_cnv(wnd))rect(mb,tmpx+wnd->x+2,tmpy+wnd->y+20,mouse_x,mouse_y,0);
              line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
              line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
              blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);         
              endx = mouse_x-wnd->x-2;
              endy = mouse_y-wnd->y-20;
            }
            if(mouse_over_cnv(wnd))
            {
              if(tmpx < endx && tmpy < endy)
              {
                objekt = make_inline_quad(tmpx, tmpy, endx, endy, SIMPLE_COLOR, makecol(c_red, c_green, c_blue), 0, 0, 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx > endx && tmpy < endy)
              {
                objekt = make_inline_quad(endx, tmpy, tmpx, endy, SIMPLE_COLOR, makecol(c_red, c_green, c_blue), 0, 0, 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx < endx && tmpy > endy)
              {
                objekt = make_inline_quad(tmpx, endy, endx, tmpy, SIMPLE_COLOR, makecol(c_red, c_green, c_blue), 0, 0, 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx > endx && tmpy > endy)
              {
                objekt = make_inline_quad(endx, endy, tmpx, tmpy, SIMPLE_COLOR, makecol(c_red, c_green, c_blue), 0, 0, 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
            }
          break;
          case 1: //INLINE CIRC
            blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
            tmpx = mouse_x-wnd->x-2;
            tmpy = mouse_y-wnd->y-20;
            float plmr;
            show_os_cursor(MOUSE_CURSOR_NONE);
            while(mouse_b & 1)
            {
              blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
              plmr = sqrt((tmpx+wnd->x+2-mouse_x)*(tmpx+wnd->x+2-mouse_x)+(tmpy+wnd->y+20-mouse_y)*(tmpy+wnd->y+20-mouse_y));
              if(mouse_over_cnv(wnd))  circlefill(mb, tmpx+wnd->x+2, tmpy+wnd->y+20, plmr, 0);
              line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
              line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
              blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            show_os_cursor(MOUSE_CURSOR_ARROW);
            objekt = make_inline_circ(tmpx,tmpy,plmr,SIMPLE_COLOR,makecol(c_red, c_green, c_blue),0x00ffff,0,1);
            stick_object_to_canvas(wnd->cnvs,objekt);
          break;
          case 2: //INLINE RECT
            blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
            tmpx = mouse_x-wnd->x-2;
            tmpy = mouse_y-wnd->y-20;
            while(mouse_b & 1)
            {
              blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
              if(mouse_over_cnv(wnd))
              {
                if(mouse_x < wnd->x+2+tmpx && mouse_y < wnd->y+20+tmpy){
                  endx = (tmpx+2+wnd->x-mouse_x > tmpy+20+wnd->y-mouse_y) ? mouse_x : wnd->x+2+tmpx-tmpy-wnd->y-20+mouse_y;
                  endy = (tmpx+2+wnd->x-mouse_x > tmpy+20+wnd->y-mouse_y) ? wnd->y+20+tmpy-tmpx-wnd->x-2+mouse_x : mouse_y;
                  rect(mb, tmpx+wnd->x+2, tmpy+wnd->y+20, endx, endy, 0);
                }
                else if(mouse_x >= wnd->x+2+tmpx && mouse_y < wnd->y+20+tmpy){
                  endx = (mouse_x-tmpx-wnd->x-2 > tmpy+20+wnd->y-mouse_y) ? mouse_x : wnd->x+2+tmpx+wnd->y+tmpy+20-mouse_y;
                  endy = (mouse_x-tmpx-wnd->x-2 > tmpy+20+wnd->y-mouse_y) ? wnd->y+20+tmpy-mouse_x+wnd->x+tmpx+2 : mouse_y;
                  rect(mb, tmpx+wnd->x+2, tmpy+wnd->y+20, endx, endy, 0);
                }
                else if(mouse_x < wnd->x+tmpx+2 && mouse_y >= wnd->y+20+tmpy){
                  endx = (tmpx+wnd->x+2-mouse_x > mouse_y-tmpy-wnd->y-20) ? mouse_x : wnd->x+2+tmpx-mouse_y+tmpy+20+wnd->y;
                  endy = (tmpx+wnd->x+2-mouse_x > mouse_y-tmpy-wnd->y-20) ? wnd->y+20+tmpy+wnd->x+tmpx+2-mouse_x : mouse_y;
                  rect(mb, tmpx+wnd->x+2, tmpy+wnd->y+20, endx, endy, 0);
                }
                else if(mouse_x >= wnd->x+2+tmpx && mouse_y >= wnd->y+20+tmpy){
                  endx = (mouse_x-tmpx-wnd->x-2 > mouse_y-tmpy-wnd->y-20) ? mouse_x : wnd->x+tmpx+2+mouse_y-tmpy-wnd->y-20;
                  endy = (mouse_x-tmpx-wnd->x-2 > mouse_y-tmpy-wnd->y-20) ? mouse_x-tmpx-wnd->x-2+wnd->y+20+tmpy : mouse_y;
                  rect(mb, tmpx+wnd->x+2, tmpy+wnd->y+20, endx, endy, 0);
                }
              }
              line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
              line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
              blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            if(mouse_over_cnv(wnd))
            {
              if(tmpx+wnd->x+2 < endx && tmpy+wnd->y+20 < endy)
              {
                objekt = make_inline_rect(tmpx, tmpy, endx-tmpx-wnd->x-2, SIMPLE_COLOR, makecol(c_red, c_green, c_blue), 0, 0, 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx+wnd->x+2 > endx && tmpy+wnd->y+20 < endy)
              {
                objekt = make_inline_rect(endx-wnd->x-2, tmpy, tmpx+wnd->x+2-endx, SIMPLE_COLOR, makecol(c_red, c_green, c_blue), 0, 0, 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx+wnd->x+2 < endx && tmpy+wnd->y+20 > endy)
              {
                objekt = make_inline_rect(tmpx, endy-wnd->y-20, tmpy+wnd->y+20-endy, SIMPLE_COLOR, makecol(c_red, c_green, c_blue), 0, 0, 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx+wnd->x+2 > endx && tmpy+wnd->y+20 > endy)
              {
                objekt = make_inline_rect(endx-wnd->x-2, endy-20-wnd->y, tmpx+wnd->x+2-endx, SIMPLE_COLOR, makecol(c_red, c_green, c_blue), 0, 0, 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
            }
          break;
          case 3: //INLINE ELIP
            blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
            tmpx = mouse_x-wnd->x-2;
            tmpy = mouse_y-wnd->y-20;
            float plmrx, plmry;
            while(mouse_b & 1)
            {
              blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
              if(mouse_over_cnv(wnd))
              {
                plmrx = (key[KEY_LSHIFT] || key[KEY_RSHIFT]) ? abs(mouse_x-2-wnd->x-tmpx) : abs(mouse_x-2-wnd->x-tmpx)/2;
                plmry = (key[KEY_LSHIFT] || key[KEY_RSHIFT]) ? abs(mouse_y-20-wnd->y-tmpy) : abs(mouse_y-20-wnd->y-tmpy)/2;
                ellipsefill(mb, (key[KEY_LSHIFT] || key[KEY_RSHIFT]) ? 2+wnd->x+tmpx : 2+wnd->x+tmpx+((mouse_x-wnd->x-2-tmpx)/2), (key[KEY_LSHIFT] || key[KEY_RSHIFT]) ? 20+wnd->y+tmpy : 20+wnd->y+tmpy+((mouse_y-wnd->y-20-tmpy)/2), plmrx, plmry, 0x20aa20);
              }
              line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
              line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
              blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            if(mouse_over_cnv(wnd))
            {
              objekt = (key[KEY_LSHIFT] || key[KEY_RSHIFT]) ? make_inline_elip(tmpx,tmpy,plmrx,plmry,SIMPLE_COLOR,makecol(c_red, c_green, c_blue),0x20aa20,0,3) : make_inline_elip(tmpx+((mouse_x-wnd->x-2-tmpx)/2),tmpy+((mouse_y-wnd->y-20-tmpy)/2),plmrx,plmry,SIMPLE_COLOR,makecol(c_red, c_green, c_blue),0x20aa20,0,3);
              stick_object_to_canvas(wnd->cnvs,objekt);
            }
          break;
        }
        wnd->cnvs->redraw = 1;
        printf("MUHAAAAAAAAAAAAAAAA\n\n\n\n");
      }
    break;
    
    case MODE_DRAW_OUTLINE:
      if(mouse_over_cnv(wnd) && mouse_b & 1)
      {
        switch(chsnprmtv)
        {
          case 0: //OUTLINE QUAD
            blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
            tmpx = mouse_x-wnd->x-2;
            tmpy = mouse_y-wnd->y-20;
            while(mouse_b & 1)
            {
              blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
              if(mouse_over_cnv(wnd))  rect(mb,tmpx+wnd->x+2,tmpy+wnd->y+20,mouse_x,mouse_y,0);
              line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
              line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
              blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);         
              endx = mouse_x-wnd->x-2;
              endy = mouse_y-wnd->y-20;
            }
            if(mouse_over_cnv(wnd))
            {
              if(tmpx < endx && tmpy < endy)
              {
                objekt = make_outline_quad(tmpx, tmpy, endx, endy, makecol(c_red, c_green, c_blue), 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx > endx && tmpy < endy)
              {
                objekt = make_outline_quad(endx, tmpy, tmpx, endy, makecol(c_red, c_green, c_blue), 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx < endx && tmpy > endy)
              {
                objekt = make_outline_quad(tmpx, endy, endx, tmpy, makecol(c_red, c_green, c_blue), 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx > endx && tmpy > endy)
              {
                objekt = make_outline_quad(endx, endy, tmpx, tmpy, makecol(c_red, c_green, c_blue), 0);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
            }
          break;
          case 1: //OUTLINE_CIRC
           /*
            blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
            tmpx = mouse_x-wnd->x;
            tmpy = mouse_y-wnd->y-20;
            float plmr;
            show_os_cursor(MOUSE_CURSOR_NONE);
            while(mouse_b & 1)
            {
              blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
              plmr = sqrt((tmpx+wnd->x-mouse_x)*(tmpx+wnd->x-mouse_x)+(tmpy+wnd->y+20-mouse_y)*(tmpy+wnd->y+20-mouse_y));
              if(mouse_over_cnv(wnd))  circle(mb, tmpx+wnd->x, tmpy+wnd->y+20, plmr, 0);
              line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
              line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
              blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            show_os_cursor(MOUSE_CURSOR_ARROW);
            objekt = make_outline_circ(tmpx,tmpy,plmr,0,0);
            stick_object_to_canvas(wnd->cnvs,objekt);*/
            blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
            tmpx = mouse_x-wnd->x-2;
            tmpy = mouse_y-wnd->y-20;
            float plmr;
            show_os_cursor(MOUSE_CURSOR_NONE);
            while(mouse_b & 1)
            {
              blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
              plmr = sqrt((tmpx+wnd->x+2-mouse_x)*(tmpx+wnd->x+2-mouse_x)+(tmpy+wnd->y+20-mouse_y)*(tmpy+wnd->y+20-mouse_y));
              if(mouse_over_cnv(wnd))
              {
                int xx, yy;
                for(xx = x-plmr;xx < x+plmr+1;xx++)
                for(yy = y-plmr;yy < y+plmr+1;yy++)
                {
                  if(abs((x - xx) * (x - xx)) + abs((y - yy) * (y - yy)) >= plmr*plmr && 
                     abs((x - xx) * (x - xx)) + abs((y - yy) * (y - yy)) <= (plmr+1)*(plmr+1))
                  {
                    circlefill(mb,wnd->x+tmpx+2+xx,wnd->y+tmpy+20+yy,2,0x00ffff);
                  }       
                }
              }
              line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
              line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
              blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            show_os_cursor(MOUSE_CURSOR_ARROW);
            objekt = make_outline_circ(tmpx,tmpy,plmr,makecol(c_red, c_green, c_blue),0);
            stick_object_to_canvas(wnd->cnvs,objekt);
          break;
          case 2:  //OUTLINE RECT
            blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
            tmpx = mouse_x-wnd->x-2;
            tmpy = mouse_y-wnd->y-20;
            while(mouse_b & 1)
            {
              blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
              if(mouse_over_cnv(wnd))
              {
                if(mouse_x < wnd->x+2+tmpx && mouse_y < wnd->y+20+tmpy){
                  endx = (tmpx+2+wnd->x-mouse_x > tmpy+20+wnd->y-mouse_y) ? mouse_x : wnd->x+2+tmpx-tmpy-wnd->y-20+mouse_y;
                  endy = (tmpx+2+wnd->x-mouse_x > tmpy+20+wnd->y-mouse_y) ? wnd->y+20+tmpy-tmpx-wnd->x-2+mouse_x : mouse_y;
                  rect(mb, tmpx+wnd->x+2, tmpy+wnd->y+20, endx, endy, 0);
                }
                else if(mouse_x >= wnd->x+2+tmpx && mouse_y < wnd->y+20+tmpy){
                  endx = (mouse_x-tmpx-wnd->x-2 > tmpy+20+wnd->y-mouse_y) ? mouse_x : wnd->x+2+tmpx+wnd->y+tmpy+20-mouse_y;
                  endy = (mouse_x-tmpx-wnd->x-2 > tmpy+20+wnd->y-mouse_y) ? wnd->y+20+tmpy-mouse_x+wnd->x+tmpx+2 : mouse_y;
                  rect(mb, tmpx+wnd->x+2, tmpy+wnd->y+20, endx, endy, 0);
                }
                else if(mouse_x < wnd->x+2+tmpx && mouse_y >= wnd->y+20+tmpy){
                  endx = (tmpx+2+wnd->x-mouse_x > mouse_y-tmpy-wnd->y-20) ? mouse_x : wnd->x+2+tmpx-mouse_y+tmpy+20+wnd->y;
                  endy = (tmpx+2+wnd->x-mouse_x > mouse_y-tmpy-wnd->y-20) ? wnd->y+20+tmpy+wnd->x+tmpx+2-mouse_x : mouse_y;
                  rect(mb, tmpx+wnd->x+2, tmpy+wnd->y+20, endx, endy, 0);
                }
                else if(mouse_x >= wnd->x+2+tmpx && mouse_y >= wnd->y+20+tmpy){
                  endx = (mouse_x-tmpx-wnd->x-2 > mouse_y-tmpy-wnd->y-20) ? mouse_x : wnd->x+2+tmpx+mouse_y-tmpy-wnd->y-20;
                  endy = (mouse_x-tmpx-wnd->x-2 > mouse_y-tmpy-wnd->y-20) ? mouse_x-2-tmpx-wnd->x+wnd->y+20+tmpy : mouse_y;
                  rect(mb, tmpx+wnd->x+2, tmpy+wnd->y+20, endx, endy, 0);
                }
              }
              line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
              line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
              blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            if(mouse_over_cnv(wnd))
            {
              if(tmpx+wnd->x+2 < endx && tmpy+wnd->y+20 < endy)
              {
                objekt = make_outline_rect(tmpx, tmpy, endx-tmpx-wnd->x-2, makecol(c_red, c_green, c_blue), 1);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx+wnd->x+2 > endx && tmpy+wnd->y+20 < endy)
              {
                objekt = make_outline_rect(endx-wnd->x-2, tmpy, tmpx+wnd->x+2-endx, makecol(c_red, c_green, c_blue), 1);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx+wnd->x+2 < endx && tmpy+wnd->y+20 > endy)
              {
                objekt = make_outline_rect(tmpx, endy-wnd->y-20, tmpy+wnd->y+20-endy, makecol(c_red, c_green, c_blue), 1);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
              if(tmpx+wnd->x+2 > endx && tmpy+wnd->y+20 > endy)
              {
                objekt = make_outline_rect(endx-wnd->x-2, endy-20-wnd->y, tmpx+2+wnd->x-endx, makecol(c_red, c_green, c_blue), 1);
                stick_object_to_canvas(wnd->cnvs,objekt);        
              }
            }
          break;
          case 3: //OUTLINE ELIP
            /*blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
            tmpx = mouse_x-wnd->x;
            tmpy = mouse_y-wnd->y-20;
            float plmrx, plmry;
            while(mouse_b & 1)
            {
              blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
              if(mouse_over_cnv(wnd))
              {
                plmrx = abs(tmpx-mouse_x+wnd->x);
                plmry = abs(tmpy-mouse_y+20+wnd->y);
                ellipse(mb, wnd->x+tmpx, 20+wnd->y+tmpy, plmrx, plmry, 0x20aa20);
              }
              line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
              line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
              blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            if(mouse_over_cnv(wnd))
            {
              objekt = make_outline_elip(tmpx,tmpy,plmrx,plmry,0x20aa20,3);
              stick_object_to_canvas(wnd->cnvs,objekt);
            }*/
            blit(screen,tmpbmp,0,0,0,0,SCREEN_W, SCREEN_H);
            tmpx = mouse_x-wnd->x-2;
            tmpy = mouse_y-wnd->y-20;
            float plmrx, plmry;
            while(mouse_b & 1)
            {
              blit(tmpbmp,mb,0,0,0,0,SCREEN_W, SCREEN_H);
              if(mouse_over_cnv(wnd))
              {
                plmrx = (key[KEY_LSHIFT] || key[KEY_RSHIFT]) ? abs(mouse_x-2-wnd->x-tmpx) : abs(mouse_x-2-wnd->x-tmpx)/2;
                plmry = (key[KEY_LSHIFT] || key[KEY_RSHIFT]) ? abs(mouse_y-20-wnd->y-tmpy) : abs(mouse_y-20-wnd->y-tmpy)/2;
                ellipse(mb, (key[KEY_LSHIFT] || key[KEY_RSHIFT]) ? wnd->x+tmpx+2 : wnd->x+tmpx+2+((mouse_x-wnd->x-2-tmpx)/2), (key[KEY_LSHIFT] || key[KEY_RSHIFT]) ? 20+wnd->y+tmpy : 20+wnd->y+tmpy+((mouse_y-wnd->y-20-tmpy)/2), plmrx, plmry, 0x20aa20);
              }
              line(mb, mouse_x - 10, mouse_y, mouse_x + 10, mouse_y, 0xff00ff);
              line(mb, mouse_x, mouse_y - 10, mouse_x, mouse_y + 10, 0xff00ff);
              blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            if(mouse_over_cnv(wnd))
            {
              objekt = (key[KEY_LSHIFT] || key[KEY_RSHIFT]) ? make_outline_elip(tmpx,tmpy,plmrx,plmry,makecol(c_red, c_green, c_blue),3) : make_outline_elip(tmpx+((mouse_x-wnd->x-2-tmpx)/2),tmpy+((mouse_y-wnd->y-20-tmpy)/2),plmrx,plmry,makecol(c_red, c_green, c_blue),3);
              stick_object_to_canvas(wnd->cnvs,objekt);
            }
          break;
        }
        wnd->cnvs->redraw = 1;
      }
    break;
  }
}

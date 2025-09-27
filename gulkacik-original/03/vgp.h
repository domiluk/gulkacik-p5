#include "engine.h"

/*int save_vgp(char *filename, WIND *wnd)
{
 FILE *vgp;
 vgp = fopen(filename, "w");
 if(vgp == NULL)printf("cannot create file");
 int loop = 0;
 OBJECT *oobj = (OBJECT*)malloc(sizeof(OBJECT));
 
 oobj = wnd->cnvs->obj;
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
    if(oobj->nextobject != NULL)
       oobj = oobj->nextobject;
    loop++;
    printf("%d",loop);
  }
  fclose(vgp);
 return 1;    
}
*/
/*int gggg;
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
}*/

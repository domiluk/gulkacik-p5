OBJECT *make_curve(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int stroke, int clr1, int clr2)
{
 OBJECT *obj;
 obj = (OBJECT*)malloc(sizeof(OBJECT)); 			 
 
 obj->type = TYPE_CURVE;
 obj->cr = (CURVE*)malloc(sizeof(CURVE));
 
 obj->cr->x1 = x1;
  obj->cr->x2 = x2;
   obj->cr->x3 = x3;
    obj->cr->x4 = x4;
 
 obj->cr->y1 = y1;
  obj->cr->y2 = y2;
   obj->cr->y3 = y3;
    obj->cr->y4 = y4;
 
 obj->cr->stroke = stroke;
 obj->cr->clr1 = clr1;
 obj->cr->clr2 = clr2;
 
 return obj; 			 
}

int manage_curve(WIND *wnd, BITMAP *bmp, OBJECT *obj)
{
 		
 return 1; 		
}

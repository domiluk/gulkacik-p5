OBJECT *make_line(int x1, int y1, int x2, int y2, int clr1, int clr2, int stroke)
{
 OBJECT *obj;
 obj = (OBJECT*)malloc(sizeof(OBJECT)); 			 
 
 obj->type = TYPE_LINE;
 obj->ln = (LINE*)malloc(sizeof(LINE));
 
 obj->x1 = x1;
 obj->y1 = y1;
 obj->x2 = x2;
 obj->y2 = y2;
 
 obj->clr1 = clr1;
 obj->clr2 = clr2;
 
 obj->stroke = stroke;
 
 return obj;
}


int manage_line(WIND *wnd, BITMAP *bmp, OBJECT *obj)
{
 		
 return 1; 		
}

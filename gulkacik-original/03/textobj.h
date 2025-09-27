OBJECT *make_text(int x, int y, char *path, int fh, char *text, int clr)
{
 int w;
 
 OBJECT *obj;
 obj = (OBJECT*)malloc(sizeof(OBJECT)); 			 
 
 obj->type = TYPE_TEXT;
 obj->tx = (TEXT*)malloc(sizeof(TEXT)); 			 
 
 obj->tx->x1 = x;
 obj->tx->y1 = y;
 obj->tx->clr = clr;
 obj->tx->text = text;
 obj->tx->fh = fh;
 
 obj->tx->font = alfont_load_font(path);
 alfont_set_font_size(obj->tx->font, fh);
 
 w = alfont_text_length(obj->tx->font);
 
 obj->tx->bmp = create_bitmap(w, fh);
 clear_to_color(obj->tx->bmp, clr ^ 0xffffff);
 alfont_textprintf(obj->tx->bmp, obj->tx->font, 0, 0, clr, "%s", text);
 
 
 return obj;
}

int clicked_on_text(OBJECT *obj)
{
 if(getpixel(obj->tx->bmp, mouse_x - obj->tx->x, mouse_y - obj->tx->y) == obj->tx->clr && mouse_b & 1)
 return 1;
 else return 0; 		
}

int manage_text(OBJECT *obj)
{
 int dx = 0, dy = 0;
 //if clicked on text
 //while mouse_b & 1
 //draw everything exept old text
 //draw new text
 //text->x += dx;
 //text->y += dy;
 //get_mouse_mickeys(&dx, &dy);
 //end of while 		
 
 return 1;
}

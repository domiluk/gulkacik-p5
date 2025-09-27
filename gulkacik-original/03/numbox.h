//#define 

NUMBOX *init_numbox(float value, int is_float, float step, int up_max, int down_max)
{
 NUMBOX *nb;
 nb = (NUMBOX*)malloc(sizeof(NUMBOX));
 nb->value = value;
 nb->is_float = is_float;
 nb->step = step;
 nb->up_max = up_max;
 nb->down_max = down_max;
 nb->additive_step = 0.0;
 
 return nb;			 
}

int draw_numbox(BITMAP *bmp, NUMBOX *nb, int x, int y, int w, int h)
{
 alfont_set_font_size(larabie, 17);
 rectfill(bmp, x, y, x+w, y+h, 0x444444);
 //rect(bmp, x-1-(w/4), y-1, x+w+1+(w/4), y+h+1,0);
 rectfill(bmp, x, y, x-15, y + h,0x222222);
 draw_sprite(bmp, gradleft, x, y);
 draw_sprite(bmp, gradright, x+w-20, y);
 rectfill(bmp, x+w, y, x+w+(15), y+h,0x222222);
 
 if(nb->is_float == 1) alfont_textprintf_centre_aa(bmp, larabie, x+(w/2), y, 0xffffff, "%2.2f", nb->value);
 else  alfont_textprintf_centre_aa(bmp, larabie, x+(w/2), y, 0xffffff, "%2.0f", nb->value);
 
 
 if(mir(x+w, y, x+w+(15), y+h,0)) 
 {
  if(mouse_b & 1 && nb->value < nb->up_max)
  {
   alfont_textprintf_centre_aa(bmp, larabie, x+w+(7)+1, y+1-1, 0xff9600, ">");						
   nb->value += nb->step;
   nb->additive_step+=0.2;
   nb->value += nb->additive_step;
   rest(50);
	}
	else 
	{
	 alfont_textprintf_centre_aa(bmp, larabie, x+w+(7), y-1, 0xff9600, ">");						 
   nb->additive_step = 0.0;
	}
 }
 else alfont_textprintf_centre_aa(bmp, larabie, x+w+(7), y-1, 0xffffff, ">");

 //LEFT ONE
 if(mir(x-(w/4), y, x, y+h,0)) 
 {
  if(mouse_b & 1 && nb->value > nb->down_max)
  {
   alfont_textprintf_centre_aa(bmp, larabie, x-(7)+1-1, y+1-1, 0xff9600, "<");						
   nb->value -= nb->step;
   nb->additive_step+=0.2;
   nb->value -= nb->additive_step;
   rest(50);
	}
	else 
	{
	 alfont_textprintf_centre_aa(bmp, larabie, x-(7)-1, y-1, 0xff9600, "<");						 
   nb->additive_step = 0.0;
	}
 }
 else alfont_textprintf_centre_aa(bmp, larabie, x-(7)-1, y-1, 0xffffff, "<");


if(nb->value > nb->up_max)nb->value = nb->up_max;
if(nb->value < nb->down_max)nb->value = nb->down_max;

return 1;  		
}

//Quick Bar for Vectoria

bool draw_qbar(BITMAP *bmp)
{
 rectfill(bmp,0,20,SCREEN_W,50,makecol(60,60,60));
 alfont_textprintf_aa(bmp,larabie,5,28,0xffffff,"Q-Bar"); 
//set_texture "butty"
 if(qb_set_texture)
 {
  if(fill_mode == MODE_FILL_SIMPLE)
  {
   rect(bmp,60,25,100,48,0);
   rectfill(bmp,61,26,99,47,makecol(c_red,c_green,c_blue));             
  }                 
  
  
  if(mir(60,26,100,47,1))set_visibility(set_texture_wnd,true);
  if(mir(60,26,100,47,0))wwd = 8;
 }
 
 if(qb_border)
 {
  alfont_textprintf_centre_aa(bmp, larabie, 170, 20, 0xffffff, "Border");
  alfont_set_font_size(larabie, 17);
	draw_numbox(bmp, bordernb, 150,34,40,15);
 }
 
 if(qb_angle)
 {
  alfont_textprintf_centre_aa(bmp, larabie, 170, 20, 0xffffff, "Angle");
  alfont_set_font_size(larabie, 17);
	draw_numbox(bmp, anglenb, 150,34,40,15);	 					 
 }
    
}

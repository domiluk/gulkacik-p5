//tu budu actions co sa ma stat po kliknuti na tlacitka toolbaru, a este vykreslovanie
//a podobne veci...


#include "engine.h"
//#include "ststuff.h"

WIND *toolbar_wnd;
BITMAP *mov_ico, *inline_ico, *outline_ico, *transform_ico, *brush_ico, *spray_ico, *las_ico;
BUTTON *inlinebtn, *movebtn, *textbtn, *outlinebtn, *transformbtn, *brushbtn, *spraybtn, *lasbtn;
//actions
void text_button_action()
{
  set_visibility(insert_text_wnd, 1);  
  mode = MODE_DRAW_TEXT;
  insert_text_wnd->active = true; 
  textbtn->switch_on = 1;
  
  movebtn->switch_on = 0;
  inlinebtn->switch_on = 0;
  outlinebtn->switch_on = 0;
  transformbtn->switch_on = 0;
  brushbtn->switch_on = 0;
  spraybtn->switch_on = 0;
  lasbtn->switch_on = 0;
  
  qb_set_texture = true;
}

void inline_button_action()
{
  mode = MODE_DRAW_INLINE;
  type_wnd->visible = 1;
  
  inlinebtn->switch_on = 1;
  
  movebtn->switch_on = 0;
  textbtn->switch_on = 0;
  outlinebtn->switch_on = 0;
  transformbtn->switch_on = 0;
  brushbtn->switch_on = 0;
  spraybtn->switch_on = 0;
  lasbtn->switch_on = 0;
  
  qb_set_texture = true;
  qb_border = true;
}

void outline_button_action()
{
  mode = MODE_DRAW_OUTLINE;
  outlinebtn->switch_on = 1;
  
  movebtn->switch_on = 0;
  textbtn->switch_on = 0;
  inlinebtn->switch_on = 0;
  transformbtn->switch_on = 0;
  brushbtn->switch_on = 0;
  spraybtn->switch_on = 0;
  lasbtn->switch_on = 0;
  
  qb_set_texture = true;
  qb_border = true;
}

void move_button_action()
{
  mode = MODE_TOOL_MOVE;
  movebtn->switch_on = 1;
  
  inlinebtn->switch_on = 0;
  textbtn->switch_on = 0;
  outlinebtn->switch_on = 0;
  transformbtn->switch_on = 0;
  brushbtn->switch_on = 0;
  spraybtn->switch_on = 0;
  lasbtn->switch_on = 0;
  window->cnvs->redraw = 1;
  
  qb_set_texture = true;
  qb_angle = false;
  qb_border = true;
}

void transform_button_action()
{
  mode = MODE_TOOL_TRANSFORM;
  qb_angle = true;
  qb_border = false;
  qb_set_texture = false;
  transformbtn->switch_on = 1;
  
  inlinebtn->switch_on = 0;
  textbtn->switch_on = 0;
  outlinebtn->switch_on = 0;
  movebtn->switch_on = 0;
  brushbtn->switch_on = 0;
  spraybtn->switch_on = 0;
  lasbtn->switch_on = 0;
  window->cnvs->redraw = 1;
}

void brush_button_action()
{
  mode = MODE_DRAW_BRUSH;
  brushbtn->switch_on = 1;
  
  inlinebtn->switch_on = 0;
  textbtn->switch_on = 0;
  outlinebtn->switch_on = 0;
  movebtn->switch_on = 0;
  transformbtn->switch_on = 0;
  spraybtn->switch_on = 0;
  lasbtn->switch_on = 0;
}

void spray_button_action() //GET COLOR TOOL
{
  mode = MODE_TOOL_GETCOLOR;
  spraybtn->switch_on = 1;
  
  lasbtn->switch_on = 0;
  inlinebtn->switch_on = 0;
  textbtn->switch_on = 0;
  outlinebtn->switch_on = 0;
  movebtn->switch_on = 0;
  transformbtn->switch_on = 0;
  brushbtn->switch_on = 0;
  
  qb_set_texture = true;
  qb_border = false;
}

void las_button_action()
{
  mode = MODE_DRAW_LAS;
  lasbtn->switch_on = 1;
  
  inlinebtn->switch_on = 0;
  textbtn->switch_on = 0;
  outlinebtn->switch_on = 0;
  movebtn->switch_on = 0;
  transformbtn->switch_on = 0;
  brushbtn->switch_on = 0;
  spraybtn->switch_on = 0;
  
  qb_set_texture = true;
}

//funkcia na zinicializovanie toolbaru
int make_toolbar()
{
  toolbar_wnd = make_wind(0,50,52,300,"Tools",true,false,false);
  rectfill(toolbar_wnd->bmp,1,20,51,95+24,0);
  toolbar_wnd->active = true;

  
  mov_ico = load_bitmap("mov_ico.bmp",NULL);
  inline_ico = load_bitmap("inline_ico.bmp",NULL);
  outline_ico = load_bitmap("outline_ico.bmp",NULL);
  transform_ico = load_bitmap("transform_ico.bmp",NULL);
  brush_ico = load_bitmap("brush_ico.bmp",NULL);
  spray_ico = load_bitmap("spray_ico.bmp",NULL);
  las_ico = load_bitmap("las_ico.bmp",NULL);
  
  //line and arc's butty
  lasbtn = init_button(1,95,24,24," ",13,  las_ico,0,0);
  set_button_action(lasbtn,las_button_action);
  stick_button_to_window(toolbar_wnd,lasbtn);
  
  //spray's butty
  spraybtn = init_button(26,70,24,24," ",13,  spray_ico,0,0);
  set_button_action(  spraybtn,spray_button_action);
  stick_button_to_window(toolbar_wnd,spraybtn);
  
  //brush's butty  
  brushbtn = init_button(1,70,24,24," ",13,  brush_ico,0,0);
  set_button_action(  brushbtn,brush_button_action);
  stick_button_to_window(toolbar_wnd,brushbtn);

  //insert text's butty
  textbtn = init_button(25,95,24,24,"T",25,NULL,0,0);
  set_button_action(textbtn,text_button_action);
  stick_button_to_window(toolbar_wnd,textbtn);
  
  //inline obj's butty
  inlinebtn = init_button(1,45,24,24," ",15,inline_ico,0,0);
  set_button_action(inlinebtn,inline_button_action);
  stick_button_to_window(toolbar_wnd,inlinebtn);
  
  //outline obj's butty
  outlinebtn = init_button(25,45,24,24," ",13,outline_ico,0,0);
  set_button_action(outlinebtn,outline_button_action);
  stick_button_to_window(toolbar_wnd,outlinebtn);
  
  //transform tool's butty
  transformbtn = init_button(26,20,24,24," ",13,  transform_ico,0,0);
  set_button_action(transformbtn,transform_button_action);
  stick_button_to_window(toolbar_wnd,transformbtn);
  
  //move tool's butty
  movebtn = init_button(1,20,24,24," ",25,mov_ico,0,1);//set as default switched
  set_button_action(movebtn,move_button_action);
  stick_button_to_window(toolbar_wnd,movebtn);
  
  return 1;
}



int draw_toolbar(BITMAP *bmp)
{
  draw_wind(toolbar_wnd,bmp); 
  draw_buttons(toolbar_wnd, bmp); 
  //draw_desc(bmp); 
  //draw_sprite(bmp,toolbar_btn->bmp,200,200); 
}

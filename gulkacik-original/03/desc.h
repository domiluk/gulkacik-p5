#include "engine.h"


char desc[9][80] = {"Tool for moving objects on the canvas","Tool for scaling, rotating and other transformations","Enables to draw filled 2d primitives to the canvas","Enables to draw borders of 2d primitives to the canvas","Enables to draw-by-hand technique with chosen stroke texture","Niggaz & Grafitti - ya bra'","Tool for drawing curves and lines","Tool for inserting text into the canvas", "Choose color of active object"};

int draw_desc(BITMAP *bmp)
{
  alfont_set_font_size(larabie, 15);
  if(wwd>=0)alfont_textprintf(bmp, larabie, 20, SCREEN_H-17, 0xffffff, "%s", desc[wwd]);
  if(!mir(0,70, 49,70+24*4, 0)) wwd = -1;
  if(mir(0,70, 24,94, 0)) wwd = 0;
  if(mir(25,70,49,94 ,0)) wwd = 1;
  if(mir(0,95, 24,118,0)) wwd = 2;
  if(mir(25,95, 49,118,0)) wwd = 3;
  if(mir(0,119, 24,119+24,0)) wwd = 4;
  if(mir(25,119, 49,119+24,0)) wwd = 5;
  if(mir(0,119+25, 24,119+48,0)) wwd = 6;
  if(mir(25,119+25, 49,119+48,0)) wwd = 7;
  
  return 1;
}

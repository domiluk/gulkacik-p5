/************
ludzia sadnite si rovno, rovno a rovno, 
a budete jest ho a ho...
hovedziu polievku z dreveneho taneriku,
hovedziu polievku z dreveneho taneriku!

stara baba krici, krici a krici
ze jej tecie z pi a pi...
pitvora do dvora, bystra voda studena,
pitvora do dvora, bystra voda studena!

pod mostom sme stali, stali a stali
ludia na nas sra, a sra...
sradostcou cakali, dockat sa nas nemohli,
sradostcou cakali, dockat sa nas nemohli!

vrestauraci bula, bula bula, 
sedi stara ku a ku...
kucharka v kuchzni, natahuje hodiny,
kucharka v kuchzni, natahuje hodiny!

otec robi dvere, dvere a dvere
simultanne se, a se...
sekerku podava, robi sa ze pomaha,
sekerku podava, robi sa ze pomaha!

ked som isiel rovno, rovno a rovno
stupil som na ho a ho...
hokejku drevenu, v surovej vyrobenu,
hokejku drevenu, v surovej vyrobenu!

strielal som raz z kuse, kuse a kuse, 
trafil som do pu, a pu
pupavy zelenej.......................todo
**************/

//DEFINES
#define MODE_DRAW_INLINE 1
#define MODE_DRAW_OUTLINE 2
#define MODE_DRAW_TEXT 3
#define MODE_DRAW_BRUSH 4
#define MODE_DRAW_SPRAY 5
#define MODE_DRAW_LAS 6
#define MODE_TOOL_MOVE 7
#define MODE_TOOL_TRANSFORM 8
#define MODE_TOOL_GETCOLOR 9

//for _object->type
#define TYPE_INLINE_QUAD 0
#define TYPE_OUTLINE_QUAD 10

#define TYPE_INLINE_RECT 1
#define TYPE_OUTLINE_RECT 11

#define TYPE_INLINE_CIRC 2
#define TYPE_OUTLINE_CIRC 12

#define TYPE_INLINE_ELIP 3
#define TYPE_OUTLINE_ELIP 13

#define TYPE_LINE 4
#define TYPE_SPLINE 5

#define TYPE_TEXT 6

#define TYPE_BRUSH 7
#define TYPE_SPRAY 8

#define TYPE_NGON 9

#define MODE_FILL_SIMPLE 1
#define MODE_FILL_GRADIENT 2
#define MODE_FILL_PICTURE 3
#define SIMPLE_COLOR 1
#define GRADIENT_COLOR 2


//INCLUDES
#pragma once

#include <allegro.h>
#include <alfont.h>
#include <algif.h>
#include <alpng.h>
#include <jpgalleg.h>
#include <winalleg.h>
#include <string.h>
#include <stdio.h>
#include <io.h>
//#include <ttfinfo.h>
//#include <io.h>


//TYPES


typedef struct _qm
{
 int value;
 int flip;
 int x;
 int y;
 int done;
 //struct _qm *next;       
}QM;

typedef struct _tel
{
 int value, x, y;        
}TEL;

typedef struct _level
{
 int w, h;
 int info[100][100];
 int qma;
 int tela;
 int la;
 float bx, by;
 QM qm[100];
 TEL tel[3];
 BITMAP *bmp;
 BITMAP *alpha;
 char name[512];        
}LEVEL;

typedef struct _numbox {
 float value;
 int is_float;
 float step;
 int up_max;
 int down_max;
 float additive_step;
}NUMBOX;

typedef struct _combo_unit {

char *text;
int value;
}CB_UNIT;

typedef struct _combo_list {
        
 CB_UNIT *units[25];
 BITMAP *grad;
 
 int cpoio;
 int cpoi;
 int rolled;
 int slidebar;
 
 int x, y;

}CB_LIST;

typedef struct _textbox
{
int x, y;
int w, h;
int fy;
int achar;
int active;
int amtchar;
int multiline;
int maxchar;
float blick;
BITMAP *bmp;
char text[512];        
}TEXTBOX;

typedef struct _dirr
{
 char name[19];//16 + 3 bodky
 char real_name[50];
 int attrib;
 int longer;        
}DIRR;

typedef struct _flee
{
 char name[19];//16 + 3 bodky    
 char real_name[50];
 int longer;   
}FLEE;

typedef struct _filebrowser
{
 int x, y;
 int nofiles;
 int refresh;
 int fyf; //from y files
 int fyd; //from y dirs       
 char path[512];
 int nod, nof;
 DIRR dir[100];
 FLEE fle[400];
 TEXTBOX *tbox;
 CB_LIST *cblst;
}FILEBROWSER;

typedef struct _nunit {

char path[75];
char name[75];        
}N_UNIT;

typedef struct _ninja_list {

N_UNIT *units[1000];
int cpoi;
int cpoio;
int rolled;
int slidebar;
BITMAP *grad;

int x, y;       
}N_LIST;


typedef struct _unit_menu_handler
{
 char *text;
 void (*proc)();
 char shortcut; 		
}UMH;

typedef struct _cell_menu_handler
{
 char *text;
 void (*proc)();
 char shortcut;
 char mshortcut;
 int noumh;
 UMH *umh[10];
 int rolled;
 int rollable;
 int au; 	
 int slx, elx;	
}CMH;

typedef struct _sub_menu_handler
{
 char *text;
 int nocmh;
 char shortcut;
 int x, w;
 int rolled;
 int ac;
 int ord;
 int slx, elx;
 CMH *cmh[10];		
}SMH;

typedef struct _main_menu_handler
{
 int nosmh;
 int as;
 SMH *smh[5];		
 BITMAP	*grad;
}MMH;


typedef struct _inline_quad {
  
  int x1, x2;
  int y1, y2;
  
  int fill_type;
  
  int clr1, clr2;
  
  int border_clr;
  int border_width;
}INLINE_QUAD;

typedef struct _inline_rect {
  
  int x1, y1;
  int w_and_h;
  
  int fill_type;
  
  int clr1, clr2;
  
  int border_clr;
  int border_width;        
}INLINE_RECT;

typedef struct _inline_circ {
  
  int x1, y1;
  int r;
  
  int fill_type;
  
  int clr1, clr2;
  
  int border_clr;
  int border_width;        
}INLINE_CIRC;

typedef struct _inline_elip {
  
  int x1, y1;
  int rx, ry;
  
  int fill_type;
  
  int clr1, clr2;
  
  int border_clr;
  int border_width;        
}INLINE_ELIP;

//OUTLINEZZZZZZZZZZZZZZZZZZZZZ

typedef struct _outline_quad {
  
  int x1, x2;
  int y1, y2;
  
  int clr1;
  
  int stroke;      
}OUTLINE_QUAD;

typedef struct _outline_rect {
  
  int x1, y1;
  int w_and_h;
  
  int clr1;
  
  int stroke;       
}OUTLINE_RECT;

typedef struct _outline_circ {
  
  int x1, y1;
  int r;
  
  int clr1;
  
  int stroke;       
}OUTLINE_CIRC;

typedef struct _outline_elip {
  
  int x1, y1;
  int rx, ry;
  
  int clr1;
  
  int stroke;
}OUTLINE_ELIP;

typedef struct _text {
          
  char *text;
  ALFONT_FONT *font;
  int fh;
  int clr;
  int x1, y1;
  BITMAP *bmp;
}TEXT;

typedef struct _line {
          
  int x1;
  int x2;
  int y1;
  int y2;
  int stroke;
  int clr1;
  int clr2;
}LINE;

typedef struct _curve {
				
  int x1, x2, x3, x4;
  int y1, y2, y3, y4;
  
  int stroke;
  int clr1;
  int clr2;
}CURVE;

typedef struct _object {
  int type;
//  void *rt;
  INLINE_QUAD *iq;
  INLINE_CIRC *ic;
  INLINE_RECT *ir;
  INLINE_ELIP *ie;
  OUTLINE_QUAD *oq;
  OUTLINE_CIRC *oc;
  OUTLINE_RECT *ore;
  OUTLINE_ELIP *oe;
  LINE *ln;
  struct _object *prevobject;
  struct _object *nextobject;
}OBJECT;

//other
typedef struct _canvas
{
  BITMAP *bmp; //bitmapa neskor aj pozadia
  int x, y, w, h; //lalala, basic info
  OBJECT *obj; //no a platno ma v sebe zoznam objektov
  OBJECT *lastobj;//no a platno ma v sebe zoznam objektov odzadu
  int obj_amount;        
  int redraw;
}CANVAS;



typedef struct _button {
  void (*proc)(); //odkaz na funkciu ktora sa vykona pri kliknuti
  int x, y, w, h; //pos + sirka a vyska
  char *text;     //caption
  int font_height;//velkost fontu
  int light_on;   //ci je ten gradient efekt okolo neho
  int switch_on;  //ci po stlaceni zostane zakliknuty
  BITMAP *bmp;    //pripadna bitmapa
  float light;    //to pre ten pripadny efekt gradientu, je to vlastne vzdialenost 
  float re,bl,gr; //to pre ten gradient ;)
  int visible;    //viditelnost buttyho
  struct _button *nextbutton; //dalsi butty
}BUTTON;



typedef struct _wind{
  int x,y,w,h;              //rosemary + pos
  char *title;              //title
  BITMAP *bmp;              //bitmapa celeho okna
  bool visible;             //ci je visible
  bool active;
  bool canexit;
  bool canmove;
    
  //sem dalej patria vsakovake gui objekty
  BUTTON* btns; //tlacitk(o/a)
  int btn_amount;
  
  CANVAS* cnvs; //kresliace platno
}WIND;

//DECL of WINDS
WIND *insert_text_wnd;
WIND *set_texture_wnd;
WIND *credits_wnd;
WIND *type_wnd;
     BUTTON *rbtn, *sbtn, *ebtn, *cbtn;
WIND *save_as_wnd;
WIND *open_wnd;
WIND *new_wnd;
WIND *new_hlaska;


//VARIABLES
BITMAP *arrup, *arrdown, *arrback, *newdir;
BITMAP *mb, *tmpbmp, *trix, *triy;
BITMAP *gradleft, *gradright;
WIND *window, *windowzwei, *windowdrei;
CANVAS *platno;
OBJECT *objekt;
BUTTON *tlacitko;
FILEBROWSER *fbsave, *fbopen;
CB_LIST *listt, *formatt, *formatto;
CB_UNIT *unitt, *unitto;
N_LIST *nnlist;
NUMBOX *ww, *hhh, *bordernb, *anglenb;
MMH *menu;
SMH *upcell, *upcell2, *upcell3, *upcell4, *upcell45, *upcell5;
BITMAP *teleport;
CMH *cell;
UMH *unit;
BITMAP *laser, *laser2;
BITMAP *arrow[4];
BITMAP *kocka_cista;
bool have_level = false;
BITMAP *teleportend;
BITMAP *diebrick;
TEXTBOX *ittbox, *fnametbox, *fnametboxo, *project_name;
WIND *fm_wnd;
BUTTON *GTYPE;
BITMAP *hb;
BITMAP *normal_brick[13], *water_field[5], *qm[4], *symbol_brick[50], *bg, *gulkacik, *trava[5];
LEVEL *lvl;
int camx = 0, camy = 0;
BITMAP *up, *upa;
int ldm = 0, xxsur, yysur, generated = 0;

ALFONT_FONT *larabie;
bool changed = true;
volatile int close_button_pressed = FALSE;
int activemenu = -1;
int mode = 1;
int chsnprmtv = 0;
int rectogon[8];
int fill_mode = 1;
float gcx = 0.0;
int gv = 1;
int xx;
float c;
int symbol_amount[5] = {0, 0, 0, 0, 0};

BITMAP *qgrad;
int getpixledr, getpixledg, getpixledb;
int getpx,getpy;
float r, g, b;
float rr = 74, gg = 185, bb = 52;
float rs, gs, bs;
//int trix, triy;


//qbar
bool qb_set_texture = false;
bool qb_font_size = false;
bool qb_set_font = false;
bool qb_scale = false;
bool qb_rotate = false;
bool qb_border = true;
bool qb_angle = false;

int c_red = 74;
int c_green = 185;
int c_blue = 52;

int c_red2 = 145;
int c_green2 = 82;
int c_blue2 = 22;

BITMAP *picture_fill;



int wwd = -1;

BITMAP *wwum; //What Was Under Menulist

//FUNCTIONS
int invert_rect(BITMAP *dest, int x1, int y1, int x2, int y2, char *bitch)
{
  int clr,r,g,b;
  int nclr,nr,ng,nb;
  int x,y;
  
  for(y = y1; y <= y2; y++)
  for(x = x1; x <= x2; x++)
  {
    clr = getpixel(dest,x,y);
    r = getr(clr); g = getg(clr); b = getb(clr);
    nr = 128-(r-127);
    ng = 128-(g-127);
    nb = 128-(b-127);
    putpixel(dest,x,y,makecol(nr,ng,nb));
  }
  //rest(1000); --- wtf??
  printf("%s\n",bitch);
}


OBJECT* make_inline_quad(int x1, int y1, int x2, int y2, int fill_type, int clr1, int clr2, int border_clr, int border_width)
{
OBJECT *obj;
obj = (OBJECT*)malloc(sizeof(OBJECT));

obj->type = TYPE_INLINE_QUAD;
obj->iq = (INLINE_QUAD*)malloc(sizeof(INLINE_QUAD));

obj->iq->x1 = x1;
obj->iq->y1 = y1;
obj->iq->x2 = x2;
obj->iq->y2 = y2;

obj->iq->fill_type = fill_type;
obj->iq->clr1 = clr1;
obj->iq->clr2 = clr2;

obj->iq->border_clr = border_clr;
obj->iq->border_width = border_width;

return obj;
}

OBJECT* make_inline_circ(int x1, int y1, int r, int fill_type, int clr1, int clr2, int border_clr, int border_width)
{
  OBJECT *obj;
  obj = (OBJECT*)malloc(sizeof(OBJECT));
  obj->type = TYPE_INLINE_CIRC;
  obj->ic = (INLINE_CIRC*)malloc(sizeof(INLINE_CIRC));
  
  obj->ic->x1 = x1;
  obj->ic->y1 = y1;
  obj->ic->r = r;
  obj->ic->fill_type = fill_type;
  obj->ic->clr1 = clr1;
  obj->ic->clr2 = clr2;
  obj->ic->border_clr = border_clr;
  obj->ic->border_width = border_width;
  return obj;
}

OBJECT* make_inline_rect(int x1, int y1, int w_and_h, int fill_type, int clr1, int clr2, int border_clr, int border_width)
{
  OBJECT *obj;
  obj = (OBJECT*)malloc(sizeof(OBJECT));
  obj->type = TYPE_INLINE_RECT;
  obj->ir = (INLINE_RECT*)malloc(sizeof(INLINE_RECT));
  
  obj->ir->x1 = x1;
  obj->ir->y1 = y1;
  obj->ir->w_and_h = w_and_h;
  obj->ir->fill_type = fill_type;
  obj->ir->clr1 = clr1;
  obj->ir->clr2 = clr2;
  obj->ir->border_clr = border_clr;
  obj->ir->border_width = border_width;
  return obj;
}

OBJECT* make_inline_elip(int x1, int y1, int rx, int ry, int fill_type, int clr1, int clr2, int border_clr, int border_width)
{
  OBJECT* obj;
  obj = (OBJECT*)malloc(sizeof(OBJECT));
  obj->type = TYPE_INLINE_ELIP;
  obj->ie = (INLINE_ELIP*)malloc(sizeof(INLINE_ELIP));
  
  obj->ie->x1 = x1;
  obj->ie->y1 = y1;
  obj->ie->rx = rx;
  obj->ie->ry = ry;
  obj->ie->fill_type = fill_type;
  obj->ie->clr1 = clr1;
  obj->ie->clr2 = clr2;
  obj->ie->border_clr = border_clr;
  obj->ie->border_width = border_width;
  return obj;
}

OBJECT* make_outline_quad(int x1, int y1, int x2, int y2, int clr1, int stroke)
{
  OBJECT *obj;
  obj = (OBJECT*)malloc(sizeof(OBJECT));
  obj->type = TYPE_OUTLINE_QUAD;
  obj->oq = (OUTLINE_QUAD*)malloc(sizeof(OUTLINE_QUAD));
  obj->oq->x1 = x1;
  obj->oq->x2 = x2;
  obj->oq->y1 = y1;
  obj->oq->y2 = y2;
  obj->oq->clr1 = clr1;
  obj->oq->stroke = stroke;
  return obj;
}

OBJECT* make_outline_circ(int x1, int y1, int r, int clr1, int stroke)
{
  OBJECT *obj;
  obj = (OBJECT*)malloc(sizeof(OBJECT));
  obj->type = TYPE_OUTLINE_CIRC;
  obj->oc = (OUTLINE_CIRC*)malloc(sizeof(OUTLINE_CIRC));
  
  obj->oc->x1 = x1;
  obj->oc->y1 = y1;
  obj->oc->r = r;
  obj->oc->clr1 = clr1;
  obj->oc->stroke = stroke;
  return obj;
}

OBJECT* make_outline_rect(int x1, int y1, int w_and_h, int clr1, int stroke)
{
  OBJECT *obj;
  obj = (OBJECT*)malloc(sizeof(OBJECT));
  obj->type = TYPE_OUTLINE_RECT;
  obj->ore = (OUTLINE_RECT*)malloc(sizeof(OUTLINE_RECT));
  
  obj->ore->x1 = x1;
  obj->ore->y1 = y1;
  obj->ore->w_and_h = w_and_h;
  obj->ore->clr1 = clr1;
  obj->ore->stroke = stroke;
  return obj;
}

OBJECT* make_outline_elip(int x1, int y1, int rx, int ry, int clr1, int stroke)
{
  OBJECT *obj;
  obj = (OBJECT*)malloc(sizeof(OBJECT));
  obj->type = TYPE_OUTLINE_ELIP;
  obj->oe = (OUTLINE_ELIP*)malloc(sizeof(OUTLINE_ELIP));
  obj->oe->x1 = x1;
  obj->oe->y1 = y1;
  obj->oe->rx = rx;
  obj->oe->ry = ry;
  obj->oe->clr1 = clr1;
  obj->oe->stroke = stroke;
  return obj;
}


int mir(int x1, int y1, int x2, int y2, int bp)
{
  if(bp == 0){
    if(mouse_x >= x1 && mouse_x <= x2 && mouse_y >= y1 && mouse_y <= y2)
      return 1;
    else return 0;
  }
  else{
    if(mouse_x >= x1 && mouse_x <= x2 && mouse_y >= y1 && mouse_y <= y2 && mouse_b & bp)
      return 1;
    else return 0;
  }
}




WIND* make_wind(int x, int y, int w, int h, char *title, bool enablevisibility, bool canexit, bool canmove)
{
  WIND *wnd;
  wnd = (WIND *) malloc(sizeof(WIND));
  wnd->x  = x;
  wnd->y  = y;
  wnd->w  = w;
  wnd->h  = h;
  wnd->title = title;
  wnd->bmp = create_bitmap(w+4,h+22);
  wnd->visible = enablevisibility;
  wnd->active = false;
  wnd->title = title;
  wnd->canexit = canexit;
  wnd->canmove = canmove;
  
  clear_to_color(wnd->bmp, 0x999999);
  rectfill(wnd->bmp, 0,0, wnd->w-1, 19, 0); //titlebar
  rect(wnd->bmp, 0,0, w-1, h-1, makecol(20,20,20)); //border 1
  rect(wnd->bmp, 1,1, w-2, h-2, makecol(20,20,20)); //border 2
  alfont_textout(wnd->bmp, larabie, title, 10, 3, 0xff9600);
  if(canexit){
    alfont_textout_right_aa(wnd->bmp, larabie, "X", wnd->w-5, 3, 0xff9600);
    alfont_textout_right_aa(wnd->bmp, larabie, "_", wnd->w-20, 3, 0xff9600);
    }
  set_clip_rect(wnd->bmp, 2, 20, w-3, h-3); //set_clip_rect
  int yy; //stvaranie pasikov
  for(yy = 20; yy < wnd->h; yy += 6){
    rectfill(wnd->bmp, 0, yy, w, yy+2, makecol(100,100,100));
    rectfill(wnd->bmp, 0, yy+3, w, yy+5, makecol(120,120,120));}
  //wnd->first = wnd->last;
  return wnd;
}

void destroy_wind(WIND *wnd)
{
  free((void *) wnd);
}

void set_visibility(WIND *wnd, bool enable)
{
  wnd->visible = enable;
}

bool get_visibility(WIND *wnd)
{
  return wnd->visible;
}
/*
//////////////////////////////////////////////////////////////////////////////////////////////
//     TOTO JE TA FUNKCIA KDE MAS DAT TEN GRADIENT - DRAW_WIND - SNAD TOMU KODU POCHOPIS    //
//////////////////////////////////////////////////////////////////////////////////////////////
*/

bool draw_wind(WIND *wnd, BITMAP *where)
{  
     
blit(wnd->bmp,where, 0,0, wnd->x,wnd->y, wnd->w,wnd->h);     
if(wnd->canmove){     
if(gv == 1)gcx+=5.1;
else gcx -= 5.1;

if(gcx > 254)gv = 0;
if(gcx < 1)gv = 1;


  c = 90.0;
  for(xx = wnd->x;xx < wnd->x+(wnd->w/6*1);)
  {
   line(where,xx, wnd->y - 4, xx, wnd->y,makecol(c,c,c));       
   line(where,xx, wnd->y + wnd->h-2, xx, wnd->y+wnd->h+3,makecol(c,c,c));
   //c-=(float)((wnd->w/6*1)/ 90.0); 
   c-=(float)(90.0/(wnd->w/6*1));
   if(c < 0.0)c = 0.0;
   xx++;
  }
  
  c = 0.0;
  for(xx = wnd->x + (wnd->w/6*5);xx < wnd->x+wnd->w;)
  {
   line(where,xx, wnd->y - 4, xx, wnd->y,makecol(c,c,c));
   line(where,xx, wnd->y + wnd->h-2, xx, wnd->y+wnd->h+3,makecol(c,c,c));       
   c+=(float)(90.0/(wnd->w/6*1));
   if(c > 90.0)c = 90.0;
   xx++;
  }
  //odteraz bude xx vlastne yy ;)
  c = 90.0;
  for(xx = wnd->y-4;xx < wnd->y+(wnd->h/6*1);)
  {
   line(where,wnd->x-4,xx, wnd->x,xx,makecol(c,c,c));
   line(where,wnd->x+wnd->w+3,xx,wnd->x+wnd->w-1,xx,makecol(c,c,c));       
   c-=(float)(90.0/(wnd->h/6*1)); 
   if(c < 0.0)c = 0.0;
   xx++;
  }
  
   c = 0.0;
  for(xx = wnd->y + (wnd->h/6*5);xx < wnd->y+wnd->h+4;)
  {
   line(where, wnd->x-4, xx, wnd->x, xx, makecol(c,c,c));
   line(where, wnd->x+wnd->w-1, xx, wnd->x+wnd->w+3, xx, makecol(c,c,c));       
   c+=(float)(90.0/(wnd->h/6*1));
   if(c > 90.0)c = 90.0;
   xx++;
  }
  
  
  
  line(where,wnd->x,wnd->y+wnd->h-2,wnd->x+wnd->w,wnd->y+wnd->h-2,0);
  //rect(where, wnd->x-4, wnd->y-4, wnd->x+wnd->w+3, wnd->y+wnd->h+3, makecol(128,128,128));
  //rect(where, wnd->x-3, wnd->y-3, wnd->x+wnd->w+2, wnd->y+wnd->h+2, makecol(128,128,128));
  //rect(where, wnd->x-2, wnd->y-2, wnd->x+wnd->w+1, wnd->y+wnd->h+1, makecol(128,128,128));
  //rect(where, wnd->x-1, wnd->y-1, wnd->x+wnd->w, wnd->y+wnd->h, makecol(128,128,128));
  //KRESLENIE ROHOVYCH STVORCEKOV
  if(mir(wnd->x-3, wnd->y-3, wnd->x+1, wnd->y+1, 0))
  {
    rectfill(where, wnd->x-3, wnd->y-3, wnd->x+1, wnd->y+1, makecol(gcx, gcx, gcx));
  }
  else rectfill(where, wnd->x-3, wnd->y-3, wnd->x+1, wnd->y+1, 0);
  
  
  if(mir(wnd->x+wnd->w-2, wnd->y-3, wnd->x+wnd->w+2, wnd->y+1, 0))
  {
    rectfill(where, wnd->x+wnd->w-2, wnd->y-3, wnd->x+wnd->w+2, wnd->y+1, makecol(gcx, gcx, gcx));
  }
  else rectfill(where, wnd->x+wnd->w-2, wnd->y-3, wnd->x+wnd->w+2, wnd->y+1, 0);
  
  
  if(mir(wnd->x-3, wnd->y+wnd->h-2, wnd->x+1, wnd->y+wnd->h+2, 0))
  {
    rectfill(where, wnd->x-3, wnd->y+wnd->h-2, wnd->x+1, wnd->y+wnd->h+2, makecol(gcx, gcx, gcx));
  }
  else rectfill(where, wnd->x-3, wnd->y+wnd->h-2, wnd->x+1, wnd->y+wnd->h+2, 0);
  
  
  if(mir(wnd->x+wnd->w-2, wnd->y+wnd->h-2, wnd->x+wnd->w+2, wnd->y+wnd->h+2, 0))
  {
    rectfill(where, wnd->x+wnd->w-2, wnd->y+wnd->h-2, wnd->x+wnd->w+2, wnd->y+wnd->h+2, makecol(gcx, gcx, gcx));
  }
  else rectfill(where, wnd->x+wnd->w-2, wnd->y+wnd->h-2, wnd->x+wnd->w+2, wnd->y+wnd->h+2, 0);
  //KRESLENIE HRANOVYCH OBDLZNICKOV
  if(mir(wnd->x+(wnd->w/6*1), wnd->y-4, wnd->x+(wnd->w/6*5), wnd->y, 0))
  {
    rectfill(where, wnd->x+(wnd->w/6*1), wnd->y-4, wnd->x+(wnd->w/6*5), wnd->y, makecol(gcx, gcx, gcx));
  }
  else rectfill(where, wnd->x+(wnd->w/6*1), wnd->y-4, wnd->x+(wnd->w/6*5), wnd->y, 0);
  
  if(mir(wnd->x-4, wnd->y+(wnd->h/6*1), wnd->x, wnd->y+(wnd->h/6*5), 0))
  {
    rectfill(where, wnd->x-4, wnd->y+(wnd->h/6*1), wnd->x, wnd->y+(wnd->h/6*5), makecol(gcx, gcx, gcx));
  }
  else rectfill(where, wnd->x-4, wnd->y+(wnd->h/6*1), wnd->x, wnd->y+(wnd->h/6*5), 0);
  
  if(mir(wnd->x+wnd->w-1, wnd->y+(wnd->h/6*1), wnd->x+wnd->w+3, wnd->y+(wnd->h/6*5), 0))
  {
    rectfill(where, wnd->x+wnd->w-1, wnd->y+(wnd->h/6*1), wnd->x+wnd->w+3, wnd->y+(wnd->h/6*5), makecol(gcx, gcx, gcx));
  }
  else rectfill(where, wnd->x+wnd->w-1, wnd->y+(wnd->h/6*1), wnd->x+wnd->w+3, wnd->y+(wnd->h/6*5), 0);
  
  if(mir(wnd->x+(wnd->w/6*1), wnd->y+wnd->h-1, wnd->x+(wnd->w/6*5), wnd->y+wnd->h+3, 0))
  {
    rectfill(where, wnd->x+(wnd->w/6*1), wnd->y+wnd->h-1, wnd->x+(wnd->w/6*5), wnd->y+wnd->h+3, makecol(gcx, gcx, gcx));
  }
  else rectfill(where, wnd->x+(wnd->w/6*1), wnd->y+wnd->h-1, wnd->x+(wnd->w/6*5), wnd->y+wnd->h+3, 0);
}//canmove
  //draw_buttons(wnd,where);
  return true;
}

int manage_window(WIND *wnd)
{
  BITMAP *beempe;
  int tmpx, tmpy;
  int x1, y1;
  x1 = wnd->x;
  y1 = wnd->y;
  beempe = create_bitmap(SCREEN_W, SCREEN_H);
  //mouse_over_title_bar
  if(mouse_b & 1 && mouse_x > wnd->x && mouse_x < wnd->x+wnd->w-15 && mouse_y > wnd->y && mouse_y < wnd->y+20)
  {
    blit(screen,beempe,0,0,0,0,SCREEN_W, SCREEN_H);
    tmpx = mouse_x - wnd->x;
    tmpy = mouse_y - wnd->y;  
    while(mouse_b & 1)
    {
      wnd->x = mouse_x - tmpx;
      wnd->y = mouse_y - tmpy;
      blit(beempe,mb,0,0,0,0,SCREEN_W, SCREEN_H);
      //draw_wind(wnd,mb);
      rect(mb,mouse_x - tmpx, mouse_y - tmpy, mouse_x - tmpx+ wnd->w, mouse_y - tmpy + wnd->h,0);
      blit(mb,screen,0,0,0,0,SCREEN_W, SCREEN_H);         
    }           
  }//endof mouse over
  
  //natahovanie okienka
  if(mir(wnd->x-3, wnd->y-3, wnd->x+1, wnd->y+1, 1))
  {
    blit(screen,beempe,0,0,0,0,SCREEN_W, SCREEN_H);
    while(mouse_b & 1)
    {
      if(wnd->x+wnd->w - mouse_x > 100)
      tmpx = mouse_x;
      if(wnd->y+wnd->h - mouse_y > 50)
      tmpy = mouse_y;
      blit(beempe,mb,0,0,0,0,SCREEN_W, SCREEN_H);
      rect(mb,tmpx, tmpy, wnd->x+wnd->w, wnd->y+wnd->h, 0);
      blit(mb,screen,0,0,0,0,SCREEN_W, SCREEN_H);
    }
    int ow = wnd->w, oh = wnd->h;
    if(wnd->x+wnd->w - mouse_x > 100)
      wnd->w = abs(wnd->x+wnd->w - mouse_x);
    else
      wnd->w = 100;
    if(wnd->y+wnd->h - mouse_y > 50)
      wnd->h = abs(wnd->y+wnd->h - mouse_y);
    else
      wnd->h = 50;
    wnd->x = wnd->x + ow - wnd->w;
    wnd->y = wnd->y + oh - wnd->h;
    wnd->bmp = create_bitmap(wnd->w, wnd->h);
    clear_to_color(wnd->bmp, 0x999999);
    alfont_set_font_size(larabie,16);
    rectfill(wnd->bmp, 0,0, wnd->w-1, 19, 0); //titlebar
    rect(wnd->bmp, 0,0, wnd->w-1, wnd->h-1, makecol(20,20,20)); //border 1
    rect(wnd->bmp, 1,1, wnd->w-2, wnd->h-2, makecol(20,20,20)); //border 2
    alfont_textout(wnd->bmp, larabie, wnd->title, 10, 3, 0xff9600);
    if(wnd->canexit){
    alfont_textout_right_aa(wnd->bmp, larabie, "X", wnd->w-5, 3, 0xff9600);
    alfont_textout_right_aa(wnd->bmp, larabie, "_", wnd->w-20, 3, 0xff9600);
    }
    set_clip_rect(wnd->bmp, 2, 20, wnd->w-3, wnd->h-3); //set_clip_rect
    int yy; //stvaranie pasikov
    for(yy = 20; yy < wnd->h; yy += 6){
      rectfill(wnd->bmp, 0, yy, wnd->w, yy+2, makecol(100,100,100));
      rectfill(wnd->bmp, 0, yy+3, wnd->w, yy+5, makecol(120,120,120));}
  }
  if(mir(wnd->x+wnd->w-2, wnd->y-3, wnd->x+wnd->w+2, wnd->y+1, 1))
  {}
  if(mir(wnd->x-3, wnd->y+wnd->h-1, wnd->x+2, wnd->y+wnd->h+2, 1))
  {}
  if(mir(wnd->x+wnd->w-2, wnd->y+wnd->h-2, wnd->x+wnd->w+2, wnd->y+wnd->h+2, 1))
  {
    blit(screen,beempe,0,0,0,0,SCREEN_W, SCREEN_H);
    while(mouse_b & 1)
    {
      if(mouse_x - wnd->x > 100)
      tmpx = mouse_x - wnd->w;
      if(mouse_y - wnd->y > 50)
      tmpy = mouse_y - wnd->h;
      blit(beempe,mb,0,0,0,0,SCREEN_W, SCREEN_H);
      rect(mb,wnd->x, wnd->y, wnd->w+tmpx, wnd->h+tmpy, 0);
      blit(mb,screen,0,0,0,0,SCREEN_W, SCREEN_H);
    }
    if(mouse_x - wnd->x > 100)
      wnd->w = abs(wnd->x-mouse_x);
    else
      wnd->w = 100;
    if(mouse_y - wnd->y > 50)
      wnd->h = abs(wnd->y-mouse_y);
    else
      wnd->h = 50;
    wnd->bmp = create_bitmap(wnd->w, wnd->h);
    clear_to_color(wnd->bmp, 0x999999);
    alfont_set_font_size(larabie,16);
    rectfill(wnd->bmp, 0,0, wnd->w-1, 19, 0); //titlebar
    rect(wnd->bmp, 0,0, wnd->w-1, wnd->h-1, makecol(20,20,20)); //border 1
    rect(wnd->bmp, 1,1, wnd->w-2, wnd->h-2, makecol(20,20,20)); //border 2
    alfont_textout(wnd->bmp, larabie, wnd->title, 10, 3, 0xff9600);
    if(wnd->canexit){
    alfont_textout_right_aa(wnd->bmp, larabie, "X", wnd->w-5, 3, 0xff9600);
    alfont_textout_right_aa(wnd->bmp, larabie, "_", wnd->w-20, 3, 0xff9600);
    }
    set_clip_rect(wnd->bmp, 2, 20, wnd->w-3, wnd->h-3); //set_clip_rect
    int yy; //stvaranie pasikov
    for(yy = 20; yy < wnd->h; yy += 6){
      rectfill(wnd->bmp, 0, yy, wnd->w, yy+2, makecol(100,100,100));
      rectfill(wnd->bmp, 0, yy+3, wnd->w, yy+5, makecol(120,120,120));}
    //wnd->first = wnd->last;
  }
  //zatvaranie okienka pomocou X a set visibility
  if(mouse_b & 1 && mouse_x > wnd->x+wnd->w-20 && mouse_x < wnd->x+wnd->w && mouse_y > wnd->y && mouse_y < wnd->y+20)
    set_visibility(wnd, false);
    
  destroy_bitmap(beempe);
  return 1;
}


bool make_qgrad()
{
 int x, y;
 int clr; 

 getpixledr = c_red; getpixledg = c_green; getpixledb = c_blue;
 getpx = 0;
 getpy = 0;
 //rr = c_red;gg= c_green;bb = c_blue;
 //r = c_red;g = c_green;b = c_blue;//rr = r;gg =g;bb=b;
 r =rr;g=gg;b=bb;
 for(x = 0;x < 200;x++)
 {
  r -= rr/200;
  g -= gg/200;
  b -= bb/200;      
  //printf("%f %f %f",r,g,b);
  putpixel(qgrad,x,0,makecol((int)r % 256,(int)g % 256,(int)b % 256));
 }


 for(x = 0;x < 200;x++)
 {
  clr = getpixel(qgrad,x,0);
  rs = getr(clr);
  gs = getg(clr);
  bs = getb(clr);
  r = rs;b = bs;g = gs;
  for(y = 0;y < 200;y++)
  {
   r -= (rs-255)/200;
   g -= (gs-255)/200;
   b -= (bs-255)/200;
   putpixel(qgrad,x,y,makecol(abs((int)r % 256),abs((int)g % 256),abs((int)b % 256)));      
  }       

 }
 
 getpixledr = getr(getpixel(qgrad,0,0));
 getpixledg = getg(getpixel(qgrad,0,0));
 getpixledb = getb(getpixel(qgrad,0,0));
 return true;

}


#include "canvas.h"

int get_color_tool(WIND *wnd)
{
 int color;
 
 if(mode == MODE_TOOL_GETCOLOR)
 {
  if(mouse_over_cnv(wnd) && mouse_b & 1)
	{
	 color = getpixel(screen, mouse_x, mouse_y);
	 c_red = rr = getr(color); 														 
	 c_green = gg = getg(color);
	 c_blue = bb = getb(color);
	 make_qgrad();
	}				 
 } 		
}




#include "numbox.h"
#include "combobox.h"
#include "filebrowser.h"
#include "textbox.h"

#include "button.h"
#include "toolbar.h"

#include "miradors.h"
#include "desc.h"
#include "qbar.h"
#include "ststuff.h"
#include "ninjabox.h"
#include "menu2.h"
#include "level.h"


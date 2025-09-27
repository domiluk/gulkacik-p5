//INCLUDES
//#pregnant once

#define FIELD_SIZE 60

#include "engine.h"
//#include "desc.h"
//#include "button.h"
#define NO_MAGIC_MAIN
//FUNCTIONS
/*int _mangled_main()
{
return 1;    
}*/

int before = 0, now = 0;
int hh;

void close_button_handler(void)
{
  close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

int tmpx,tmpy,endx,endy;

void init()
{
  allegro_init();
  alfont_init();
  algif_init();
  alpng_init();
  //jpgalleg_init();
  alfont_text_mode(-1);
  //set_color_depth(desktop_color_depth());
  set_color_depth(32);
  if(set_gfx_mode(2, 800, 600, 0, 0) != 0)
    exit(-1);
  install_mouse();
  install_keyboard();
  install_timer();
  LOCK_FUNCTION(close_button_handler);
  set_close_button_callback(close_button_handler);
  show_os_cursor(MOUSE_CURSOR_ARROW);
  
 
  listt = init_list(30,30);//(CB_LIST*)malloc(sizeof(CB_LIST));
  
  //listt->cpoi = 0;
  
  unitt = init_unit("12",12);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("13",13);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("14",14);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("15",15);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("16",16);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("17",17);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("18",18);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("19",19);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("20",20);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("21",21);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("22",22);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("23",23);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("24",24);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("25",25);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("26",26);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("27",27);
  stick_unit_to_combo_list(listt,unitt);
  unitt = init_unit("28",28);
  stick_unit_to_combo_list(listt,unitt);
  
  nnlist = init_nlist(100,200);
  
  printf("%d ", sizeof(BUTTON));
  printf("%d ", sizeof(WIND));
  printf("%d ", sizeof(CANVAS));
  printf("%d ", sizeof(OBJECT));
  printf("%d ", sizeof(TEXTBOX));
  printf("%d ", sizeof(BITMAP));
  
  _rmdir("delete");
  rmdir("delete");
  system("rm delete/main.o");
  system("rm main.o");
  system("rmdir delete");
  
  
  bordernb = init_numbox(1.0, 0, 1.0, 10, 0);
  anglenb = init_numbox(0.0, 0, 1.0, 360, 0);
  fill_the_list(nnlist);
  printf("\ndokoncil som fonty");
  rest(2000);
}

void deinit()
{
  clear_keybuf();
  destroy_bitmap(mb);
  destroy_bitmap(tmpbmp);
  _rmdir("delete");
  rmdir("delete");
  system("rm delete/main.o");
  system("rm main.o");
  system("rmdir delete");
  set_gfx_mode(GFX_TEXT, 0,0,0,0);
  exit(-1);
}


//MAIN
int _mangled_main()
{
  init();
  printf("\n dokoncil si init ty pako?");
  //char *file_arg;
  //strcpy(file_arg, argc[1]);
  //set_window_title("Vectoria Graphics Editor");
  mb = create_system_bitmap(SCREEN_W, SCREEN_H);
  printf("\n aig mama");
  tmpbmp = create_system_bitmap(SCREEN_W, SCREEN_H);
  printf("\n big mama");
  clear_to_color(mb, 0x999999);
  printf("\n cig mama");
  larabie = alfont_load_font("larabieb.ttf");
  printf("\n dig mama");
  arrup = load_bitmap("arrowup.bmp",NULL);
  printf("\n eig mama");
  arrdown = load_bitmap("arrowdown.bmp",NULL);
  printf("\n fig mama");
  arrback = load_bitmap("arrowback.bmp", NULL);
  printf("\n big mama");
  newdir = load_bitmap("newdir.bmp",NULL);
    printf("\n big mama");
  hb = load_bitmap("heart.bmp",NULL);
  
  
 normal_brick[0] = load_bitmap("graphics/kocka01.bmp", NULL);
 normal_brick[1] = load_bitmap("graphics/kocka02.bmp", NULL);
 normal_brick[2] = load_bitmap("graphics/kocka03.bmp", NULL);
 normal_brick[3] = load_bitmap("graphics/kocka04.bmp", NULL);
 normal_brick[4] = load_bitmap("graphics/kocka05.bmp", NULL);
 normal_brick[5] = load_bitmap("graphics/kocka06.bmp", NULL);
 normal_brick[6] = load_bitmap("graphics/kocka07.bmp", NULL);
 normal_brick[7] = load_bitmap("graphics/kocka08.bmp", NULL);
 normal_brick[8] = load_bitmap("graphics/kocka09.bmp", NULL);
 normal_brick[9] = load_bitmap("graphics/kocka10.bmp", NULL);
 normal_brick[10] = load_bitmap("graphics/kocka11.bmp", NULL);
 normal_brick[11] = load_bitmap("graphics/kocka12.bmp", NULL);
 normal_brick[12] = load_bitmap("graphics/kocka13.bmp", NULL);
 
 water_field[0] = load_bitmap("graphics/water.bmp", NULL); 
  water_field[1] = load_bitmap("graphics/water1.bmp", NULL);
   water_field[2] = load_bitmap("graphics/water2.bmp", NULL);
    water_field[3] = load_bitmap("graphics/water3.bmp", NULL);
     water_field[4] = load_bitmap("graphics/water4.bmp", NULL);
 qm[0] = load_bitmap("graphics/qm1.bmp", NULL);
 symbol_brick[0] = load_bitmap("graphics/symbol1.bmp", NULL);
 symbol_brick[1] = load_bitmap("graphics/symbol2.bmp", NULL);
 symbol_brick[2] = load_bitmap("graphics/symbol3.bmp", NULL);
 symbol_brick[3] = load_bitmap("graphics/symbol4.bmp", NULL);
 symbol_brick[4] = load_bitmap("graphics/symbol5.bmp", NULL);
 
 trava[0] = load_bitmap("graphics/trava.bmp", NULL); 
  trava[1] = load_bitmap("graphics/trava1.bmp", NULL);
   trava[2] = load_bitmap("graphics/trava2.bmp", NULL);
    trava[3] = load_bitmap("graphics/trava3.bmp", NULL);
     trava[4] = load_bitmap("graphics/trava4.bmp", NULL);
     
 diebrick = load_bitmap("graphics/diebrick.bmp", NULL);
 teleport = load_bitmap("graphics/teleport.bmp", NULL);
 teleportend = load_bitmap("graphics/teleportend.bmp", NULL);    
 laser = load_bitmap("graphics/laser.bmp", NULL);
 laser2 = load_bitmap("graphics/laser2.bmp", NULL);
 
 arrow[0] = load_bitmap("graphics/arrow1.bmp", NULL);
 arrow[1] = load_bitmap("graphics/arrow2.bmp", NULL);
 arrow[2] = load_bitmap("graphics/arrow3.bmp", NULL);
 arrow[3] = load_bitmap("graphics/arrow4.bmp", NULL);
  
 printf("ppp");
 bg = load_bitmap("bg.bmp", NULL);
 gulkacik = load_bitmap("gulkacik.bmp", NULL);
 up = load_bitmap("up.bmp", NULL);
 upa = load_bitmap("upa.bmp", NULL);
 kocka_cista = load_bitmap("kocka_cista.bmp", NULL);
  
  printf("\n TUTUUUUTUUUTUUUUUTTTTT");
  alfont_set_font_size(larabie,16);
  window = make_wind(300,100,400,300,"A",true,true,true);
  window->active = true;
  platno = init_canvas(0,20,398,278);
  
  int g_x;
  float g_c;
	
	g_c = 34; 
	gradleft = create_bitmap(20,16);
	gradright = create_bitmap(20,16); 
	for(g_x = 0;g_x < 20;g_x++)
	{
	 line(gradleft, g_x, 0, g_x, 16, makecol(g_c, g_c, g_c));
	 line(gradright, 10+(10-g_x), 0, 10+(10-g_x), 16, makecol(g_c, g_c, g_c));
	 g_c += (float)(68-34)/20; 				
  }
  line(gradright, 0,0,0,16,0x444444);
  
  stick_canvas_to_window(window,platno);
  qgrad = create_bitmap(200,200);
  /*printf("%d", argv);*/
  //printf("%s", argc[1]);
  //open_vgp(argc[1], window);
  make_toolbar();
  make_insert_text();
  make_set_texture();
  make_credits();
  make_menu();
  make_type();
  printf("\nTUTUUUUTUUUTUUUUUTTTTT");
  make_save_as();
  make_open();
  make_new();
  make_fm();
  
  
  make_qgrad();
  
  while(!close_button_pressed)
  {
    //ich liebe marry, i love marry...
		if(key[KEY_I] && key[KEY_L] && key[KEY_M])
		fm_wnd->visible = 1;
		
		//manage_canvas(window);
    get_color_tool(window);
    
    //clear_to_color(mb,0x999999);
    clear_to_color(mb,0);
    
    //draw_numbox(mb, ww, 150, 150, 60, 15);
    
    
    if(have_level)
       {
        rectfill(mb, SCREEN_W/2-FIELD_SIZE*5-13, (SCREEN_H)/2 - FIELD_SIZE*4 +8-13, SCREEN_W/2-FIELD_SIZE*5+FIELD_SIZE*10+13, (SCREEN_H)/2 - FIELD_SIZE*4 +8+FIELD_SIZE*8+13, 0x444444);
        alfont_textprintf_centre_aa(mb, larabie, SCREEN_W/2-FIELD_SIZE*5+FIELD_SIZE*10+5, SCREEN_H/2, 0xffffff, ">");
        alfont_textprintf_centre_aa(mb, larabie, SCREEN_W/2-FIELD_SIZE*5+5-13, SCREEN_H/2, 0xffffff, "<");
        draw_sprite(mb, up, SCREEN_W/2 - up->w/2, 58);
        draw_sprite_v_flip(mb, up, SCREEN_W/2 - up->w/2, 58 + FIELD_SIZE*8+13);

                  
        //right
        if( mir(SCREEN_W/2-FIELD_SIZE*5+FIELD_SIZE*10+0 , (SCREEN_H)/2 - FIELD_SIZE*4 +8 +13, SCREEN_W/2-FIELD_SIZE*5+FIELD_SIZE*10+13, (SCREEN_H)/2 - FIELD_SIZE*4 +8+FIELD_SIZE*8+0-13, 0))
        {
         rectfill(mb, SCREEN_W/2-FIELD_SIZE*5+FIELD_SIZE*10+0 , (SCREEN_H)/2 - FIELD_SIZE*4 +8+13, SCREEN_W/2-FIELD_SIZE*5+FIELD_SIZE*10+13, (SCREEN_H)/2 - FIELD_SIZE*4 +8+FIELD_SIZE*8+0-13,0x999999);                                               
         alfont_textprintf_centre_aa(mb, larabie, SCREEN_W/2-FIELD_SIZE*5+FIELD_SIZE*10+5, SCREEN_H/2, 0, ">");
         if(mouse_b & 1)
         {
          if(camx+10 < lvl->w)
          {
           camx++;
           rest(120);           
          }           
         }
        }
        
        //left
        if(mir(SCREEN_W/2-FIELD_SIZE*5-13, (SCREEN_H)/2 - FIELD_SIZE*4 +8 +13, SCREEN_W/2-FIELD_SIZE*5, (SCREEN_H)/2 - FIELD_SIZE*4 +8+FIELD_SIZE*8+0-13, 0))
        {
         rectfill(mb, SCREEN_W/2-FIELD_SIZE*5-13, (SCREEN_H)/2 - FIELD_SIZE*4 +8 +13, SCREEN_W/2-FIELD_SIZE*5, (SCREEN_H)/2 - FIELD_SIZE*4 +8+FIELD_SIZE*8+0-13,0x999999);                                               
         alfont_textprintf_centre_aa(mb, larabie, SCREEN_W/2-FIELD_SIZE*5+5-13, SCREEN_H/2, 0, "<");
         if(mouse_b & 1)
         {
          if(camx > 0)
          {
           camx--;
           rest(120);           
          }           
         }
        }
        
        //up
        if(mir(SCREEN_W/2 - FIELD_SIZE*4 + 13 - FIELD_SIZE*4, 58, SCREEN_W/2 + FIELD_SIZE*4 - 13+FIELD_SIZE*4, 58+13, 0))
        {
         rectfill(mb, SCREEN_W/2 - FIELD_SIZE*4 + 13, 58-2, SCREEN_W/2 + FIELD_SIZE*4 - 13, 58+13,0x999999);                                               
         //alfont_textprintf_centre_aa(mb, larabie, SCREEN_W/2-FIELD_SIZE*5+5-13, SCREEN_H/2, 0, "<");
         draw_sprite(mb, upa, SCREEN_W/2 - up->w/2, 58);
         if(mouse_b & 1)
         {
          if(camy > 0)
          {
           camy--;
           rest(120);           
          }           
         }                  
        }
        
        //down
        if(mir(SCREEN_W/2 - FIELD_SIZE*4 + 13 - FIELD_SIZE*4, 58+FIELD_SIZE*8+13, SCREEN_W/2 + FIELD_SIZE*4 - 13+FIELD_SIZE*4, 58+13+FIELD_SIZE*8+13, 0))
        {
         rectfill(mb, SCREEN_W/2 - FIELD_SIZE*4 + 13, 58-2+FIELD_SIZE*8+13-1, SCREEN_W/2 + FIELD_SIZE*4 - 13, 58+13+FIELD_SIZE*8+13-3,0x999999);                                               
         //alfont_textprintf_centre_aa(mb, larabie, SCREEN_W/2-FIELD_SIZE*5+5-13, SCREEN_H/2, 0, "<");
         draw_sprite_v_flip(mb, upa, SCREEN_W/2 - up->w/2, 58+FIELD_SIZE*8+13);
         if(mouse_b & 1)
         {
          if(camy+8 < lvl->h)
          {
           camy++;
           rest(120);           
          }           
         }                  
        }
        

        
        
        blit(lvl->bmp, mb, camx*FIELD_SIZE, camy*FIELD_SIZE, SCREEN_W/2-FIELD_SIZE*5, (SCREEN_H)/2 - FIELD_SIZE*4 +8, FIELD_SIZE*10, FIELD_SIZE*8);
        draw_sprite(mb, gulkacik, lvl->bx, lvl->by);
        alfont_set_font_size(larabie, 24);
        alfont_textprintf_centre_aa(mb, larabie, SCREEN_W/2, 42-13, 0xffffff, "%s", lvl->name);
   
   
   
       if(new_wnd->visible == false && save_as_wnd->visible == false && open_wnd->visible == false && menu->smh[0]->rolled == 0 && menu->smh[1]->rolled == 0 && menu->smh[2]->rolled == 0)
        {
         if(mir(400-300, 300-240+8, 400+300, 300+240+6, 0))       
         {
          xxsur = (int)((mouse_x-100)/FIELD_SIZE);
          yysur = (int)((mouse_y-58)/FIELD_SIZE);
          if(yysur == 10)yysur = 9;
          if(ldm == 0)
           draw_sprite(mb, normal_brick[generated], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2); 
          if(ldm == 1)
           draw_sprite(mb, water_field[0], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 2)
           draw_sprite(mb, water_field[1], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 3)
           draw_sprite(mb, water_field[2], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2); 
          if(ldm == 4)
           draw_sprite(mb, water_field[3], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2); 
          if(ldm == 5)
           draw_sprite(mb, water_field[4], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2); 
          if(ldm == 10)
           draw_sprite(mb, symbol_brick[0], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 11)
           draw_sprite(mb, symbol_brick[1], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 12)
           draw_sprite(mb, symbol_brick[2], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2); 
          if(ldm == 13)
           draw_sprite(mb, symbol_brick[3], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2); 
          if(ldm == 14)
           draw_sprite(mb, symbol_brick[4], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);  
          if(ldm == 20)
           draw_sprite(mb, trava[0], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 21)
           draw_sprite(mb, trava[1], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 22)
           draw_sprite(mb, trava[2], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2); 
          if(ldm == 23)
           draw_sprite(mb, trava[3], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2); 
          if(ldm == 24)
           draw_sprite(mb, trava[4], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 7)
           draw_sprite(mb, qm[0], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 9)
           draw_sprite(mb, diebrick, xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);   
          if(ldm == 6)
           draw_sprite(mb, teleport, xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == -50)
           draw_sprite(mb, teleportend, xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 40 || ldm == 41)
           draw_sprite(mb, laser, xxsur*FIELD_SIZE+100-60, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 42 || ldm == 43)
           draw_sprite(mb, laser2, xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2-60);
          if(ldm == 50)
           draw_sprite(mb, arrow[0], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 51)
           draw_sprite(mb, arrow[1], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 52)
           draw_sprite(mb, arrow[2], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2);
          if(ldm == 53)
           draw_sprite(mb, arrow[3], xxsur*FIELD_SIZE+100, yysur*FIELD_SIZE+58+13-2); 
               
          if(mouse_b & 1)
          {
           if(ldm == 0)
           {
            draw_sprite(lvl->bmp, normal_brick[generated], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 0;
            rest(120);
            generated = rand () % 13;
           }
           if(ldm == 1)
           {
            draw_sprite(lvl->bmp, water_field[0], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 1;
            rest(120);       
           }
           if(ldm == 2)
           {
            draw_sprite(lvl->bmp, water_field[1], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 2;
            rest(120);       
           }
           if(ldm == 3)
           {
            draw_sprite(lvl->bmp, water_field[2], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 3;
            rest(120);       
           }
           if(ldm == 4)
           {
            draw_sprite(lvl->bmp, water_field[3], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 4;
            rest(120);       
           }
           if(ldm == 5)
           {
            draw_sprite(lvl->bmp, water_field[4], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 5;
            rest(120);       
           }
           if(ldm == 5)
           {
            draw_sprite(lvl->bmp, water_field[4], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 5;
            rest(120);       
           }
           if(ldm == 20)
           {
            draw_sprite(lvl->bmp, trava[0], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 20;
            rest(120);       
           }
           if(ldm == 21)
           {
            draw_sprite(lvl->bmp, trava[1], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 21;
            rest(120);       
           }
           if(ldm == 22)
           {
            draw_sprite(lvl->bmp, trava[2], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 22;
            rest(120);       
           }
           if(ldm == 23)
           {
            draw_sprite(lvl->bmp, trava[3], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 23;
            rest(120);       
           }
           if(ldm == 24)
           {
            draw_sprite(lvl->bmp, trava[4], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 24;
            rest(120);       
           }
           if(ldm == 7)
           {
            draw_sprite(lvl->bmp, qm[0], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 7;
            rest(120);       
           }
           if(ldm == 9)
           {
            draw_sprite(lvl->bmp, diebrick, (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 9;
            rest(120);       
           }
           if(ldm == 40)
           {
            draw_sprite(lvl->bmp, laser, (xxsur+camx)*FIELD_SIZE-60, (yysur+camy)*FIELD_SIZE);           
            if(lvl->info[xxsur+camx][yysur+camy] != 40)lvl->la++;
            lvl->info[xxsur+camx][yysur+camy] = 40;
            rest(120);       
           }
           if(ldm == 41)
           {
            draw_sprite(lvl->bmp, laser, (xxsur+camx)*FIELD_SIZE-60, (yysur+camy)*FIELD_SIZE);           
            if(lvl->info[xxsur+camx][yysur+camy] != 41)lvl->la++;
            lvl->info[xxsur+camx][yysur+camy] = 41;
            rest(120);       
           }
           if(ldm == 42)
           {
            draw_sprite(lvl->bmp, laser2, (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE-60);           
            if(lvl->info[xxsur+camx][yysur+camy] != 42)lvl->la++;
            lvl->info[xxsur+camx][yysur+camy] = 42;
            rest(120);       
           } 
           if(ldm == 43)
           {
            draw_sprite(lvl->bmp, laser2, (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE-60);           
            if(lvl->info[xxsur+camx][yysur+camy] != 43)lvl->la++;
            lvl->info[xxsur+camx][yysur+camy] = 43;
            rest(120);       
           }    
           if(ldm == 50)
           {
            draw_sprite(lvl->bmp, arrow[0], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 50;
            rest(120);       
           }  
           if(ldm == 51)
           {
            draw_sprite(lvl->bmp, arrow[1], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 51;
            rest(120);       
           }
           if(ldm == 52)
           {
            draw_sprite(lvl->bmp, arrow[2], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 52;
            rest(120);       
           }
           if(ldm == 53)
           {
            draw_sprite(lvl->bmp, arrow[3], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = 53;
            rest(120);       
           }
               
           if(ldm == 6 && lvl->tela < 3)
           {
            draw_sprite(lvl->bmp, teleport, (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->info[xxsur+camx][yysur+camy] = lvl->tela+30;
            printf("tela%d", lvl->tela+30);
            rest(160);    
            ldm = -50;   
           }
           else if(ldm == -50)
           {
            draw_sprite(lvl->bmp, teleportend, (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            lvl->tel[lvl->tela].x = xxsur+camx;
            lvl->tel[lvl->tela].y = yysur+camy;
            lvl->tel[lvl->tela].value = lvl->tela+30;
            printf("xxsur yysur %d %d", xxsur+camx, yysur+camy);
            lvl->tela++;
            rest(160);    
            ldm = 6;       
           }
           
           if(ldm == 10 && symbol_amount[0] < 2)
           {
            draw_sprite(lvl->bmp, symbol_brick[0], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            if(lvl->info[xxsur+camx][yysur+camy] != 10)symbol_amount[0]++;
            lvl->info[xxsur+camx][yysur+camy] = 10;
            
            rest(120);     
            printf("##########10################ %d\n", symbol_amount[0]);  
           }
          if(ldm == 11 && symbol_amount[1] < 2)
           {
            draw_sprite(lvl->bmp, symbol_brick[1], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            if(lvl->info[xxsur+camx][yysur+camy] != 11)symbol_amount[1]++;
            lvl->info[xxsur+camx][yysur+camy] = 11;
            //symbol_amount[1]++;
            rest(120);
            printf("##########11################ %d\n", symbol_amount[1]);       
          }
          if(ldm == 12 && symbol_amount[2] < 2)
           {
            draw_sprite(lvl->bmp, symbol_brick[2], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            if(lvl->info[xxsur+camx][yysur+camy] != 12)symbol_amount[2]++;
            lvl->info[xxsur+camx][yysur+camy] = 12;
            //symbol_amount[2]++;
            rest(120);
            printf("##########12################ %d\n", symbol_amount[2]);       
          }
          if(ldm == 13 && symbol_amount[3] < 2)
           {
            draw_sprite(lvl->bmp, symbol_brick[3], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            if(lvl->info[xxsur+camx][yysur+camy] != 13)symbol_amount[3]++;
            lvl->info[xxsur+camx][yysur+camy] = 13;
            //symbol_amount[3]++;
            rest(120);     
            printf("##########13################ %d\n", symbol_amount[3]); 
          }
          if(ldm == 14 && symbol_amount[4] < 2)
           {
            draw_sprite(lvl->bmp, symbol_brick[4], (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            if(lvl->info[xxsur+camx][yysur+camy] != 14)symbol_amount[4]++;
            lvl->info[xxsur+camx][yysur+camy] = 14;
            //symbol_amount[4]++;
            rest(120); 
            printf("##########14################ %d\n", symbol_amount[4]);      
          }
          if(ldm == -1)
           {
            /*draw_sprite(lvl->bmp, gulkacik, (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
            //lvl->info[xxsur+camx][yysur+camy] = 12;
            lvl->bx = (yysur+camy)*FIELD_SIZE - 30;
            lvl->by = (yysur+camy)*FIELD_SIZE - 30;
            
            symbol_amount[2]++;*/
            
            xxsur = mouse_x;
            yysur = mouse_y;
            //mir(400-300, 300-240+8, 400+300, 300+240+6,
            if(mouse_x > 700)xxsur = 700;
            if(mouse_x < 100)xxsur = 100;
            if(mouse_y > 546)yysur = 546;
            if(mouse_y < 58) yysur =  58;
            
            lvl->bx = xxsur;
            lvl->by = yysur;
            rest(120);       
          }
          }
          if(mouse_b & 2)
          {
           if(lvl->info[xxsur+camx][yysur+camy] == 10)symbol_amount[0]--;
           if(lvl->info[xxsur+camx][yysur+camy] == 11)symbol_amount[1]--;
           if(lvl->info[xxsur+camx][yysur+camy] == 12)symbol_amount[2]--;
           if(lvl->info[xxsur+camx][yysur+camy] == 13)symbol_amount[3]--;
           if(lvl->info[xxsur+camx][yysur+camy] == 14)symbol_amount[4]--;
           draw_sprite(lvl->bmp, kocka_cista, (xxsur+camx)*FIELD_SIZE, (yysur+camy)*FIELD_SIZE);           
           lvl->info[xxsur+camx][yysur+camy] = 8;
           rest(120);              
          }
          
          
          //printf("<%d %d>\n", xxsur, yysur);                   
         }
        }
        
        //rect(mb, 400-300, 300-240, 400+300, 300+240,0xff0000);
       }
    if(new_wnd->visible == 1)
    {
		 draw_wind(new_wnd, mb);
		 draw_numbox(mb, ww, new_wnd->x+65, new_wnd->y+50, 60, 15); 										
		 draw_numbox(mb, hhh, new_wnd->x+65, new_wnd->y+75, 60, 15);
		 draw_textbox(mb, project_name, new_wnd);
		 draw_buttons(new_wnd, mb);
		 manage_window(new_wnd);
	  }
    
    
    /*if(window->visible)
    {
      if(window->cnvs->redraw)
      {
        draw_canvas(window,window->bmp);
        window->cnvs->redraw = 0;
      }
      if(!window->cnvs->redraw && mode != MODE_TOOL_TRANSFORM)
      {
        blit(window->cnvs->bmp, mb, 0,0, window->x+window->cnvs->x, window->y+window->cnvs->y, window->x+window->cnvs->x+window->cnvs->w, window->y+window->cnvs->y+window->cnvs->h);
      }
      draw_wind(window, mb);
      if(!window->cnvs->redraw && mode == MODE_TOOL_TRANSFORM)
      {
        blit(window->cnvs->bmp, mb, 0,0, window->x+window->cnvs->x, window->y+window->cnvs->y, window->x+window->cnvs->x+window->cnvs->w, window->y+window->cnvs->y+window->cnvs->h);
        //blit(mywind->cnvs->bmp, mb, 0,0, mywind->x+mywind->cnvs->x, mywind->y+mywind->cnvs->y, mywind->x+mywind->cnvs->x+mywind->cnvs->w, mywind->y+mywind->cnvs->y+mywind->cnvs->h);
      }
      manage_window(window);
    }*/
      
    /*if(windowzwei->visible)
      draw_wind(windowzwei, mb);*/
    if(fm_wnd->visible == 1)
    {
		 draw_wind(fm_wnd, mb);
     draw_buttons(fm_wnd, mb);
		 manage_window(fm_wnd); 									 
		}
		
		
		if(insert_text_wnd->visible)
    {
      draw_wind(insert_text_wnd, mb);
      draw_buttons(insert_text_wnd, mb);
      draw_textbox(mb,ittbox, insert_text_wnd);
      draw_list(mb,listt,insert_text_wnd);
      draw_ninja(nnlist, mb, 100 + insert_text_wnd->x, 30+insert_text_wnd->y);
      manage_window(insert_text_wnd); 
    }
    
    alfont_set_font_size(larabie, 15);
    draw_set_texture(mb);
    
    if(credits_wnd->visible)
    {
	   draw_wind(credits_wnd, mb); 						
     draw_buttons(credits_wnd, mb);
     manage_window(credits_wnd);
	  }
    
    if(type_wnd->visible == 1)
    {
     draw_wind(type_wnd, mb);
     draw_buttons(type_wnd, mb);
     manage_window(type_wnd);
    }
    
    if(save_as_wnd->visible == 1)
    {
     draw_wind(save_as_wnd, mb);
     draw_filebrowser(mb, fbsave, save_as_wnd);
     draw_buttons(save_as_wnd, mb);
     draw_textbox(mb, fnametbox, save_as_wnd);
     //draw_list(mb, formatt, save_as_wnd);
   //  hh = now;
   //  before = hh;    
     //before = now;
	//	 now = formatt->units[formatt->cpoi]->value;
     //if(now == before){}
     //else fbsave->refresh = 1;
     //printf("\nbefore = %d <> now = %d\n", before, now);
     
     
     //alfont_textprintf_right_aa(mb, larabie, save_as_wnd->x + 48, 270+save_as_wnd->y, 0xffffff, "Format:");
     alfont_textprintf_right_aa(mb, larabie, save_as_wnd->x + 48, 250+save_as_wnd->y, 0xffffff, "Meno:");
     manage_window(save_as_wnd);
    }
    
    if(open_wnd->visible == 1)
    {
     draw_wind(open_wnd, mb);
     draw_filebrowser(mb, fbopen, open_wnd);
     draw_buttons(open_wnd, mb);
     draw_textbox(mb, fnametboxo, open_wnd);
     //draw_list(mb, formatto, open_wnd);
     hh = now;
     before = hh;    
     //before = now;
	/*	 now = formatto->units[formatto->cpoi]->value;
     if(now == before){}
     else fbopen->refresh = 1;*/
     //printf("\nbefore = %d <> now = %d\n", before, now);
     
     
     //alfont_textprintf_right_aa(mb, larabie, open_wnd->x + 48, 270+open_wnd->y, 0xffffff, "Format:");
     alfont_textprintf_right_aa(mb, larabie, open_wnd->x + 48, 250+open_wnd->y, 0xffffff, "Meno:");
     manage_window(open_wnd);
    }
    
    
    
    //if(window->visible)
      //manage_window(window);
    //draw_toolbar(mb);
    rectfill(mb, 0, SCREEN_H-20, SCREEN_W, SCREEN_H, makecol(60,60,60));
    if(menu->smh[0]->rolled == 0)draw_desc(mb);
    //draw_qbar(mb);
    //alfont_textprintf(mb,larabie,100,60,0xffffff,"%d",window->btns->x);
    alfont_set_font_size(larabie, 16);
    //draw_menu(mb);//musi byt ako jedna z poslednych volanych funkcii z vykreslovacieho dovodu
    
   	
   	
   	draw_mmh(menu,mb);
   	//toto je ta najvecsia zbtocnost z celeho programu, vymazte to niekto!
    blit(mb, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
    //if(quit == true)
      //close_button_pressed = TRUE;
      //printf("\549");
  }
  deinit();
}
END_OF_MAIN()

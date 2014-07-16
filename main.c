#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#define alto 800
#define ancho 900
#define tamanotecla 16.8
const float FPS = 60;
int inicializar();
void createcellmodel();
void creatmenu();
void mousemenu();
void reproducir (char * cancion,int onoff);
void imagen(char * imagen);
void savepantallas(char save);
void cargarpantalla();
void creatmensaje(int tl);
void writeme (int tls);
void mouseMP3();
int createword(char letra);
void showit(int renglon);
int counter ();
int borrartxt(int renglon);
int nextword(int renglon);
int counterrenglon(int renglon);
int diccionario (int renglon);
void mousepantalla();
void getword (int renglon,int borrar);


 ALLEGRO_DISPLAY *janela= NULL;
 ALLEGRO_BITMAP *bouncer = NULL;
 ALLEGRO_EVENT_QUEUE *event_queue = NULL;
 ALLEGRO_TIMER *timer = NULL;

 bool redraw=true;

void main()
{

  inicializar();



   createcellmodel();


   creatmenu();




   al_destroy_display(janela);

}



int inicializar()
{
    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return false;
    }


    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "failed to create primitives!\n");
        return false;
    }


    if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    janela = al_create_display(ancho, alto);
    if (!janela)
    {
        fprintf(stderr, "failed to create display!\n");
        return false;
    }



    timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }



   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(janela);
      al_destroy_timer(timer);
      return -1;
    }

         if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }

    al_clear_to_color(al_map_rgb(0, 0, 255));
    al_flip_display();
     bouncer = al_create_bitmap(10,10);
   if(!bouncer)
    {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(janela);
      al_destroy_timer(timer);
      return -1;
   }



if(!al_init_image_addon()) {
      al_show_native_message_box(janela, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
            }


    return true;
}

void createcellmodel()
{
    ALLEGRO_COLOR carcasa=al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR bdisplay=al_map_rgb(255,0, 255);
    ALLEGRO_COLOR black=al_map_rgb(0,0,0);

  al_draw_line(ancho/2-100,alto/3,ancho/2-100,(alto/3)*2,carcasa,3.0);
  al_draw_line(ancho/2+100,alto/3,ancho/2+100,(alto/3)*2,carcasa,3.0);
  al_draw_arc((ancho/2)-50,((alto/3)*2)-10,50,-ALLEGRO_PI,-ALLEGRO_PI/2,carcasa,3.0);
  al_draw_arc((ancho/2)+50,((alto/3)*2)-10,50,0,ALLEGRO_PI/2,carcasa,3.0);
  al_draw_arc((ancho/2)-50,((alto/3)),50,-ALLEGRO_PI,ALLEGRO_PI/2,carcasa,3.0);
  al_draw_arc((ancho/2)+50,((alto/3)),50,0,-ALLEGRO_PI/2,carcasa,3.0);
  al_draw_line(ancho/2-50,(alto/3)-50,ancho/2+50,(alto/3)-50,carcasa,3.0);
  al_draw_line(ancho/2-50,(alto/3)*2+40,ancho/2+50,(alto/3)*2+40,carcasa,3.0);
  al_draw_rectangle((ancho/2)-85,(alto/3)*2,(ancho/2)+85,(alto/3),bdisplay,3.0);
  al_draw_filled_rectangle((ancho/2)-84,(alto/3)*2-2,(ancho/2)+82,(alto/3),black);
  al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay);


  al_flip_display();
}


void creatmenu()
{
        ALLEGRO_COLOR bdisplay=al_map_rgb(255,0, 255);
        ALLEGRO_FONT *font = al_load_ttf_font("Cargo.ttf",15,0 );
        ALLEGRO_COLOR black=al_map_rgb(0,0,0);
   if (!font)
      fprintf(stderr, "Could not load 'Cargo.ttf'.\n");


    al_draw_filled_rectangle((ancho/2)-84,(alto/3)*2-2,(ancho/2)+82,(alto/3),black);
    cargarpantalla();
    al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay,3.0);
    al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay,3.0);
    al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay,3.0);
    al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (alto/3)+25,ALLEGRO_ALIGN_CENTRE, "MP3");
    al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (alto/3)+20+50+15,ALLEGRO_ALIGN_CENTRE, "mensajes");
    al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (alto/3)+20+50+10+10+55,ALLEGRO_ALIGN_CENTRE, "personalizar");

    mousemenu();
}



void creatmensaje(int tl)
{
    float i,count,count2,j;
    int letras=0;

       char * alfabeto[][37]={"q","w","e","r","t","y","u","i","o","p","a","s","d","f","g","h","j","k","l","Br","z","x","c","v","b","n","m","!",";","$","CR","Tl","My","Espacio",",",".","Dic",
                            "Q","W","E","R","T","Y","U","I","O","P","A","S","D","F","G","H","J","K","L","Br","Z","X","C","V","B","N","M","!",";","$","CR","Tl","My","Espacio",",",".","Dic",
                            "1","2","3","4","5","6","7","8","9","0","-","/",":",";","(",")","|","&","@","Br","+","*","?","!","<",">","#","|","=","~","CR","Tl","My","Espacio",",",".","Dic"};






        ALLEGRO_COLOR bdisplay=al_map_rgb(255,0, 255);
        ALLEGRO_FONT *font1 = al_load_ttf_font("Blissful.ttf",11,0 );
        ALLEGRO_COLOR black=al_map_rgb(0,0,0);

        if (!font1)
      fprintf(stderr, "Could nott load Cargo.ttf.\n");



        al_draw_filled_rectangle((ancho/2)-84,(alto/3)*2-2,(ancho/2)+82,(alto/3),black);
        cargarpantalla();
        al_draw_filled_rectangle((ancho/2)-84,(alto/3)*2-2,(ancho/2)+82,(alto/3),black);
        for(j=0,count2=0;count2<=4;j-=tamanotecla,count2++)
            al_draw_line(ancho/2-84,((2*alto)/3)+j,ancho/2+84,((2*alto/3))+j,bdisplay,3.0);
        for(i=0,count=0;count<=10;i+=tamanotecla,count++)
            al_draw_line(ancho/2-84+i,((2*alto)/3)-tamanotecla,ancho/2-84+i,((2*alto/3))-tamanotecla*4,bdisplay,3.0);
        for(i=0,count=0;count<=2;i+=tamanotecla,count++)
        al_draw_line(ancho/2-84+tamanotecla+i,((2*alto)/3),ancho/2-84+tamanotecla+i,((2*alto/3))-tamanotecla,bdisplay,3.0);
        al_draw_line(ancho/2-84+7*tamanotecla,((2*alto)/3),ancho/2-84+7*tamanotecla,((2*alto/3))-tamanotecla,bdisplay,3.0);
        for(i=0,count=0;count<=2;i+=tamanotecla,count++)
            al_draw_line((ancho/2-84)+8*tamanotecla+i,((2*alto)/3),ancho/2-84+8*tamanotecla+i,((2*alto/3))-tamanotecla,bdisplay,3.0);

            fprintf(stderr, "letra=%s\n",alfabeto[0][0]);
            fprintf(stderr, "letra=%s\n",alfabeto[0][1]);
            fprintf(stderr, "letra=%s\n",alfabeto[0][2]);
            fprintf(stderr, "letra=%s\n",alfabeto[1][0]);

            for(j=0,count2=0;count2<=2;j--,count2++)
            for(i=0,count=0;count<=9;i++,count++,letras++)
        al_draw_text(font1, al_map_rgb(255,255,255), ancho/2-76+(tamanotecla*i), ((2*alto/3)-65.2)-j*tamanotecla,ALLEGRO_ALIGN_CENTRE, alfabeto[tl][letras]);

            for(i=0,count=0;count<=2;i++,count++,letras++)
        al_draw_text(font1, al_map_rgb(255,255,255), ancho/2-76+(tamanotecla*i), ((2*alto/3)-65.2)-j*tamanotecla,ALLEGRO_ALIGN_CENTRE, alfabeto[tl][letras]);
        al_draw_text(font1, al_map_rgb(255,255,255), ancho/2, ((2*alto/3)-65.2)-j*tamanotecla,ALLEGRO_ALIGN_CENTER, alfabeto[tl][letras]);
        letras++;
            for(i=0,count=0;count<=2;i++,count++,letras++)
        al_draw_text(font1, al_map_rgb(255,255,255), ancho/2-76+(tamanotecla*i)+7*tamanotecla, ((2*alto/3)-65.2)-j*tamanotecla,ALLEGRO_ALIGN_CENTRE, alfabeto[tl][letras]);
        for(j=0;j!=9;++j)
            {
                showit(j);
            }
        writeme (tl);

}



void createMP3()
{
    ALLEGRO_COLOR black=al_map_rgb(0,0,0);
    ALLEGRO_COLOR bdisplay=al_map_rgb(255,0, 255);
    ALLEGRO_FONT *font = al_load_ttf_font("Cargo.ttf",15,0 );
    ALLEGRO_COLOR stop=al_map_rgb(255,0, 0);



    al_draw_filled_rectangle((ancho/2)-84,(alto/3)*2-2,(ancho/2)+82,(alto/3),black);
    cargarpantalla();
    al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay,3.0);
    al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay,3.0);
    al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay,3.0);
    al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (alto/3)+25,ALLEGRO_ALIGN_CENTRE, "Agustina");
    al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (alto/3)+20+50+15,ALLEGRO_ALIGN_CENTRE, "Gabriel");
    al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (alto/3)+20+50+10+10+55,ALLEGRO_ALIGN_CENTRE, "Martin");
    al_draw_filled_rectangle((ancho/2)-84,(2*alto/3)-3,(ancho/2)+83,(2*alto/3)-50,stop);
    al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (2*alto/3)-35,ALLEGRO_ALIGN_CENTRE, "STOP");
    mouseMP3();
}


void createpantalla()
{
    ALLEGRO_COLOR black=al_map_rgb(0,0,0);
    ALLEGRO_COLOR bdisplay=al_map_rgb(255,0, 255);
    ALLEGRO_FONT *font = al_load_ttf_font("Cargo.ttf",15,0 );


    al_draw_filled_rectangle((ancho/2)-84,(alto/3)*2-2,(ancho/2)+82,(alto/3),black);
    cargarpantalla();
    al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay,3.0);
    al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay,3.0);
    al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay,3.0);
    al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (alto/3)+25,ALLEGRO_ALIGN_CENTRE, "Agustina");
    al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (alto/3)+20+50+15,ALLEGRO_ALIGN_CENTRE, "Gabriel");
    al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (alto/3)+20+50+10+10+55,ALLEGRO_ALIGN_CENTRE, "Martin");
    mousepantalla();
}


void mousemenu()
{
    float mark=1;
    ALLEGRO_COLOR bdisplay=al_map_rgb(0,0, 255);
    ALLEGRO_COLOR bdisplay1=al_map_rgb(255,0, 255);

    ALLEGRO_COLOR white=al_map_rgb(255,255, 255);
    if (mark==1)
          {
            al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,white,3.0);
            al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);
          }


    al_register_event_source(event_queue, al_get_display_event_source(janela));


    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_keyboard_event_source());


al_start_timer(timer);


ALLEGRO_MOUSE_STATE state;
al_get_mouse_state(&state);
    while(1)
   {



     ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
      }
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if((ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP))
      {

       if((ev.mouse.x>=(ancho/2)-15)&&(ev.mouse.x<=(ancho/2)+15)&&(ev.mouse.y>=((alto/3)*2)+5)&&(ev.mouse.y<=((alto/3)*2)+35))
      {
        creatmenu();
      }
      else if((ev.mouse.x>=(ancho/2)-75)&&(ev.mouse.x<=(ancho/2)+75)&&(ev.mouse.y>=(alto/3)+20)&&(ev.mouse.y<=((alto/3)+70)))
      {
        al_draw_filled_rectangle((ancho/2)-75,(alto/3)+50,(ancho/2)+75,(alto/3)+70,bdisplay);
        al_flip_display();
        al_rest(0.3);
        createMP3();
      }
      else if(ev.mouse.x>=(ancho/2)-75&&(ev.mouse.x<=(ancho/2)+75)&&ev.mouse.y>=(alto/3)+20+50+10&&(ev.mouse.y<=((alto/3)+70+50+10)))
      {
        al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay);
        al_flip_display();
        al_rest(0.3);
         creatmensaje(0);
      }

      else if(ev.mouse.x>=(ancho/2)-75&&(ev.mouse.x<=(ancho/2)+75)&&ev.mouse.y>=(alto/3)+20+50+10+10+50&&(ev.mouse.y<=((alto/3)+70+50+10+10+50)))
      {
        al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay);
        al_flip_display();
        al_rest(0.3);
        createpantalla();
      }
      }
      if(ev.type == ALLEGRO_EVENT_KEY_UP)
      {
        if(mark>=1&&mark<=4)
        switch(ev.keyboard.keycode)
         {
            case ALLEGRO_KEY_UP:
            mark--;
            break;
            case ALLEGRO_KEY_DOWN:
            mark++;
         }
         if (mark==1||mark<1)
         {
             mark=1;
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay1,3.0);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay1,3.0);
            al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);
              al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,white,3.0);
             al_flip_display();
             if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER){
                al_draw_filled_rectangle((ancho/2)-75,(alto/3)+50,(ancho/2)+75,(alto/3)+70,bdisplay);
                al_flip_display();
                al_rest(0.3);
                createMP3();
             }

         }
         else if(mark==2)
         {
             al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay1,3.0);
              al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay1,3.0);
              al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);
             al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,white,3.0);
            al_flip_display();
            if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER){
            al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay);
            al_flip_display();
            al_rest(0.3);
            creatmensaje(0);
            }
         }
         else if(mark==3)
         {
            mark=3;
            al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay1,3.0);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay1,3.0);
            al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,white,3.0);
            al_flip_display();
            if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER){
                al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay);
                al_flip_display();
                al_rest(0.3);
                createpantalla();
            }
         }
         else if(mark==4||mark>4)
         {
            mark=4;
            al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay1,3.0);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay1,3.0);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay1,3.0);
            al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,white);
            if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
                creatmenu();

         }
      }
        if(redraw && al_is_event_queue_empty(event_queue))
         redraw = false;
         al_flip_display();
      }
   al_destroy_display(janela);


}

void mouseMP3()
{
  int loop=1;
  static float mark=1;
  ALLEGRO_COLOR bdisplay=al_map_rgb(0,0, 255);
    ALLEGRO_COLOR stoped=al_map_rgb(0,255, 0);
    ALLEGRO_COLOR bdisplay1=al_map_rgb(255,0, 255);
    ALLEGRO_COLOR white=al_map_rgb(255,255, 255);
    ALLEGRO_COLOR xxx=al_map_rgb(229,215,93);
      if (mark==1)
          al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,white,3.0);
          else if(mark==2)
          al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,white,3.0);
          else if(mark==3)
          al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,white,3.0);
          else if(mark==4)
            al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,white);
    ALLEGRO_FONT *font = al_load_ttf_font("Cargo.ttf",15,0 );
      if (!font)
      fprintf(stderr, "Could not load 'Cargo.ttf'.\n");
    al_install_audio();
	al_init_acodec_addon();

    al_register_event_source(event_queue, al_get_display_event_source(janela));


    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_keyboard_event_source());


al_start_timer(timer);



ALLEGRO_MOUSE_STATE state;
al_get_mouse_state(&state);
    while(1)
   {

      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
      }
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        al_destroy_display(janela);
      }
      else if((ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP))
      {

       if((ev.mouse.x>=(ancho/2)-15)&&(ev.mouse.x<=(ancho/2)+15)&&(ev.mouse.y>=((alto/3)*2)+5)&&(ev.mouse.y<=((alto/3)*2)+35))
      {
        creatmenu();

      }
      else if((ev.mouse.x>=(ancho/2)-75)&&(ev.mouse.x<=(ancho/2)+75)&&(ev.mouse.y>=(alto/3)+20)&&(ev.mouse.y<=((alto/3)+70)))
      {
          mark=1;
        reproducir ("C",0);
        al_draw_filled_rectangle((ancho/2)-75,(alto/3)+50,(ancho/2)+75,(alto/3)+70,bdisplay);
        al_flip_display();
        al_rest(0.3);
        reproducir("barbie.wav",1);
        createMP3();
      }

       else if(ev.mouse.x>=(ancho/2)-75&&(ev.mouse.x<=(ancho/2)+75)&&ev.mouse.y>=(alto/3)+20+50+10&&(ev.mouse.y<=((alto/3)+70+50+10)))
      {
        mark=2;
        reproducir ("C",0);
        reproducir("trooper.wav",1);
        al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay);
        al_flip_display();
        al_rest(0.3);
        createMP3();
      }
      else if(ev.mouse.x>=(ancho/2)-75&&(ev.mouse.x<=(ancho/2)+75)&&ev.mouse.y>=(alto/3)+20+50+10+10+50&&(ev.mouse.y<=((alto/3)+70+50+10+10+50)))
      {
        mark=3;
        reproducir ("C",0);
        al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay);
        al_flip_display();
        al_rest(0.3);
        reproducir("mimujer.wav",1);
        createMP3();
      }
      else if(ev.mouse.x>=(ancho/2)-84&&(ev.mouse.x<=(ancho/2)+83)&&ev.mouse.y>=(2*alto/3)-50&&(ev.mouse.y<=((2*alto/3)-3)))
      {
        al_draw_filled_rectangle((ancho/2)-84,(2*alto/3)-3,(ancho/2)+83,(2*alto/3)-50,stoped);
        al_flip_display();
        al_rest(0.3);
        reproducir ("C",0);
        createMP3();

      }

      }

      if(ev.type == ALLEGRO_EVENT_KEY_UP)
      {
        if(mark>=1&&mark<=5)
        switch(ev.keyboard.keycode)
         {
            case ALLEGRO_KEY_UP:
            mark--;
            break;
            case ALLEGRO_KEY_DOWN:
            mark++;
         }
         if (mark==1||mark<1)
         {
             mark=1;
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay1,3.0);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay1,3.0);
            al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);
             al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (2*alto/3)-35,ALLEGRO_ALIGN_CENTRE, "STOP");
              al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,white,3.0);
             al_flip_display();
             if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
              {   reproducir ("C",0);
                  al_draw_filled_rectangle((ancho/2)-75,(alto/3)+50,(ancho/2)+75,(alto/3)+70,bdisplay);
                  al_flip_display();
                  al_rest(0.3);
                  reproducir("barbie.wav",1);
                  createMP3();

              }

         }
         else if(mark==2)
         {
             al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay1,3.0);
              al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay1,3.0);
              al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);
             al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (2*alto/3)-35,ALLEGRO_ALIGN_CENTRE, "STOP");
             al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,white,3.0);
            al_flip_display();
            if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
            {
                reproducir ("C",0);
                al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay);
                al_flip_display();
                al_rest(0.3);
                reproducir("trooper.wav",1);
                createMP3();

            }
         }
         else if(mark==3)
         {
            al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay1,3.0);
             al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay1,3.0);
             al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);
            al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (2*alto/3)-35,ALLEGRO_ALIGN_CENTRE, "STOP");
               al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,white,3.0);
             al_flip_display();
             if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
             {
                 reproducir ("C",0);
                 al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay);
                 al_flip_display();
                 al_rest(0.3);
                 reproducir("mimujer.wav",1);
                 createMP3();

             }
         }
         else if(mark==4)
         {
            al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay1,3.0);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay1,3.0);
            al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);

            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay1,3.0);
            al_draw_text(font, al_map_rgb(000,255,255), ancho/2, (2*alto/3)-35,ALLEGRO_ALIGN_CENTRE, "STOP");
               if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
             {
                al_draw_filled_rectangle((ancho/2)-84,(2*alto/3)-3,(ancho/2)+83,(2*alto/3)-50,stoped);
                al_flip_display();
                al_rest(0.3);
                reproducir ("C",0);
                createMP3();
             }
         }
         else if(mark==5||mark>5)
         {
             mark=5;
             al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay1,3.0);
             al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay1,3.0);
             al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay1,3.0);
             al_draw_text(font, al_map_rgb(255,255,255), ancho/2, (2*alto/3)-35,ALLEGRO_ALIGN_CENTRE, "STOP");
             al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,white);
              if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
             {

                 creatmenu();

             }
         }
      }

        if(redraw && al_is_event_queue_empty(event_queue))
         redraw = false;
         al_flip_display();
      }

}
void reproducir (char * cancion,int onoff)
{
ALLEGRO_SAMPLE *sample = NULL;
    if(onoff==1)
    {
  al_reserve_samples(1);
  sample = al_load_sample(cancion);
        if (!sample)
        printf( "Audio clip sample not loaded!\n" );
        al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

    }
    else
       al_stop_samples();
}

void imagen(char * imagen)
{

        bouncer = al_load_bitmap(imagen);

   if(!bouncer) {
      al_show_native_message_box(janela, "Error", "Error", "Failed to load image!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(janela);
      return -1;
   }

   al_draw_scaled_bitmap(bouncer,0,0,300,168,(ancho/2)-84,alto/3,166,alto/3-2,0);
   al_flip_display();

}


void mousepantalla()
{
  int loop=1;
  ALLEGRO_COLOR bdisplay=al_map_rgb(0,0, 255);
  ALLEGRO_COLOR bdisplay1=al_map_rgb(255,0, 255);
  ALLEGRO_COLOR white=al_map_rgb(255,255, 255);
   static float mark=1;
    if (mark==1||mark==4)
          al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,white,3.0);


    if (mark==1||mark==4)
        {
            mark=1;
            al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,white,3.0);
        }
    else if(mark==2)
        al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,white,3.0);
    else if(mark==3)
        al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,white,3.0);


    al_register_event_source(event_queue, al_get_display_event_source(janela));


    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_keyboard_event_source());


al_start_timer(timer);



ALLEGRO_MOUSE_STATE state;
al_get_mouse_state(&state);
    while(loop)
   {


      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
      }
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        al_destroy_display(janela);
      }
      else if((ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP))
      {

       if((ev.mouse.x>=(ancho/2)-15)&&(ev.mouse.x<=(ancho/2)+15)&&(ev.mouse.y>=((alto/3)*2)+5)&&(ev.mouse.y<=((alto/3)*2)+35))
      {
        al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,white);
        creatmenu();
        loop-=1;
      }
      else if((ev.mouse.x>=(ancho/2)-75)&&(ev.mouse.x<=(ancho/2)+75)&&(ev.mouse.y>=(alto/3)+20)&&(ev.mouse.y<=((alto/3)+70)))
      {
        mark=1;
        savepantallas(1);
        al_draw_filled_rectangle((ancho/2)-75,(alto/3)+50,(ancho/2)+75,(alto/3)+70,bdisplay);
        al_flip_display();
        al_rest(0.3);
        createpantalla();

      }

       else if(ev.mouse.x>=(ancho/2)-75&&(ev.mouse.x<=(ancho/2)+75)&&ev.mouse.y>=(alto/3)+20+50+10&&(ev.mouse.y<=((alto/3)+70+50+10)))
      {
        mark=2;
        savepantallas(2);
        al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay);
        al_flip_display();
        al_rest(0.3);
        createpantalla();
      }
      else if(ev.mouse.x>=(ancho/2)-75&&(ev.mouse.x<=(ancho/2)+75)&&ev.mouse.y>=(alto/3)+20+50+10+10+50&&(ev.mouse.y<=((alto/3)+70+50+10+10+50+10+50)))
      {
        mark=3;
        savepantallas(3);
        al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay);
        al_flip_display();
        al_rest(0.3);
        createpantalla();
      }
      }

       if(ev.type == ALLEGRO_EVENT_KEY_UP)
      {

        if(mark>=1&&mark<=4)
        switch(ev.keyboard.keycode)
         {
            case ALLEGRO_KEY_UP:
            mark--;
            break;
            case ALLEGRO_KEY_DOWN:
            mark++;
         }
         if (mark==1||mark<1)
         {
             mark=1;
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay1,3.0);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay1,3.0);
            al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);
              al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,white,3.0);

             if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
             {
                savepantallas(1);
                al_draw_filled_rectangle((ancho/2)-75,(alto/3)+50,(ancho/2)+75,(alto/3)+70,bdisplay);
                al_flip_display();
                al_rest(0.3);
                createpantalla();


             }

         }
         else if(mark==2)
         {
             al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay1,3.0);
              al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay1,3.0);
              al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);
             al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,white,3.0);

            if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
            {
                savepantallas(2);
                al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay);
                al_flip_display();
                al_rest(0.3);
                createpantalla();

            }
         }
         else if(mark==3)
         {
            mark=3;
            al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay1,3.0);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay1,3.0);
            al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,bdisplay1);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,white,3.0);


            if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
               {savepantallas(3);
                al_draw_filled_rectangle((ancho/2)-75,(alto/3)+20+80+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay);
                al_flip_display();
                al_rest(0.3);
                createpantalla();

                }
         }
         else if(mark==4||mark>4)
         {
            mark=4;
            al_draw_rectangle((ancho/2)-75,(alto/3)+20,(ancho/2)+75,(alto/3)+70,bdisplay1,3.0);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10,(ancho/2)+75,(alto/3)+70+50+10,bdisplay1,3.0);
            al_draw_rectangle((ancho/2)-75,(alto/3)+20+50+10+10+50,(ancho/2)+75,(alto/3)+70+50+10+10+50,bdisplay1,3.0);
            al_draw_filled_circle(ancho/2,((alto/3)*2)+20,15.0,white);
            if(ev.type == ALLEGRO_EVENT_KEY_UP&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
                creatmenu();

         }
      }

        if(redraw && al_is_event_queue_empty(event_queue))
         redraw = false;
         al_flip_display();
      }

}

void savepantallas(char save)
{
    FILE * pantalla;

    fprintf(stderr,"save=%d",save);

    pantalla=fopen("pantalla.txt","w+");
    fprintf(pantalla,"%d",save);

    fclose(pantalla);

}

void cargarpantalla()
{
    FILE * pantalla;
    char c;


    pantalla=fopen("pantalla.txt","r");

    c=fgetc(pantalla);
    switch(c)
    {
        case '1' :
        imagen("humo.png");
        break;
        case '2' :
        imagen("soldado.png");
        break;
        case '3' :
        imagen("leon.png");
        break;
    }

}


void writeme (int tls)
{

    int loop=1,renglon=0,j=0;
    ALLEGRO_COLOR bdisplay=al_map_rgb(0,0, 255);
    ALLEGRO_COLOR stoped=al_map_rgb(0,255, 0);
    ALLEGRO_FONT *font1 = al_load_ttf_font("Blissful.ttf",15,0 );
    FILE * pantalla;
    int tl=tls;
    char mensaje[]= "mensaje0.txt";

    char palabra;


    al_register_event_source(event_queue, al_get_display_event_source(janela));


    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_keyboard_event_source());


al_start_timer(timer);



ALLEGRO_MOUSE_STATE state;
al_get_mouse_state(&state);
    while(1)
   {


      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
         redraw = true;


      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            for(;renglon>=0;--renglon){
         mensaje[7]=renglon+'0';
         pantalla=fopen(mensaje,"w+");
         j=remove(mensaje);
         if(j==0)
            fprintf(stderr, "Error: unable to delete the file\n");
         fclose(pantalla);
         if(j==0)
            fprintf(stderr, "Error: unable to delete the file\n");
         }
            counter(0);

        al_destroy_display(janela);
      }

      else if((ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP))
      {


    if(ev.mouse.y>=((2*alto)/3)-(tamanotecla*4)&&(ev.mouse.y<=((2*alto/3)-(tamanotecla*(3)))))

      {
       if(ev.mouse.x>=ancho/2-84&&(ev.mouse.x<=ancho/2-84+tamanotecla)){
          switch(tl)
         {

        case 0: renglon=createword('q');
                break;
        case 1: renglon=createword('Q');
                break;
        default: renglon=createword('1');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla&&(ev.mouse.x<=ancho/2-84+tamanotecla*2)){
        switch(tl)
         {

        case 0: renglon=createword('w');
                break;
        case 1: renglon=createword('W');
                break;
        default: renglon=createword('2');
                break;
         }
      }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*2&&(ev.mouse.x<=ancho/2-84+tamanotecla*3)){
         switch(tl)
         {

        case 0: renglon=createword('e');
                break;
        case 1: renglon=createword('E');
                break;
        default: renglon=createword('3');
                break;
         }
      }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*3&&(ev.mouse.x<=ancho/2-84+tamanotecla*4)){
         switch(tl)
         {

        case 0: renglon=createword('r');
                break;
        case 1: renglon=createword('R');
                break;
        default: renglon=createword('4');
                break;
         }
      }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*4&&(ev.mouse.x<=ancho/2-84+tamanotecla*5)){
         switch(tl)
         {

        case 0: renglon=createword('t');
                break;
        case 1: renglon=createword('T');
                break;
        default: renglon=createword('5');
                break;
         }
      }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*5&&(ev.mouse.x<=ancho/2-84+tamanotecla*6)){
         switch(tl)
         {

        case 0: renglon=createword('y');
                break;
        case 1: renglon=createword('Y');
                break;
        default: renglon=createword('6');
                break;
         }
          }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*6&&(ev.mouse.x<=ancho/2-84+tamanotecla*7)){
         switch(tl)
         {

        case 0: renglon=createword('u');
                break;
        case 1: renglon=createword('U');
                break;
        default: renglon=createword('7');
                break;
         }
          }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*7&&(ev.mouse.x<=ancho/2-84+tamanotecla*8)){
         switch(tl)
         {

        case 0: renglon=createword('i');
                break;
        case 1: renglon=createword('I');
                break;
        default: renglon=createword('8');
                break;
         }
          }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*8&&(ev.mouse.x<=ancho/2-84+tamanotecla*9)){
         switch(tl)
         {

        case 0: renglon=createword('o');
                break;
        case 1: renglon=createword('O');
                break;
        default: renglon=createword('9');
                break;
         }
          }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*9&&(ev.mouse.x<=ancho/2-84+tamanotecla*10))
         switch(tl)
         {

        case 0: renglon=createword('p');
                break;
        case 1: renglon=createword('P');
                break;
        default: renglon=createword('0');
                break;
         }
          }


    else if(ev.mouse.y>=((2*alto)/3)-(tamanotecla*3)&&(ev.mouse.y<=((2*alto/3)-(tamanotecla*(2)))))
        {

       if(ev.mouse.x>=ancho/2-84&&(ev.mouse.x<=ancho/2-84+tamanotecla)){
         switch(tl)
         {

        case 0: renglon=createword('a');
                break;
        case 1: renglon=createword('A');
                break;
        default: renglon=createword('-');
                break;
         }

       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla&&(ev.mouse.x<=ancho/2-84+tamanotecla*2)){
         switch(tl)
         {

        case 0: renglon=createword('s');
                break;
        case 1: renglon=createword('S');
                break;
        default: renglon=createword('/');
                break;
         }

       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*2&&(ev.mouse.x<=ancho/2-84+tamanotecla*3)){
         switch(tl)
         {

        case 0: renglon=createword('d');
                break;
        case 1: renglon=createword('D');
                break;
        default: renglon=createword(':');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*3&&(ev.mouse.x<=ancho/2-84+tamanotecla*4)){
         switch(tl)
         {

        case 0: renglon=createword('f');
                break;
        case 1: renglon=createword('F');
                break;
        default: renglon=createword(';');
                break;
         }

       }
       if(ev.mouse.x>=ancho/2-84+tamanotecla*4&&(ev.mouse.x<=ancho/2-84+tamanotecla*5)){
         switch(tl)
         {

        case 0: renglon=createword('g');
                break;
        case 1: renglon=createword('G');
                break;
        default: renglon=createword('(');

                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*5&&(ev.mouse.x<=ancho/2-84+tamanotecla*6)){
         switch(tl)
         {

        case 0: renglon=createword('h');
                break;
        case 1: renglon=createword('H');
                break;
        default: renglon=createword(')');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*6&&(ev.mouse.x<=ancho/2-84+tamanotecla*7)){
         switch(tl)
         {

        case 0: renglon=createword('j');
                break;
        case 1: renglon=createword('J');
                break;
        default: renglon=createword('¿');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*7&&(ev.mouse.x<=ancho/2-84+tamanotecla*8)){
         switch(tl)
         {

        case 0: renglon=createword('k');
                break;
        case 1: renglon=createword('K');
                break;
        default: renglon=createword('&');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*8&&(ev.mouse.x<=ancho/2-84+tamanotecla*9)){
         switch(tl)
         {

        case 0: renglon=createword('l');
                break;
        case 1: renglon=createword('L');
                break;
        default: renglon=createword('@');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*9&&(ev.mouse.x<=ancho/2-84+tamanotecla*10)){
        renglon=borrartxt(renglon);
        fprintf(stderr, "Error: unable to delete the file\n");
       }

        }
    else if(ev.mouse.y>=((2*alto)/3)-(tamanotecla*2)&&(ev.mouse.y<=((2*alto/3)-(tamanotecla*(1)))))

        {

       if(ev.mouse.x>=ancho/2-84&&(ev.mouse.x<=ancho/2-84+tamanotecla)){
         switch(tl)
         {

        case 0: renglon=createword('z');
                break;
        case 1: renglon=createword('Z');
                break;
        default: renglon=createword('+');
                break;
         }
        }

       if(ev.mouse.x>=ancho/2-84+tamanotecla&&(ev.mouse.x<=ancho/2-84+tamanotecla*2)){
         switch(tl)
         {

        case 0: renglon=createword('x');
                break;
        case 1: renglon=createword('X');
                break;
        default: renglon=createword('*');
                break;
         }

       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*2&&(ev.mouse.x<=ancho/2-84+tamanotecla*3)){
         switch(tl)
         {

        case 0: renglon=createword('c');
                break;
        case 1: renglon=createword('C');
                break;
        default: renglon=createword('?');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*3&&(ev.mouse.x<=ancho/2-84+tamanotecla*4)){
         switch(tl)
         {

        case 0: renglon=createword('v');
                break;
        case 1: renglon=createword('V');
                break;
        default: renglon=createword('!');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*4&&(ev.mouse.x<=ancho/2-84+tamanotecla*5)){
         switch(tl)
         {

        case 0: renglon=createword('b');
                break;
        case 1: renglon=createword('B');
                break;
        default: renglon=createword('<');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*5&&(ev.mouse.x<=ancho/2-84+tamanotecla*6)){
         switch(tl)
         {

        case 0: renglon=createword('n');
                break;
        case 1: renglon=createword('N');
                break;
        default: renglon=createword('>');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*6&&(ev.mouse.x<=ancho/2-84+tamanotecla*7)){
         switch(tl)
         {

        case 0: renglon=createword('m');
                break;
        case 1: renglon=createword('M');
                break;
        default: renglon=createword('#');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*7&&(ev.mouse.x<=ancho/2-84+tamanotecla*8)){
        renglon=createword('!');

       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*8&&(ev.mouse.x<=ancho/2-84+tamanotecla*9)){

         switch(tl)
         {

        case 0: renglon=createword(';');
                break;
        case 1: renglon=createword(';');
                break;
        default: renglon=createword('=');
                break;
         }
       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*9&&(ev.mouse.x<=ancho/2-84+tamanotecla*10)){
         switch(tl)
         {

        case 0: renglon=createword('$');
                break;
        case 1: renglon=createword('$');
                break;
        default: renglon=createword('~');
                break;
         }
        }
        }

    else if(ev.mouse.y>=((2*alto)/3)-(tamanotecla*1)&&(ev.mouse.y<=((2*alto/3)-(tamanotecla*(0)))))

        {

      if(ev.mouse.x>=ancho/2-84&&(ev.mouse.x<=ancho/2-84+tamanotecla)){
          renglon=counter(1);


      }
       if(ev.mouse.x>=ancho/2-84+tamanotecla&&(ev.mouse.x<=ancho/2-84+tamanotecla*2)){
          creatmensaje(2);

       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*2&&(ev.mouse.x<=ancho/2-84+tamanotecla*3)){
          creatmensaje(1);

       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*3&&(ev.mouse.x<=ancho/2-84+tamanotecla*7)){
          createword(' ');

       }

       if(ev.mouse.x>=ancho/2-84+tamanotecla*7&&(ev.mouse.x<=ancho/2-84+tamanotecla*8)){
          createword(',');

       }
       if(ev.mouse.x>=ancho/2-84+tamanotecla*8&&(ev.mouse.x<=ancho/2-84+tamanotecla*9)){
          createword('.');

       }

        if(ev.mouse.x>=ancho/2-84+tamanotecla*9&&(ev.mouse.x<=ancho/2-84+tamanotecla*10)){
          fprintf(stderr, "failed to create timer!  Dic\n");
          diccionario(renglon);
       }
       }






        else if((ev.mouse.x>=(ancho/2)-15)&&(ev.mouse.x<=(ancho/2)+15)&&(ev.mouse.y>=((alto/3)*2)+5)&&(ev.mouse.y<=((alto/3)*2)+35))
      {

        for(;renglon>=0;--renglon){

         mensaje[7]=renglon+'0';
         pantalla=fopen(mensaje,"w+");
         j=remove(mensaje);
         if(j==0)
            fprintf(stderr, "Error: unable to delete the file\n");
         fclose(pantalla);
         }

        counter(0);
        creatmenu();
      }
    }


 if(ev.type == ALLEGRO_EVENT_KEY_UP)   /*si se solto una tecla de teclado entro a un analizador que identifica que tecla fue apretada*/
        {


               switch(ev.keyboard.keycode)

        {
            case ALLEGRO_KEY_Q:
             switch(tl)

         {

        case 0: renglon=createword('q');
                break;
        case 1: renglon=createword('Q');
                break;
        default: renglon=createword('-');
                break;
         }
               break;
        case ALLEGRO_KEY_SPACE:
            renglon=createword(' ');
                break;
             case ALLEGRO_KEY_ENTER:
           renglon=counter(1);
                break;
        case ALLEGRO_KEY_BACKSPACE:
            renglon=borrartxt(renglon);
        break;

            case ALLEGRO_KEY_W:
            switch(tl)

         {

        case 0: renglon=createword('w');
                break;

        case 1: renglon=createword('W');
                break;
        default: renglon=createword('2');
                break;
         }
               break;
            case ALLEGRO_KEY_E:
             switch(tl)
         {

        case 0: renglon=createword('e');
                break;
        case 1: renglon=createword('E');
                break;
        default: renglon=createword('3');
                break;
         }
               break;
            case ALLEGRO_KEY_R:
             switch(tl)
         {

        case 0: renglon=createword('r');
                break;
        case 1: renglon=createword('R');
                break;
        default: renglon=createword('4');
                break;
         }
               break;
            case ALLEGRO_KEY_T:
              switch(tl)
         {

        case 0: renglon=createword('t');
                break;
        case 1: renglon=createword('T');
                break;
        default: renglon=createword('5');
                break;
         }
               break;


            case ALLEGRO_KEY_Y:
          switch(tl)
         {

        case 0: renglon=createword('y');
                break;
        case 1: renglon=createword('Y');
                break;
        default: renglon=createword('6');
                break;
         }
               break;
            case ALLEGRO_KEY_U:
             switch(tl)
         {

        case 0: renglon=createword('u');
                break;
        case 1: renglon=createword('U');
                break;
        default: renglon=createword('7');
                break;
         }
               break;

            case ALLEGRO_KEY_I:
             switch(tl)
         {

        case 0: renglon=createword('i');
                break;
        case 1: renglon=createword('I');
                break;
        default: renglon=createword('8');
                break;
         }
               break;
            case ALLEGRO_KEY_O:
             switch(tl)
         {

        case 0: renglon=createword('o');
                break;
        case 1: renglon=createword('O');
                break;
        default: renglon=createword('9');
                break;
         }
               break;

            case ALLEGRO_KEY_P:
            switch(tl)
         {

        case 0: renglon=createword('p');
                break;
        case 1: renglon=createword('P');
                break;
        default: renglon=createword('0');
                break;
         }
               break;
            case ALLEGRO_KEY_A:
            switch(tl)
         {

        case 0: renglon=createword('a');
                break;
        case 1: renglon=createword('A');
                break;
        default: renglon=createword('-');
                break;
         }
               break;

            case ALLEGRO_KEY_S:
            switch(tl)
         {

        case 0: renglon=createword('s');
                break;
        case 1: renglon=createword('S');
                break;
        default: renglon=createword('/');
                break;
         }
               break;
            case ALLEGRO_KEY_D:
             switch(tl)
         {

        case 0: renglon=createword('d');
                break;
        case 1: renglon=createword('D');
                break;
        default: renglon=createword(':');
                break;
         }
               break;


            case ALLEGRO_KEY_F:
           switch(tl)
         {

        case 0: renglon=createword('f');
                break;
        case 1: renglon=createword('F');
                break;
        default: renglon=createword(';');
                break;
         }
               break;

            case ALLEGRO_KEY_G:
            switch(tl)
         {

        case 0: renglon=createword('g');
                break;
        case 1: renglon=createword('G');
                break;
        default: renglon=createword('(');

                break;
         }
               break;

            case ALLEGRO_KEY_H:
            switch(tl)
         {

        case 0: renglon=createword('h');
                break;
        case 1: renglon=createword('H');
                break;
        default: renglon=createword(')');
                break;
         }
               break;
            case ALLEGRO_KEY_J:
             switch(tl)
         {

        case 0: renglon=createword('j');
                break;
        case 1: renglon=createword('J');
                break;
        default: renglon=createword('|');
                break;
         }
               break;

            case ALLEGRO_KEY_K:
           switch(tl)
         {

        case 0: renglon=createword('k');
                break;
        case 1: renglon=createword('K');
                break;
        default: renglon=createword('&');
                break;
         }
               break;
            case ALLEGRO_KEY_L:
            switch(tl)
         {

        case 0: renglon=createword('l');
                break;
        case 1: renglon=createword('L');
                break;
        default: renglon=createword('@');
                break;
         }
               break;

            case ALLEGRO_KEY_Z:
           switch(tl)
         {

        case 0: renglon=createword('z');
                break;
        case 1: renglon=createword('Z');
                break;
        default: renglon=createword('+');
                break;
         }
               break;

            case ALLEGRO_KEY_X:
           switch(tl)
         {

        case 0: renglon=createword('x');
                break;
        case 1: renglon=createword('X');
                break;
        default: renglon=createword('*');
                break;
         }
               break;
            case ALLEGRO_KEY_C:
             switch(tl)
         {

        case 0: renglon=createword('c');
                break;
        case 1: renglon=createword('C');
                break;
        default: renglon=createword('?');
                break;
         }
               break;

            case ALLEGRO_KEY_B:
            switch(tl)
         {

        case 0: renglon=createword('b');
                break;
        case 1: renglon=createword('B');
                break;
        default: renglon=createword('<');
                break;
         }
               break;
            case ALLEGRO_KEY_N:
              switch(tl)
         {

        case 0: renglon=createword('n');
                break;
        case 1: renglon=createword('N');
                break;
        default: renglon=createword('>');
                break;
         }
               break;

            case ALLEGRO_KEY_M:
             switch(tl)
         {

        case 0: renglon=createword('m');
                break;
        case 1: renglon=createword('M');
                break;
        default: renglon=createword('#');
                break;
         }
               break;
            case ALLEGRO_KEY_SLASH:
             switch(tl)
         {

        case 0: renglon=createword(';');
                break;
        case 1: renglon=createword(';');
                break;
        default: renglon=createword('=');
                break;
         }
         }



        }




        if(redraw && al_is_event_queue_empty(event_queue))
        {


        redraw = false;


         al_flip_display();

        }
   }

}

int createword(char letra)
{
    int renglon,i,test;
    static int save;
    FILE * pantalla;
    static char mensaje[] ="mensaje0.txt";

i=counter (-2);
if(i==8)
{
    renglon=counter(3);
    return renglon;
}
if(i==-1)
{
    return 0;
}


renglon=i;

fprintf(stderr, "stringcre=%s \n",mensaje);



      if (renglon==0){
        save=1;

      }
mensaje[7]=renglon+'0';



  if (renglon==save){
            save+=1;
            mensaje[7]=renglon+'0';

    }

    pantalla=fopen(mensaje,"a+");
    fprintf(pantalla,"%c",letra);


    fclose(pantalla);




showit(renglon);

return renglon;
}


void showit(int renglon)
{
    FILE * pantalla;
    char mensaje[]= "mensaje0.txt";

    ALLEGRO_FONT *font1 = al_load_ttf_font("Blissful.ttf",15,0 );

    char palabra[100];
    ALLEGRO_COLOR black=al_map_rgb(0,0,0);

mensaje[7]=renglon+'0';
 pantalla=fopen(mensaje,"r");
 pantalla=fopen(mensaje,"a+");
 fprintf(stderr, "aca llego!\n");

if(fgetc(pantalla)!=EOF)
{
    rewind(pantalla);


    fprintf(stderr, "stringshow=%s \n",mensaje);


     al_draw_filled_rectangle((ancho/2)-84,(alto/3)+28+15*renglon,(ancho/2)+82,(alto/3)+10+15*renglon,black);



    fgets (palabra,1000,pantalla);


    fprintf(stderr, "stringpalabra=%s \n",palabra);

    al_draw_text(font1, al_map_rgb(255,255,255),(ancho/2)-80, (alto/3)+10+renglon*15,ALLEGRO_ALIGN_LEFT, palabra);

    al_flip_display();

    fclose(pantalla);
}

}


int counter (int next)
{
    static int limite;
    static int renglon;
    int i;


        if(limite==-1)
                limite=1;
        else
                limite+=1;


        if(next==3)
        {
            renglon-=1;
            limite=counterrenglon(renglon);

        }

        if(next==2){
            limite-=next;
        }

        if(next==1)
        {
        renglon+=next;
        limite=0;
        }

        if(next==0){
        limite=0;
        renglon=0;
        }




fprintf(stderr, "limite=%d \n",limite);

    if(limite==14)
    {
        limite=nextword(renglon);
        fprintf(stderr, "limitefinal=%d \n",limite);
        ++renglon;
         fprintf(stderr, "renglon=%d \n",renglon);

         if(limite==-1)
            return -1;

    }

fprintf(stderr, "rengloncounter=%d \n",renglon);

    return renglon;
}

int borrartxt(int renglon)

{       fprintf(stderr, "aca llego borrar txt!\n");
        FILE * pantalla;
        char arr[100];
        int i=0;
        ALLEGRO_COLOR black=al_map_rgb(0,0,0);
        char mensaje[] ="mensaje0.txt";
        static int stop=0;
fprintf(stderr, "renglon=%d \n",renglon);

mensaje[7]=renglon+'0';

pantalla=fopen(mensaje,"r");

    fgets(arr,100,pantalla);







while(arr[i]!='\0')
    ++i;
fprintf(stderr, "i=%d \n",i);
fprintf(stderr, "renglon=%d \n",renglon);


    arr[i-1]='\0';

    pantalla=fopen(mensaje,"w+");

    fprintf(pantalla,"%s",arr);

    al_draw_filled_rectangle((ancho/2)-84,(alto/3)+28+15*renglon,(ancho/2)+82,(alto/3)+10+15*renglon,black);

    fclose(pantalla);

    renglon=counter(2);



if((i==0)&&renglon!=0)
{

    renglon=counter(3);
    fprintf(stderr,"renglonvorr=%d",renglon);
    mensaje[7]=renglon+'0';
}

showit(renglon);




    return renglon;

}

  int nextword(int renglon)
    {
              char mensaje[] ="mensaje0.txt";
              char arr[100];
              char arraux[100];
              char * pasador;
              FILE * pantalla;
              int i,j,k,save,save2;
              ALLEGRO_COLOR black=al_map_rgb(0,0,0);



              mensaje[7]=renglon+'0';
              fprintf(stderr,"mensaje=%s",mensaje);

              pantalla=fopen(mensaje,"r");

              fgets(arr,100,pantalla);
              fclose(pantalla);



              for(i=0;arr[i]!='\0';)
                ++i;





            for(save=0;arr[i]!=' '&&i!=0;i--)
            {
                save++;

            }

            if(save==13)
                return 1;
            save2=i;

            fprintf(stderr, "i=%d",i);
            for(j=0,i-=1;i!=-1;i--,j++)
            {
                arraux[i]=arr[i];
                fprintf(stderr, "stringaux=%s\n",arraux);
            }

            fprintf(stderr,"aux1=%s",arraux);

            arraux[j]='\0';
              fprintf(stderr, "stringaux=%s",arraux);


              remove(mensaje);
              pantalla=fopen(mensaje,"w+");
               fprintf(pantalla, "%s",arraux);
               fclose(pantalla);
               showit(renglon);

                  fprintf(stderr, "%d",save);

            for(j=0 ,save2+=1;arr[save2]!='\0';save2++,j++)
            {
                arraux[j]=arr[save2];
                fprintf(stderr, "stringaux2=%c stringalgo=%c\n",arraux[j],arr[save2]);
            }
                    arraux[j]='\0';
                    fprintf(stderr, "stringaux2=%s\n",arraux);
                    ++renglon;

                    mensaje[7]=renglon+'0';

                    pantalla=fopen(mensaje,"w+");
               fprintf(pantalla, "%s",arraux);
               fclose(pantalla);
               showit(renglon);

               return save;

    }


int counterrenglon(int renglon)
{
              char mensaje[] ="mensaje0.txt";
              char arr[100];
              FILE * pantalla;
              int i;

              mensaje[7]=renglon+'0';


pantalla=fopen(mensaje,"r");
fgets(arr,100,pantalla);
fclose(pantalla);

if(arr[0]==EOF)
return 0;
            for(i=0;arr[i]!='\0';){
                ++i;
            }


return i;

}



int diccionario (int renglon)
{
char mensaje[] ="mensaje0.txt";
char diccionario[] ="diccionario0.txt";
char arre[27]; //ESTA ES LA PALABRA QUE INGRESA
char palabra[27];
int n=1;		//ESTE ES EL NUMERO DE CARACTERES QUE INGRESA AL PROGRAMA
FILE *ptr;
char resultado[2][27];	//ESTAS SON LAS 3 QUE TE DEVUELVE
int i=0,j=0,coun,save;



mensaje[7]=renglon+'0';

ptr=fopen(mensaje,"r");
              fgets(palabra,100,ptr);
              fclose(ptr);


for(i=0;palabra[i]!='\0';)
                ++i;

n=i-1;

for(j=0;n>=0&&palabra[n]!=' ';--n){

        ++j;

}
++n;




for(j=0;palabra[n]!='\0';++j,++n){
        arre[j]=palabra[n];
}
arre[j]='\0';






fprintf(stderr, "%c\n",arre[0]);
fprintf(stderr, "%c\n",arre[1]);
fprintf(stderr, "%c\n",arre[2]);
fprintf(stderr, "%c\n",arre[3]);

for(n=0;arre[n]!='\0';){
    n+=1;

    save=n;
}
j=0;
i=0;

ptr= fopen("espanol.txt","r");
if (ptr == 0)
{perror("error");
return (-1);}

while ( fgets(resultado[i],27,ptr) != 0 && i<3)
{for(j=0,coun = 0;j<n && coun != 1;j++)
{if(arre[j]!=resultado[i][j])
{coun=1;
			//ACA DEBERIAS DE HACER QUE PONGA CERO
}}
if(coun == 0)
{

i++;}

}
fclose(ptr);
if(i==0)
{resultado[i][0]=0;
resultado[1][0]=0;
resultado[2][0]=0;}

fprintf(stderr,"%s\n",resultado[0]);
fprintf(stderr,"%s\n",resultado[1]);
fprintf(stderr,"%s\n",resultado[2]);

for(i=0;i<=3;i++){
diccionario[11]=i+'0';
ptr=fopen(diccionario,"w+");

if(i!=3)
{fprintf(ptr,"%s",resultado[i]);
}
else
fprintf(ptr,"%s",arre);
fclose(ptr);
}
fprintf(stderr,"%d",save);
getword(renglon,save);

}



 void getword (int renglon,int borrar)
{   fprintf(stderr,"acallego!!!!!!!!!!!!!!!!!!!\n");
    static int dic,j;
    char mensaje[] ="mensaje0.txt";
    char diccionario[] ="diccionario0.txt";
    char arre[27];
   FILE * ptr;
    diccionario[11]=dic+'0';
   fprintf(stderr,"acallego!!!!!!!!!!!!!!!!!!!\n");
    ptr=fopen(diccionario,"a+");
    fprintf(ptr,"%c",'\0');
    fclose(ptr);
    ptr=fopen(diccionario,"r");
    fprintf(stderr,"acallego!!!!!!!!!!!!!!!!!!!\n");
    fgets(arre,27,ptr);
     fprintf(stderr,"acallego1\n");
    fclose(ptr);

for(j=0;arre[j]!=0;j++)
{}
printf("j=%d\n", j);
arre[j]='\0';
    while(borrar!=0)
   {borrartxt(renglon);
    borrar-=1;}
    mensaje[7]=renglon+'0';
    ptr=fopen(mensaje,"a+");
    fprintf(ptr,"%s",arre);
    fclose(ptr);



showit(renglon);
dic++;


}

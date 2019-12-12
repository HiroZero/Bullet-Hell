#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5\allegro_primitives.h>
#include<vector>
#include<iostream>
#include"stars.h"
#include"Mothership.h"
#include"globals.h"
#include "Bullets.h"

using namespace std;



int main()
{
//set up allegro
al_init();
al_install_keyboard();
al_init_image_addon();
al_init_primitives_addon();
//goes at the top of main where you creare your game display
//ALLEGRO_DISPLAY* Ship = al_create_display(500, 500);
ALLEGRO_BITMAP* cat = al_load_bitmap("mothership.png");
ALLEGRO_BITMAP* explosion = al_load_bitmap("explosion.jfif");
ALLEGRO_BITMAP* shipPic = al_load_bitmap("player2.png");
ALLEGRO_DISPLAY* nomnom;
srand(time(NULL));
al_init();
//nomnom = al_create_display(800, 800);
//set up game screen, event queue, and timer

ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
al_start_timer(timer);
//position of player
double xPos = 400;
double yPos = 700;
//game variables
bool key[5] = { false, false, false, false, false }; //holds key clicks
bool redraw = true; //variable needed for render section
bool doexit = false; //handles game loop

//tell event queue what to look for
al_register_event_source(event_queue, al_get_display_event_source(display));
al_register_event_source(event_queue, al_get_timer_event_source(timer));
al_register_event_source(event_queue, al_get_keyboard_event_source());
int JustShot = 0;
int frameWIDTH=30;
int curFrame=0;
int frameHEIGHT=30;
int playerHealth = 100;
//vector to hold missles
vector<Bullets*>BulletsBag;
vector<Bullets*>::iterator iter2;

//vector to hold stars
vector<stars*>starscloud;
vector<stars*>::iterator iter3;

for (int T = 0; T < 500; T++) {
stars* newStar = new stars();
starscloud.push_back(newStar);
}

for (int i = 0; i < 50; i++) {
Bullets* newBullets = new Bullets(0, 0);
BulletsBag.push_back(newBullets);
}
Mothership MO(200, 300, cat);
int AlienHit = 0;
int hitx = 0;
int hity = 0;

while (!doexit)//game loop!
{
ALLEGRO_EVENT ev;

al_wait_for_event(event_queue, &ev);

//timer (physics) section////////////////////////////////////////
if (ev.type == ALLEGRO_EVENT_TIMER) {
MO.move(); //good!
//move the missles
for (iter2 = BulletsBag.begin(); iter2 != BulletsBag.end(); iter2++) {
if ((*iter2)->isAlive())
(*iter2)->movement();
}
//cull the missiles
for (iter2 = BulletsBag.begin(); iter2 != BulletsBag.end(); iter2++) {
if ((*iter2)-> offScreen())
(*iter2)-> kill();
}
//check missle collision w/mothership
for (iter2 = BulletsBag.begin(); iter2 != BulletsBag.end(); iter2++) {
if ((*iter2)->collide(MO.getX(), MO.getY())) {
MO.decreaseHealth();
cout << "Mothership Hit!!!" << endl;
AlienHit = 30;
hitx = (*iter2)->getx();
hity = (*iter2)->gety();
}
}

JustShot++;





for (iter3 = starscloud.begin(); iter3 != starscloud.end(); iter3++) {
(*iter3)->repos();
(*iter3)->movment();

}


//move player 4 pixels in a direction when key is pressed
if (key[KEY_UP]) {
yPos -= 4.0;
}
if (key[KEY_DOWN]) {
yPos += 4.0;
}
if (key[KEY_LEFT]) {
xPos -= 4.0;
}
if (key[KEY_RIGHT]) {
xPos += 4.0;
}
if (key[KEY_SPACE]) {

for (iter2 = BulletsBag.begin(); iter2 != BulletsBag.end(); iter2++) {
if (((*iter2)->isAlive()) == false && JustShot > 5) {
(*iter2)->shoot(xPos, yPos);
JustShot = 0;

}
}
}
redraw = true;
}
//keyboard and screen sections//////////////////////////////////////////
else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
break;
}
else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
switch (ev.keyboard.keycode) {
case ALLEGRO_KEY_UP:
key[KEY_UP] = true;
break;
case ALLEGRO_KEY_DOWN:
key[KEY_DOWN] = true;
break;
case ALLEGRO_KEY_LEFT:
key[KEY_LEFT] = true;
break;
case ALLEGRO_KEY_RIGHT:
key[KEY_RIGHT] = true;
break;
case ALLEGRO_KEY_SPACE:
key[KEY_SPACE] = true;
break;
}

}
else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
switch (ev.keyboard.keycode) {
case ALLEGRO_KEY_UP:
key[KEY_UP] = false;
break;
case ALLEGRO_KEY_DOWN:
key[KEY_DOWN] = false;
break;
case ALLEGRO_KEY_LEFT:
key[KEY_LEFT] = false;
break;
case ALLEGRO_KEY_RIGHT:
key[KEY_RIGHT] = false;
break;
case ALLEGRO_KEY_ESCAPE:
doexit = true;
break;
case ALLEGRO_KEY_SPACE:
key[KEY_SPACE] = false;
break;
}


}//end of for loop
//render section//////////////////////////////////////////////////
if (redraw && al_is_event_queue_empty(event_queue)) {
redraw = false;
al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing

//draw player health bar
al_draw_rectangle(20, 20, 120, 40, al_map_rgb(255, 255, 255), 10);
al_draw_filled_rectangle(20, 20, +playerHealth, 40, al_map_rgb(200, 40, 140));
//al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 50, NULL, "Player shilds");

//draw motgership healthbar
al_draw_rectangle(20, 20, 120, 40, al_map_rgb(255, 255, 255), 10);
al_draw_filled_rectangle(20, 20, +playerHealth, 40, al_map_rgb(200, 40, 140));
//al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 50, NULL, "Mothership shilds");


//(without this things smear)
//replaces the draw circle function in the render section
if (AlienHit > 0) {
al_draw_bitmap_region(explosion, curFrame * frameWIDTH, 0, frameWIDTH, frameHEIGHT, hitx, hity, 0);
AlienHit == 0;
}
//stars
for (iter3 = starscloud.begin(); iter3 != starscloud.end(); iter3++) {
(*iter3)->draw();
}
//draw the missles
for (iter2 = BulletsBag.begin(); iter2 != BulletsBag.end(); iter2++) {
(*iter2)->draw();
}
al_draw_bitmap_region(shipPic, 0, 0, 32, 32, xPos, yPos, NULL);
MO.draw();
al_flip_display(); //flip everything from memory to gamescreen
}//end render

}//end game loop
//clean up memory
al_destroy_timer(timer);
al_destroy_display(display);
al_destroy_event_queue(event_queue);
// al_destroy_display(Ship);
//al_destroy_display(nomnom);


return 0;
}//end of main

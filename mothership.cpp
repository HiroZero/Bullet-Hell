#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5\allegro_primitives.h>
#include<vector>
#include<iostream>

#include "Bullets.h"





Bullets::Bullets(int x, int y) { //constructor
xpos = x;
ypos = y;

}

void Bullets::movement() {
ypos -= 15;
}

void Bullets::draw() {
if (alive == true) {
al_draw_filled_circle(xpos + 15, ypos, 15, al_map_rgb(100, 200, 234));
}
}

void Bullets::kill() {
alive = false;
}

bool Bullets::offScreen() {
if (ypos < 0) {
return true;
}
else
return false;
}

void Bullets::shoot(int x, int y) {
alive = true;
xpos = x;
ypos = y;
}

bool Bullets::isAlive() {
return alive;
}

float  Bullets::collide(float x1, float y1) {
return 0;
}

float Bullets::getx() {
return xpos;
}

float Bullets::gety() {
return ypos;

}

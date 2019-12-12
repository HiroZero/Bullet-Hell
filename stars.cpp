#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5\allegro_primitives.h>
#include<vector>
#include<iostream>

class Mothership {
private:
double xpos;
double ypos;
double xdir;
double ydir;
int Health;
ALLEGRO_BITMAP* image;
public:
int getX();
int getY();
int gethealth();
void move();
void draw();
void decreaseHealth();
Mothership(int x, int y, ALLEGRO_BITMAP* pic); //constructor: built in initialization function
};

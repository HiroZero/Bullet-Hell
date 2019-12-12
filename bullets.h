#include<allegro5/allegro.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5\allegro_primitives.h>

class Bullets {

private:
double xpos;
double ypos;
double angle;
double radius;
int color;
int size;
bool alive;
ALLEGRO_BITMAP* pic;



public:

Bullets(int x, int y); //constructor
void movement();
void draw();
void kill();
bool isAlive();
bool offScreen();
float getx();
float gety();
void shoot(int x, int y);
float  collide(float x1, float y1);
}; 

#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5\allegro_primitives.h>
#include<vector>
#include<iostream>


//star class here
class stars {
private:
int Xpos;
int Ypos;
int blue;
int red;
int green;
int size;

public:
void repos();
void draw();
void movment();
void starscloud();
stars(); //constructor
};

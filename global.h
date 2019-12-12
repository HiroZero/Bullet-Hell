#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5\allegro_primitives.h>
#include<vector>
#include<iostream>

//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 800;
//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};


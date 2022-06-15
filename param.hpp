#pragma once
#include "things/util/util.hpp"

using namespace std;

int GAME_W = 900;
int GAME_H = 700;
double G_ACC = 0.2;//0.981;
double EPS = 0.1;
Point MIDPOINT = {0.0,0.0};
string TITLE = "Bababooey";
string ASSETPATH =  "assets\\";
sf::Font DEF_FONT ;
bool EXIT = false;

void setup_once(){
    createFont(DEF_FONT,"assets\\prstartk.ttf");
}

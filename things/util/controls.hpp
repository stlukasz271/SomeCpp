#pragma once
#include<bits/stdc++.h>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Graphics.hpp>
#include "../../param.hpp"

using namespace std;

int buttons[100003],keys[100003];
bool SHIFT = false, CONTROL = false, ALT = false;
bool leftclicked=false,rightclicked=false,middleclicked=false;
double MOUSEX=0.0,MOUSEY=0.0;

sf::Event event;

bool leftClicked(){
    return leftclicked;
}

bool rightClicked(){
    return rightclicked;
}

bool middleClicked(){
    return middleclicked;
}

bool leftPressed(){
    return buttons[0];
}

bool rightPressed(){
    return buttons[1];
}

bool middlePressed(){
    return buttons[2];
}


void def_listen(sf::RenderWindow &window){ 
    leftclicked=false;rightclicked=false;middleclicked=false;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            EXIT = 1;
        }
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        MOUSEX = pixelPos.x;
        MOUSEY = pixelPos.y;
        leftclicked=false;rightclicked=false;middleclicked=false;
        if (event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Middle){
                middleclicked = true;
            }else{
                middleclicked=false;
            }
            if(event.mouseButton.button == sf::Mouse::Right){
                rightclicked = true;
            }else{
                rightclicked=false;
            }
            if(event.mouseButton.button == sf::Mouse::Left){
                leftclicked = true;
            }else{
                leftclicked=false;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed){
            buttons[event.mouseButton.button] = 1;
        }
        if (event.type == sf::Event::MouseButtonReleased){
            buttons[event.mouseButton.button] = 0;
        }
        if (event.type == sf::Event::KeyPressed){
            keys[event.key.code] = 1;
            if(event.key.alt){ALT = true;}
            if(event.key.shift){SHIFT = true;}
            if(event.key.control){CONTROL = true;}
        }
        if (event.type == sf::Event::KeyReleased){
            keys[event.key.code] = 0;
            if(event.key.alt){ALT = false;}
            if(event.key.shift){SHIFT = false;}
            if(event.key.control){CONTROL = false;}
        }
    }
}
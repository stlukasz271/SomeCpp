#pragma once
#include "util/sprite.hpp"
#include "util/util.hpp"
#include<bits/stdc++.h>
#include<SFML/Window.hpp>

using namespace std;

const string BALLPATH = "C:\\RandomProgramming\\SomeCpp\\assets\\ball.png";

class Ball : public Sprite{
    private:
        int index=0;
        bool last = false;
    public:
        void assignIndex(int index, bool last){
            this->index=index;
            this->last=last;
        }
        void handleCollision(vector<Ball> balls){
            return;
        }
        Ball(double x, double y) : Sprite(x,y,BALLPATH){
            v.set(0.1*randint(-100,100),0);
            a.set(-v.getX()/500.0,G_ACC);
            w = 32;
            h = 32;
        }
    Ball(double x, double y, Vector v) : Sprite(x,y,BALLPATH){
        //v.set(0.1*randint(-100,100),0);
        this->v=v;
        w = 32;
        h = 32;
        a.set(-v.getX()/500.0,G_ACC);
    }
    protected:
        void prepaint(sf::RenderWindow &window){
            Arrow arr(getX()+24,getY()+24,v*20);
            //arr.paint(window);
            Arrow arr2(getX()+24,getY()+24,a*50, sf::Color(0,255,0));
            //arr2.paint(window);
            if(abs(v.getX())<=EPS){
                v.nulX();
                a.nulX();
            }else{
                a.set(-v.getX()/300.0,G_ACC);
            }
            if(getY()+48+v.getY() >= GAME_H || getY()+v.getY()-EPS <= 0){
                //addY(-v.getY());
                v.multY(-0.80);
            }
            if(getX()+48+v.getX() >= GAME_W || getX()+v.getX()-EPS <= 0){
                //addX(-v.getX());
                v.multX(-0.80);
            }
        }
};


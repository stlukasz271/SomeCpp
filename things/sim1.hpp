#include<bits/stdc++.h>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include "../param.hpp"
#include "util/sprite.hpp"
#include "util/controls.hpp"
#include "util/physics.hpp"
#include "ball.hpp"
#include "util/menus.hpp"

using namespace std;

struct point{
    double x=0.0,y=0.0;
};

class Simulation{

    private:
        int frames = 0, points = 0, inside = 0, outside = 0;
        Caption frame_cnt = Caption(0,0,"Frame: 0");
        //Caption point_cnt = Caption(225,0,"Points: 0");
        Caption pi_appr = Caption(320,0,"PI=");
        Caption p_in = Caption(0,30,"Dots In Circle:");
        Caption p_out = Caption(320,30,"Dots Outside:");
        vector<point*> pts;      
    public:
        int getFrames(){ 
            return frames;
        }
        int getPoints(){
            return points;
        }
        Simulation(){
            GAME_W = 600;
            GAME_H = 650;

            frame_cnt.animate=false;
            frame_cnt.life = -1;
            frame_cnt.size = 16;

            //point_cnt.animate=false;
            //point_cnt.life = -1;
            //point_cnt.size = 18;

            pi_appr.animate=false;
            pi_appr.life = -1;
            pi_appr.size = 16;

            p_in.animate=false;
            p_in.life = -1;
            p_in.size = 14;

            p_out.animate=false;
            p_out.life = -1;
            p_out.size = 14;

        }
        void newPoint(){
            double x = randint(0,GAME_W);
            double y = randint(50,GAME_H);
            point *pt = new point();
            pt->x = x;
            pt->y = y;
            if((x-300)*(x-300) + (y-350)*(y-350) <= 300*300){
                inside++;
            }else{
                outside++;
            }
            points++;
            pts.push_back(pt);
        }
        void paint(sf::RenderWindow &window){
            frames ++;
            if(frames % 3 == 1){
            newPoint();
            newPoint();
            newPoint();
             }

            frame_cnt.all_message = "Frames: "+to_string(frames);
            //point_cnt.all_message = "Points: "+to_string(points);
            pi_appr.all_message = "PI = "+to_string(0);
            //std::cout<<frames<<endl;std::cout.flush();
            sf::CircleShape circle;
            circle.setRadius(GAME_W/2);
            circle.setFillColor(sf::Color::Red);
            circle.setPosition(0, 50);
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(GAME_W,GAME_W));
            rect.setFillColor(sf::Color(50,50,50));
            rect.setPosition(0, 50);
            window.draw(rect);
            window.draw(circle);
            
            frame_cnt.paint(window);
            //point_cnt.paint(window);

            p_in.all_message = "Dots In Circle:"+to_string(inside);
            p_out.all_message = "Dots Outside:"+to_string(outside);
            outside = max(outside,1);
            pi_appr.all_message = "PI="+to_string(4.0*double(inside) / double(outside+inside));
            p_in.paint(window);
            p_out.paint(window);
            pi_appr.paint(window);

            for(point *pt : pts){
                sf::CircleShape pc;
                pc.setRadius(3);
                pc.setFillColor(sf::Color::Green);
                pc.setPosition(pt->x, pt->y);
                window.draw(pc);
            }
        }

};
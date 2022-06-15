#pragma once
#include<bits/stdc++.h>
#include<SFML/Graphics.hpp>
#include<SFML/Main.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include "../../param.hpp"
#include "util.hpp"

using namespace std;

class Caption{
    private:
        sf::Font font;
        sf::Color color = sf::Color::White;
        double w=-1.0,h=-1.0;
        int style = sf::Text::Regular;
    public:
        void load(){
            life--;
            if(life==0){
                is_alive=false;
                return;
            }
            vector<string> lines = split_string_by_newline(message);
            texts.clear();
            h = 0.0;
            for(string line : lines){
                sf::Text this_line;
                this_line.setFont(font);
                this_line.setColor(color);
                this_line.setCharacterSize(size);
                this_line.setStyle(style);
                this_line.setString(line);
                double this_h = double(this_line.getLocalBounds().height);
                this_line.setPosition(x,y+double(texts.size())*(this_h+line_indent));
                w = max(w,double(this_line.getLocalBounds().width));
                texts.push_back(this_line);
                h = (this_h+line_indent)*texts.size();
            }
        }
    public:
        string message;
        string all_message = "";
        int ind = 0;
        double x,y, line_indent=6;
        int anim_delay = 10,anim_interval = 10;
        int life=-1, size = 24, loops = 1;
        bool is_alive = true, animate = false;
        vector<sf::Text> texts;
        double getW(){
            if(w==-1.0){
                load();
            }
            return w;
        }
        double getH(){
            if(h==-1.0){
                load();
            }
            return h;
        }
        double getMaxW(){
            string tm = message;
            message = all_message;
            load();
            double tw = getW();
            message = tm;
            load();
            return tw;
        }
        double getMaxH(){
            string tm = message;
            message = all_message;
            load();
            double th = getH();
            message = tm;
            load();
            return th;
        }
    Caption(double x, double y, string start_text, int life = -1){
            this->x=x;
            this->y=y;
            this->all_message=start_text;
            this->life=life;
            font = DEF_FONT;
        }
        Caption(double x, double y, string start_text, int life, sf::Font font, sf::Color color, int size, int style = sf::Text::Regular){
            this->x=x;
            this->y=y;
            this->all_message=start_text;
            this->life=life;
            this->font = font;
            this->color = color;
            this->size=size;
            this->style=style;
        }
        void paint(sf::RenderWindow &window){
            if(!is_alive){return;}
            if(animate){
                if(anim_delay>0){
                    anim_delay-=1;
                }else if(ind<all_message.size()) {
                    anim_delay = anim_interval;
                    message += all_message[ind];
                    ind++;
                    if(ind==all_message.size()){
                        if(loops!=0){
                            loops-=1;
                            ind=0;
                            message="";
                        }
                    }
                }
            }else{
                message=all_message;
            }
            load();
            for(sf::Text single_text : texts) {
                window.draw(single_text);
            }
        }
        int getStyle() {
            return style;
        }
        void setStyle(int style) {
            this->style = style;
        }
        void centerX(){
            if(w==-1.0) {load();}
            x = (GAME_W-w)/2.0;
        }
        void centerY(){
            if(h==-1.0) {load();}
            y = (GAME_H-h)/2.0;
        }
        void center(){
            centerX();
            centerY();
        }
        sf::Font getFont() {
            return font;
        }
        void setFont(sf::Font font) {
            this->font = font;
        }
        sf::Color getColor() {
            return color;
        }
        void setColor(sf::Color color) {
            this->color = color;
        }

};

class FieldOfText{
    private:
        sf::Color border_color, bg_color;
    public:
        double x,y,w,h, border_size=3;
        string message;
        Caption caption = Caption(-1.0,-1.0, "nigger ass");
        bool fitToText = false;
        FieldOfText(double x, double y, string message, bool fitToText=false){
            this->x=x;
            this->y=y;
            this->message = message;
            caption = Caption(x,y, message);
        };
        FieldOfText(double x, double y, double w, double h, string message, sf::Color border_color, sf::Color bg_color, bool fitToText, int life, sf::Color color, sf::Font font, int size, int style=sf::Text::Regular){
            this->x=x;
            this->y=y;
            this->w=w;
            this->h=h;
            this->message = message;
            this->border_color=border_color;
            this->bg_color=bg_color;
            this->fitToText=fitToText;
            caption = Caption(x,y, message,life,font,color,size,style);
        };
        void centerTextX(){
            caption.x = x+w*0.5 - caption.getW()*0.5;
        }
        void centerTextY(){
            caption.y = y+h*0.5 - caption.getH()*0.5;
        }
        void centerText() {
            centerTextX();
            centerTextY();
        }
        void paint(sf::RenderWindow &window){
            if(caption.is_alive){
                if(fitToText){
                    w = 2.1*border_size+caption.getMaxW();
                    h = 2.1*border_size+caption.getMaxH();
                }
                sf::RectangleShape rectangle{ { float(w), float(h)} };
                rectangle.setFillColor(border_color);
                rectangle.setPosition({ float(x), float(y)});
                window.draw(rectangle);
                sf::RectangleShape rectangle2{ { float(w-2.0*border_size), float(h-2.0*border_size)} };
                rectangle2.setFillColor(bg_color);
                rectangle2.setPosition({ float(x+border_size), float(y+border_size)});
                window.draw(rectangle2);
                if(caption.x != x+w*0.5 - caption.getW()*0.5) {
                    caption.x = x + border_size * 1.05;
                }
                if(caption.y != y+h*0.5 - caption.getH()*0.5) {
                    caption.y = y + border_size * 1.05;
                }
                caption.paint(window);
            }
        }
};

class Button{

    public:
        bool is_alive = true;
        FieldOfText released = FieldOfText(-1.0,-1.0, "nigger ass");
        FieldOfText pressed = FieldOfText(-1.0,-1.0, "nigger ass");
        FieldOfText current = FieldOfText(-1.0,-1.0, "nigger ass");
        Button(FieldOfText released, FieldOfText pressed){
            this->released = released;
            this->pressed = pressed;
            current = released;
        }
        void paint(sf::RenderWindow &window){
            if(is_alive){
                if(current.caption.is_alive) {
                    released.paint(window);
                }else{
                    is_alive = false;
                    return;
                }
            }else{
                return;
            }
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            double mx = pixelPos.x;
            double my = pixelPos.y;
            if(mx >= current.x && mx <= current.x+current.w && my >= current.y && my <= current.y+current.h){
                current = pressed;
            }else{
                current = released;
            }
        }

};

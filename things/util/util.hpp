#pragma once
#include "physics.hpp"
#include<SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <sstream>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

vector<string> list_dir(char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    vector<string> res;
    if (dir == NULL) {
        return res;
    }
    while ((entry = readdir(dir)) != NULL) {
        //printf("%s\n",entry->d_name);
        res.push_back(entry->d_name);
    }
    closedir(dir);
    return res;
}

std::vector<std::string> split_string_by_newline(const std::string& str)
{
    auto result = std::vector<std::string>{};
    auto ss = std::stringstream{str};

    for (std::string line; std::getline(ss, line, '\n');)
        result.push_back(line);

    return result;
}

int sign(int x){
    if(x==0){return 0;}
    if(x<0){return -1;}
    if(x>0){return 1;}
}

double sign(double x){
    if(x==0){return 0.0;}
    if(x<0){return -1.0;}
    if(x>0){return 1.0;}
}

int randint(int a, int b){
    int range = b - a + 1;
    int num = rand() % range + a;
}

class Arrow{
    private:
        double x=0.0,y=0.0;
        Vector v = Vector(0.0,0.0);
        sf::Color color = sf::Color(0,255,0);
    public:
        double getX(){
            return x;
        }
        double getY(){
            return y;
        }
        double getX2(){
            return getX()+v.getX();
        }
        double getY2(){
            return getY()+v.getY();
        }
        Arrow(double x, double y, Vector v){
            this->x=x;
            this->y=y;
            this->v.set(v.getX(),v.getY());
        }
        Arrow(double x, double y, Vector v, sf::Color color){
            this->x=x;
            this->y=y;
            this->v.set(v.getX(),v.getY());
            this->color=color;
        }
        void paint(sf::RenderWindow &window){
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(getX(), getY());
            line[0].color = sf::Color(0, 255, 0);
            line[1].position = sf::Vector2f(getX2(), getY2());
            line[1].color = sf::Color(0, 255, 0);
            window.draw(line);


            double tga = v.getY()/v.getX();
            double sina = tga/sqrt((tga*tga)+1);
            double cosa = sina/tga;
            double a = atan2(v.getY(),v.getX());
            double add = 3.141/4;
            double backlen = max(6.0,sqrt(v.len()));
            Vector back = Vector(backlen*cos(a+add),backlen*sin(a+add));
            Vector back2 = Vector(backlen*cos(a-add),backlen*sin(a-add));
            sf::VertexArray line2(sf::Lines, 2);
            line2[0].position = sf::Vector2f(getX2(), getY2());
            line2[0].color = color;
            line2[1].position = sf::Vector2f(getX2()-back.getX(), getY2()-back.getY());
            line2[1].color = color;
            window.draw(line2);

            sf::VertexArray line3(sf::Lines, 2);
            line3[0].position = sf::Vector2f(getX2(), getY2());
            line3[0].color = color;
            line3[1].position = sf::Vector2f(getX2()-back2.getX(), getY2()-back2.getY());
            line3[1].color = color;
            window.draw(line3);

        }
};

void createFont(sf::Font &target, string path){
    sf::Font temp;
    temp.loadFromFile(path);
    target = temp;
}
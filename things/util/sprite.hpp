#pragma once
#include "physics.hpp"
#include "../../param.hpp"

using namespace std;

class Sprite{

    private:
        double x=0.0,y=0.0,dx=0.0,dy=0.0,ax=0.0,ay=0.0;
    int frame=0,anim=0;
        sf::Image image;
        sf::Texture texture;
        vector<vector<string>> paths;
        vector<vector<sf::Texture>> textures;

    protected:
            double w=-1.0,h=-1.0;
            virtual void render(sf::RenderWindow &window){
                load();
                sf::Texture curr = getTexture();
                sprite.setTexture(curr);
                sprite.setPosition(x,y);
                if(w*h<=0.0){
                    cerr<<"WHAT THE FUCK";cerr.flush();
                    throw std::invalid_argument("WHAT THE FUCK");
                }
                if(w!=-1.0) {
                    if(sprite.getGlobalBounds().width!=w||sprite.getGlobalBounds().height!=h){/*if(abs(sprite.getGlobalBounds().width-w)>EPS&&abs(sprite.getGlobalBounds().height-h)>EPS) {*/
                       sprite.scale(w / sprite.getGlobalBounds().width, h / sprite.getGlobalBounds().height);
                    }
                }
                window.draw(sprite);
            }
            virtual void prepaint(sf::RenderWindow &window){}
            virtual void postpaint(sf::RenderWindow &window){}
    double smooth = true;
    public:
        sf::Sprite sprite;
        bool is_alive = true;
        Vector v = Vector(0.0,0.0), a = Vector(0.0,0.0);
        double getX(){
            return x;
        }
        double getY(){
            return y;
        }
        void setX(double x){
            this->x=x;
        }
        void setY(double y){
            this->y=y;
        }
        void set(double x, double y){
            this->x=x;
            this->y=y;
        }
        void nul(){
            set(0.0,0.0);
        }
        void nulX(){
            setX(0.0);
        }
        void nulY(){
            setY(0.0);
        }
        void addX(double x){
            setX(this->x+x);
        }
        void addY(double y){
            setY(this->y+y);
        }
        void move(double x, double y){
            addX(x);
            addY(y);
        }
        void move(Vector vec){
            addX(vec.getX());
            addY(vec.getY());
        }
        Point point(){
            return {getX()+24,getY()+24};
        }
        string getPath(){
            return paths[anim][frame];
        }
        sf::Texture getTexture(){
            return textures[anim][frame];
        }
        Sprite(double x, double y, string path,bool smooth = true){
            this->x=x;
            this->y=y;
            this->smooth=smooth;
            vector<string> tmp({path});
            paths.push_back(tmp);
            load();
        }
        Sprite(double x, double y, vector<vector<string>> paths,bool smooth = true){
            this->x=x;
            this->y=y;
            this->paths=paths;
            this->smooth=smooth;
            load();
        }
        void load(){
            if(textures.size()){
                return;
            }
            for(vector<string> vpaths : paths){
                vector<sf::Texture> vtextures;
                for(string path : vpaths){
                    sf::Image temp;
                    temp.loadFromFile(path);
                    sf::Texture texture;
                    texture.loadFromImage(temp);
                    vtextures.push_back(texture);
                }
                textures.push_back(vtextures);
            }
        }
        void paint(sf::RenderWindow &window){
            if(!is_alive){return;}
            prepaint(window);
            render(window);
            postpaint(window);
            v.add(a);
            x+=v.getX();
            y+=v.getY();
        }

};

bool comp_sprite(Sprite a, Sprite b){
    if(a.getX()==b.getX()){
        return a.getY()<b.getY();
    }
    return a.getX()<b.getX();
}
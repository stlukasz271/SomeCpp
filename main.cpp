#include<bits/stdc++.h>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include "param.hpp"
#include "things/util/sprite.hpp"
#include "things/util/controls.hpp"
#include "things/util/physics.hpp"
#include "things/ball.hpp"
#include "things/sim1.hpp"

using namespace std;

int main(){

    setup_once();
    srand(NULL);
    Simulation sim = Simulation();
    sf::RenderWindow window(sf::VideoMode(GAME_W, GAME_H), "My window");
    window.setVerticalSyncEnabled(false);
   // window.setFramerateLimit(60);
    while (window.isOpen())
    {
         sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        def_listen(window);
        sim.paint(window);
        window.display();
    }



    return 0;
}
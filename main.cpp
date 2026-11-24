#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "player.hpp"
#include "ball.hpp"
#include "menu.hpp"

State state = State::Menu;

const std::string ASSET_DIR = "assets/";
sf::Vector2u winSize = {800, 600};

int main(){
    sf::RenderWindow window(sf::VideoMode(winSize), "Pong");
    window.setFramerateLimit(60);
    sf::Font font;
    if(!font.openFromFile(ASSET_DIR + "font.ttf")) return 1;

    Menu menu(font, winSize);

    sf::Text debug(font, "", 14);
    debug.setPosition({10.f, 10.f});
    debug.setFillColor(sf::Color::White);

    Player player(winSize);
    Ball ball(winSize, font);

    sf::Clock clock;
    while(window.isOpen()){
        float dt = clock.restart().asSeconds();
        while(const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            menu.handleEvent(*event, state, window);
        }
        debug.setString("p1y: " + std::to_string(player.getP1y()) +
                        "\np2y: " + std::to_string(player.getP2y()) + 
                        "\nball: " + std::to_string(ball.getPos().x) + ", " + std::to_string(ball.getPos().y));
        
        if (state == State::Dual || state == State::Single){
            player.handleInput(winSize, dt, state);
            player.update(winSize, dt, state);
            ball.update(winSize, dt, player, state);
            ball.checkCollision(winSize, player, state);
        }
        menu.update(window, state);

        window.clear();
        if (state == State::Dual || state == State::Single){
            player.draw(window, state);
            ball.draw(window);
        }
        menu.draw(window, state);
        window.draw(debug);
        window.display();
    }
}
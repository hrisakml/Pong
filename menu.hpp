#pragma once
#include <SFML/Graphics.hpp>
#include "game_state.hpp"

class Menu {
    public:
        Menu(const sf::Font &font, sf::Vector2u winSize);
        void handleEvent(const sf::Event& event, State &state);
        void draw(sf::RenderTarget& target, State state) const;
    private:
        sf::Text title, hint, hint2, gameOver;
        static void center(sf::Text &t, float x, float y);
};
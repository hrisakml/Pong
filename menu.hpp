#pragma once
#include <SFML/Graphics.hpp>
#include "game_state.hpp"
#include "button.hpp"

class Menu {
    public:
        Menu(const sf::Font &font, sf::Vector2u winSize);
        void handleEvent(const sf::Event& event, State &state, const sf::RenderWindow &window);
        void update(const sf::RenderWindow& window, State state);
        void draw(sf::RenderTarget& target, State state) const;
    private:
        sf::Text title, hint, hint2, gameOver;
        Button startBtn, retryBtn, menuBtn, startBtn2;
        State lastState;
        static void center(sf::Text &t, float x, float y);
};
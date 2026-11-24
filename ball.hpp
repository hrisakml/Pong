#pragma once
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "game_state.hpp"

class Ball{
    public:
        Ball(sf::Vector2u winSize, const sf::Font &font);
        void draw(sf::RenderTarget &target) const;
        void checkCollision(sf::Vector2u winSize, Player& player);
        void resetPos(sf::Vector2u winSize, Player& player);
        void update(sf::Vector2u winSize, float dt, Player& player, State &state);

        sf::FloatRect getGB() const { return ball.getGlobalBounds(); }
        sf::Vector2f getPos() const { return ball.getPosition(); }
    private:
        void refreshScoreText(sf::Vector2u winSize, Player &player);
        sf::Vector2f bSize = {10.f, 10.f};
        sf::Vector2f bPos;
        sf::Vector2i dir;
        sf::RectangleShape ball;
        sf::Text scoreText;
        int speed = 200;
        int plusSpeed = 0;
        int baseSpeed = 200;
};
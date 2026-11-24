#pragma once
#include <SFML/Graphics.hpp>

class Player{
    public:
        Player(sf::Vector2u winSize);
        void draw(sf::RenderTarget &target) const;
        void update(sf::Vector2u winSize, float dt);
        void handleInput(sf::Vector2u winSize,float dt);

        float getP1y() const {return p1y;}
        float getP2y() const {return p2y;}

        sf::FloatRect getGB1() const { return player1.getGlobalBounds(); }
        sf::FloatRect getGB2() const { return player2.getGlobalBounds(); }

        int getScore1() const {return score1;}
        void plusScore1(int score) { this->score1 += score; }
        void setScore1(int score) { this->score1 = score; }

        int getScore2() const {return score2;}
        void plusScore2(int score) { this->score2 += score; }
        void setScore2(int score) { this->score2 = score; }

        void resetPos(sf::Vector2u winSize);
    private:
        sf::Vector2f pSize = {15.f, 75.f};
        sf::RectangleShape player1,player2;
        int score1 = 0, score2 = 0;
        float p1y = 0.f;
        float p2y = 0.f;
        float align = 25.f;
        float speed = 250.f;
};
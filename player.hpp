#pragma once
#include <SFML/Graphics.hpp>
#include "game_state.hpp"

class Player{
    public:
        Player(sf::Vector2u winSize);
        void draw(sf::RenderTarget &target, State &state) const;
        void update(sf::Vector2u winSize, float dt, State& state);
        void handleInput(sf::Vector2u winSize,float dt, State &state);
        void resetPos(sf::Vector2u winSize, State &state);

        float getP1y() const {return p1y;}
        float getP2y() const {return p2y;}

        sf::FloatRect getGB1() const { return player1.getGlobalBounds(); }
        sf::FloatRect getGB2() const { return player2.getGlobalBounds(); }
        sf::FloatRect getSB() const { return single.getGlobalBounds(); }

        int getScore1() const {return score1;}
        void plusScore1(int score) { this->score1 += score; }
        void setScore1(int score) { this->score1 = score; }

        int getScore2() const {return score2;}
        void plusScore2(int score) { this->score2 += score; }
        void setScore2(int score) { this->score2 = score; }

        int getSScore() const {return singleScore;}
        void plusSScore(int score) {this->singleScore += score;}
        void setSScore(int score) {this->singleScore = score;} 
    private:
        sf::Vector2f pSize = {15.f, 75.f};
        sf::Vector2f sSize = {75.f, 15.f};
        sf::RectangleShape player1,player2,single;
        int score1 = 0, score2 = 0, singleScore = 0;
        float p1y = 0.f;
        float p2y = 0.f;
        float sX = 0.f;
        float align = 30.f;
        float speed = 250.f;
};
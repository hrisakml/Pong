#include "ball.hpp"
#include <random>

int getRandom(){
    static std::mt19937 gen(std::random_device{}());
    static std::bernoulli_distribution dist(0.5);
    return dist(gen) ? 1 : -1;
}

Ball::Ball(sf::Vector2u winSize, const sf::Font &font)
    :ball(bSize), scoreText(font, "0 0", 25)
{
    ball.setOrigin(bSize/2.f);
    bPos = {winSize.x / 2.f, winSize.y / 2.f};
    dir = {getRandom(), getRandom()};
    ball.setFillColor(sf::Color::White);
    ball.setPosition(bPos);

    scoreText.setFillColor(sf::Color::White);
    scoreText.setOrigin(scoreText.getGlobalBounds().position + scoreText.getGlobalBounds().size / 2.f);
    scoreText.setPosition({winSize.x / 2.f, 20.f});
}

void Ball::update(sf::Vector2u winSize, float dt, Player& player, State &state){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
        resetPos(winSize, player);
        refreshScoreText(winSize, player, state);
    }

    if (state == State::Single){
        if (bPos.y - (bSize.y/2.f) < 0) dir.y *=-1;
        if (bPos.x - (bSize.x/2.f) < 0 || bPos.x + (bSize.x/2.f) > winSize.x) dir.x *= -1;
        if (bPos.y + (bSize.y/2.f) > winSize.y){
            resetPos(winSize,player);
            player.resetPos(winSize, state);
            state = State::Gameover;
            refreshScoreText(winSize, player, state);
        }
    }
    else if (state == State::Dual){
        if ((bPos.y + (bSize.y/2.f) > winSize.y) || bPos.y - (bSize.y/2.f) < 0) dir.y *= -1;
        if (bPos.x > winSize.x || bPos.x < 0){
            resetPos(winSize, player);
            player.resetPos(winSize, state);
            state = State::Gameover;
            refreshScoreText(winSize, player, state);
        }
    }

    bPos += {dir.x * speed * dt, dir.y * speed * dt};
    ball.setPosition(bPos);
}

void Ball::checkCollision(sf::Vector2u winSize, Player &player, State &state){
    auto b = ball.getGlobalBounds();
    if (state == State::Single){
        if (dir.y > 0 && b.findIntersection(player.getSB())){
            dir.y = - dir.y;
            player.plusSScore(1);
        }
    }
    else if (state == State::Dual){
        if (dir.x < 0 && b.findIntersection(player.getGB1())){
            dir.x = std::abs(dir.x);
            player.plusScore1(1);
        }
        if (dir.x > 0 && b.findIntersection(player.getGB2())){
            dir.x = -dir.x;
            player.plusScore2(1);
        }
    }
    refreshScoreText(winSize, player, state);
}

void Ball::resetPos(sf::Vector2u winSize, Player& player){
    bPos = {winSize.x / 2.f, winSize.y / 2.f};
    dir = {getRandom(), getRandom()};
    ball.setPosition(bPos);
    player.setScore1(0);
    player.setScore2(0);
    player.setSScore(0);
}

void Ball::refreshScoreText(sf::Vector2u winSize, Player &player, State &state){
    if (state == State::Single)
        scoreText.setString(std::to_string(player.getSScore()));
    if (state == State::Dual)
        scoreText.setString(std::to_string(player.getScore1()) + " " + std::to_string(player.getScore2()));

    scoreText.setPosition({winSize.x / 2.f, 20.f});
}

void Ball::draw(sf::RenderTarget &target) const{
    target.draw(ball);
    target.draw(scoreText);
}
#include "player.hpp"
#include <cmath>

Player::Player(sf::Vector2u winSize)
    : player1(pSize), player2(pSize), single(sSize)
{
    player1.setOrigin(pSize/2.f);
    player2.setOrigin(pSize/2.f);
    single.setOrigin(sSize/2.f);

    player1.setFillColor(sf::Color::White);
    player2.setFillColor(sf::Color::White);
    single.setFillColor(sf::Color::White);

    p1y = winSize.y/2.f;
    p2y = winSize.y/2.f;

    sX = winSize.x / 2.f;
}

void Player::handleInput(sf::Vector2u winSize,float dt, State &state){
    using K = sf::Keyboard::Key;

    if (state == State::Single){
        if (sf::Keyboard::isKeyPressed(K::A) && sX - (sSize.x/2.f) > 0) sX -= speed * dt;
        if (sf::Keyboard::isKeyPressed(K::D) && sX + (sSize.x/2.f) < winSize.x) sX += speed * dt;
    }
    else if (state == State::Dual){
        if (sf::Keyboard::isKeyPressed(K::W) && p1y - (pSize.y/2.f) > 0) p1y -= speed * dt;
        if (sf::Keyboard::isKeyPressed(K::S) && p1y + (pSize.y/2.f) < winSize.y) p1y += speed * dt;

        if ((sf::Keyboard::isKeyPressed(K::Up) || sf::Keyboard::isKeyPressed(K::O)) && p2y - (pSize.y/2.f) > 0) p2y -= speed * dt;
        if ((sf::Keyboard::isKeyPressed(K::Down) || sf::Keyboard::isKeyPressed(K::L)) && p2y + (pSize.y/2.f) < winSize.y) p2y += speed * dt;
    }
}

void Player::resetPos(sf::Vector2u winSize, State &state){
    if (state == State::Single){
        sX = winSize.x/2.f;
    }
    else if (state == State::Dual){
        p1y = winSize.y/2.f; p2y = winSize.y/2.f;
    }
}

void Player::update(sf::Vector2u winSize, float dt, State &state){
    if (state == State::Single){
        single.setPosition({sX, winSize.y - align});
    }
    else if (state == State::Dual){
        player1.setPosition({0.f + align, p1y});
        player2.setPosition({winSize.x - align, p2y});
    }
}

void Player::draw(sf::RenderTarget &target, State& state) const{
    if (state == State::Single){
        target.draw(single);
    }else if (state == State::Dual){
        target.draw(player1);
        target.draw(player2);
    }
}
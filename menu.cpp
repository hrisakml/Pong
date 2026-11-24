#include "menu.hpp"

Menu::Menu(const sf::Font& font, sf::Vector2u winSize)
    :title(font, "PONG", 50), hint(font, "Press Enter", 30),
    gameOver(font, "Game Over", 50), hint2(font, "ENTER: Play Again\nESC: Menu", 30),
    startBtn(font, "Dual", {winSize.x / 2.f, 400.f}, {200.f, 50.f}),
    retryBtn(font, "Retry", {winSize.x / 2.f, 320.f}, {200.f, 50.f}),
    menuBtn(font, "Menu", {winSize.x / 2.f, 400.f}, {200.f, 50.f}),
    startBtn2(font, "Single", {winSize.x / 2.f, 320.f}, {200.f, 50.f})
{
    float cx = winSize.x / 2.f;
    center(title, cx, 200.f);
    center(gameOver,  cx, 200.f);
}

void Menu::center(sf::Text &t, float x, float y){
    auto b = t.getGlobalBounds();
    t.setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
    t.setPosition({x, y});
}

void Menu::handleEvent(const sf::Event& event, State &state, const sf::RenderWindow &window){
    const auto* key = event.getIf<sf::Event::MouseButtonPressed>();
    if(!key) return;

    if (state == State::Menu){
        if (startBtn2.isClicked(event, window)) { state = State::Single; lastState = State::Single; }
        if (startBtn.isClicked(event, window)) { state = State::Dual; lastState = State::Dual; }
    }else if(state == State::Gameover){
        if (menuBtn.isClicked(event, window)) state = State::Menu;
        else if (retryBtn.isClicked(event, window)){
            state = lastState;
        }
    }
}

void Menu::update(const sf::RenderWindow& window, State state){
    if (state == State::Menu){
        startBtn.update(window);
        startBtn2.update(window);
    }
    if (state == State::Gameover){
        retryBtn.update(window);
        menuBtn.update(window);
    }
}

void Menu::draw(sf::RenderTarget& target, State state) const{
    if (state == State::Menu){
        target.draw(title);
        startBtn.draw(target);
        startBtn2.draw(target);
    }
    if (state == State::Gameover){
        target.draw(gameOver);
        menuBtn.draw(target);
        retryBtn.draw(target);
    }
}
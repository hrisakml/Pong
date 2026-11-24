#include "menu.hpp"

Menu::Menu(const sf::Font& font, sf::Vector2u winSize)
    :title(font, "PONG", 50), hint(font, "Press Enter", 30),
    gameOver(font, "Game Over", 50), hint2(font, "ENTER: Play Again  |  ESC: Menu", 30)
{
    float cx = winSize.x / 2.f;
    center(title, cx, 220.f);
    center(hint, cx, 320.f);
    center(gameOver, cx, 220.f);
    center(hint2, cx, 320.f);
}

void Menu::center(sf::Text &t, float x, float y){
    auto b = t.getGlobalBounds();
    t.setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
    t.setPosition({x, y});
}

void Menu::handleEvent(const sf::Event& event, State &state){
    const auto* key = event.getIf<sf::Event::KeyPressed>();
    if(!key) return;

    if (state == State::Menu && key->code == sf::Keyboard::Key::Enter){
        state = State::Dual;
    }else if (state == State::Gameover){
        if (key->code == sf::Keyboard::Key::Enter){
            state = State::Dual;
        }else if (key->code == sf::Keyboard::Key::Escape){
            state = State::Menu;
        }
    }
}

void Menu::draw(sf::RenderTarget& target, State state) const{
    if (state == State::Menu){
        target.draw(title);
        target.draw(hint);
    }
    if (state == State::Gameover){
        target.draw(gameOver);
        target.draw(hint2);
    }
}
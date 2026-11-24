#include "button.hpp"

Button::Button(const sf::Font &font, const std::string &label,
                sf::Vector2f center, sf::Vector2f size) 
                :box(size), text(font, label, 24)
{
    box.setOrigin(size/2.f);
    box.setPosition(center);
    box.setFillColor(sf::Color(70, 70, 70));
    box.setOutlineThickness(2.f);
    box.setOutlineColor(sf::Color::White);

    auto b = text.getLocalBounds();
    text.setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
    text.setPosition(center);
};

bool Button::contains(const sf::RenderWindow &window) const{
    sf::Vector2i px = sf::Mouse::getPosition(window);
    sf::Vector2f pos = window.mapPixelToCoords(px);
    return box.getGlobalBounds().contains(pos);
}

void Button::update(const sf::RenderWindow &window){
    hovered = contains(window);
    box.setFillColor(hovered ? sf::Color(120, 120, 120) : sf::Color(70, 70, 70));
}

bool Button::isClicked(const sf::Event &event, const sf::RenderWindow& window) const{
    const auto *mouse = event.getIf<sf::Event::MouseButtonPressed>();
    return mouse && mouse->button == sf::Mouse::Button::Left && contains(window);
}

void Button::draw(sf::RenderTarget &target) const{
    target.draw(box);
    target.draw(text);
}
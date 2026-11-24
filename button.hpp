#pragma once
#include <SFML/Graphics.hpp>

class Button{
    public:
        Button(const sf::Font &font, const std::string &label,
                sf::Vector2f center, sf::Vector2f size);
        void update(const sf::RenderWindow &window);
        bool isClicked(const sf::Event &event, const sf::RenderWindow& window) const;
        void draw(sf::RenderTarget &target) const;
    private:
        sf::RectangleShape box;
        sf::Text text;
        bool hovered = false;

        bool contains(const sf::RenderWindow &window) const;
};
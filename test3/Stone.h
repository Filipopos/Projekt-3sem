#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape {
private:
    int hp;
    bool destroyed;

    static const std::array<sf::Color, 4> colorLut;

public:
    Stone(sf::Vector2f pos, sf::Vector2f size, int lives);

    bool isDestroyed() const;
    sf::FloatRect getBounds() const;

    void hit();
    void draw(sf::RenderTarget& window);
};

#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

    void bounceX();
    void bounceY();

public:
    Pilka(float poczX, float poczY, float ppredX, float ppredY, float r);

    //aktualizacja poz i sprawdzanie scian
    void update(float dTime, float windowWidth, float windowHeight);

    //kolizja z paletko, korzysta z metod paletki
    void resolvePaddleCollision(const Paletka& p);

    void setPosition(const sf::Vector2f& pos);
    void setVelocity(const sf::Vector2f& v);
    void bounceYForce();

    void draw(sf::RenderTarget& target);

    sf::FloatRect getBounds() const;
    float getX() const;
    float getY() const;
    float getVx() const;
    float getVy() const;
};
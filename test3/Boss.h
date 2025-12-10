#pragma once
#include <SFML/Graphics.hpp>

class Pilka;

class Boss {
private:
    sf::RectangleShape shape;
    float speed;
    int hp;
    bool destroyed;

public:
    Boss(float x, float y); // Konstruktor

    void update(float dt);
    bool checkCollision(Pilka& pilka);
    void draw(sf::RenderTarget& target);

    bool isDead() const { return destroyed; }
    void setPosition(float x, float y) { shape.setPosition(x, y); } // Do resetu to
};
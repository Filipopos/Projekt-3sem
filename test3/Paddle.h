#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x, y;
    float szerokosc, wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float poczX, float poczY, float poczSzer, float poczWys, float poczpred);

    //sprawdzanie klawiszy i ruch
    void update(float dTime, float windowWidth);

    void setPosition(const sf::Vector2f& pos);
    void draw(sf::RenderTarget& target);

    
    float getX() const;
    float getY() const;
    float getSzerokosc() const;
    float getWysokosc() const;
};
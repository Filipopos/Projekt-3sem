#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x, y;
    float szerokosc, wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float poczX, float poczY, float poczSzer, float poczWys, float poczpred)
    {
        x = poczX;
        y = poczY;
        szerokosc = poczSzer;
        wysokosc = poczWys;
        predkosc = poczpred;
        shape.setSize({ szerokosc, wysokosc });
        shape.setOrigin(szerokosc / 2, wysokosc / 2);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Green);
    }
    //dTime-czas pomiadzy klatkami
    void moveLeft(float dTime) {
        x -= predkosc * dTime;
        shape.setPosition(x, y);
    }

    void setPosition(const sf::Vector2f& pos) {
        x = pos.x;
        y = pos.y;
        shape.setPosition(x, y);
    }


    void moveRight(float dTime) {
        x += predkosc * dTime;
        shape.setPosition(x, y);
    }

    void clampToBounds(float width) {
        if (x - szerokosc / 2 < 0)
            x = szerokosc / 2;
        if (x + szerokosc / 2 > width)
            x = width - szerokosc / 2.f;
        shape.setPosition(x, y);
    }

    void draw(sf::RenderTarget& target) {
        target.draw(shape);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }
};

#include "Paddle.h"

Paletka::Paletka(float poczX, float poczY, float poczSzer, float poczWys, float poczpred)
{
    x = poczX;
    y = poczY;
    szerokosc = poczSzer;
    wysokosc = poczWys;
    predkosc = poczpred;

    shape.setSize({ szerokosc, wysokosc });
    shape.setOrigin(szerokosc / 2, wysokosc / 2);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}
//to powywalane z game.cpp plus troche z paletki
void Paletka::update(float dTime, float windowWidth) {
    //Sterowanie
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        x -= predkosc * dTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        x += predkosc * dTime;
    }

    // ograniczanie ruchu
    if (x - szerokosc / 2 < 0)
        x = szerokosc / 2;
    if (x + szerokosc / 2 > windowWidth)
        x = windowWidth - szerokosc / 2.f;

    shape.setPosition(x, y);
}

void Paletka::setPosition(const sf::Vector2f& pos) {
    x = pos.x;
    y = pos.y;
    shape.setPosition(x, y);
}

void Paletka::draw(sf::RenderTarget& target) {
    target.draw(shape);
}

float Paletka::getX() const { return x; }
float Paletka::getY() const { return y; }
float Paletka::getSzerokosc() const { return szerokosc; }
float Paletka::getWysokosc() const { return wysokosc; }
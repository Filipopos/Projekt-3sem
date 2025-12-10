#include "pilkah.h"
#include "Paddle.h"
#include <cmath>

Pilka::Pilka(float poczX, float poczY, float ppredX, float ppredY, float r)
{
    x = poczX;
    y = poczY;
    vx = ppredX;
    vy = ppredY;
    radius = r;

    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Pilka::update(float dTime, float windowWidth, float windowHeight) {
    x += vx * dTime * 60.f;
    y += vy * dTime * 60.f;

    if (x - radius <= 0.f) {
        x = radius;
        bounceX();
    }
    else if (x + radius >= windowWidth) {
        x = windowWidth - radius;
        bounceX();
    }

    if (y - radius <= 0.f) {
        y = radius;
        bounceY();
    }

    shape.setPosition(x, y);
}

//kolizja z paletko, korzysta z metod paletki
void Pilka::resolvePaddleCollision(const Paletka& p) {
    float palX = p.getX();
    float palY = p.getY();
    float palW = p.getSzerokosc();
    float palH = p.getWysokosc();

    
    if (x >= palX - palW / 2 - radius && x <= palX + palW / 2 + radius) {
        if (vy > 0 && (y + radius) >= (palY - palH / 2) && (y - radius) < (palY + palH / 2)) {
            y = (palY - palH / 2) - radius - 0.1f;
            bounceY();
            shape.setPosition(x, y);
        }
    }
}

void Pilka::bounceX() { vx = -vx; }
void Pilka::bounceY() { vy = -vy; }
void Pilka::bounceYForce() { vy = -vy; }

void Pilka::setPosition(const sf::Vector2f& pos) {
    x = pos.x; y = pos.y; shape.setPosition(x, y);
}

void Pilka::setVelocity(const sf::Vector2f& v) {
    vx = v.x; vy = v.y;
}
void Pilka::draw(sf::RenderTarget& target) {
    target.draw(shape);
}
sf::FloatRect Pilka::getBounds() const {
    return shape.getGlobalBounds();
}
float Pilka::getY() const { return y; }
float Pilka::getX() const { return x; }
float Pilka::getVx() const { return vx; }
float Pilka::getVy() const { return vy; }
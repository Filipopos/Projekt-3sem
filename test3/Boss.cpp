#include "Boss.h"
#include "pilkah.h"
#include <iostream>

Boss::Boss(float x, float y) {
    shape.setSize({ 60.f, 20.f });
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Blue);
    speed = 150.f;
    hp = 1;
    destroyed = false;
}

void Boss::update(float dt) {
    if (destroyed) return;

    //Poruszanie bosa
    sf::Vector2f pos = shape.getPosition();
    pos.x += speed * dt;

    if (pos.x > 740.f) {
        pos.x = 740.f;
        speed = -speed;
    }
    else if (pos.x < 500.f) {
        pos.x = 500.f;
        speed = -speed;
    }
    shape.setPosition(pos);
}

bool Boss::checkCollision(Pilka& pilka) {
    if (destroyed) return false;

    if (pilka.getBounds().intersects(shape.getGlobalBounds())) {
        //destroyed=true potem nam wyswietla komunikat o wygranej w game.cpp
        destroyed = true;
        return true; //jak nastapila kolizja to zwracamy true
    }
    return false;
}

void Boss::draw(sf::RenderTarget& target) {
    if (!destroyed) target.draw(shape);
}
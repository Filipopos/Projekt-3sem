#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Paddle.h"
#include "pilkah.h"
#include "Stone.h"

int main() {
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Arkanoid test");
    window.setFramerateLimit(60);

    srand(time(NULL));

    Paletka pal(320.f, 440.f, 100.f, 20.f, 400.f);
    Pilka pilka(320.f, 240.f, 3.f, 4.f, 8.f);

    std::vector<Brick> bloki;

    const int ILOSC_WIERSZY = 7;
    const int ILOSC_KOLUMN = 6;

    const float ODSTEP = 2.f;
    const float WYSOKOSC_CEGIEL = 25.f;
    const float START_Y = 50.f;

    // automatycznie wyliczana szerokość cegły
    float SZEROKOSC_CEGIEL =
        (WIDTH - (ILOSC_KOLUMN + 1) * ODSTEP) / ILOSC_KOLUMN;


    bloki.reserve(ILOSC_WIERSZY * ILOSC_KOLUMN);

    for (int w = 0; w < ILOSC_WIERSZY; w++)
    {
        for (int k = 0; k < ILOSC_KOLUMN; k++)
        {
            // obliczamy pozycję każdej cegły
            float x = ODSTEP + k * (SZEROKOSC_CEGIEL + ODSTEP);
            float y = START_Y + w * (WYSOKOSC_CEGIEL + ODSTEP);

            // logika punktów życia zależna od numeru wiersza
            int zycie = 1;

            if (w < 2)      zycie = 3;   // wiersze 0–1: 3 HP
            else if (w < 4) zycie = 2;   // wiersze 2–3: 2 HP
            else            zycie = 1;   // wiersze 4–6: 1 HP

            bloki.emplace_back(
                sf::Vector2f(x, y),
                sf::Vector2f(SZEROKOSC_CEGIEL, WYSOKOSC_CEGIEL),
                zycie
            );
        }
    }


    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        // sterowanie
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            pal.moveLeft(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            pal.moveRight(dt);

        pal.clampToBounds(WIDTH);

        // ruch piłki
        pilka.move(dt);
        pilka.collideWalls(WIDTH, HEIGHT);

        if (pilka.collidePaddle(pal))
            std::cout << "HIT PADDLE\n";

        if (pilka.getY() - pilka.getRadius() > HEIGHT) {
            std::cout << "MISS! KONIEC GRY\n";
            window.close();
        }

        // kolizje piłka–cegła
        for (Brick& b : bloki) {
            if (!b.czyZniszczony()) {
                if (pilka.getBounds().intersects(b.getBounds())) {
                    b.trafienie();
                    pilka.bounceY();
                }
            }
        }

        // rysowanie
        window.clear(sf::Color(20, 20, 30));
        pal.draw(window);
        pilka.draw(window);

        for (Brick& b : bloki)
            b.draw(window);

        window.display();
    }

    return 0;
}

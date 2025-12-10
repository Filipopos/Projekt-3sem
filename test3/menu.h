#pragma once
#include <SFML/Graphics.hpp>

#define MAX_LICZBA_POZIOMOW 5

class Menu
{
private:
    int wybraneOpcje;
    sf::Font font;
    sf::Text opcje[MAX_LICZBA_POZIOMOW];

public:
    Menu(float szerokosc, float wysokosc)
    {
        wybraneOpcje = 0;
        font.loadFromFile("assets/fonts/Starborn.ttf");
        const char* labels[MAX_LICZBA_POZIOMOW] = { "Poziom 1", "Poziom 2", "Poziom 3", "Wczytaj gre", "Wyjscie" };

        for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
        {
            opcje[i].setFont(font);
            opcje[i].setCharacterSize(40);
            opcje[i].setString(labels[i]);
            opcje[i].setFillColor(sf::Color::White);
            opcje[i].setPosition(szerokosc / 2 - 100, wysokosc / 4 + i * 60);
        }
        opcje[0].setFillColor(sf::Color::Red);
    }

//poryszanie po menu, jak nic sie nie wybierze to zwraca -1
    int handleInput(sf::Event event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                przesunG();
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                przesunD();
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                return wybraneOpcje; // Zwracamy co wybrano
            }
        }
        return -1; // Nic nie wybrano
    }
    

    void draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
            window.draw(opcje[i]);
    }

private:
    void przesunG()
    {
        if (wybraneOpcje - 1 >= 0) {
            opcje[wybraneOpcje].setFillColor(sf::Color::White);
            wybraneOpcje--;
            opcje[wybraneOpcje].setFillColor(sf::Color::Red);
        }
    }

    void przesunD()
    {
        if (wybraneOpcje + 1 < MAX_LICZBA_POZIOMOW) {
            opcje[wybraneOpcje].setFillColor(sf::Color::White);
            wybraneOpcje++;
            opcje[wybraneOpcje].setFillColor(sf::Color::Red);
        }
    }
};
#pragma once
#include <SFML/Graphics.hpp>

#define MAX_LICZBA_POZIOMOW 6

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

        const char* labels[MAX_LICZBA_POZIOMOW] =
        {
            "Nowa gra",
            "Wczytaj gre",
            "Poziom 1",
            "Poziom 2",
            "Poziom 3",
            "Wyjscie"
        };

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

    void draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
            window.draw(opcje[i]);
    }

    void przesunG()
    {
        if (wybraneOpcje - 1 >= 0)
        {
            opcje[wybraneOpcje].setFillColor(sf::Color::White);
            wybraneOpcje--;
            opcje[wybraneOpcje].setFillColor(sf::Color::Red);
        }
    }

    void przesunD()
    {
        if (wybraneOpcje + 1 < MAX_LICZBA_POZIOMOW)
        {
            opcje[wybraneOpcje].setFillColor(sf::Color::White);
            wybraneOpcje++;
            opcje[wybraneOpcje].setFillColor(sf::Color::Red);
        }
    }

    int getSelectedItem() const { return wybraneOpcje; }
};

#pragma once
#include <SFML/Graphics.hpp>

#define MAX_LICZBA_POZIOMOW 4

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

        if (!font.loadFromFile("assets/fonts/Starborn.ttf"))
        {
            //std::cout << "nie moge zaladowac czcionki " << std::endl;
        }

//nowa gra
        opcje[0].setFont(font);
        opcje[0].setFillColor(sf::Color::Red);
        opcje[0].setString("Nowa gra");
        opcje[0].setCharacterSize(40);
        opcje[0].setPosition(szerokosc / 2 - 100, wysokosc / 4);

//wczytaj gre
        opcje[1].setFont(font);
        opcje[1].setFillColor(sf::Color::White);
        opcje[1].setString("Wczytaj gre");
        opcje[1].setCharacterSize(40);
        opcje[1].setPosition(szerokosc / 2 - 110, wysokosc / 4 + 60);

//wyniki
        opcje[2].setFont(font);
        opcje[2].setFillColor(sf::Color::White);
        opcje[2].setString("Wyniki");
        opcje[2].setCharacterSize(40);
        opcje[2].setPosition(szerokosc / 2 - 80, wysokosc / 4 + 120);

//wyjscie
        opcje[3].setFont(font);
        opcje[3].setFillColor(sf::Color::White);
        opcje[3].setString("Wyjscie");
        opcje[3].setCharacterSize(40);
        opcje[3].setPosition(szerokosc / 2 - 80, wysokosc / 4 + 180);
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

    int getSelectedItem() const
    {
        return wybraneOpcje;
    }
};

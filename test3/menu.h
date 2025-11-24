#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

inline void myDelay(int czas)
{
    sf::Clock clk;
    while (clk.getElapsedTime().asMilliseconds() < czas) {}
}


class Menu
{
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[3];

public:
    Menu(float width, float height)
    {
        if (!font.loadFromFile("assets/fonts/Starborn.ttf"));
            std::cout << "Nie mogę załadować czcionki!\n";

        menu[0].setFont(font);
        menu[0].setFillColor(sf::Color::Red);
        menu[0].setString("Nowa gra");
        menu[0].setPosition(width / 2 - 50, height / 2 - 50);

        menu[1].setFont(font);
        menu[1].setFillColor(sf::Color::White);
        menu[1].setString("Wyniki");
        menu[1].setPosition(width / 2 - 50, height / 2);

        menu[2].setFont(font);
        menu[2].setFillColor(sf::Color::White);
        menu[2].setString("Wyjscie");
        menu[2].setPosition(width / 2 - 50, height / 2 + 50);

        selectedItemIndex = 0;
    }

    void draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < 3; i++)
            window.draw(menu[i]);
    }

    void przesunG()
    {
        if (selectedItemIndex - 1 >= 0)
        {
            menu[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex--;
            menu[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    void przesunD()
    {
        if (selectedItemIndex + 1 < 3)
        {
            menu[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex++;
            menu[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    int getSelectedItem() const
    {
        return selectedItemIndex;
    }
};

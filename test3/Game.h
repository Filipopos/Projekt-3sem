#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Menu.h"
#include "Paddle.h"
#include "pilkah.h"
#include "Stone.h"

class Game
{
private:
    enum class GameState { Menu, Playing, Exiting };

    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;

    GameState m_state;

    // MENU
    Menu m_menu;

    // GAMEPLAY
    Paletka m_paletka;
    Pilka   m_pilka;
    std::vector<Stone> m_bloki;

    // Maszyna stanów:
    void processEvents();
    void update(sf::Time dt);
    void render();

    // Logika gry
    void updateGameplay(sf::Time dt);
    void renderGameplay();
    void loadLevel();
    void resetGameplay();

public:
    Game();
    void run();
};

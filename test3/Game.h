#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Menu.h"
#include "Paddle.h"
#include "pilkah.h"
#include "Stone.h"
#include "GameState.h"
#include "Boss.h"

class Game
{
private:
    enum class GameMode { Menu, Playing };

    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;

    GameMode m_state;
    Menu m_menu;

    Paletka m_paletka;
    Pilka   m_pilka;
    std::vector<Stone> m_bloki;

    Boss m_boss;

    int m_score;
    sf::Font m_font;
    sf::Text m_scoreText;

    void processEvents();
    void update(sf::Time dt);
    void render();

    void updateGameplay(sf::Time dt);
    void renderGameplay();

    
    void loadLevel1();
    void loadLevel2();
    void loadLevel3();

    void resetGameplay();

public:
    Game();
    void run();
};

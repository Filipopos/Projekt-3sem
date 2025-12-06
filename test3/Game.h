#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Menu.h"
#include "Paddle.h"
#include "pilkah.h"
#include "Stone.h"
#include "GameState.h"

class Game
{
private:
    enum class GameMode{ Menu, Playing, Exiting };

    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;

    GameMode m_state;

   
    Menu m_menu;

   

   
    Paletka m_paletka;
    Pilka   m_pilka;
    std::vector<Stone> m_bloki;
    int m_score;
    sf::Font m_font;
    sf::Text m_scoreText;

    
    void processEvents();
    void update(sf::Time dt);
    void render();

    
    void updateGameplay(sf::Time dt);
    void renderGameplay();
    void loadLevel();
    void resetGameplay();

public:
    Game();
    void run();
};

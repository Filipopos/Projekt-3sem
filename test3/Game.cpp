#include "Game.h"
#include <iostream>
#include <algorithm>//potrzebne do usuwania blokow

Game::Game()
    : m_window(sf::VideoMode({ 800, 600 }), "Arkanoid")
    , m_menu(m_window.getSize().x, m_window.getSize().y)
    , m_paletka(400.f, 550.f, 100.f, 20.f, 400.f)
    , m_pilka(400.f, 310.f, 4.f, 3.f, 8.f)
    , m_boss(600.f, 10.f)
    , m_state(GameMode::Menu)
    , m_score(0)
{
    m_window.setFramerateLimit(60); 

    m_font.loadFromFile("assets/fonts/Starborn.ttf");
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(28);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(10, 10);
    loadLevel(1);
}

void Game::run()
{
    while (m_window.isOpen())
    {
        processEvents();
        update(m_deltaClock.restart());
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        // zapis odczyt, zostaly w game bo dotycza calej gry
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::F5) {
                GameState gs;
                gs.capture(m_paletka, m_pilka, m_bloki, m_score);
                if (gs.saveToFile("save.txt")) std::cout << "Zapisano gre!\n";
            }
            if (event.key.code == sf::Keyboard::F9) {
                GameState gs;
                if (gs.loadFromFile("save.txt")) {
                    gs.apply(m_paletka, m_pilka, m_bloki, m_score);
                    m_score = gs.getScore();
                    m_state = GameMode::Playing;
                    std::cout << "Wczytano gre!\n";
                }
            }
            // Wyjscie z gry do menu
            if (event.key.code == sf::Keyboard::Escape && m_state == GameMode::Playing) {
                m_state = GameMode::Menu;
            }
        }

        
        if (m_state == GameMode::Menu)
        {
            
            int action = m_menu.handleInput(event);
            //0-leve1, 1-level2, 2-level3, 3-wczytaj, 4-wyjdz
            if (action != -1)
            {
                
                
                if (action == 0) { resetGameplay(); loadLevel(1); m_state = GameMode::Playing; }
                else if (action == 1) { resetGameplay(); loadLevel(2); m_state = GameMode::Playing; }
                else if (action == 2) { resetGameplay(); loadLevel(3); m_state = GameMode::Playing; }
                   
                
                else if (action == 3) {
                    
                    GameState gs;
                    if (gs.loadFromFile("save.txt")) {
                        gs.apply(m_paletka, m_pilka, m_bloki, m_score);
                        m_score = gs.getScore();
                        m_state = GameMode::Playing;
                    }
                }
                else if (action == 4) { m_window.close(); }
            }
        }
    }
}
void Game::update(sf::Time dt)
{
    if (m_state == GameMode::Playing)
        updateGameplay(dt);
}

void Game::render()
{
    m_window.clear();

    if (m_state == GameMode::Menu)
        m_menu.draw(m_window);
    else if (m_state == GameMode::Playing)
        renderGameplay();

    m_window.display();
}




void Game::resetGameplay()
{
    m_paletka = Paletka(400.f, 550.f, 100.f, 20.f, 400.f);
    m_pilka = Pilka(400.f, 310.f, 4.f, 3.f, 8.f);
    m_score = 0;
    m_boss = Boss(600.f, 10.f);

}

void Game::updateGameplay(sf::Time dt)
{
    float t = dt.asSeconds();
    //logika gry i kolizji, wszystko w klasach odpowiednich jest
    m_paletka.update(t, 800.f); 

    
    m_pilka.update(t, 800.f, 600.f);

    
    m_pilka.resolvePaddleCollision(m_paletka);

    for (auto& s : m_bloki)
    {
        
        if (s.checkCollision(m_pilka))
        {
            m_score += 10; 
        }
    }

    
    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(),
            [](const Stone& s) { return s.isDestroyed(); }),
        m_bloki.end()
    );

    //boss nasz
    m_boss.update(t);

    if (m_boss.checkCollision(m_pilka))
    {
        std::cout << "============================" << std::endl;
        std::cout << "WYGRALES!" << std::endl;
        std::cout << "============================" << std::endl;
        m_state = GameMode::Menu;
        return;
    }

    //przegrana
    if (m_pilka.getY() > 600)
    {
        m_state = GameMode::Menu;
    }

    m_scoreText.setString("Punkty: " + std::to_string(m_score));
}

void Game::renderGameplay()
{
    m_paletka.draw(m_window);
    m_pilka.draw(m_window);

    for (auto& blok : m_bloki)
        blok.draw(m_window);

    m_boss.draw(m_window);

    m_window.draw(m_scoreText);
}


void Game::loadLevel(int levelNumber)
{
    m_bloki.clear();

    if (levelNumber == 1) {
        
        m_bloki = LevelManager::loadLevel1();
    }
    else if (levelNumber == 2) {
        m_bloki = LevelManager::loadLevel2();
    }
    else if (levelNumber == 3) {
        m_bloki = LevelManager::loadLevel3();
    }
}
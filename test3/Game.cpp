#include "Game.h"
#include <iostream>

Game::Game()
    : m_window(sf::VideoMode({ 800, 600 }), "Arkanoid")
    , m_menu(m_window.getSize().x, m_window.getSize().y)
    , m_paletka(400.f, 550.f, 100.f, 20.f, 400.f)
    , m_pilka(400.f, 200.f, 4.f, 3.f, 8.f)
    , m_state(GameMode::Menu)
    , m_score(0)
{
    m_window.setFramerateLimit(60);

    m_font.loadFromFile("assets/fonts/Starborn.ttf");
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(28);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(10, 10);

    loadLevel1();
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

        if (event.type == sf::Event::KeyPressed)
        {
            sf::Keyboard::Key key = event.key.code;

            
            // ZAPIS GRY
            
            if (key == sf::Keyboard::F5)
            {
                GameState gs;
                gs.capture(m_paletka, m_pilka, m_bloki, m_score);

                if (gs.saveToFile("save.txt"))
                    std::cout << "Zapisano gre!\n";
            }

           
            // WCZYTANIE GRY
            
            if (key == sf::Keyboard::F9)
            {
                GameState gs;
                if (gs.loadFromFile("save.txt"))
                {
                    gs.apply(m_paletka, m_pilka, m_bloki, m_score);

                    m_score = gs.getScore();
                    std::cout << "Wczytano gre!\n";
                }
            }

            // ====================== MENU ======================
            if (m_state == GameMode::Menu)
            {
                if (key == sf::Keyboard::Up)
                {
                    m_menu.przesunG();
                }

                if (key == sf::Keyboard::Down)
                {
                    m_menu.przesunD();
                }

                if (key == sf::Keyboard::Enter)
                {
                    int selected = m_menu.getSelectedItem();

                    switch (selected)
                    {
                    case 0: // NOWA GRA
                        resetGameplay();
                        m_state = GameMode::Playing;
                        break;

                    case 1: // WCZYTAJ GRE
                    {
                        GameState gs;
                        if (gs.loadFromFile("save.txt"))
                        {
                            gs.apply(m_paletka, m_pilka, m_bloki, m_score);

                            m_score = gs.getScore();
                            m_state = GameMode::Playing;
                        }
                        break;
                    }

                    case 2: // poziom 1
                        resetGameplay();
                        loadLevel1();
                        m_state = GameMode::Playing;
                        break;

                    case 3: // poziom 2
                        resetGameplay();
                        loadLevel2();
                        m_state = GameMode::Playing;
                        break;

                    case 4: // poziom 3
                        resetGameplay();
                        loadLevel3();
                        m_state = GameMode::Playing;
                        break;

                    case 5: // WYJŚCIE
                        m_window.close();
                        break;
                    }
                }
            }

            // =================== GAMEPLAY ====================
            else if (m_state == GameMode::Playing)
            {
                if (key == sf::Keyboard::Escape)
                    m_state = GameMode::Menu;
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

//                          GAMEPLAY


void Game::resetGameplay()
{
    m_paletka = Paletka(400.f, 550.f, 100.f, 20.f, 400.f);
    m_pilka = Pilka(400.f, 200.f, 4.f, 3.f, 8.f);
    m_score = 0;
}

void Game::updateGameplay(sf::Time dt)
{
    float t = dt.asSeconds();

    // Ruch paletki
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft(t);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight(t);

    m_paletka.clampToBounds(800);

    // Ruch piłki
    m_pilka.move(t);
    m_pilka.collideWalls(800, 600);
    m_pilka.collidePaddle(m_paletka);

    // Kolizje z blokami
    for (auto& s : m_bloki)
    {
        if (!s.isDestroyed() &&
            m_pilka.getBounds().intersects(s.getBounds()))
        {
            s.hit();
            m_pilka.bounceY();
            m_score += 10;
        }
    }

    // Usuwanie zniszczonych
    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(),
            [](const Stone& s) { return s.isDestroyed(); }),
        m_bloki.end()
    );

    // Czy piłka spadła
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

    m_window.draw(m_scoreText);
}


//LEVELS


void Game::loadLevel()
{
    loadLevel1();
}

void Game::loadLevel1()
{
    m_bloki.clear();

    const int rows = 7;
    const int cols = 6;

    const float blockH = 25.f;
    const float gap = 2.f;
    const float startY = 50.f;

    float blockW = (800.f - (cols + 1) * gap) / cols;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            float x = gap + c * (blockW + gap);
            float y = startY + r * (blockH + gap);

            int hp = 1;
            if (r < 2)      hp = 3;
            else if (r < 4) hp = 2;

            m_bloki.emplace_back(sf::Vector2f(x, y),
                sf::Vector2f(blockW, blockH),
                hp);
        }
    }
}

void Game::loadLevel2()
{
    m_bloki.clear();

    const int rows = 5;
    const int cols = 10;

    const float blockH = 25.f;
    const float gap = 2.f;
    const float startY = 80.f;

    float blockW = (800.f - (cols + 1) * gap) / cols;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            float x = gap + c * (blockW + gap);
            float y = startY + r * (blockH + gap);

            int hp = (r % 2 == 0) ? 2 : 1;

            m_bloki.emplace_back(sf::Vector2f(x, y),
                sf::Vector2f(blockW, blockH),
                hp);
        }
    }
}

void Game::loadLevel3()
{
    m_bloki.clear();

    const float blockH = 25.f;
    const float gap = 3.f;
    const float startY = 60.f;

    float blockW = 80.f;

    for (int c = 0; c < 8; c++)
    {
        float x = 50 + c * (blockW + gap);
        m_bloki.emplace_back(sf::Vector2f(x, startY),
            sf::Vector2f(blockW, blockH),
            3);
    }

    for (int c = 0; c < 6; c++)
    {
        float x = 100 + c * (blockW + gap);
        m_bloki.emplace_back(sf::Vector2f(x, startY + 40),
            sf::Vector2f(blockW, blockH),
            2);
    }

    for (int c = 0; c < 4; c++)
    {
        float x = 150 + c * (blockW + gap);
        m_bloki.emplace_back(sf::Vector2f(x, startY + 80),
            sf::Vector2f(blockW, blockH),
            1);
    }
}

#include "Game.h"
#include "GameState.h" 

Game::Game()
    : m_window(sf::VideoMode({ 800, 600 }), "Arkanoid")
    , m_menu(m_window.getSize().x, m_window.getSize().y)
    , m_paletka(400.f, 550.f, 100.f, 20.f, 400.f)
    , m_pilka(400.f, 200.f, 4.f, 3.f, 8.f)
    , m_state(GameMode::Menu)
    , m_score(-1200)

{
    m_window.setFramerateLimit(60);
    loadLevel();
    if (!m_font.loadFromFile("assets/fonts/Starborn.ttf"))
    {
        std::cout << "Blad ladowania czcionki do wyniku!\n";
    }

    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(10, 10);

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

            if (key == sf::Keyboard::F5)
            {
                GameState gs;
                gs.capture(m_paletka, m_pilka, m_bloki);

                if (gs.saveToFile("save.txt"))
                    std::cout << "Zapisano gre!\n";
            }

            if (key == sf::Keyboard::F9)
            {
                GameState gs;
                if (gs.loadFromFile("save.txt"))
                {
                    gs.apply(m_paletka, m_pilka, m_bloki);
                    std::cout << "Wczytano gre!\n";
                }
            }


//menu
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

                    if (selected == 0)   
                    {
                        resetGameplay();
                        m_state = GameMode::Playing;
                    }
                    else if (selected == 1)   
                    {
                        GameState gs;
                        if (gs.loadFromFile("save.txt"))
                        {
                            gs.apply(m_paletka, m_pilka, m_bloki);
                            m_state = GameMode::Playing;
                            std::cout << "Wczytano gre!\n";
                        }
                        else
                        {
                            std::cout << "Brak pliku save.txt lub blad w pliku.\n";
                        }
                    }
                    else if (selected == 2)   
                    {
                        std::cout << "Brak systemu wynikow.\n";
                    }
                    else if (selected == 3) 
                    {
                        m_window.close();
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



//gameplay


void Game::loadLevel()
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

            m_bloki.emplace_back(
                sf::Vector2f(x, y),
                sf::Vector2f(blockW, blockH),
                hp
            );
        }
    }
}

void Game::resetGameplay()
{
    m_paletka = Paletka(400.f, 550.f, 100.f, 20.f, 400.f);
    m_pilka = Pilka(400.f, 200.f, 4.f, 3.f, 8.f);
    loadLevel();
    m_score = -1200;
    m_scoreText.setString("Punkty: 0");

}   

void Game::updateGameplay(sf::Time dt)
{
    float t = dt.asSeconds();

    // ----- sterowanie paletką -----
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft(t);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight(t);

    m_paletka.clampToBounds(800);

    // ----- ruch pilki -----
    m_pilka.move(t);
    m_pilka.collideWalls(800, 600);
    m_pilka.collidePaddle(m_paletka);

    // ----- kolizje z cegłami -----
    for (auto& s : m_bloki)
    {
        if (!s.isDestroyed() &&
            m_pilka.getBounds().intersects(s.getBounds()))
        {
            s.hit();
            m_pilka.bounceY();

          
            //100 za zielony, 200 za zolty i 300 za czerowny
            if (s.getHP() == 2) m_score += 100;//po zderzeniu ma 2 czyli wczesniej mial 3
            else if (s.getHP() == 1) m_score += 200;
            else if (s.getHP() == 0) m_score += 300;
        }
        m_scoreText.setString("Punkty: " + std::to_string(m_score));

    }


    // ----- usuwanie zniszczonych bloków -----
    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(),
            [](const Stone& s) { return s.isDestroyed(); }),
        m_bloki.end()
    );

    // ----- reset po straceniu piłki -----
    if (m_pilka.getY() > 600)
    {
        resetGameplay();
        m_state = GameMode::Menu;
    }
}

void Game::renderGameplay()
{
    m_paletka.draw(m_window);
    m_pilka.draw(m_window);

    for (auto& blok : m_bloki)
        blok.draw(m_window);

    m_window.draw(m_scoreText);
}

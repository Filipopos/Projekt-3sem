#include "levele.h"

std::vector<Stone> LevelManager::loadLevel1()
{
    std::vector<Stone> tempBloki; // Tymczasowy pojemnik

    const int rows = 7;
    const int cols = 6;
    const float blockH = 25.f;
    const float gap = 2.f;
    const float startY = 50.f;
    float blockW = (800.f - (cols + 1) * gap) / cols;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            float x = gap + c * (blockW + gap);
            float y = startY + r * (blockH + gap);
            int hp = 1;
            if (r < 2) hp = 3;
            else if (r < 4) hp = 2;

            //tymczasowy wektor
            tempBloki.emplace_back(sf::Vector2f(x, y), sf::Vector2f(blockW, blockH), hp);
        }
    }
    return tempBloki; //oddaje gotowy zestaw
}

std::vector<Stone> LevelManager::loadLevel2()
{
    std::vector<Stone> tempBloki;

    const int rows = 5;
    const int cols = 10;
    const float blockH = 25.f;
    const float gap = 2.f;
    const float startY = 80.f;
    float blockW = (800.f - (cols + 1) * gap) / cols;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            float x = gap + c * (blockW + gap);
            float y = startY + r * (blockH + gap);
            int hp = (r % 2 == 0) ? 2 : 1;
            tempBloki.emplace_back(sf::Vector2f(x, y), sf::Vector2f(blockW, blockH), hp);
        }
    }
    return tempBloki;
}

std::vector<Stone> LevelManager::loadLevel3()
{
    std::vector<Stone> tempBloki;

    const float blockH = 25.f;
    const float gap = 3.f;
    const float startY = 60.f;
    float blockW = 80.f;

    for (int c = 0; c < 8; c++) {
        float x = 50 + c * (blockW + gap);
        tempBloki.emplace_back(sf::Vector2f(x, startY), sf::Vector2f(blockW, blockH), 3);
    }
    for (int c = 0; c < 6; c++) {
        float x = 100 + c * (blockW + gap);
        tempBloki.emplace_back(sf::Vector2f(x, startY + 40), sf::Vector2f(blockW, blockH), 2);
    }
    for (int c = 0; c < 4; c++) {
        float x = 150 + c * (blockW + gap);
        tempBloki.emplace_back(sf::Vector2f(x, startY + 80), sf::Vector2f(blockW, blockH), 1);
    }
    return tempBloki;
}
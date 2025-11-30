#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Paddle.h"
#include "pilkah.h"
#include "Stone.h"

struct BlockData {
    float x, y;
    int hp;
};

class GameState
{
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:

//zapis danych z obiektow hry
    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones)
    {
       
        paddlePosition = sf::Vector2f(p.getX(), p.getY());


        ballPosition = sf::Vector2f(b.getX(), b.getY());
        ballVelocity = sf::Vector2f(b.getVx(), b.getVy());

        
        blocks.clear();
        for (const Stone& s : stones)
        {
            if (!s.isDestroyed())
            {
                BlockData bd;
                bd.x = s.getPosition().x;
                bd.y = s.getPosition().y;
                bd.hp = s.getHP();
                blocks.push_back(bd);
            }
        }
    }

//zapois do pliku

    bool saveToFile(const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        file << "PADDLE "
            << paddlePosition.x << " " << paddlePosition.y << "\n";

        file << "BALL "
            << ballPosition.x << " " << ballPosition.y << " "
            << ballVelocity.x << " " << ballVelocity.y << "\n";

        file << "BLOCKS_COUNT " << blocks.size() << "\n";

        for (auto& b : blocks)
            file << b.x << " " << b.y << " " << b.hp << "\n";

        return true;
    }

//wczytanie z pliku

    bool loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::string label;

        file >> label >> paddlePosition.x >> paddlePosition.y;

        file >> label >> ballPosition.x >> ballPosition.y
            >> ballVelocity.x >> ballVelocity.y;

        int count;
        file >> label >> count;

        blocks.clear();
        for (int i = 0; i < count; i++)
        {
            BlockData bd;
            file >> bd.x >> bd.y >> bd.hp;
            blocks.push_back(bd);
        }

        return true;
    }


    void apply(Paletka& p, Pilka& b, std::vector<Stone>& stones)
    {

        p.setPosition(paddlePosition);


        b.setPosition(ballPosition);
        b.setVelocity(ballVelocity);

        stones.clear();

        const int rows = 7;
        const int cols = 6;
        const float gap = 2.f;
        const float blockH = 25.f;
        float blockW = (800.f - (cols + 1) * gap) / cols;

        for (const auto& bd : blocks)
        {
            stones.emplace_back(
                sf::Vector2f(bd.x, bd.y),
                sf::Vector2f(blockW, blockH),
                bd.hp
            );
        }
    }
};

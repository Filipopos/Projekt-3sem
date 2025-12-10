#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Paddle.h"
#include "pilkah.h"
#include "Stone.h"

struct BlockData {
    float x, y;
    float w, h;
    int hp;
};

class GameState
{
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    int score = 0;

    std::vector<BlockData> blocks;

public:

    
    //getter/setter do wyniku
    
    void setScore(int s) { score = s; }
    int  getScore() const { return score; }


   
    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones, int points)
    {
        score = points;

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
                bd.w = s.getSize().x;
                bd.h = s.getSize().y;
                bd.hp = s.getHP();
                blocks.push_back(bd);
            }
        }
    }

     
    //savuje i dodaje opisy do pliku
    
    bool saveToFile(const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        file << "SCORE " << score << "\n";

        file << "PADDLE "
            << paddlePosition.x << " " << paddlePosition.y << "\n";

        file << "BALL "
            << ballPosition.x << " " << ballPosition.y << " "
            << ballVelocity.x << " " << ballVelocity.y << "\n";

        file << "BLOCKS_COUNT " << blocks.size() << "\n";

        for (auto& b : blocks)
            file << b.x << " " << b.y << " "
            << b.w << " " << b.h << " "
            << b.hp << "\n";

        return true;
    }

    
    
    
    bool loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::string label;

        file >> label >> score;

        file >> label >> paddlePosition.x >> paddlePosition.y;

        file >> label >> ballPosition.x >> ballPosition.y
            >> ballVelocity.x >> ballVelocity.y;

        int count;
        file >> label >> count;

        blocks.clear();
        for (int i = 0; i < count; i++)
        {
            BlockData bd;
            file >> bd.x >> bd.y >> bd.w >> bd.h >> bd.hp;
            blocks.push_back(bd);
        }

        return true;
    }

    
    
    
    void apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, int& outScore)
    {
        outScore = score;

        p.setPosition(paddlePosition);
        b.setPosition(ballPosition);
        b.setVelocity(ballVelocity);

        stones.clear();

        for (const auto& bd : blocks)
        {
            stones.emplace_back(
                sf::Vector2f(bd.x, bd.y),
                sf::Vector2f(bd.w, bd.h),
                bd.hp
            );
        }
    }
};

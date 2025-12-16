#pragma once
#include <vector>
#include "Stone.h"

class LevelManager {
public:
    static std::vector<Stone> loadLevel1();
    static std::vector<Stone> loadLevel2();
    static std::vector<Stone> loadLevel3();
};
#pragma once

#include <vector>

#include <SDL3/SDL.h>

#include "GameObject.hpp"
#include "SquareGrid.hpp"

class Game {
public:
    Game();
    ~Game();
    
    SquareGrid grid;

    // Will get rid of soon
    std::vector<std::unique_ptr<GameObject>> gameObjects;

private:
    
};

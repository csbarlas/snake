#pragma once

#include <vector>

#include <SDL3/SDL.h>

#include "GameObject.hpp"
#include "SquareGrid.hpp"

enum class GameState {
    Running,
    Win,
    Lost,
    ForceQuit
};


class Game {
public:
    Game();
    ~Game();
    
    GameState state;
    SquareGrid grid;

private:
    
};

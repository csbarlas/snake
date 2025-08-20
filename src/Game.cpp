#include "Game.hpp"

#include <vector>
#include <memory>

Game::Game() : grid(10), snake(&grid) {
    SDL_Log("Game constructor called");
}

Game::~Game() {
    SDL_Log("Game destructor called");
}

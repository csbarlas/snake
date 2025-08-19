#include "Game.hpp"

#include <vector>
#include <memory>

Game::Game() : grid(12), snake(&grid) {
    SDL_Log("Game constructor called");
}

Game::~Game() {
    SDL_Log("Game destructor called");
}

#include "Game.hpp"

#include <vector>
#include <memory>

Game::Game() : grid(6), snake(&grid) {
    SDL_Log("Game constructor called");
}

Game::~Game() {
    SDL_Log("Game destructor called");
}
#include "Game.hpp"

#include <vector>
#include <memory>

Game::Game() {
    SDL_Log("Game constructor called");
    std::unique_ptr<GameObject> tempObj = std::make_unique<DummyObject>();
    gameObjects.push_back(std::move(tempObj));
}

Game::~Game() {
    SDL_Log("Game destructor called");
}

void DummyObject::render(SDL_Renderer* renderer) {
    SDL_Log("DummyObject render called");
}

void DummyObject::update() {
    SDL_Log("DummyObject update called");
}
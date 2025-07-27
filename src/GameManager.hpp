#pragma once

#include <SDL3/SDL.h>
#include <memory>

#include "Game.hpp"

class GameManager {
public:
    GameManager();
    ~GameManager();

    bool init();
    void enterMainLoop();

private:
    SDL_Window* gWindow{nullptr};
    SDL_Renderer* gWindowRenderer{nullptr};
    
    std::unique_ptr<Game> currentGame;

    bool processEvents();
    void update();
    void render();
};

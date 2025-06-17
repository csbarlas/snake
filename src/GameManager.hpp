#pragma once

#include <SDL3/SDL.h>

#include "Game.hpp"

class GameManager {
public:
    ~GameManager();

    bool init();
    void enterMainLoop();

private:
    SDL_Window* gWindow{nullptr};
    SDL_Renderer* gWindowRenderer{nullptr};
    
    Game currentGame;

    bool processEvents();
    void update();
    void render();
};

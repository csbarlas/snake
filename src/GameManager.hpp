#pragma once

#include <SDL3/SDL.h>

class GameManager {
public:
    GameManager();

    bool init();
    void enterMainLoop();

private:
    SDL_Window* gWindow{nullptr};
    SDL_Renderer* gWindowRenderer{nullptr};

    bool processEvents();
    void update();
    void render();
};

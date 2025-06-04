#include "GameManager.hpp"

#include <SDL3/SDL.h>

GameManager::GameManager() {
    SDL_Log("GameManager initialized");
}

bool GameManager::init() {
    bool success{true};

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if (SDL_CreateWindowAndRenderer("Snake", 500, 500, SDL_WINDOW_RESIZABLE, &gWindow, &gWindowRenderer); gWindow == nullptr || gWindowRenderer == nullptr) {
            SDL_Log("SDL could not create window or renderer! Error: %s\n", SDL_GetError());
            success = false;
        }

        SDL_SetRenderLogicalPresentation(gWindowRenderer, 500, 500, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    }

    return success;
}

void GameManager::enterMainLoop() { 
    bool quit{false};

    while (!quit) {
        bool shouldQuit{processEvents()};
        if (shouldQuit) {
            break;
        }

        update();
        render();
    }
}

bool GameManager::processEvents() {
    SDL_Event event;
    SDL_zero(event);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return true;
        }
    }

    return false;
}

void GameManager::update() { }

void GameManager::render() { }

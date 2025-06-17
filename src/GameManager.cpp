// 1. Own Header
#include "GameManager.hpp"

// 2. C++ Standard Library
#include <vector>

// 3. Third-party Libraries
#include <SDL3/SDL.h>

// 4. Project Headers

namespace {
    constexpr int FRAME_RATE{60};
    constexpr Uint64 FRAME_TIME{(int)1e9 / FRAME_RATE};
}

GameManager::~GameManager() {
    if (gWindowRenderer) {
        SDL_DestroyRenderer(gWindowRenderer);
        gWindowRenderer = nullptr;
    }

    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }
}

bool GameManager::init() {
    bool success{true};

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if (SDL_CreateWindowAndRenderer("Snake", 500, 500, 0, &gWindow, &gWindowRenderer); gWindow == nullptr || gWindowRenderer == nullptr) {
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
        Uint64 startTime{SDL_GetTicksNS()};

        bool shouldQuit{processEvents()};
        if (shouldQuit) {
            break;
        }

        SDL_Log("Num game objects: %zu", currentGame.gameObjects.size());
        for (auto& gameObject : currentGame.gameObjects) {
            gameObject->update();
        }
        
        for (auto& gameObject : currentGame.gameObjects) {
            gameObject->render(gWindowRenderer);
        }

        Uint64 frameTime{0};
        frameTime = SDL_GetTicksNS() - startTime;

        if (frameTime < FRAME_TIME) {
            Uint64 sleepTimeNS{FRAME_TIME - frameTime};

            // spin wait, not great for CPU but more accurate
            //Uint64 targetTimeNS{SDL_GetTicksNS() + sleepTimeNS};
            //while (SDL_GetTicksNS() < targetTimeNS) { }

            // Yield CPU but incurs overhead
            SDL_DelayNS(sleepTimeNS);
        }

        Uint64 totalFrameTimeNS{SDL_GetTicksNS() - startTime};
        double framesPerSecond{(double)1e9 / totalFrameTimeNS};
        //SDL_Log("FPS: %.2f", framesPerSecond);
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

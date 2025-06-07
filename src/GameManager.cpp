#include "GameManager.hpp"

#include <SDL3/SDL.h>

namespace {
    constexpr int FRAME_RATE{60};
    constexpr Uint64 FRAME_TIME{(int)1e9 / FRAME_RATE};
}

GameManager::GameManager() {
    SDL_Log("GameManager initialized");
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
        Uint64 startTime{SDL_GetTicksNS()};

        bool shouldQuit{processEvents()};
        if (shouldQuit) {
            break;
        }

        update();
        render();

        Uint64 frameTime{0};
        frameTime = SDL_GetTicksNS() - startTime;

        if (frameTime < FRAME_TIME) {
            Uint64 sleepTimeNS{FRAME_TIME - frameTime};

            Uint64 targetTimeNS{SDL_GetTicksNS() + sleepTimeNS};
            // spin wait, not great for CPU
            while (SDL_GetTicksNS() < targetTimeNS) { }

            // Can yield CPU but incurs overhead
            //SDL_DelayNS(sleepTimeNS);
        }

        Uint64 totalFrameTimeNS{SDL_GetTicksNS() - startTime};
        double framesPerSecond{(double)1e9 / totalFrameTimeNS};
        SDL_Log("FPS: %.2f", framesPerSecond);
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

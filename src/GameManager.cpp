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
    constexpr Uint16 INITIAL_WINDOW_SQUARE_SIZE{500};
    constexpr Uint16 LOGICAL_WINDOW_SQUARE_SIZE{500};
}

GameManager::GameManager() {
    SDL_Log("GameManager constructor called");
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
        if (SDL_CreateWindowAndRenderer("Snake", INITIAL_WINDOW_SQUARE_SIZE, INITIAL_WINDOW_SQUARE_SIZE, 0, &gWindow, &gWindowRenderer); gWindow == nullptr || gWindowRenderer == nullptr) {
            SDL_Log("SDL could not create window or renderer! Error: %s\n", SDL_GetError());
            success = false;
        }

        SDL_SetRenderLogicalPresentation(gWindowRenderer, LOGICAL_WINDOW_SQUARE_SIZE, LOGICAL_WINDOW_SQUARE_SIZE, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    }

    return success;
}

void GameManager::enterMainLoop() {
    currentGame = std::make_unique<Game>();

    while (currentGame.get()->state == GameState::Running) {
        Uint64 startTime{SDL_GetTicksNS()};

        processInputEvents();
        updateGameObjects();
        renderGameObjects(gWindowRenderer);

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

void GameManager::processInputEvents() {
    SDL_Event event;
    SDL_zero(event);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            currentGame.get()->state = GameState::ForceQuit;
        }
    }
}

void GameManager::updateGameObjects() {
    currentGame.get()->grid.update(SDL_GetTicks());
    currentGame.get()->snake.update(SDL_GetTicks());
}

void GameManager::renderGameObjects(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    currentGame.get()->grid.render(renderer);
    currentGame.get()->snake.render(renderer);

    SDL_RenderPresent(renderer);
}

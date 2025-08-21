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
    currentGame->candy.randomizeLocation(currentGame->snake.gridCoords, currentGame->grid.colCount);

    while (currentGame->state == GameState::Running) {
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
            currentGame->state = GameState::ForceQuit;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            /* TODO: Do not allow certain inputs when moving in certain directions
             * For example, if snake is moving down do not accept up input
             */

            switch (event.key.scancode) {
                case SDL_SCANCODE_W:
                    currentGame->snake.move(SnakeMoveDirection::Up);
                    break;
                case SDL_SCANCODE_S:
                    currentGame->snake.move(SnakeMoveDirection::Down);
                    break;
                case SDL_SCANCODE_A:
                    currentGame->snake.move(SnakeMoveDirection::Left);
                    break;
                case SDL_SCANCODE_D:
                    currentGame->snake.move(SnakeMoveDirection::Right);
                    break;
                default:
                    break;
            }
        }
    }
}

void GameManager::updateGameObjects() {
    currentGame->grid.update(SDL_GetTicks());
    currentGame->snake.update(SDL_GetTicks());
    currentGame->candy.update(SDL_GetTicks());

    // Detect collisions
    checkSnakeCollidesWithWorldEdges();
    checkSnakeCollidesWithSelf();
}

void GameManager::renderGameObjects(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    currentGame->grid.render(renderer);
    currentGame->snake.render(renderer);
    currentGame->candy.render(renderer);

    SDL_RenderPresent(renderer);
}

void GameManager::checkSnakeCollidesWithWorldEdges() {
    GridCoordinate snakeFront = currentGame->snake.gridCoords.front();
    int colCount = currentGame->grid.colCount;
    if (snakeFront.x < 0 || snakeFront.x >= colCount || snakeFront.y < 0 || snakeFront.y >= colCount) {
        currentGame->snake.tempClear();
    }
}

void GameManager::checkSnakeCollidesWithSelf() {
    if (currentGame->snake.gridCoords.size() <= 1) { return; }

    bool collidedWithSelf = false;
    auto iter = currentGame->snake.gridCoords.begin();
    GridCoordinate snakeFront = *iter;
    iter++;
    while (iter != currentGame->snake.gridCoords.end()) {
        if (iter->x == snakeFront.x && iter->y == snakeFront.y) {
            collidedWithSelf = true;
            break;
        }

        iter++;
    }

    if (collidedWithSelf) {
        currentGame->snake.tempClear();
    }
}

#include "Snake.hpp"

#include <random>

#include <SDL3/SDL.h>

Snake::Snake(LogicalPositionProvider* provider): positionProvider(provider), lastGameTick{0}, gridCoord{0, 0} {
    SDL_Log("Initializing snake object");
}

Snake::~Snake() {
    SDL_Log("Destructor for snake object");
}

void Snake::update(Uint64 gametick) {
    SDL_Log("Snake update called");
    if (gametick - lastGameTick > 1000) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        int min = 0;
        int max = 5;
        unsigned int x = min + (std::rand() % (max - min + 1));
        unsigned int y = min + (std::rand() % (max - min + 1));
        GridCoordinate newCoord{x, y};
        gridCoord = newCoord;
        SDL_Log("Snake new position is: (%d, %d)", x, y);
        lastGameTick = gametick;
    }
}

void Snake::render(SDL_Renderer* renderer) {
    SDL_Log("Snake render called");

    GridSquare result;
    positionProvider->logicalPositionForGridCoordinate(gridCoord, &result);

    SDL_FRect drawRect;
    drawRect.x = result.topLeft.x;
    drawRect.y = result.topLeft.y;
    drawRect.w = result.sideLength;
    drawRect.h = result.sideLength;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(renderer, &drawRect);

    SDL_Log("Snake resolved top-left position: (%d, %d) with side length: %d", result.topLeft.x, result.topLeft.y, result.sideLength);
}
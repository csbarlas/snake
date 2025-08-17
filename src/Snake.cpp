#include "Snake.hpp"

#include <random>

#include <SDL3/SDL.h>

Snake::Snake(LogicalPositionProvider* provider): positionProvider(provider), lastGameTick{0}, gridCoord{0, 0}, directionVector{ SnakeMoveDirection::Down } {
    SDL_Log("Initializing snake object");
}

Snake::~Snake() {
    SDL_Log("Destructor for snake object");
}

void Snake::update(Uint64 gametick) {
    SDL_Log("Snake update called");
    if (gametick - lastGameTick > 500) {
        int xVec = 0;
        if (directionVector == SnakeMoveDirection::Left || directionVector == SnakeMoveDirection::Right) {
            xVec = directionVector == SnakeMoveDirection::Left ? -1 : 1;
        }

        int yVec = 0;
        if (directionVector == SnakeMoveDirection::Up || directionVector == SnakeMoveDirection::Down) {
            yVec = directionVector == SnakeMoveDirection::Up ? -1 : 1;
        }

        GridCoordinate newCoord{gridCoord.x + xVec, gridCoord.y + yVec};
        gridCoord = newCoord;
        SDL_Log("Snake new coordinate is: (%d, %d)", newCoord.x, newCoord.y);
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

void Snake::move(SnakeMoveDirection direction) {
    directionVector = direction;
}

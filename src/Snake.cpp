#include "Snake.hpp"

#include <random>

#include <SDL3/SDL.h>

Snake::Snake(LogicalPositionProvider* provider): positionProvider(provider), lastGameTick{0}, directionVector{ SnakeMoveDirection::Down } {
    SDL_Log("Initializing snake object");
    GridCoordinate startingCoord{0, 0};
    gridCoords.insert(gridCoords.begin(), startingCoord);
}

Snake::~Snake() {
    SDL_Log("Destructor for snake object");
}

void Snake::update(Uint64 gametick) {
    SDL_Log("Snake update called");

    // Snake should update
    if (gametick - lastGameTick > 250) {
        GridCoordinate newCoord = nextCoordinateGivenDirection();
        gridCoords.insert(gridCoords.begin(), newCoord);
        gridCoords.pop_back();
        lastGameTick = gametick;
    }
}

void Snake::render(SDL_Renderer* renderer) {
    SDL_Log("Snake render called");

    for (GridCoordinate coord : gridCoords) {
        GridSquare result;
        positionProvider->logicalPositionForGridCoordinate(coord, &result);

        SDL_FRect drawRect;
        drawRect.x = result.topLeft.x;
        drawRect.y = result.topLeft.y;
        drawRect.w = result.sideLength;
        drawRect.h = result.sideLength;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderFillRect(renderer, &drawRect);
    }

    // SDL_Log("Snake resolved top-left position: (%d, %d) with side length: %d", result.topLeft.x, result.topLeft.y, result.sideLength);
}

void Snake::move(SnakeMoveDirection direction) {
    directionVector = direction;
}

void Snake::tempClear() {
    gridCoords.clear();
}

void Snake::addToSnakeFront(GridCoordinate coord) {
    gridCoords.insert(gridCoords.begin(), coord);
}

GridCoordinate Snake::nextCoordinateGivenDirection() {
    int xVec = 0;
    if (directionVector == SnakeMoveDirection::Left || directionVector == SnakeMoveDirection::Right) {
        xVec = directionVector == SnakeMoveDirection::Left ? -1 : 1;
    }

    int yVec = 0;
    if (directionVector == SnakeMoveDirection::Up || directionVector == SnakeMoveDirection::Down) {
        yVec = directionVector == SnakeMoveDirection::Up ? -1 : 1;
    }

    GridCoordinate snakeFront = gridCoords.front();
    GridCoordinate newCoord{snakeFront.x + xVec, snakeFront.y + yVec};
    return newCoord;
}

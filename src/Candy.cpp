//
// Created by Chris Barlas on 8/20/25.
//
#include "Candy.h"

#include <random>
#include <SDL3/SDL.h>

Candy::Candy(LogicalPositionProvider* provider): location({0, 0}), provider(provider) {
    SDL_Log("Candy initialized");
}

void Candy::update(Uint64 gametick) {
}

void Candy::render(SDL_Renderer *renderer) {
    GridSquare result;
    provider->logicalPositionForGridCoordinate(location, &result);

    SDL_FRect drawRect;
    drawRect.x = result.topLeft.x;
    drawRect.y = result.topLeft.y;
    drawRect.w = result.sideLength;
    drawRect.h = result.sideLength;

    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 0);
    SDL_RenderFillRect(renderer, &drawRect);
}

void Candy::randomizeLocation(std::vector<GridCoordinate> snakeCoords, int gridLimits) {
    if (snakeCoords.size() == (gridLimits * gridLimits)) {
        // Grid is full, cannot find a random position
        return;
    }

    bool foundNewEmptyLocation{false};
    while (!foundNewEmptyLocation) {
        std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<unsigned int> distribution(0, gridLimits - 1);
        unsigned int randomX = distribution(generator);
        unsigned int randomY = distribution(generator);

        for (auto snakeCoord: snakeCoords) {
            if (snakeCoord.x == randomX && snakeCoord.y == randomY) {
                break;
            }
        }

        location = GridCoordinate{randomX, randomY};
        foundNewEmptyLocation = true;
    }
}

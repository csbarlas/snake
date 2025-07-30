#include "Snake.hpp"

#include <SDL3/SDL.h>

Snake::Snake(LogicalPositionProvider* provider): positionProvider(provider) {
    SDL_Log("Initializing snake object");
}

Snake::~Snake() {
    SDL_Log("Destructor for snake object");
}

void Snake::update(Uint64 gametick) {
    SDL_Log("Snake update called");
}

void Snake::render(SDL_Renderer* renderer) {
    SDL_Log("Snake render called");

    int x, y;
    positionProvider->logicalPositionForGridCoordinate(-1, -1, &x, &y);
    SDL_Log("Snake resolved position: (%d, %d)", x, y);
}
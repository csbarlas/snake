#include "SquareGrid.hpp"

#include <SDL3/SDL.h>

/* File private constants */
#pragma region
namespace { }
#pragma endregion

SquareGrid::SquareGrid(int cols) : colCount(cols) {
    SDL_Log("constructor for Grid %dx%d", cols, cols);
}

SquareGrid::~SquareGrid() {
    SDL_Log("deconstructor for Grid");
}

void SquareGrid::update(Uint64 gametick) {
    SDL_Log("Grid update called with gametick: %llu", gametick);
}

void SquareGrid::render(SDL_Renderer* renderer) {
    SDL_Log("Grid render called");

    // Get size of window
    // Calculate a size that grid can cleanly go inside
    // Figure out per cell dimensions
    // Draw horizontal lines
    // Draw vertical lines
}

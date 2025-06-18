#include "SquareGrid.hpp"

#include <SDL3/SDL.h>

/* File private constants */
#pragma region
namespace {
    constexpr int ROW_COL_COUNT{10};
}
#pragma endregion

SquareGrid::SquareGrid(int cols) : colCount(cols) {
    SDL_Log("init for Grid");
}

SquareGrid::~SquareGrid() {
    SDL_Log("destroy for Grid");
}

void SquareGrid::update(Uint64 gametick) {
    SDL_Log("Grid update called with gametick: %llu", gametick);
}

void SquareGrid::render(SDL_Renderer* renderer) {
    SDL_Log("Grid render called");
}

#include "Grid.hpp"

#include <SDL3/SDL.h>

/* File private constants */
#pragma region
namespace {
    constexpr int ROW_COL_COUNT{10};
}
#pragma endregion

Grid::Grid() {
    SDL_Log("init for Grid");
}

void Grid::render() {
    SDL_Log("render grid");
}
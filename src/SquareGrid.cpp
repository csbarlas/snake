#include "SquareGrid.hpp"

#include <SDL3/SDL.h>

/* File private constants */
#pragma region

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
    int logicalHeight {0};
    int logicalWidth {0};
    SDL_GetRenderLogicalPresentation(renderer, &logicalWidth, &logicalHeight, nullptr);

    // Figure out per cell dimensions
    if (logicalHeight != logicalWidth) {
        SDL_Log("SquareGrid: Logical height and width of renderer do not match, unimplemented...");
        return;
    }

    int squareLogicalSideLength = logicalWidth / colCount;
    // If the logical window size can not be cleanly split up between the column count, readjust
    if (logicalWidth % colCount != 0) {
        int remainder = logicalWidth % colCount;
        int newLogicalSize = logicalWidth - remainder;
        squareLogicalSideLength = newLogicalSize / colCount;
    }

    // Draw horizontal lines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    for (int row = 0; row < colCount; row++) {
        int rowPos = row * squareLogicalSideLength;
        SDL_RenderLine(renderer, 0, rowPos, logicalWidth, rowPos);
    }

    // Draw vertical lines
    for (int col = 0; col < colCount; col++) {
        int colPos = col * squareLogicalSideLength;
        SDL_RenderLine(renderer, colPos, 0, colPos, logicalHeight);
    }
}

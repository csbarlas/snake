#pragma once

#include "Game.hpp"

class SquareGrid : public GameObject {
public:
    SquareGrid(int cols);
    ~SquareGrid();

    void update(Uint64 gametick) override;
    void render(SDL_Renderer* renderer) override;

private:
    const int colCount;
};
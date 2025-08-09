#pragma once

#include "GameObject.hpp"
#include "LogicalPositionProvider.hpp"

class SquareGrid : public GameObject, public LogicalPositionProvider {
public:
    SquareGrid(int cols);
    ~SquareGrid();

    void update(Uint64 gametick) override;
    void render(SDL_Renderer* renderer) override;
    void logicalPositionForGridCoordinate(GridCoordinate coord, GridSquare* result) override;

private:
    const int colCount;
    int gridSquareLogicalSideLength;
};
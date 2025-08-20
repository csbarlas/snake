#pragma once

#include <vector>

#include "GameObject.hpp"
#include "LogicalPositionProvider.hpp"

enum class SnakeMoveDirection {
    Left,
    Right,
    Up,
    Down
};

class Snake: public GameObject {
public:
    Snake(LogicalPositionProvider* provider);
    ~Snake();

    std::vector<GridCoordinate> gridCoords;

    void update(Uint64 gametick) override;
    void render(SDL_Renderer* renderer) override;
    void move(SnakeMoveDirection direction);
    void tempClear();
private:
    LogicalPositionProvider* positionProvider;
    Uint64 lastGameTick;
    SnakeMoveDirection directionVector;
};
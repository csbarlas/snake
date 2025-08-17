#pragma once

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

    void update(Uint64 gametick) override;
    void render(SDL_Renderer* renderer) override;
    void move(SnakeMoveDirection direction);
private:
    LogicalPositionProvider* positionProvider;
    Uint64 lastGameTick;
    GridCoordinate gridCoord;
    SnakeMoveDirection directionVector;
};
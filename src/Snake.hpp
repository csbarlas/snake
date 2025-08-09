#pragma once

#include "GameObject.hpp"
#include "LogicalPositionProvider.hpp"

class Snake: public GameObject {
public:
    Snake(LogicalPositionProvider* provider);
    ~Snake();

    void update(Uint64 gametick) override;
    void render(SDL_Renderer* renderer) override;
private:
    LogicalPositionProvider* positionProvider;
    Uint64 lastGameTick;
    GridCoordinate gridCoord;
};
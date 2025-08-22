//
// Created by Chris Barlas on 8/20/25.
//

#ifndef SNAKE_CANDY_H
#define SNAKE_CANDY_H

#include <vector>

#include "GameObject.hpp"
#include "SquareGrid.hpp"
#include "LogicalPositionProvider.hpp"

class Candy: public GameObject {
public:
    Candy(LogicalPositionProvider* provider);
    GridCoordinate location;

    void update(Uint64 gametick) override;
    void render(SDL_Renderer* renderer) override;
    void randomizeLocation(std::vector<GridCoordinate> snakeCoords, int gridLimits);
    void hide();
private:
    LogicalPositionProvider* provider;
    bool shouldHide{false};
};

#endif //SNAKE_CANDY_H

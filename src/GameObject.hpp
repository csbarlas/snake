#pragma once

#include <SDL3/SDL.h>

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void update(Uint64 gametick) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};
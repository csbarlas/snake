#pragma once

#include <vector>

#include <SDL3/SDL.h>

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void update(Uint64 gametick) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};

class Game {
public:
    Game();
    ~Game();
    std::vector<std::unique_ptr<GameObject>> gameObjects;

private:
    
};

class DummyObject : public GameObject {
public:
    void update(Uint64 gametick) override;
    void render(SDL_Renderer* renderer) override;
};

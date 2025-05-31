#include <iostream>

#include <SDL3/SDL.h>

#include "Grid.hpp"

/* Globals */
#pragma region
SDL_Window *gWindow{nullptr};
SDL_Renderer *gWindowRenderer{nullptr};
#pragma endregion

/* Function prototypes */
#pragma region
void processEvents(bool*);
void update();
void render();
bool init();
void enterMainLoop();
#pragma endregion

int main(int, char**){
    int exitCode{0};

    if (!init()) {
        SDL_Log("Error calling init()\n");
        exitCode = 1;
    } else {
        enterMainLoop();
    }

    return exitCode;
}

bool init() {
    bool success{true};

    Grid a;
    a.render();

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if (SDL_CreateWindowAndRenderer("Snake", 500, 500, SDL_WINDOW_RESIZABLE, &gWindow, &gWindowRenderer); gWindow == nullptr || gWindowRenderer == nullptr) {
            SDL_Log("SDL could not create window or renderer! Error: %s\n", SDL_GetError());
            success = false;
        }

        SDL_SetRenderLogicalPresentation(gWindowRenderer, 500, 500, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    }

    return success;
}

void enterMainLoop() {
    bool quitFlag{false};

    while (quitFlag == false) {
        processEvents(&quitFlag);
        update();
        render();
    }
}

void processEvents(bool* quitPtr) {
    SDL_Event e;
    SDL_zero(e);

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_EVENT_QUIT:
                *quitPtr = true;
                break;
            
            default:
                break;
        }
    }
}

void update() {

}

void render() {

}
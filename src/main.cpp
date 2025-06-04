#include <iostream>

#include <SDL3/SDL.h>

#include "GameManager.hpp"

/* Globals */
#pragma region
GameManager gameManager{};
#pragma endregion

/* Function prototypes */
#pragma region
#pragma endregion

int main(int, char**){
    int exitCode{0};

    if (!gameManager.init()) {
        SDL_Log("Error calling init()\n");
        exitCode = 1;
    } else {
        gameManager.enterMainLoop();
    }

    return exitCode;
}

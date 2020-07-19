#pragma once
#include "main.h"
#include "constants.h"

class Game {
    private:
        void render();
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Game();
        void run();
};

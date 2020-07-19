#pragma once
#include "main.h"
#include "constants.h"

class Game {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
		bool running;
		Uint32 last_frame_update_time;

    public:
        Game();
        void run();

	private:
		void initialize_window_and_renderer();	
        void render();
};

#pragma once
#include "main.h"
#include "constants.h"
#include "sprites.h"
#include "block_container.h"
#include "textures.h"
#include <pthread.h>

class Game {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
		bool running;
		bool initialization_failed;
		Uint32 last_frame_update_time;
		Textures* textures;
		///-------------- Sprites ----------------
		Pipe* pipe;	
		Crane* crane;
		Block* block;
		///-------------- Threads ----------------
		pthread_t crane_thread; 
		BlockContainer* block_container;

    public:
        Game();
        void run();
		~Game();

	private:
		void initialize_window();	
		void initialize_renderer();	
		void initialize_pipe();
		void initialize_crane();
		void initialize_test_block();
        void render();
};

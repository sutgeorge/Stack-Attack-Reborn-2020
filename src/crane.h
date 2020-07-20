#pragma once
#include "main.h"
#include "block.h"

class Crane {
	private:
		SDL_Texture *texture;
		SDL_Rect dstrect;
		SDL_Renderer *renderer;
		bool currently_sliding;			
		Uint32 last_slide_time, last_crate_drop_time;			
		enum Direction {LEFT, RIGHT} direction;
		Block* current_block;

	public:
		Crane(SDL_Renderer* renderer);	
		void draw();
		void slide();
		void generate_new_position_and_direction();
		static void* handle_thread(void* arg);
};

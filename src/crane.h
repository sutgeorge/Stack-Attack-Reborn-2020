#pragma once
#include "main.h"
#include "block.h"
#include "block_container.h"

class Crane {
	private:
		SDL_Texture *texture;
		SDL_Rect dstrect;
		SDL_Renderer *renderer;
		bool currently_sliding, holds_a_block;			
		Uint32 last_slide_time, last_crate_drop_time;			
		enum Direction {LEFT, RIGHT} direction;
		Block* current_block;
		int x_coordinate_of_the_drop_target;
		BlockContainer* block_container;		
		Textures* textures;

	public:
		Crane(SDL_Renderer* renderer, Textures* textures, BlockContainer* block_container);	
		void draw();
		void slide();
		void movement();
		void out_of_frame_waiting_time();
		void generate_new_position_and_direction();
		void drop_crate();
		void generate_crate();
		static void* handle_thread(void* arg);
};

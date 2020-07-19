#pragma once
#include "main.h"

class Crane {
	private:
		SDL_Texture *texture;
		SDL_Rect dstrect;
		SDL_Renderer *renderer;
		bool currently_sliding;			
		Uint32 last_slide_time, last_crate_drop_time;			
		enum Direction {LEFT, RIGHT} direction;

	public:
		Crane(SDL_Renderer* renderer);	
		void draw();
		void slide();
};

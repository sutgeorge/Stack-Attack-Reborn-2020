#pragma once
#include "main.h"

class Block {
	private:	
		SDL_Texture *texture;
		SDL_Rect dstrect;
		SDL_Renderer *renderer;
		int falling_velocity;
		bool falling; 
		Uint32 last_fall_time;

	public:
		Block(SDL_Renderer* renderer, int x, int y);
		void draw();
		void fall();
		~Block();
};

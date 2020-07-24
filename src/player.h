#pragma once
#include "main.h"

class Player {
	private:
		SDL_Texture *spritesheet;
		SDL_Rect frame, dstrect;
		SDL_Renderer *renderer;
		Textures* textures;
		int number_of_frames_horizontally, number_of_frames_vertically;
	
	public:
		Player(SDL_Renderer* renderer, Textures* textures);
		void draw();
};

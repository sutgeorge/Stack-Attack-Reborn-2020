#pragma once
#include "main.h"

class Player {
	private:
		SDL_Texture *spritesheet;
		SDL_Rect frame, dstrect;
		SDL_Renderer *renderer;
		Textures* textures;
		int number_of_frames_horizontally, number_of_frames_vertically;
		Uint32 last_frame_update_time;
	
	public:
		Player(SDL_Renderer* renderer, Textures* textures);
		void draw();
		Uint32 get_last_frame_update_time();
		void set_last_frame_update_time(Uint32 new_time);
		void move_to_left();
		void move_to_right();
};


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
		int get_width();
		int get_x_coordinate();
		int get_y_coordinate();
		void set_x_coordinate(int new_x_coordinate);
		void set_y_coordinate(int new_y_coordinate);
		~Block();
};

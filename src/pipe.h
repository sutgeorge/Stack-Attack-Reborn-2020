#pragma once
#include "main.h"

class Pipe {
	private:
		SDL_Renderer* renderer;
				

	public:
		Pipe(SDL_Renderer* renderer);
		void draw();
};

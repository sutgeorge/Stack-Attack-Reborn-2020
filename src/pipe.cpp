#include "pipe.h"

Pipe::Pipe(SDL_Renderer* renderer) {
	this->renderer = renderer;
}


void Pipe::draw() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	int pipe_width = 5;
	for(int i = 0; i < pipe_width; i++){
		SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 30 + i, WINDOW_WIDTH, WINDOW_HEIGHT / 30 + i);
		SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 15 + i, WINDOW_WIDTH, WINDOW_HEIGHT / 15 + i);
	}
	SDL_SetRenderDrawColor(renderer, DEFAULT_DRAW_COLOR);
}

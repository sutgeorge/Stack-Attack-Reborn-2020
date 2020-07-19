#include "game.h"

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	this->window = SDL_CreateWindow("Stack Attack Reborn",
	dm.w / 2 - WINDOW_WIDTH / 2,	/// The position of the window
	dm.h / 2 - WINDOW_HEIGHT / 2,
	WINDOW_WIDTH, WINDOW_HEIGHT,	/// Width and height of the window
	0);	/// WindowFlags are set to 0

	if(this->window == NULL) {
		printf("Window creation failed!\n");
		return;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	if(this->renderer == NULL) {
		printf("Renderer creation failed!\n");
		return;
	}

	SDL_SetRenderDrawColor(this->renderer, DEFAULT_DRAW_COLOR);		
}

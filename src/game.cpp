#include "game.h"

void Game::initialize_window() {
	this->initialization_failed = false;
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
		this->initialization_failed = true;
		return;
	}
}


void Game::initialize_renderer() {
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	if(this->renderer == NULL) {
		printf("Renderer creation failed!\n");
		this->initialization_failed = true;
		return;
	}

	SDL_SetRenderDrawColor(this->renderer, DEFAULT_DRAW_COLOR);
}


void Game::initialize_pipe() {
	this->pipe = new Pipe(this->renderer);	
}


Game::Game() {
	this->initialize_window();
	this->initialize_renderer();
	this->initialize_pipe();

	if (this->initialization_failed) {
		this->running = false;
		return;
	}

	this->running = true;	
	this->last_frame_update_time = SDL_GetTicks();
}


Game::~Game() {
	//TODO: Avoid memory leaks by freeing memory used by SDL
	delete this->pipe;
}


void Game::render() {
	if (SDL_GetTicks() - this->last_frame_update_time > 1000 / FPS) {
		SDL_RenderClear(this->renderer);
		this->pipe->draw();		
		SDL_RenderPresent(this->renderer);
		this->last_frame_update_time = SDL_GetTicks();
	}
}


void Game::run() {	
	while (this->running) {
		this->render();	
	}
}

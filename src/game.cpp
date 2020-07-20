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


void Game::initialize_crane() {
	this->crane = new Crane(this->renderer, this->textures, this->block_container);
}


void Game::initialize_test_block() {
	this->block = new Block(this->renderer, this->textures, 0, 0);
}


Game::Game() {
	this->initialize_window();
	this->initialize_renderer();
	this->textures = new Textures(this->renderer);
	this->block_container = new BlockContainer(this->renderer);	
	this->initialize_pipe();
	this->initialize_crane();
	this->initialize_test_block();	

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
	delete this->crane;
	delete this->block;
	delete this->block_container;
	delete this->textures;
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);	
	SDL_Quit();
}


void Game::render() {
	if (SDL_GetTicks() - this->last_frame_update_time > 1000 / FPS) {
		SDL_RenderClear(this->renderer);
		this->pipe->draw();		
		this->crane->draw();
		this->block_container->render_blocks();
		SDL_RenderPresent(this->renderer);
		this->last_frame_update_time = SDL_GetTicks();
	}
}


void Game::run() {	
	pthread_create(&this->crane_thread, NULL, Crane::handle_thread, this->crane);			
	while (this->running) {
		this->render();	
	}
	std::cout << "while loop stopped.\n"; 
	pthread_join(this->crane_thread, NULL);
}

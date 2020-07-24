#include "game.h"
#include "collisiondetector.h"

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


void Game::initialize_player() {
	this->player = new Player(this->renderer, this->textures);
}


Game::Game() {
	this->initialize_window();
	this->initialize_renderer();
	this->textures = new Textures(this->renderer);
	this->block_container = new BlockContainer(this->renderer);	
	this->initialize_pipe();
	this->initialize_crane();
	this->initialize_test_block();	
	this->initialize_player();

	if (this->initialization_failed) {
		this->running = false;
		return;
	}
		
	this->running = true;	
	this->last_frame_update_time = SDL_GetTicks();
}


Game::~Game() {
	delete this->pipe;
	delete this->crane;
	delete this->block;
	delete this->block_container;
	delete this->player;
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
		this->player->draw();
		this->block_container->render_blocks();
		SDL_RenderPresent(this->renderer);
		this->last_frame_update_time = SDL_GetTicks();
	}
}


void Game::input_handling() {
	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
			this->crane->stop();
			this->running = false;
		}
	}

	if(SDL_GetTicks() - this->player->get_last_jump_time() > 500 && !player->is_falling() && keyboard_state[SDL_SCANCODE_W]) {
		player->set_as_jumping();
		player->set_last_jump_time(SDL_GetTicks());
	}

	if (keyboard_state[SDL_SCANCODE_A]) {
		Uint32 player_frame_update_time = this->player->get_last_frame_update_time();
		if (SDL_GetTicks() -  player_frame_update_time > 1000 / FPS) {
			this->player->set_last_frame_update_time(SDL_GetTicks());	
			this->player->move_to_left();			
		}
	} else if (keyboard_state[SDL_SCANCODE_D]) {
		Uint32 player_frame_update_time = this->player->get_last_frame_update_time();
		if (SDL_GetTicks() -  player_frame_update_time > 1000 / FPS) {
			this->player->set_last_frame_update_time(SDL_GetTicks());	
			this->player->move_to_right();			
		}
	} else {
		this->player->stand_still();
	}  
}


void Game::run() {	
	this->crane_thread = SDL_CreateThread(Crane::handle_thread, "Crane thread", this->crane);		
	
	while (this->running) {
		this->input_handling();
		this->player->jump();
		this->player->fall();
		this->render();			
	}
	
	crane->stop();	
	SDL_WaitThread(this->crane_thread, NULL);
	std::cout << "Stopped.\n";
}

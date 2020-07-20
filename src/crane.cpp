#include "crane.h"
#include <cstdlib>
#include <ctime>

Crane::Crane(SDL_Renderer* renderer) {
	int texture_w, texture_h;
	this->renderer = renderer;
	this->texture = IMG_LoadTexture(renderer, "res/crane.png");
	SDL_QueryTexture(this->texture, NULL, NULL, &texture_w, &texture_h);

	this->dstrect.w = texture_w;
	this->dstrect.h = texture_h;
	this->dstrect.x = -texture_w;
	this->dstrect.y = 0;

	this->last_crate_drop_time = this->last_slide_time = SDL_GetTicks();
	this->currently_sliding = true;
	this->direction = RIGHT;
	this->current_block = NULL;
}


void Crane::generate_new_position_and_direction() {
	srand(time(NULL));
	int random_int = rand() % 2;

	if (!random_int) {
		this->direction = LEFT;
		this->dstrect.x = WINDOW_WIDTH + this->dstrect.w;
	} else {
		this->direction = RIGHT;
		this->dstrect.x = -this->dstrect.w;
	}	
}


void Crane::slide() {
	///TODO: Separate this if statement and place it in a new method called "movement"
	if (this->currently_sliding && SDL_GetTicks() - this->last_slide_time > 1000 / FPS) {
		this->last_slide_time = SDL_GetTicks(); 

		if (this->direction == LEFT) {
			this->dstrect.x -= CRANE_VELOCITY; 		

			if (this->dstrect.x + this->dstrect.w < 0) {
				this->currently_sliding = false;
			}
		} else {
			this->dstrect.x += CRANE_VELOCITY; 	

			if (this->dstrect.x > WINDOW_WIDTH) {
				this->currently_sliding = false;
			}
		}
	}

	if (!this->currently_sliding) {
		/// When the crane goes out of the frame of the window, it waits
		/// 3 seconds.	
		std::cout << "waiting...\n";	
		Uint32 out_of_frame_waiting_time = SDL_GetTicks();	
		while (SDL_GetTicks() - out_of_frame_waiting_time < 3000){}	

		std::cout << "done!\n";	
		this->generate_new_position_and_direction();
		this->currently_sliding = true;	
	}
}


void Crane::draw() {
	SDL_RenderCopy(this->renderer, this->texture, NULL, &this->dstrect);		
} 


void* Crane::handle_thread(void* arg) {
	Crane* crane = (Crane*)arg;
		
	while (crane->currently_sliding) {
		crane->slide();	
	}		
	
	return NULL;
}

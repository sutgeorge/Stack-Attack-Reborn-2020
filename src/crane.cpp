#include "crane.h"

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
	this->currently_sliding = false;
	this->direction = RIGHT;

	//this->current_block = NULL;
}


void Crane::slide() {
	/**
	if (!this->currently_sliding)
		return;
	**/

	if (SDL_GetTicks() - this->last_slide_time > 1000 / FPS) {
		std::cout << "Crane::slide running...\n";
		this->last_slide_time = SDL_GetTicks(); 

		if (this->direction == LEFT) {
			this->dstrect.x -= CRANE_VELOCITY; 	
		} else {
			this->dstrect.x += CRANE_VELOCITY; 	
		}	
	}	
}


void Crane::draw() {
	SDL_RenderCopy(this->renderer, this->texture, NULL, &this->dstrect);		
} 

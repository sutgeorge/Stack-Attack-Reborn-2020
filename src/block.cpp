#include "block.h"

Block::Block(SDL_Renderer* renderer, int x, int y) {	
	int texture_w, texture_h;

	this->renderer = renderer;
	this->texture = IMG_LoadTexture(renderer, "res/block.png");
	SDL_QueryTexture(this->texture, NULL, NULL, &texture_w, &texture_h);

	this->dstrect.x = x;
	this->dstrect.y = y;
	this->dstrect.w = texture_w;
	this->dstrect.h = texture_h;
	this->falling = true;
	this->falling_velocity = 1;
	this->last_fall_time = SDL_GetTicks();
}


void Block::draw() {
	SDL_RenderCopy(this->renderer, this->texture, NULL, &this->dstrect);
}


void Block::fall() {
	if (!this->falling)
		return; 

	if (this->dstrect.y + this->dstrect.h <= WINDOW_HEIGHT) {
		if (SDL_GetTicks() - this->last_fall_time > 1000 / FPS) {
			this->last_fall_time = SDL_GetTicks();
			this->dstrect.y += this->falling_velocity;	
			this->falling_velocity++;
		}
	} else {		
		this->dstrect.y = WINDOW_HEIGHT - this->dstrect.h;	
		this->falling = false;
	}
}


Block::~Block() {
			
}

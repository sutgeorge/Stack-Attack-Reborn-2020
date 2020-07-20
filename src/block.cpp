#include "block.h"

Block::Block(SDL_Renderer* renderer, Textures* textures, int x, int y) {	
	int texture_w, texture_h;

	this->renderer = renderer;
	this->texture = textures->block_texture;
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


int Block::get_width() {
	return this->dstrect.w;
}


int Block::get_x_coordinate() {
	return this->dstrect.x;
}


int Block::get_y_coordinate() {
	return this->dstrect.y;
}


void Block::set_x_coordinate(int new_x_coordinate) {
	this->dstrect.x = new_x_coordinate;
}


void Block::set_y_coordinate(int new_y_coordinate) {
	this->dstrect.y = new_y_coordinate;
}


Block::~Block() {
			
}

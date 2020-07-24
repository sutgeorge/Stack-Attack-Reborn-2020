#include "player.h"

Player::Player(SDL_Renderer* renderer, Textures* textures) {
	int sheet_width, sheet_height;

	this->renderer = renderer;
	this->spritesheet = textures->player_spritesheet;   
	SDL_QueryTexture(this->spritesheet, NULL, NULL, &sheet_width, &sheet_height);

	this->number_of_frames_horizontally = 2;
	this->number_of_frames_vertically = 3;

	this->frame.w = sheet_width / 2;
	this->frame.h = sheet_height / 3;
	this->frame.x = 0;
	this->frame.y = this->frame.h * 2;

	this->dstrect.x = WINDOW_WIDTH / 2 - this->frame.w / 2;
	this->dstrect.y = WINDOW_HEIGHT - this->frame.h;
	this->dstrect.w = this->frame.w;
	this->dstrect.h = this->frame.h;
}


void Player::draw() {
	//player->animate(player);
	SDL_RenderCopy(this->renderer, this->spritesheet,
	      		   &this->frame, &this->dstrect);
}

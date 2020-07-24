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

	this->last_frame_update_time = SDL_GetTicks();
	this->orientation = FACING_CENTER;
}


void Player::draw() {
	this->animate();
	SDL_RenderCopy(this->renderer, this->spritesheet,
	      		   &this->frame, &this->dstrect);
}


Uint32 Player::get_last_frame_update_time() {
	return this->last_frame_update_time;
}


void Player::set_last_frame_update_time(Uint32 new_time) {
	this->last_frame_update_time = new_time;
}


void Player::move_to_left() {
	this->dstrect.x -= PLAYER_VELOCITY;	
	this->orientation = FACING_LEFT;
}


void Player::move_to_right() {
	this->dstrect.x += PLAYER_VELOCITY;	
	this->orientation = FACING_RIGHT;
}


void Player::stand_still() {
	this->orientation = FACING_CENTER;
}


void Player::animate() {
	if (this->orientation == FACING_LEFT) {
		this->left_animation();
	} else if (this->orientation == FACING_RIGHT) {
		this->right_animation();
	} else {
		this->center_animation();
	}	
}


void Player::left_animation() {
	if (SDL_GetTicks() - this->last_animation_update_time > 200) {
		this->last_animation_update_time = SDL_GetTicks();
		this->left_animation_frame_index = (this->left_animation_frame_index ? 0 : 1);
		this->frame.x = this->frame.w * this->left_animation_frame_index;
		this->frame.y = 0;		
	}
}


void Player::right_animation() {	
	if (SDL_GetTicks() - this->last_animation_update_time > 200) {
		this->last_animation_update_time = SDL_GetTicks();
		this->right_animation_frame_index = (this->right_animation_frame_index ? 0 : 1);
		this->frame.x = this->frame.w * this->right_animation_frame_index;
		this->frame.y = this->frame.h;		
	}
}


void Player::center_animation() {
	this->frame.x = 0;	
	this->frame.y = this->frame.h * 2;	
}

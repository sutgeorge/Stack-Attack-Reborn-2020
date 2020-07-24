#pragma once
#include "main.h"

class Player {
	private:
		SDL_Texture *spritesheet;
		SDL_Rect frame, dstrect;
		SDL_Renderer *renderer;
		Textures* textures;
		int number_of_frames_horizontally, number_of_frames_vertically;
		int left_animation_frame_index, right_animation_frame_index;  
		int ground_level_y_coordinate;
		int vertical_velocity;
		Uint32 last_frame_update_time, last_animation_update_time, vertical_movement_update_time, last_jump_time;
		bool jumping, falling;
		enum Orientation {FACING_LEFT, FACING_RIGHT, FACING_CENTER} orientation;
	
	public:
		Player(SDL_Renderer* renderer, Textures* textures);
		void draw();
		Uint32 get_last_frame_update_time();
		void set_last_frame_update_time(Uint32 new_time);
		Uint32 get_last_jump_time();
		void set_last_jump_time(Uint32 new_time);
		void move_to_left();
		void move_to_right();
		void stand_still();
		void jump();
		void fall();
		bool is_falling();
		void set_as_jumping();
		void animate();
		void left_animation();
		void right_animation();
		void center_animation();
};

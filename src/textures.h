#pragma once
#include "main.h"

class Textures {
	public:
		SDL_Texture* block_texture;
		SDL_Texture* crane_texture;
		SDL_Texture* player_spritesheet;
		SDL_Renderer* renderer;
		Textures(SDL_Renderer* renderer);
};

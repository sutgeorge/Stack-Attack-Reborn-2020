#pragma once
#include "main.h"
#include "block.h"
#include <vector>
#include <iterator>

class BlockContainer {
	private:
		std::vector<Block*> container;	
		SDL_Renderer* renderer;
	
	public:
		BlockContainer(SDL_Renderer* renderer);	
		void add_block(Block* block);
		void remove_bottom_row();
		void render_blocks();
		std::vector<Block*>* get_pointer_to_container();
		int size();
};

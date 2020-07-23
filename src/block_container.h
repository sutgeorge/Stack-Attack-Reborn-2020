#pragma once
#include "main.h"
#include "block.h"
#include "constants.h"
#include <vector>
#include <iterator>

class BlockContainer {
	private:
		std::vector<Block*> container;	
		SDL_Renderer* renderer;
		int number_of_blocks_on_column[NUMBER_OF_COLUMNS];
	
	public:
		BlockContainer(SDL_Renderer* renderer);	
		void add_block(Block* block, int column_index);
		void remove_bottom_row();
		void render_blocks();
		std::vector<Block*>* get_pointer_to_container();
		int get_number_of_blocks_on_column(int column_index);
		int size();
};

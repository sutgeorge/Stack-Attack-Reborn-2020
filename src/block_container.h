#pragma once
#include "main.h"
#include "block.h"
#include <vector>

class BlockContainer {
	private:
		std::vector<Block*> container;	
	
	public:
		BlockContainer();	
		void add_block(Block* block);
		void remove_bottom_row();
};

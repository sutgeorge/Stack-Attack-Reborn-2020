#include "block_container.h"

BlockContainer::BlockContainer(SDL_Renderer* renderer) {
	this->renderer = renderer;
}


void BlockContainer::add_block(Block* block) {
	this->container.push_back(block);	
}


void BlockContainer::remove_bottom_row() {
	std::vector<Block*>::iterator it = container.begin();

	while(it != container.end()) {
		if ((*it)->get_y_coordinate() == WINDOW_HEIGHT - (*it)->get_width()) {
			it = container.erase(it);
		} else { 
			it++;
		}
	}
}


void BlockContainer::render_blocks() {
	for (auto block: container) {
		block->draw();
	}
}


int BlockContainer::size() {
	return container.size();
}


std::vector<Block*>* BlockContainer::get_pointer_to_container() {
	return &container;
}


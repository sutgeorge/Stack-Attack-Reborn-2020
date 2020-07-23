#include "block_container.h"
using namespace std;

BlockContainer::BlockContainer(SDL_Renderer* renderer) {
	this->renderer = renderer;
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		this->number_of_blocks_on_column[i] = 0;
	}
}


void BlockContainer::add_block(Block* block, int column_index) {
	this->container.push_back(block);	
	this->number_of_blocks_on_column[column_index]++;	
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


int BlockContainer::get_number_of_blocks_on_column(int column_index) {
	return number_of_blocks_on_column[column_index];
}

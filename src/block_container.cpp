#include "block_container.h"
using namespace std;

BlockContainer::BlockContainer(SDL_Renderer* renderer) {
	this->renderer = renderer;
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		this->number_of_blocks_on_column[i] = 0;
	}

	for (int i = 0; i < NUMBER_OF_ROWS; i++) {
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
			this->map[i][j] = 0;
		}
	}
}


void BlockContainer::add_block(Block* block, int column_index) {
	this->container.push_back(block);	
	this->number_of_blocks_on_column[column_index]++;	
	
	int block_row = (this->number_of_blocks_on_column[column_index] * BLOCK_WIDTH) / BLOCK_WIDTH;	
	this->map[block_row - 1][column_index] = 1;
	
	for (int i = 0; i < NUMBER_OF_ROWS; i++) {
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
			std::cout << this->map[i][j];	
		}
		std::cout << "\n";
	}
	
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		std::cout << "_";
	}
	std::cout << "\n";
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


bool BlockContainer::is_tile_occupied(int x, int y) {
	int tile_row = 6 - y / BLOCK_WIDTH - 1;
	int tile_column = x / BLOCK_WIDTH;
	std::cout << "Tile (" << tile_row << ";" << tile_column << ") is "; 

	if (map[tile_row][tile_column]) {
		std::cout << "occupied\n";
		return true;
	}
	std::cout << "not occupied\n";
	return false;
}

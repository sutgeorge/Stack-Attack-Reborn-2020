#pragma once
#include "main.h"
#include "block_container.h"
#include "player.h"

class Player;
class CollisionDetector {
	private:
		BlockContainer* block_container;
		
	public:
		CollisionDetector(BlockContainer* block_container);
		bool collision_between_two_blocks(Block* first_block, Block* second_block);	
		bool bottom_side_collision_of_block_in_motion(Block* block, int x_coordinate_of_landing_position);
		bool player_block_collision(Player* player, Block* block);	
		bool check_player_collision_with_other_blocks(Player* player);
};

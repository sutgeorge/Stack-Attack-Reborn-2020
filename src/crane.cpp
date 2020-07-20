#include "crane.h"
#include <cstdlib>
#include <ctime>

Crane::Crane(SDL_Renderer* renderer, Textures* textures, BlockContainer* block_container) {
	int texture_w, texture_h;

	this->renderer = renderer;
	this->texture = textures->crane_texture;
	this->textures = textures;
	SDL_QueryTexture(this->texture, NULL, NULL, &texture_w, &texture_h);

	this->dstrect.w = texture_w;
	this->dstrect.h = texture_h;
	this->dstrect.x = -texture_w;
	this->dstrect.y = 0;

	this->last_crate_drop_time = this->last_slide_time = SDL_GetTicks();
	this->currently_sliding = true;
	this->holds_a_block = true;
	this->direction = RIGHT;

	this->block_container = block_container;
	this->generate_crate();
}


void Crane::generate_new_position_and_direction() {
	srand(time(NULL));
	int random_int = rand() % 2;

	if (!random_int) {
		this->direction = LEFT;
		this->dstrect.x = WINDOW_WIDTH + this->dstrect.w;
	} else {
		this->direction = RIGHT;
		this->dstrect.x = -this->dstrect.w;
	}	
}


void Crane::movement() {	
	if (this->currently_sliding && SDL_GetTicks() - this->last_slide_time > 1000 / FPS) {
		this->last_slide_time = SDL_GetTicks(); 

		if (this->direction == LEFT) {
			this->dstrect.x -= CRANE_VELOCITY; 		
			if (this->holds_a_block) {	
				int x_coordinate_of_block_while_moving = this->dstrect.x + this->dstrect.w / 2- this->current_block->get_width() / 2;  
				this->current_block->set_x_coordinate(x_coordinate_of_block_while_moving);	
			}
	
			if (this->dstrect.x + this->dstrect.w < -2*this->dstrect.w)
				this->currently_sliding = false;
	
			if (this->dstrect.x <= this->x_coordinate_of_the_drop_target) {
				this->current_block->set_x_coordinate(this->x_coordinate_of_the_drop_target);
				this->drop_crate();	
			}		
		} else {
			this->dstrect.x += CRANE_VELOCITY; 	
			if (this->holds_a_block) {	
				int x_coordinate_of_block_while_moving = this->dstrect.x + this->dstrect.w / 2- this->current_block->get_width() / 2;  
				this->current_block->set_x_coordinate(x_coordinate_of_block_while_moving);	
			}

			if (this->dstrect.x > WINDOW_WIDTH + 2*this->dstrect.w)
				this->currently_sliding = false;

			if (this->dstrect.x >= this->x_coordinate_of_the_drop_target) {
				this->current_block->set_x_coordinate(this->x_coordinate_of_the_drop_target);
				this->drop_crate();	
			}		
		}
	}

}


void Crane::out_of_frame_waiting_time() {
	if (!this->currently_sliding) {
		/// When the crane goes out of the frame of the window, it waits
		/// 3 seconds.	
		std::cout << "waiting...\n";	
		Uint32 out_of_frame_waiting_time = SDL_GetTicks();	
		//while (SDL_GetTicks() - out_of_frame_waiting_time < 3000){}	

		std::cout << "done!\n";	
		this->generate_new_position_and_direction();
		this->generate_crate();
		this->currently_sliding = true;	
	}
}


void Crane::generate_crate() {
	this->holds_a_block = true;
	this->current_block = new Block(this->renderer, this->textures, this->dstrect.x, this->dstrect.y + this->dstrect.h / 2);	
	this->block_container->add_block(this->current_block);	

	//int possible_block_x_coordinates[] = {0, 64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704};
	srand(time(NULL));
	int random_int = rand() % 12;
	std::cout << "Random int from Crane::generate_crate(): " << random_int << "\n";
	//this->x_coordinate_of_the_drop_target = possible_block_x_coordinates[random_int];
	this->x_coordinate_of_the_drop_target = random_int * this->current_block->get_width();
}


void Crane::drop_crate() {
	/// Generate a random number between 0 and 12. (12 blocks can fit into the
	/// width of the window). Then set the x coordinate of the target to be 
	/// the random_int * block_width.			
	/// Should be called in Crane::movement.
	this->current_block->fall();
	this->holds_a_block = false;		
}


void Crane::slide() {
	this->movement();	
	this->out_of_frame_waiting_time();
}


void Crane::draw() {
	SDL_RenderCopy(this->renderer, this->texture, NULL, &this->dstrect);		
} 


static pthread_mutex_t crane_mutex; 

void* Crane::handle_thread(void* arg) {
	Crane* crane = (Crane*)arg;
	pthread_mutex_init(&crane_mutex, NULL); 		
		
	while (crane->currently_sliding) {
		pthread_mutex_lock(&crane_mutex);					
		crane->slide();	
		pthread_mutex_unlock(&crane_mutex);					
	}		
	
	pthread_mutex_destroy(&crane_mutex);
	return NULL;
}


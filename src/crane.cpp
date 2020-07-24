#include "crane.h"
#include <cstdlib>
#include <ctime>

static bool CRANE_THREAD_RUNNING; 

Crane::Crane(SDL_Renderer* renderer, Textures* textures, BlockContainer* block_container) {
	int texture_w, texture_h;
	CRANE_THREAD_RUNNING = true;	
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

	this->collision_detector = new CollisionDetector(block_container);
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


void Crane::move_to_left() {
	this->dstrect.x -= CRANE_VELOCITY; 		

	if (this->holds_a_block) {	
		int x_coordinate_of_block_while_moving = this->dstrect.x + this->dstrect.w / 2- this->current_block->get_width() / 2;  
		this->current_block->set_x_coordinate(x_coordinate_of_block_while_moving);	
	}
	
	/// The value is -2*this->dstrect.w instead of 0 because the crane thread
	/// also handles the block fall method. If it was 0, then both the crane and the
	/// block falling would stop.
	if (this->dstrect.x + this->dstrect.w < -2*this->dstrect.w)
		this->currently_sliding = false;

	if (this->dstrect.x <= this->x_coordinate_of_the_drop_target) {
		this->current_block->set_x_coordinate(this->x_coordinate_of_the_drop_target);
		this->drop_crate();	
	}		
}


void Crane::move_to_right() {
	this->dstrect.x += CRANE_VELOCITY; 	
	if (this->holds_a_block) {	
		int x_coordinate_of_block_while_moving = this->dstrect.x + this->dstrect.w / 2- this->current_block->get_width() / 2;  
		this->current_block->set_x_coordinate(x_coordinate_of_block_while_moving);	
	}

	/// The value is WINDOW_WIDTH + 2*this->dstrect.w instead of WINDOW_WIDTH because 
	/// the crane thread also handles the block fall method. If it was WINDOW_WIDTH, 
	/// then both the crane and the block falling would stop.
	if (this->dstrect.x > WINDOW_WIDTH + 2*this->dstrect.w)
		this->currently_sliding = false;

	if (this->dstrect.x >= this->x_coordinate_of_the_drop_target) {
		this->current_block->set_x_coordinate(this->x_coordinate_of_the_drop_target);
		this->drop_crate();	
	}		
}


void Crane::movement() {	
	if (this->currently_sliding && SDL_GetTicks() - this->last_slide_time > 1000 / FPS) {
		this->last_slide_time = SDL_GetTicks(); 

		if (this->direction == LEFT) {
			this->move_to_left();
		} else {
			this->move_to_right();
		}
	}
}


void Crane::out_of_frame_waiting_time() {
	if (!this->currently_sliding) {
		/// When the crane goes out of the frame of the window, it waits
		/// 3 seconds.	
		std::cout << "waiting...\n";	
		Uint32 out_of_frame_waiting_time = SDL_GetTicks();	
		while (SDL_GetTicks() - out_of_frame_waiting_time < 3000){}	

		std::cout << "done!\n";	
		this->generate_new_position_and_direction();
		this->generate_crate();
		this->currently_sliding = true;	
	}
}


void Crane::generate_crate() {
	srand(time(NULL));
	int random_int = rand() % 12;

	while (this->block_container->get_number_of_blocks_on_column(random_int) == MAXIMUM_NUMBER_OF_BLOCKS_ON_COLUMN) {
		random_int = rand() % 12;
	}

	this->holds_a_block = true;
	this->current_block = new Block(this->renderer, this->textures, this->dstrect.x, this->dstrect.y + this->dstrect.h / 2);	
	this->block_container->add_block(this->current_block, random_int);	
		
	std::cout << "Random int from Crane::generate_crate(): " << random_int << "\n";
	this->x_coordinate_of_the_drop_target = random_int * this->current_block->get_width();
}


void Crane::drop_crate() {
	this->current_block->fall();

	if (this->collision_detector->bottom_side_collision_of_block_in_motion(this->current_block, this->x_coordinate_of_the_drop_target)) {
		this->current_block->set_as_landed();						
	}

	this->holds_a_block = false;		
}


void Crane::slide() {
	this->movement();	
	this->out_of_frame_waiting_time();
}


void Crane::draw() {
	SDL_RenderCopy(this->renderer, this->texture, NULL, &this->dstrect);		
} 


void Crane::stop() {
	CRANE_THREAD_RUNNING = false;	
}


int Crane::handle_thread(void* arg) {
	Crane* crane = (Crane*)arg;
		
	while (crane->currently_sliding) {
		crane->slide();	
		if (!CRANE_THREAD_RUNNING)
			crane->currently_sliding = false;
	}		
	
	return 0;
}


Crane::~Crane() {
	delete this->collision_detector;
}

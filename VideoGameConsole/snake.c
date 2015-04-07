/*
 * game.c
 *
 * Created: 3/18/2015 2:10:13 PM
 *  Author: Patrick
 */ 

#include "snake.h"

#define GET_FRAME_BUFFER_PTR(X, Y) frame_buffer + Y * WIDTH + X

void init_snake_body();
void init_game_state();
void update_snake();
void update_snake_position(const char new_x, const char new_y);
static void add_new_snake_body_cell(const char new_cell_x, const char new_cell_y);
static void reset_game();
static void check_if_snake_ate_fruit();

register char snake_head_pos_x asm("r13");
register char snake_head_pos_y asm("r14");
register char fruit_pos_x asm("r15");
register char fruit_pos_y asm("r16");
static unsigned char snake_body_size;
static unsigned char game_paused;
static unsigned char updates;
static unsigned char update_snake_flag;

void initialize_game() {
	init_snake_body();
	init_game_state();
	fruit_pos_x = fruit_spawn_positions[fruit_pos_curr_index].x;
	fruit_pos_y = fruit_spawn_positions[fruit_pos_curr_index].y;
	*(GET_FRAME_BUFFER_PTR(fruit_pos_x, fruit_pos_y)) = FRUIT_COLOUR;
}

void init_snake_body() {
	unsigned char i;
	char x = SNAKE_BODY_INIT_X;
	char y = SNAKE_BODY_INIT_Y;
	snake_body_size = SNAKE_BODY_INIT_SIZE;
	update_snake_flag = 0x00;
	
	snake_head_pos_x = x;
	snake_head_pos_y = y;
	
	snake[0].frame_buffer_ptr = GET_FRAME_BUFFER_PTR(x, y);
	*(snake[0].frame_buffer_ptr) = SNAKE_HEAD_COLOUR;
	y++;
	
	for(i = 1; i < snake_body_size; i++) {
		snake[i].frame_buffer_ptr = GET_FRAME_BUFFER_PTR(x, y); 
		*(snake[i].frame_buffer_ptr) = SNAKE_BODY_COLOUR;
		snake[i].position.x = x;
		snake[i].position.y = y;
		y++;
	}
}

void init_game_state() {
	fruit_pos_curr_index = 0;
	curr_direction = UP;
	game_paused = 0xff;
	updates = 0;
}

void change_direction(const Direction new_direction) {
	switch(new_direction) {
		case UP:
		case DOWN:
			// If the y-coordinates for the first and second snake cell are the same it is traveling horizontally
			if(snake_head_pos_y == snake[1].position.y) {
				curr_direction = new_direction;
			}
			break;
		case LEFT:
		case RIGHT:
			// If the x-coordinate for the first and second snake cell are the same, it is traveling vertically
			if(snake_head_pos_x == snake[1].position.x) {
				curr_direction = new_direction;
			}
			break;
	}
}

void update_game_state() {
	if(!game_paused) {
		updates++;
		
		// Check if snake out of bounds
		if(snake_head_pos_y < 1 || snake_head_pos_y > HEIGHT - 2 || snake_head_pos_x < 1 || snake_head_pos_x > WIDTH - 2) {
			reset_game();
			return;
		}
		
		check_if_snake_ate_fruit();
		if(updates >= UPDATES_PER_SNAKE_UPDATE) {
			update_snake();
			updates = 0;
		}
	}
}

void update_snake() {
	switch(curr_direction) {
		case UP:
			update_snake_position(snake_head_pos_x, snake_head_pos_y - 1);
			break;
		case LEFT:
			update_snake_position(snake_head_pos_x - 1, snake_head_pos_y);
			break;
		case DOWN:
			update_snake_position(snake_head_pos_x, snake_head_pos_y + 1);
			break;
		case RIGHT:
			update_snake_position(snake_head_pos_x + 1, snake_head_pos_y);
			break;
	}
}

void update_snake_position(const char new_x, const char new_y) {
	register unsigned char i asm("r8");
	register char next_x asm("r9");
	register char next_y asm("r10");
	register char prev_x asm("r11");
	register char prev_y asm("r12");
	
	prev_x = snake_head_pos_x;
	prev_y = snake_head_pos_y;
	
	snake[0].position.x = new_x;
	snake[0].position.y = new_y;
	snake_head_pos_x = new_x;
	snake_head_pos_y = new_y;
	snake[0].frame_buffer_ptr = GET_FRAME_BUFFER_PTR(new_x, new_y); 
	*(snake[0].frame_buffer_ptr) = SNAKE_HEAD_COLOUR;
	
	next_x = prev_x;
	next_y = prev_y;
	
	for(i = 1; i < snake_body_size; i++) {
		prev_x = snake[i].position.x;
		prev_y = snake[i].position.y;
		
		if(prev_x == snake_head_pos_x && prev_y == snake_head_pos_y) {
			reset_game();
			return;
		}
			
		snake[i].position.x = next_x;
		snake[i].position.y = next_y;
		snake[i].frame_buffer_ptr = GET_FRAME_BUFFER_PTR(next_x, next_y);
		*(snake[i].frame_buffer_ptr) = SNAKE_BODY_COLOUR;
			
		next_x = prev_x;
		next_y = prev_y;
	}
	
	if(!update_snake_flag || snake_body_size >= MAX_SNAKE_SIZE) {
		*(GET_FRAME_BUFFER_PTR(next_x, next_y)) = 0x00;
		return;
	}
	
	add_new_snake_body_cell(next_x, next_y);
}

void add_new_snake_body_cell(const char new_cell_x, const char new_cell_y) {
	if(snake_body_size < MAX_SNAKE_SIZE) {
		snake[snake_body_size].position.x = new_cell_x;
		snake[snake_body_size].position.y = new_cell_y;
		snake_body_size++;
	}
	update_snake_flag = 0x00;
}

void reset_game() {
	clear_frame_buffer();
	initialize_game();
}

void check_if_snake_ate_fruit() {
	unsigned char *fruit_frame_buffer_ptr;
	if(snake_head_pos_x == fruit_pos_x && snake_head_pos_y == fruit_pos_y) {
		play_song(&up_song);
		fruit_pos_curr_index++;
		if(fruit_pos_curr_index >= NUM_POSITIONS) {
			fruit_pos_curr_index = 0;
		}
		
		fruit_pos_x = fruit_spawn_positions[fruit_pos_curr_index].x;
		fruit_pos_y = fruit_spawn_positions[fruit_pos_curr_index].y;
		fruit_frame_buffer_ptr = GET_FRAME_BUFFER_PTR(fruit_pos_x, fruit_pos_y);
		while(*fruit_frame_buffer_ptr == SNAKE_BODY_COLOUR) {
			fruit_pos_curr_index++;
			if(fruit_pos_curr_index >= NUM_POSITIONS) {
				fruit_pos_curr_index = 0;
			}
			
			fruit_pos_x = fruit_spawn_positions[fruit_pos_curr_index].x;
			fruit_pos_y = fruit_spawn_positions[fruit_pos_curr_index].y;
			fruit_frame_buffer_ptr = GET_FRAME_BUFFER_PTR(fruit_pos_x, fruit_pos_y);
		}
		*(fruit_frame_buffer_ptr) = FRUIT_COLOUR;
		update_snake_flag = 0xff;
	}
}

void toggle_pause_game() {
	if(game_paused) {
		game_paused = 0x00;
	} else {
		game_paused = 0xff;
	}
}

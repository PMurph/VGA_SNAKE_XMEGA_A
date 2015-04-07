/*
 * snake.h
 *
 * Created: 3/18/2015 2:10:27 PM
 *  Author: Patrick
 */ 


#ifndef SNAKE_H_
#define SNAKE_H_

#include "frame_buffer.h"
#include "snake_directions.h"
#include "fruit.h"
#include "sound_driver.h"

#define MAX_SNAKE_SIZE 35
#define SNAKE_BODY_INIT_SIZE 3
#define SNAKE_BODY_INIT_X 7
#define SNAKE_BODY_INIT_Y 7
#define SNAKE_BODY_COLOUR 0x03
#define SNAKE_HEAD_COLOUR 0x02
#define UPDATES_PER_SNAKE_UPDATE 8

typedef struct SNAKE_BODY_CELL {
	unsigned char* frame_buffer_ptr;
	Position position;
} SnakeBody;

SnakeBody snake[MAX_SNAKE_SIZE];

void initialize_game(); 
void change_direction(const Direction new_direction);
void update_game_state();
void toggle_pause_game();

#endif /* SNAKE_H_ */
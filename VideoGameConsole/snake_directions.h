/*
 * snake_directions.h
 *
 * Created: 3/18/2015 3:59:44 PM
 *  Author: Patrick
 */ 


#ifndef SNAKE_DIRECTIONS_H_
#define SNAKE_DIRECTIONS_H_

typedef enum DIRECTIONS {
	UP,
	LEFT,
	DOWN,
	RIGHT	
} Direction;

register Direction curr_direction asm("r17");;

#endif /* SNAKE_DIRECTIONS_H_ */
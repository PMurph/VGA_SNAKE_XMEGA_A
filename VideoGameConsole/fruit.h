/*
 * fruit.h
 *
 * Created: 3/20/2015 4:30:37 PM
 *  Author: Patrick
 */ 


#ifndef FRUIT_H_
#define FRUIT_H_

#define FRUIT_COLOUR 0x01
#define NUM_POSITIONS 20

typedef struct POSITION {
	char x;
	char y;
} Position;

const Position fruit_spawn_positions[NUM_POSITIONS];
unsigned char fruit_pos_curr_index;

#endif /* FRUIT_H_ */
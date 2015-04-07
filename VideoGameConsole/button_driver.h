/*
 * button_driver.h
 *
 * Created: 3/8/2015 3:59:03 PM
 *  Author: Patrick
 */ 


#ifndef __BUTTON_DRIVER_H_
#define __BUTTON_DRIVER_H_

#include <avr/io.h>
#include "snake.h"

#define BUTTON_ON_FLAG_bm 0x01
#define BUTTON_CHANGED_FLAG_bm 0x02;

#define DIRECTION_BTN_PORT PORTD

#define UP_BUTTON PIN0_bm
#define DOWN_BUTTON PIN1_bm
#define RIGHT_BUTTON PIN2_bm
#define LEFT_BUTTON PIN3_bm
#define UP_BUTTON_INDEX 0
#define DOWN_BUTTON_INDEX 1
#define RIGHT_BUTTON_INDEX 2
#define LEFT_BUTTON_INDEX 3

#define OPTION_BTN_PORT PORTR

#define OPT1_BTN PIN0_bm
#define OPT1_BTN_INDEX 4

#define NUM_BUTTONS 5

#define BUTTON_MAX 5
#define BUTTON_ON_THRESHOLD 3
#define BUTTON_OFF_THRESHOLD 2

typedef struct BUTTON {
	unsigned char debounce_count;
	unsigned char button_flags;
} Button;

void setup_buttons();
void sample_buttons();
const unsigned char has_button_changed(const unsigned char button_index);
const unsigned char is_button_pressed(const unsigned char button_index);

#endif /* BUTTON_DRIVER_H_ */
/*
 * button_driver.c
 *
 * Created: 3/8/2015 3:59:23 PM
 *  Author: Patrick
 */ 

#include "button_driver.h"

#define CONVERT_INDEX_TO_BITMAP(INDEX) (1 << INDEX)

Button buttons[NUM_BUTTONS] = {
	{ .debounce_count = 0, .button_flags = 0 },
	{ .debounce_count = 0, .button_flags = 0 },
	{ .debounce_count = 0, .button_flags = 0 },
	{ .debounce_count = 0, .button_flags = 0 },
	{ .debounce_count = 0, .button_flags = 0 },		
};

static void increment_button_debounce_count(const unsigned char button_index);
static void decrement_button_debounce_count(const unsigned char button_index);

register unsigned char button_on_flags asm("r6");
register unsigned char button_changed_flags asm("r7");

void setup_buttons() {
	PORTR_DIRCLR = OPT1_BTN;
	
	PORTR_PIN0CTRL &= ~(PORT_OPC_gm);
	PORTR_PIN0CTRL |= PORT_OPC_PULLUP_gc;
	
	PORTR_PIN1CTRL &= ~(PORT_OPC_gm);
	PORTR_PIN1CTRL |= PORT_OPC_PULLUP_gc;
}

void sample_buttons() {
	if(PORTD_IN & UP_BUTTON) {
		increment_button_debounce_count(UP_BUTTON_INDEX);
	} else {
		decrement_button_debounce_count(UP_BUTTON_INDEX);
	}
		
	if(PORTD_IN & DOWN_BUTTON) {
		increment_button_debounce_count(DOWN_BUTTON_INDEX);
	} else {
		decrement_button_debounce_count(DOWN_BUTTON_INDEX);
	}
		
	if(PORTD_IN & RIGHT_BUTTON) {
		increment_button_debounce_count(RIGHT_BUTTON_INDEX);
	} else {
		decrement_button_debounce_count(RIGHT_BUTTON_INDEX);
	}
		
	if(PORTD_IN & LEFT_BUTTON) {
		increment_button_debounce_count(LEFT_BUTTON_INDEX);
	} else {
		decrement_button_debounce_count(LEFT_BUTTON_INDEX);
	}
		
	if(PORTR_IN & OPT1_BTN) {
		decrement_button_debounce_count(OPT1_BTN_INDEX);
	} else {
		increment_button_debounce_count(OPT1_BTN_INDEX);
	}
}

void increment_button_debounce_count(const unsigned char button_index) {
	Button* button = &(buttons[button_index]);
	unsigned char button_index_bm = CONVERT_INDEX_TO_BITMAP(button_index);
	
	if(button->debounce_count < BUTTON_MAX) {
		button->debounce_count++;
		if(!(button_on_flags & button_index_bm) && button->debounce_count >= BUTTON_ON_THRESHOLD) {
			button_changed_flags |= button_index_bm;
			button_on_flags |= button_index_bm;
		}
	}
}

void decrement_button_debounce_count(const unsigned char button_index) {
	Button* button = &(buttons[button_index]);
	unsigned char button_index_bm = CONVERT_INDEX_TO_BITMAP(button_index);
	
	if(button->debounce_count > 0) {
		button->debounce_count--;
		if((button_on_flags & button_index_bm) && button->debounce_count <= BUTTON_OFF_THRESHOLD) {
			button_changed_flags |= button_index_bm;
			button_on_flags &= ~(button_index_bm);
		}
	}
}

const unsigned char has_button_changed(const unsigned char button_index) {
	return button_changed_flags & CONVERT_INDEX_TO_BITMAP(button_index);
}

const unsigned char is_button_pressed(const unsigned char button_index) {
	button_changed_flags &= ~(CONVERT_INDEX_TO_BITMAP(button_index));
	return (button_on_flags & CONVERT_INDEX_TO_BITMAP(button_index));
}
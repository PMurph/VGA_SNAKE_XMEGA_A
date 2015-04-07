/*
 * main.c
 *
 * Created: 2/17/2015 11:56:42 AM
 *  Author: Patrick
 */ 

#include <avr/sleep.h>
#include "vga_driver.h"

static void initialize_console();
static void initialize_games();
static void setup_main_timer();
static void update_state();

int main(void)
{
	set_sleep_mode(SLEEP_MODE_IDLE);
	PORTF.DIRSET |= 0x01;
	initialize_console();
	initialize_games();
	start_vga();
	
    while(1)
    {
		sleep_mode();
		if(vsync_backporch) {
			vsync_backporch = 0x00;
			update_state();
		}
    }
}

void initialize_console() {
	setup_main_timer();
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	cli();
	setup_sound();
	setup_buttons();
	setup_sound();
	setup_vga();
	sei();
}

void initialize_games() {
	initialize_game();
}

void setup_main_timer() {
	OSC.PLLCTRL = 0;
	OSC.PLLCTRL |= 25;
	OSC.CTRL |= OSC_PLLEN_bm;
	
	while(!(OSC.STATUS & OSC_PLLRDY_bm));
	
	CCP = CCP_IOREG_gc;
	CLK.CTRL = CLK_SCLKSEL_PLL_gc;
}

void update_state() {
	sample_buttons();
	update_game_state();
	
	if(has_button_changed(OPT1_BTN_INDEX) && is_button_pressed(OPT1_BTN_INDEX)) {
		toggle_pause_game();
	}
	
	if(has_button_changed(DOWN_BUTTON_INDEX) && is_button_pressed(DOWN_BUTTON_INDEX)) {
		change_direction(DOWN);
	}
	
	if(has_button_changed(UP_BUTTON_INDEX) && is_button_pressed(UP_BUTTON_INDEX)) {
		change_direction(UP);
	}
	
	if(has_button_changed(LEFT_BUTTON_INDEX) && is_button_pressed(LEFT_BUTTON_INDEX)) {
		change_direction(LEFT);
	}
	
	if(has_button_changed(RIGHT_BUTTON_INDEX) && is_button_pressed(RIGHT_BUTTON_INDEX)) {
		change_direction(RIGHT);
	}
}
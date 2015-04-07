/*
 * vga_driver.c
 *
 * Created: 3/6/2015 12:52:17 PM
 *  Author: Patrick
 */ 

#include "vga_driver.h"

static void setup_vga_port();
static void setup_vga_timers();
static void setup_scanline_timer();
static void setup_pixel_clock();

static volatile unsigned short curr_scanline;
register unsigned char visible_area asm("r3");
register unsigned char num_pixels_displayed asm("r4");

void setup_vga() {
	setup_vga_port();
	setup_vga_timers();
	vsync_backporch = 0x00;
	curr_scanline = 0;
	screen_colour_mask = DEFAULT_SCREEN_COLOUR_MASK;
	frame_buffer_ptr = frame_buffer;
}

void setup_vga_port() {
	PORTCFG_VPCTRLA = 0x20; // Assigns PORTC to Virtual Port 1 and PORTA to Virtual Port 0
	VGA_PORT.DIR = VSYNC_PIN | HSYNC_PIN;
	COLOR_PORT.DIR = RED_PIN | GREEN_PIN | BLUE_PIN;
	
	VGA_PORT_OUT |= VSYNC_PIN | HSYNC_PIN;
	COLOR_PORT_OUT &= ~(RED_PIN | GREEN_PIN | BLUE_PIN);
}

void setup_vga_timers() {
	setup_scanline_timer();
	setup_pixel_clock();
}

void setup_scanline_timer() {
	TCC0_PER = CYCLES_PER_HPERIOD;
	TCC0_CCA = CC_HSYNC_PULSE;
	TCC0_CCB = CC_HBACKPORCH;
	TCC0_CCC = CC_HFRONTPORCH;
	
	TCC0_INTCTRLA = TC_OVFINTLVL_HI_gc;
	TCC0_INTCTRLB = TC_CCAINTLVL_MED_gc | TC_CCBINTLVL_MED_gc | TC_CCCINTLVL_MED_gc;
}

void setup_pixel_clock() {
	TCD0_PER = CYCLES_PER_PIXEL;
	TCD0_INTCTRLA = TC_OVFINTLVL_MED_gc;
}

void start_vga() {
	curr_scanline = 0;
	TCC0_CTRLA = TC_CLKSEL_DIV2_gc;
	TCD0_CTRLA = TC_CLKSEL_DIV1_gc;
}

// Handles the end of an hsync pulse
ISR(TCC0_CCA_vect, ISR_NOBLOCK) {
	VGA_PORT_OUT |= HSYNC_PIN;
	num_pixels_displayed = 0;
	TCD0_CNT = 0;
	TCD0_INTCTRLA = TC_OVFINTLVL_LO_gc;
}

// Handles the end of the hsync back porch
ISR(TCC0_CCB_vect, ISR_NOBLOCK) {
	visible_area = 0xff;
	curr_scanline++;
	if(curr_scanline == SCAN_LINES_RESET) {
		TCE0_INTCTRLA = 0x00;
		frame_buffer_ptr = frame_buffer;
		curr_scanline = 0;
		TCD0_CTRLA = TC_CLKSEL_DIV1_gc;
	}
}

// Handles the end of the visible area
ISR(TCC0_CCC_vect, ISR_NOBLOCK) {
	visible_area = 0x00;
	TCD0_INTCTRLA = 0x00;
	COLOR_PORT_OUT = 0x00;
	if(curr_scanline == SCAN_LINES_VSYNC_OFF) {
		VGA_PORT_OUT &= ~(VSYNC_PIN);
		TCE0_INTCTRLA = TC_OVFINTLVL_LO_gc;
		vsync_backporch = 0xff;
	}
}

ISR(TCC0_OVF_vect, ISR_NOBLOCK) {
	TCC0_CNT = 0;
	VGA_PORT_OUT = ~(HSYNC_PIN);
	if((curr_scanline & 0x1f) != 24) {
		frame_buffer_ptr -= num_pixels_displayed;
	}
	if(curr_scanline == SCAN_LINES) {
		TCD0_CTRLA = TC_CLKSEL_OFF_gc;
	} else if(curr_scanline == SCAN_LINES_VSYNC) {
		VGA_PORT_OUT |= VSYNC_PIN;
	}
}

ISR(TCD0_OVF_vect) {
	TCD0_CNT = 0;
	COLOR_PORT_OUT = *frame_buffer_ptr & visible_area;
	frame_buffer_ptr += (1 & visible_area);
	num_pixels_displayed += (1 & visible_area);
}
/*
 * vga_driver.h
 *
 * Created: 3/6/2015 12:52:01 PM
 *  Author: Patrick
 */ 

#ifndef __VGA_DRIVER_H_
#define __VGA_DRIVER_H_

#include <avr/interrupt.h>

#include "vga_timing.h"
#include "button_driver.h"
#include "vga_ports.h"

#define SCAN_LINES 480
#define SCAN_LINES_VSYNC 489
#define SCAN_LINES_VSYNC_OFF 491
#define SCAN_LINES_RESET 525
#define DEFAULT_SCREEN_COLOUR_MASK 0x07
#define SCREEN_OFF_MASK 0xf8

unsigned char screen_colour_mask;

volatile unsigned char vsync_backporch;

void setup_vga();
void start_vga();

#endif /* __VGA_DRIVER_H_ */
/*
 * vga_ports.h
 *
 * Created: 3/7/2015 2:09:45 AM
 *  Author: Patrick
 */ 


#ifndef __VGA_PORTS_H_
#define __VGA_PORTS_H_

#include <avr/io.h>

#define VGA_PORT VPORT0
#define VGA_PORT_OUT VPORT0_OUT
#define COLOR_PORT VPORT1
#define COLOR_PORT_OUT VPORT1_OUT

#define RED_PIN PIN0_bm
#define GREEN_PIN PIN1_bm
#define BLUE_PIN PIN5_bm
#define HSYNC_PIN PIN6_bm
#define VSYNC_PIN PIN7_bm

#endif /* __VGA_PORTS_H_ */
/*
 * frame_buffer.h
 *
 * Created: 3/15/2015 1:14:14 PM
 *  Author: Patrick
 */ 


#ifndef FRAME_BUFFER_H_
#define FRAME_BUFFER_H_

#define WIDTH 16
#define HEIGHT 16

unsigned char frame_buffer[WIDTH * HEIGHT];
unsigned char* frame_buffer_ptr;

void clear_frame_buffer();

#endif /* FRAME_BUFFER_H_ */
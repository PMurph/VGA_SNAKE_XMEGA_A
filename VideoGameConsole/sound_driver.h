/*
 * sound_driver.h
 *
 * Created: 3/8/2015 1:34:04 PM
 *  Author: Patrick
 */ 


#ifndef __SOUND_DRIVER_H_
#define __SOUND_DRIVER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "sounds.h"

void setup_sound();
void play_song(const Song *song);

#endif /* SOUND_DRIVER_H_ */
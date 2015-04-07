/*
 * sound_driver.h
 *
 * Created: 3/8/2015 1:34:04 PM
 *  Author: Patrick
 */ 

#include "sound_driver.h"

static void setup_speaker();
static void setup_sound_timer();

static const Song *song_ptr;
static unsigned char curr_note;
static unsigned short curr_repeat;
static unsigned char curr_sound;
static unsigned char curr_song_repeat;

void setup_sound() {
	setup_speaker();
	setup_sound_timer();
}

void setup_speaker() {
	// Enable onboard speaker
	PORTQ_PIN3CTRL &= ~(PORT_OPC_gm);
	PORTQ_PIN3CTRL |= PORT_OPC_PULLUP_gc;
	
	DACB_CTRLC |= DAC_REFSEL_AVCC_gc;
	DACB_CTRLA |= DAC_ENABLE_bm | DAC_CH0EN_bm;
}

void setup_sound_timer() {
	TCE0_INTCTRLA = TC_OVFINTLVL_LO_gc;
	TCE0_CNT = 0;
}

void play_song(const Song *song) {
	song_ptr = song;
	
	curr_note = 0;
	curr_repeat = 0;
	curr_sound = 0;
	curr_song_repeat = 0;
	
	DACB_CH0DATA = song_ptr->notes[curr_note].sounds[curr_sound].amplitude;
	TCE0_PER = song_ptr->notes[curr_note].sounds[curr_sound].period;
	
	TCE0_CNT = 0;
	TCE0_CTRLA = TC_CLKSEL_DIV1_gc;
}

ISR(TCE0_OVF_vect) {
	if(curr_note == song_ptr->num_sounds) {
		if(curr_song_repeat < song_ptr->num_repeats) {
			curr_sound = 0;
			curr_repeat = 0;
			curr_note = 0;
			curr_song_repeat++;
			} else {
			TCE0_CTRLA = TC_CLKSEL_OFF_gc;
		}
	} else if(curr_sound < song_ptr->notes[curr_note].num_sounds) {
		curr_sound++;
	} else if(curr_repeat < song_ptr->notes[curr_note].num_repeats) {
		curr_repeat++;
		curr_sound = 0;
	} else if(curr_repeat == song_ptr->notes[curr_note].num_repeats) {
		curr_note++;
		curr_repeat = 0;
		curr_sound = 0;
	}
	DACB_CH0DATA = song_ptr->notes[curr_note].sounds[curr_sound].amplitude;
	TCE0_PER = song_ptr->notes[curr_note].sounds[curr_sound].period;
	TCE0_CNT = 0;
}
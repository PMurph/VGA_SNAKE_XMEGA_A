/*
 * sounds.c
 *
 * Created: 3/9/2015 11:16:54 AM
 *  Author: Patrick
 */ 

#include "sounds.h"

const Sound e_sound[SOUNDS_PER_NOTE] = {
	{ .amplitude = 0x7ff, .period = 635/*6325*/ },
	{ .amplitude = 0xbff, .period = 635/*6325*/ },
	{ .amplitude = 0xeff, .period = 635/*6325*/ },
	{ .amplitude = 0xfff, .period = 635/*6325*/ },
	{ .amplitude = 0xeff, .period = 635/*6325*/ },
	{ .amplitude = 0xbff, .period = 635/*6325*/ },
	{ .amplitude = 0x7ff, .period = 635/*6325*/ },
	{ .amplitude = 0x3ff, .period = 635/*6325*/ },
	{ .amplitude = 0x0ff, .period = 635/*6325*/ },
	{ .amplitude = 0x000, .period = 635/*6325*/ },
	{ .amplitude = 0x0ff, .period = 635/*6325*/ },
	{ .amplitude = 0x3ff, .period = 635/*6325*/ },
};

const Sound c_sound[SOUNDS_PER_NOTE] = {
	{ .amplitude = 0x7ff, .period = 587/*5875*/ },
	{ .amplitude = 0xbff, .period = 587/*5875*/ },
	{ .amplitude = 0xeff, .period = 587/*5875*/ },
	{ .amplitude = 0xfff, .period = 587/*5875*/ },
	{ .amplitude = 0xeff, .period = 587/*5875*/ },
	{ .amplitude = 0xbff, .period = 587/*5875*/ },
	{ .amplitude = 0x7ff, .period = 587/*5875*/ },
	{ .amplitude = 0x3ff, .period = 587/*5875*/ },
	{ .amplitude = 0x0ff, .period = 587/*5875*/ },
	{ .amplitude = 0x000, .period = 587/*5875*/ },
	{ .amplitude = 0x0ff, .period = 587/*5875*/ },
	{ .amplitude = 0x3ff, .period = 587/*5875*/ },
};

const Sound g_sound[SOUNDS_PER_NOTE] = {
	{ .amplitude = 0x7ff, .period = 532/*5325*/ },
	{ .amplitude = 0xbff, .period = 532/*5325*/ },
	{ .amplitude = 0xeff, .period = 532/*5325*/ },
	{ .amplitude = 0xfff, .period = 532/*5325*/ },
	{ .amplitude = 0xeff, .period = 532/*5325*/ },
	{ .amplitude = 0xbff, .period = 532/*5325*/ },
	{ .amplitude = 0x7ff, .period = 532/*5325*/ },
	{ .amplitude = 0x3ff, .period = 532/*5325*/ },
	{ .amplitude = 0x0ff, .period = 532/*5325*/ },
	{ .amplitude = 0x000, .period = 532/*5325*/ },
	{ .amplitude = 0x0ff, .period = 532/*5325*/ },
	{ .amplitude = 0x3ff, .period = 532/*5325*/ },
};

const Sound d_sound[SOUNDS_PER_NOTE] = {
	{ .amplitude = 0x7ff, .period = 710/*7100*/ },
	{ .amplitude = 0xbff, .period = 710/*7100*/ },
	{ .amplitude = 0xeff, .period = 710/*7100*/ },
	{ .amplitude = 0xfff, .period = 710/*7100*/ },
	{ .amplitude = 0xeff, .period = 710/*7100*/ },
	{ .amplitude = 0xbff, .period = 710/*7100*/ },
	{ .amplitude = 0x7ff, .period = 710/*7100*/ },
	{ .amplitude = 0x3ff, .period = 710/*7100*/ },
	{ .amplitude = 0x0ff, .period = 710/*7100*/ },
	{ .amplitude = 0x000, .period = 710/*7100*/ },
	{ .amplitude = 0x0ff, .period = 710/*7100*/ },
	{ .amplitude = 0x3ff, .period = 710/*7100*/ },
};

const Note up_notes[NUM_SOUNDS] = {
	{
		.num_sounds = SOUNDS_PER_NOTE,
		.sounds = e_sound,
		.num_repeats = 8/*82*/,
	},
	{
		.num_sounds = SOUNDS_PER_NOTE,
		.sounds = g_sound,
		.num_repeats = 10/*98*/,
	},
	{
		.num_sounds = SOUNDS_PER_NOTE,
		.sounds = e_sound,
		.num_repeats = 8/*82*/,
	},
	{
		.num_sounds = SOUNDS_PER_NOTE,
		.sounds = c_sound,
		.num_repeats = 9/*90*/,
	},
	{
		.num_sounds = SOUNDS_PER_NOTE,
		.sounds = d_sound,
		.num_repeats = 7/*74*/,
	},
	{
		.num_sounds = SOUNDS_PER_NOTE,
		.sounds = g_sound,
		.num_repeats = 10/*98*/,
	}
};

const Song up_song = {
	.num_sounds = 6,
	.notes = up_notes,
	.num_repeats = 1,
};
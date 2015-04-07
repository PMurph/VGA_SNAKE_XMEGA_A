/*
 * sounds.h
 *
 * Created: 3/9/2015 11:17:07 AM
 *  Author: Patrick
 */ 


#ifndef SOUNDS_H_
#define SOUNDS_H_

#define SOUNDS_PER_NOTE 12
#define NUM_SOUNDS 6

typedef struct SOUND {
	unsigned short amplitude;
	unsigned short period;
} Sound;

typedef struct NOTE {
	const unsigned char num_sounds;
	const Sound *sounds;
	const unsigned short num_repeats;
} Note;


typedef struct SONG {
	const unsigned char num_sounds;
	const Note *notes;
	const unsigned char num_repeats;
} Song;

const Song up_song;

#endif /* SOUNDS_H_ */
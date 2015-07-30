#ifndef SOUND_H
#define SOUND_H
#include "fmod.hpp"
#include "common.h"

class Sound{

public:
	FMOD::System     *sSystem;
	FMOD::Sound      *sound, *sound_to_play;
	FMOD::Channel    *channel;
	FMOD::DSP		 *fft;
	FMOD_RESULT       result;
	unsigned int      version;
	void             *extradriverdata;
	int               numsubsounds;

	void initialize();

	void playSong(const char *song);

	void update();

	void shutDown();
};

#endif
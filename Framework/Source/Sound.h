#ifndef SOUND_H
#define SOUND_H
#include "fmod.hpp"
#include "common.h"

class Sound{

public:
	FMOD::System     *sSystem;
	FMOD::Sound      *sound, *sound_to_play;
	FMOD::Channel    *channel = 0;
	FMOD_RESULT       result;
	unsigned int      version;
	void             *extradriverdata = 0;
	int               numsubsounds;

	void initialize();

	void playsong(const char *song);

	void update();

	void shutdown();
};

#endif
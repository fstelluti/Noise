#include "fmod.hpp"
#include "common.h"
#include "Sound.h"

	FMOD::System     *sSystem;
	FMOD::Sound      *sound, *sound_to_play;
	FMOD::Channel    *channel = 0;
	FMOD_RESULT       result;
	unsigned int      version;
	void             *extradriverdata = 0;
	int               numsubsounds;

	void initialize(){
		
		Common_Init(&extradriverdata);

		/*
		Create a System object and initialize.
		*/
		result = FMOD::System_Create(&sSystem);
		ERRCHECK(result);
	
		result = sSystem->getVersion(&version);
		ERRCHECK(result);
	
		if (version < FMOD_VERSION)
		{
			Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
		}
	
		result = sSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
		ERRCHECK(result);
	}

	void playSong(const char *song){
		result = sSystem->createStream(song, FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
		ERRCHECK(result);

		result = sound->getNumSubSounds(&numsubsounds);
		ERRCHECK(result);

		if (numsubsounds)
		{
			sound->getSubSound(0, &sound_to_play);
			ERRCHECK(result);
		}
		else
		{
			sound_to_play = sound;
		}

		/*
		Play the sound.
		*/
		result = sSystem->playSound(sound_to_play, 0, false, &channel);
		ERRCHECK(result);

		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);
	}

	void update(){
		Common_Update();

		if (Common_BtnPress(BTN_ACTION1))
		{
			bool paused;
			result = channel->getPaused(&paused);
			ERRCHECK(result);
			result = channel->setPaused(!paused);
			ERRCHECK(result);
		}

		result = sSystem->update();
		ERRCHECK(result);

		{
			unsigned int ms = 0;
			unsigned int lenms = 0;
			bool         playing = false;
			bool         paused = false;

			if (channel)
			{
				result = channel->isPlaying(&playing);
				if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
				{
					ERRCHECK(result);
				}

				result = channel->getPaused(&paused);
				if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
				{
					ERRCHECK(result);
				}

				result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
				if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
				{
					ERRCHECK(result);
				}

				result = sound_to_play->getLength(&lenms, FMOD_TIMEUNIT_MS);
				if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
				{
					ERRCHECK(result);
				}
			}
		}
	}

	void shutDown(){
		result = sound->release();  /* Release the parent, not the sound that was retrieved with getSubSound. */
		ERRCHECK(result);
		result = sSystem->close();
		ERRCHECK(result);
		result = sSystem->release();
		ERRCHECK(result);

		Common_Close();
	}
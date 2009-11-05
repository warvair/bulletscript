#include <iostream>
#include "AudioSystem.h"

bs::Machine<Bullet, Area, SoundEffect, Unit>* AudioSystem::mMachine = 0;
FSOUND_SAMPLE* AudioSystem::mSamples[AudioSystem::NUM_SAMPLES];
SoundEffect AudioSystem::mEffects[AudioSystem::NUM_FX];
std::list<int> AudioSystem::mFreeList;

// --------------------------------------------------------------------------------
void AudioSystem::initialise(bs::Machine<Bullet, Area, SoundEffect, Unit>* machine)
{
	mMachine = machine;
	FSOUND_Init(44100, 32, 0);

	// Load sound effects
	mSamples[0] = FSOUND_Sample_Load(FSOUND_FREE, "dblbass.wav", FSOUND_2D, 0, 0);
	mSamples[1] = FSOUND_Sample_Load(FSOUND_FREE, "discharge.wav", FSOUND_2D, 0, 0);
	mSamples[2] = FSOUND_Sample_Load(FSOUND_FREE, "drop1.wav", FSOUND_2D, 0, 0);
	mSamples[3] = FSOUND_Sample_Load(FSOUND_FREE, "extend2.wav", FSOUND_2D, 0, 0);
	mSamples[4] = FSOUND_Sample_Load(FSOUND_FREE, "gamelan.wav", FSOUND_2D, 0, 0);
	mSamples[5] = FSOUND_Sample_Load(FSOUND_FREE, "juno.wav", FSOUND_2D, 0, 0);
	mSamples[6] = FSOUND_Sample_Load(FSOUND_FREE, "keyb1.wav", FSOUND_2D, 0, 0);
	mSamples[7] = FSOUND_Sample_Load(FSOUND_FREE, "kick1.wav", FSOUND_2D, 0, 0);
	mSamples[8] = FSOUND_Sample_Load(FSOUND_FREE, "laser1.wav", FSOUND_2D, 0, 0);
	mSamples[9] = FSOUND_Sample_Load(FSOUND_FREE, "laser2.wav", FSOUND_2D, 0, 0);
	mSamples[10] = FSOUND_Sample_Load(FSOUND_FREE, "laser3.wav", FSOUND_2D, 0, 0);
	mSamples[11] = FSOUND_Sample_Load(FSOUND_FREE, "rhodes.wav", FSOUND_2D, 0, 0);
	mSamples[12] = FSOUND_Sample_Load(FSOUND_FREE, "shimmer.wav", FSOUND_2D, 0, 0);

	for (int i = 0; i < NUM_FX; ++i)
	{
		mEffects[i].__index = -1;
		mEffects[i].channel = -1;
		mFreeList.push_back(i);
	}
}
// --------------------------------------------------------------------------------
void AudioSystem::shutdown()
{
	FSOUND_Close();
}
// --------------------------------------------------------------------------------
void AudioSystem::update(float frameTime)
{
	for (int i = 0; i < NUM_FX; ++i)
	{
		if (mEffects[i].channel >= 0)
		{
			// Bulletscript: apply affectors and control functions
			mMachine->updateType(&mEffects[i], 0, 0, frameTime);

			// See if sound has stopped playing
			if (!FSOUND_IsPlaying(mEffects[i].channel))
				killSound(&mEffects[i], false);
		}
	}
}
// --------------------------------------------------------------------------------
bs::UserTypeBase* AudioSystem::emitSound(bs::bstype x, bs::bstype y, const bs::bstype* args)
{
	if (mFreeList.empty())
	{
		// No space, failure
		return 0;
	}

	int slot = mFreeList.front();
	mFreeList.pop_front();

	int index = args[-2];
	bool loop = args[-1] == 0 ? false : true;

	mEffects[slot].__index = slot;
	mEffects[slot].channel = FSOUND_PlaySound(FSOUND_FREE, mSamples[index]);
	
	if (loop)
		FSOUND_SetLoopMode(mEffects[slot].channel, FSOUND_LOOP_NORMAL);

	return &(mEffects[slot]);
}
// --------------------------------------------------------------------------------
void AudioSystem::killSound(bs::UserTypeBase* object)
{
	killSound(static_cast<SoundEffect*>(object), true);
}
// --------------------------------------------------------------------------------
void AudioSystem::killSound(SoundEffect* fx, bool stop)
{
	// Stop sound effect
	if (stop)
		FSOUND_StopSound(fx->channel);

	fx->__index = -1;
	fx->channel = -1;

	mFreeList.push_back(fx->__index);
}
// --------------------------------------------------------------------------------
void AudioSystem::setVolume(bs::UserTypeBase* object, bs::bstype value)
{
	SoundEffect* fx = static_cast<SoundEffect*>(object);
	
	int volume = value * 255.0f;
	int x = FSOUND_SetVolume(fx->channel, value * 255.0f);
}
// --------------------------------------------------------------------------------
bs::bstype AudioSystem::getVolume(bs::UserTypeBase* object)
{
	SoundEffect* fx = static_cast<SoundEffect*>(object);

	int volume = FSOUND_GetVolume(fx->channel);
	return volume / 255.0f;
}
// --------------------------------------------------------------------------------
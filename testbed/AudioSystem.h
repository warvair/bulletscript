#ifndef __AUDIOSYSTEM_H__
#define __AUDIOSYSTEM_H__

#include <fmod.h>
#include "bsBulletScript.h"

struct Bullet;
struct Area;
struct Unit;

struct SoundEffect
{
	int channel;

	int __index;

	// For bulletscript
	bs::FireTypeControl* __ft;
};

class AudioSystem
{
	static bs::Machine<Bullet, Area, SoundEffect, Unit>* mMachine;

	static const int NUM_SAMPLES = 13;
	static FSOUND_SAMPLE* mSamples[NUM_SAMPLES];

	static const int NUM_FX = 32;
	static SoundEffect mEffects[NUM_FX];

	static std::list<int> mFreeList;

	static void killSound(SoundEffect* fx, bool stop);

public:

	static void initialise(bs::Machine<Bullet, Area, SoundEffect, Unit>* machine);

	static void shutdown();

	static void update(float frameTime);

	// Scripting
	static SoundEffect* emitSound(bs::bstype x, bs::bstype y, const bs::bstype* args);

	static void killSound(void* object);

	static void setVolume(void* object, bs::bstype value);

	static bs::bstype getVolume(void* object);
};

#endif
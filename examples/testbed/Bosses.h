#ifndef __BOSSES_H__
#define __BOSSES_H__

#include "Boss.h"

class Boss1 : public Boss
{
public:

	explicit Boss1(bs::Machine* machine) :
		Boss(machine) 
	{
		setBounds(112, 20, 112, 40);
		mImageFile = "boss1.tga";
	}


	void update(float frameTime)
	{
	}
};

class Boss2 : public Boss
{
public:

	explicit Boss2(bs::Machine* machine) :
		Boss(machine)
	{
		setBounds(148, 26, 148, 26);
		mImageFile = "boss2.tga";
	}

	void update(float frameTime)
	{
	}
};

#endif
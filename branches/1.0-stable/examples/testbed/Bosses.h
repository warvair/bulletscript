#ifndef __BOSSES_H__
#define __BOSSES_H__

#include "Main.h"
#include "Boss.h"

class Boss1 : public Boss
{
public:

	explicit Boss1(bs::Machine* machine) :
		Boss(machine) 
	{
		setBounds(112, 20, 112, 40);
		mImageFile = "boss1.tga";
		mControllerName = "Boss1";
	}

	int getTargetY() const
	{
		return SCREEN_HEIGHT - getHeight() / 2;
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
		mControllerName = "Boss2";
	}

	int getTargetY() const
	{
		return SCREEN_HEIGHT - getHeight() / 2;
	}

	void update(float frameTime)
	{
	}
};

class Boss3 : public Boss
{
public:

	explicit Boss3(bs::Machine* machine) :
		Boss(machine)
	{
		setBounds(65, 30, 65, 30);
		mImageFile = "boss3.tga";
		mControllerName = "Boss3";
	}

	void update(float frameTime)
	{
	}
};

class Boss4 : public Boss
{
	bool m25, m50;

public:

	explicit Boss4(bs::Machine* machine) :
		Boss(machine),
		m25(false),
		m50(false)
	{
		setBounds(70, 67, 70, 63);
		mImageFile = "boss4.tga";
		mControllerName = "Boss4";
	}

	int getTargetY() const
	{
		return SCREEN_HEIGHT - getHeight() / 2;
	}

	void update(float frameTime)
	{
		if (!m50 && getHealth() < 50)
		{
			// Goto erratic state
			mGunController->raiseEvent("On50", 0);
			m50 = true;
		}
		if (!m25 && getHealth() < 25)
		{
			// Goto erratic state
			mGunController->raiseEvent("On25", 0);
			m25 = true;
		}
	}
};

#endif
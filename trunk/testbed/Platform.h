#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "Main.h"

#ifndef MINIMAL_APP
#include <SDL.h>
#endif

bool processMessages();

bool keyDown(int key);

float getHorzMovement();

float getVertMovement();

float getBulletCount();

bool inFocus();

bool debugging();

bool paused();

int getCurBullet();

void setCurBullet(int val);

#endif
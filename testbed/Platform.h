#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <SDL.h>

bool processMessages();

float getHorzMovement();

float getVertMovement();

float getBulletCount();

bool inFocus();

bool debugging();

bool paused();

int getCurBullet();

void setCurBullet(int val);

#endif
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <SDL.h>

bool processMessages();

float getHorzMovement();

float getVertMovement();

float getBulletCount();

bool inFocus();

#endif
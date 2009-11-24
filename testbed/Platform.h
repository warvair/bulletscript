#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <vector>
#include <string>
#include "Main.h"

#ifndef MINIMAL_APP
#include <SDL.h>
#endif

bool processMessages();

bool keyDown(int key);

bool inFocus();

bool debugging();

bool paused();

unsigned int getTicks();

std::vector<std::string> getDirectoryListing(const std::string &dir, const std::string &pattern);

#endif
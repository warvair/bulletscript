#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <vector>
#include <string>
#include "Main.h"

#include <SDL.h>
#endif

unsigned char* loadFile(const char* fileName, size_t& byteSize);

bool processMessages();

bool keyDown(int key);

bool keyPressed(int key);

bool keyReleased(int key);

bool inFocus();

bool debugging();

bool paused();

unsigned int getTicks();

std::vector<std::string> getDirectoryListing(const std::string &dir, const std::string &pattern);

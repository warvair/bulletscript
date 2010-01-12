#include "Platform.h"
#include "bsBulletScript.h"

static bool gInFocus = true;
static bool gDebug = false;
static bool gPaused = false;

//
// Input/message handling
//
static int gKeys[SDLK_LAST] = {0};
static int gOldKeys[SDLK_LAST] = {0};

bool processMessages()
{
//	memset(gKeys, 0, SDLK_LAST * sizeof(int));
	memcpy(gOldKeys, gKeys, SDLK_LAST * sizeof(int));

	SDL_Event evt;
	while (SDL_PollEvent(&evt)) 
	{
		switch (evt.type) 
		{
		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:
			gKeys[evt.key.keysym.sym] = 1;
			if (evt.key.keysym.sym == SDLK_ESCAPE)
				return false;
			break;

		case SDL_KEYUP:
			gKeys[evt.key.keysym.sym] = 0;
			break;

		case SDL_ACTIVEEVENT:
			if (evt.active.state == SDL_APPMOUSEFOCUS)
			{
				if (evt.active.gain == 0)
				{
					gInFocus = false;
				}
				else if (evt.active.gain == 1)
				{
					gInFocus = true;
				}
			}
			break;

		default:
			break;
		}
	}

	return true;
}

bool keyDown(int key)
{
	return (gKeys[key] == 1);
}

bool keyPressed(int key)
{
	return (gKeys[key] == 1 && gOldKeys[key] == 0);
}

bool keyReleased(int key)
{
	return (gKeys[key] == 0 && gOldKeys[key] == 1);
}

bool inFocus()
{
	return gInFocus;
}

bool debugging()
{
	return gDebug;
}

bool paused()
{
	return gPaused;
}

//
// Timing
//
#if BS_PLATFORM == BS_PLATFORM_LINUX
#	include <stdlib.h>
#	include <sys/time.h>
#	include <time.h>

timeval start_time;

unsigned int timeGetTime()
{
	timeval now;
	unsigned int ticks;
	
	gettimeofday(&now, NULL);
	ticks = (now.tv_sec - start_time.tv_sec) * 1000 + (now.tv_usec - start_time.tv_usec) / 1000;
	return ticks;
}
#endif

#if BS_PLATFORM == BS_PLATFORM_WIN32
#	include <windows.h>
#	include <direct.h>
#	include <io.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>

unsigned int getTicks()
{
	return SDL_GetTicks();
}

//
// File utils
//

unsigned char* loadFile(const char* fileName, size_t& byteSize)
{
	FILE *fp = fopen(fileName, "rb");

	if (!fp)
	{
		byteSize = 0;
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	byteSize = ftell(fp);
	
	rewind(fp);
	unsigned char* buffer = new unsigned char[byteSize];
	fread(buffer, byteSize, 1, fp);
	fclose(fp);

	return buffer;
}

#if BS_PLATFORM == BS_PLATFORM_WIN32
std::vector<std::string> getDirectoryListing(const std::string& dir, const std::string& pattern)
{
	std::vector<std::string> fileList;
	
	long lHandle, res;
	struct _finddata_t tagData;

	std::string fullPath = dir + "/" + pattern;

	lHandle = (long) _findfirst (fullPath.c_str (), &tagData);
	res = 0;
	while (lHandle != -1 && res != -1)
	{
		// Don't add directories
		if ((tagData.attrib & _A_SUBDIR) == 0 &&
			(strcmp (tagData.name, ".") && strcmp (tagData.name, "..")))
		{
			std::string fileName = std::string (tagData.name);
			fileList.push_back (fileName);
		}

		res = _findnext (lHandle, &tagData);
	}

	// Close if we found any files
	if (lHandle != -1)
		_findclose (lHandle);

	return fileList;
}
#elif BS_PLATFORM == BS_PLATFORM_LINUX
std::vector<std::string> getDirectoryListing(const std::string &dir, const std::string &pattern)
{
	std::vector<std::string> fileList;
	
	return fileList;
}
#endif



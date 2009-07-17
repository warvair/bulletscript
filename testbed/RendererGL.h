#ifndef __RENDERERGL_H__
#define __RENDERERGL_H__

#include "shPrerequisites.h"

#if SHMUPPET_PLATFORM == SHMUPPET_PLATFORM_WIN32
#	include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>
#include <SDL.h>

class TGALoader
{
	std::string mFileName;
	int mWidth, mHeight, mBPP;

public:

	TGALoader (const std::string &file) :
		mFileName (file),
		mWidth (0),
		mHeight (0),
		mBPP (0)
	{
	}

	GLuint loadToVRAM (int& width, int& height);
};

class RendererGL
{
	static const int MAX_BULLETS = 2048;
	static const int BULLET_RADIUS = 4;

	float mBulletPos[MAX_BULLETS * 8];
	float mBulletTex[MAX_BULLETS * 8];
	unsigned short mIndices[MAX_BULLETS * 4];

	int mNumBullets;

	GLuint mTextureId;

public:

	RendererGL ();

	bool initialise (int width, int height);

	void startRendering ();

	void finishRendering ();

	void addBullet (float x, float y);

	void renderQuickQuad(float x0, float y0, float x1, float y1, GLuint texture);

	void renderQuickUVQuad(float x0, float y0, float x1, float y1, float u0, float v0, 
		float u1, float v1, GLuint texture);

	void renderQuickTriangle(float x0, float y0, float x1, float y1, float x2, float y2, GLuint texture);

};

#endif
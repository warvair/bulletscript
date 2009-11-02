#ifndef __RENDERERGL_H__
#define __RENDERERGL_H__

#include <vector>
#include "bsPrerequisites.h"

#if BS_PLATFORM == BS_PLATFORM_WIN32
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

struct Area;

class RendererGL
{
	// Bullets
	static const int MAX_BULLETS = 2048;
	static const int BULLET_RADIUS = 4;
	float mBulletPos[MAX_BULLETS * 8];
	float mBulletTex[MAX_BULLETS * 8];
	float mBulletCol[MAX_BULLETS * 16];
	unsigned short mBulletIndices[MAX_BULLETS * 4];
	int mNumBullets;
	GLuint mBulletTexture;

	void renderBulletBatch();

	// Quads
	static const int MAX_QUADS = 128;
	float mQuadPos[MAX_QUADS * 8];
	float mQuadTex[MAX_QUADS * 8];
	float mQuadCol[MAX_QUADS * 16];
	unsigned short mQuadIndices[MAX_QUADS * 4];
	int mNumQuads;
	GLuint mBeamTexture, mBeamTipTexture;	

	void renderQuadBatch();

	// Ellipses
	// An ellipse is a triangle fan, and how many triangles it uses depends on its size.
	// Therefore, we must generate the indices dynamically.  
	static const int MAX_ELLIPSE_POINTS = 512;
	float mEllipsePos[MAX_ELLIPSE_POINTS * 2];
	float mEllipseTex[MAX_ELLIPSE_POINTS * 2];
	float mEllipseCol[MAX_ELLIPSE_POINTS * 4];
	unsigned short mEllipseIndices[MAX_ELLIPSE_POINTS];
	GLuint mEllipseTexture;

	// Arcs
	static const int MAX_ARC_POINTS = 1024;
	float mArcPos[MAX_ARC_POINTS * 2];
	float mArcTex[MAX_ARC_POINTS * 2];
	float mArcCol[MAX_ARC_POINTS * 4];
	unsigned short mArcIndices[MAX_ARC_POINTS];
	GLuint mArcTexture;

	// Units
	GLuint mUnit1Texture;

public:

	RendererGL ();

	bool initialise(int width, int height);

	void startRendering();

	void finishRendering();

	void addBullet(float x, float y, float fade);

	void addQuadArea(Area* a);

	void addEllipseArea(Area* a);

	void addArcArea(Area* a);

	void renderUnit(float x, float y);

};

#endif
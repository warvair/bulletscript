#include <cmath>
#include <iostream>
#include "RendererGL.h"
#include "AreaSystem.h"

// --------------------------------------------------------------------------------
GLuint TGALoader::loadToVRAM(int& width, int& height)
{
	unsigned char TGAHeaderDef[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char header[12];
	unsigned char fields[6];

	FILE *fp = fopen (mFileName.c_str (), "rb");
	if (!fp)
	{
		return false;
	}

	fread (header, 12, 1, fp);
	if (memcmp (header, TGAHeaderDef, 12))
	{
		fclose (fp);
		return 0;
	}

	fread (fields, 6, 1, fp);
	mWidth = fields[1] * 256 + fields[0];
	mHeight = fields[3] * 256 + fields[2];
	mBPP = fields[4];

	width = mWidth;
	height = mHeight;

	int byteSize = mWidth * mHeight * mBPP / 8;
	unsigned char *data = new unsigned char[byteSize];
	fread (data, byteSize, 1, fp);
	fclose (fp);

	GLuint texId;
	glGenTextures (1, &texId);
	glBindTexture (GL_TEXTURE_2D, texId);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (mBPP == 24)
	{
		glTexImage2D (GL_TEXTURE_2D, 
					  0, 
					  GL_RGB8, 
					  mWidth, 
					  mHeight, 
					  0,
					  GL_BGR_EXT, 
					  GL_UNSIGNED_BYTE, 
					  data);
	}
	else if (mBPP == 32)
	{
		glTexImage2D (GL_TEXTURE_2D, 
					  0, 
					  GL_RGBA8, 
					  mWidth, 
					  mHeight, 
					  0,
					  GL_BGRA_EXT, 
					  GL_UNSIGNED_BYTE, 
					  data);
	}
	else
	{
		delete[] data;
		return 0;
	}

	delete[] data;
	return texId;
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
RendererGL::RendererGL () :
	mNumBullets (0),
	mNumQuads(0),
	mBulletTexture (0),
	mBeamTexture(0),
	mBeamTipTexture(0),
	mNumEllipsePoints(0)
{
	// Set up bullets
	for (int i = 0; i < MAX_BULLETS * 8; i += 8)
	{
		mBulletTex[i + 0] = 0;
		mBulletTex[i + 1] = 0;
		mBulletTex[i + 2] = 1;
		mBulletTex[i + 3] = 0;
		mBulletTex[i + 4] = 1;
		mBulletTex[i + 5] = 1;
		mBulletTex[i + 6] = 0;
		mBulletTex[i + 7] = 1;
	}

	for (int i = 0; i < MAX_BULLETS * 16; ++i)
		mBulletCol[i] = 1;

	for (int i = 0; i < MAX_BULLETS * 4; ++ i)
		mBulletIndices[i] = i;

	// Set up beams
	for (int i = 0; i < MAX_QUADS * 8; i += 8)
	{
		mQuadTex[i + 0] = 0;
		mQuadTex[i + 1] = 0;
		mQuadTex[i + 2] = 1;
		mQuadTex[i + 3] = 0;
		mQuadTex[i + 4] = 1;
		mQuadTex[i + 5] = 1;
		mQuadTex[i + 6] = 0;
		mQuadTex[i + 7] = 1;
	}

	for (int i = 0; i < MAX_QUADS * 16; ++i)
		mQuadCol[i] = 1;

	for (int i = 0; i < MAX_QUADS * 4; ++ i)
		mQuadIndices[i] = i;

	// Set up ellipses
	// Set indices
	for (int i = 0; i < MAX_ELLIPSE_POINTS; ++ i)
		mEllipseIndices[i] = i;

	// Set colours
	for (int i = 0; i < MAX_ELLIPSE_POINTS * 4; ++i)
		mEllipseCol[i] = 1.0f;
}
// --------------------------------------------------------------------------------
bool RendererGL::initialise (int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;

	SDL_WM_SetCaption ("BulletScript", "");
	SDL_GL_SetAttribute (SDL_GL_SWAP_CONTROL, 0);  // No vsync
	SDL_SetVideoMode (width, height, 32, SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF/* | SDL_FULLSCREEN*/);
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, width, 0, height, -1, 1);

	glEnable (GL_TEXTURE_2D);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_BLEND);

	// Create bullet sprite
	TGALoader bulletLoader ("bullet1.tga");
	int bwidth, bheight;
	mBulletTexture = bulletLoader.loadToVRAM (bwidth, bheight);
	if (mBulletTexture == 0)
		return false;

	// Create beam sprite
	TGALoader beamLoader ("beam1.tga");
	mBeamTexture = beamLoader.loadToVRAM (bwidth, bheight);
	if (mBeamTexture == 0)
		return false;

	TGALoader beamTipLoader ("beam2.tga");
	mBeamTipTexture = beamTipLoader.loadToVRAM (bwidth, bheight);
	if (mBeamTipTexture == 0)
		return false;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapBuffers();

	return true;
}
// --------------------------------------------------------------------------------
void RendererGL::startRendering ()
{
	mNumBullets = 0;
	mNumQuads = 0;
	mNumEllipsePoints = 0;
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
// --------------------------------------------------------------------------------
void RendererGL::finishRendering ()
{
	renderBulletBatch();
	renderQuadBatch();

	SDL_GL_SwapBuffers ();
}
// --------------------------------------------------------------------------------
void RendererGL::addBullet (float x, float y, float fade)
{
	if (mNumBullets >= MAX_BULLETS)
	{
		renderBulletBatch();
		mNumBullets = 0;
	}

	int bOffset = mNumBullets * 8;
	int cOffset = mNumBullets * 16;

	mBulletPos[bOffset + 0] = x - BULLET_RADIUS;
	mBulletPos[bOffset + 1] = y - BULLET_RADIUS;
	mBulletPos[bOffset + 2] = x + BULLET_RADIUS;
	mBulletPos[bOffset + 3] = y - BULLET_RADIUS;
	mBulletPos[bOffset + 4] = x + BULLET_RADIUS;
	mBulletPos[bOffset + 5] = y + BULLET_RADIUS;
	mBulletPos[bOffset + 6] = x - BULLET_RADIUS;
	mBulletPos[bOffset + 7] = y + BULLET_RADIUS;

	mBulletCol[cOffset + 3] = fade;
	mBulletCol[cOffset + 7] = fade;
	mBulletCol[cOffset + 11] = fade;
	mBulletCol[cOffset + 15] = fade;

	mNumBullets++;
}
// --------------------------------------------------------------------------------
void RendererGL::addQuadArea(Area* a)
{
	if (mNumQuads >= (MAX_QUADS - 1))
	{
		renderQuadBatch();
		mNumQuads = 0;
	}

	float sinAngle = sin((a->angle - 180) * BS::DEG_TO_RAD);
	float cosAngle = cos((a->angle - 180) * BS::DEG_TO_RAD);

	float w2 = a->w / 2;
	float h2 = a->h / 2;

	int bOffset = mNumQuads * 8;
	int cOffset = mNumQuads * 16;
	if (a->type == AT_QuadCentred)
	{
		mQuadPos[bOffset + 0] = a->x - w2 * cosAngle - h2 * sinAngle;
		mQuadPos[bOffset + 1] = a->y + h2 * cosAngle - w2 * sinAngle;
		mQuadPos[bOffset + 2] = a->x + w2 * cosAngle - h2 * sinAngle;
		mQuadPos[bOffset + 3] = a->y + h2 * cosAngle + w2 * sinAngle;
		mQuadPos[bOffset + 4] = a->x + w2 * cosAngle + h2 * sinAngle;
		mQuadPos[bOffset + 5] = a->y - h2 * cosAngle + w2 * sinAngle;
		mQuadPos[bOffset + 6] = a->x - w2 * cosAngle + h2 * sinAngle;
		mQuadPos[bOffset + 7] = a->y - h2 * cosAngle - w2 * sinAngle;
	}
	else if (a->type == AT_QuadBased)
	{
		mQuadPos[bOffset + 0] = a->x - w2 * cosAngle;
		mQuadPos[bOffset + 1] = a->y - w2 * sinAngle;
		mQuadPos[bOffset + 2] = a->x + w2 * cosAngle;
		mQuadPos[bOffset + 3] = a->y + w2 * sinAngle;
		mQuadPos[bOffset + 4] = a->x + w2 * cosAngle + a->h * sinAngle;
		mQuadPos[bOffset + 5] = a->y - a->h * cosAngle + w2 * sinAngle;
		mQuadPos[bOffset + 6] = a->x - w2 * cosAngle + a->h * sinAngle;
		mQuadPos[bOffset + 7] = a->y - a->h * cosAngle - w2 * sinAngle;
	}

	mQuadCol[cOffset + 3] = a->fade;
	mQuadCol[cOffset + 7] = a->fade;
	mQuadCol[cOffset + 11] = a->fade;
	mQuadCol[cOffset + 15] = a->fade;

	mNumQuads += 2;
}
// --------------------------------------------------------------------------------
void RendererGL::addEllipseArea(Area* a)
{
	// Work out how many points to use based on its size
	int size = a->w + a->h;
	int numPoints = size / 4;

	// +1 for the central vertex
	if ((numPoints + 1) >= MAX_ELLIPSE_POINTS)
		return;

	float w2 = a->w / 2;
	float h2 = a->h / 2;

	mEllipsePos[0] = a->x;
	mEllipsePos[1] = a->y;
	mEllipseTex[0] = 0.5f;
	mEllipseTex[1] = 0.5f;
	mEllipseCol[3] = a->fade;

	for (int i = 0, j = 0; i < numPoints * 2; i += 2)
	{
		float angle = (a->angle - 180) + 360 * ((float) j / (numPoints - 1)) * BS::DEG_TO_RAD;

		float sinAngle = sin(angle);
		float cosAngle = cos(angle);
		// Pos
		mEllipsePos[2 + i + 0] = a->x + sinAngle * w2;
		mEllipsePos[2 + i + 1] = a->y + cosAngle * h2;
		// UVs
		mEllipseTex[2 + i + 0] = sinAngle / 2.0f + 0.5;
		mEllipseTex[2 + i + 1] = cosAngle / 2.0f + 0.5;
		// Colour
		mEllipseCol[7 + j * 4] = a->fade;

		j++;
	}

	// Render
	glBindTexture (GL_TEXTURE_2D, 0);

	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glEnableClientState (GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, mEllipsePos);
	glTexCoordPointer(2, GL_FLOAT, 0, mEllipseTex);
	glColorPointer(4, GL_FLOAT, 0, mEllipseCol);

	glDrawElements(GL_TRIANGLE_FAN, numPoints + 1, GL_UNSIGNED_SHORT, mEllipseIndices);

	glDisableClientState (GL_COLOR_ARRAY);
	glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
}
// --------------------------------------------------------------------------------
void RendererGL::renderBulletBatch()
{
	glBindTexture (GL_TEXTURE_2D, mBulletTexture);

	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glEnableClientState (GL_COLOR_ARRAY);

	glVertexPointer (2, GL_FLOAT, 0, mBulletPos);
	glTexCoordPointer (2, GL_FLOAT, 0, mBulletTex);
	glColorPointer (4, GL_FLOAT, 0, mBulletCol);

	glDrawElements (GL_QUADS, 4 * mNumBullets, GL_UNSIGNED_SHORT, mBulletIndices);

	glDisableClientState (GL_COLOR_ARRAY);
	glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
}
// --------------------------------------------------------------------------------
void RendererGL::renderQuadBatch()
{
	glBindTexture (GL_TEXTURE_2D, mBeamTexture);

	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glEnableClientState (GL_COLOR_ARRAY);

	glVertexPointer (2, GL_FLOAT, 0, mQuadPos);
	glTexCoordPointer (2, GL_FLOAT, 0, mQuadTex);
	glColorPointer (4, GL_FLOAT, 0, mQuadCol);

	glDrawElements (GL_QUADS, 4 * mNumQuads, GL_UNSIGNED_SHORT, mQuadIndices);

	glDisableClientState (GL_COLOR_ARRAY);
	glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
}
// --------------------------------------------------------------------------------
void RendererGL::renderEllipseBatch()
{
	glBindTexture (GL_TEXTURE_2D, 0);

	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glEnableClientState (GL_COLOR_ARRAY);

	glVertexPointer (2, GL_FLOAT, 0, mQuadPos);
	glTexCoordPointer (2, GL_FLOAT, 0, mQuadTex);
	glColorPointer (4, GL_FLOAT, 0, mQuadCol);

	glDrawElements (GL_TRIANGLE_FAN, 4 * mNumQuads, GL_UNSIGNED_SHORT, mQuadIndices);

	glDisableClientState (GL_COLOR_ARRAY);
	glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
}
// --------------------------------------------------------------------------------
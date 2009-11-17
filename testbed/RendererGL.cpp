#include <cmath>
#include <iostream>
#include "RendererGL.h"
#include "AreaSystem.h"

#ifndef MINIMAL_APP

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
	mArcTexture(0),
	mUnit1Texture(0)
{
	int i;

	// Set up bullets
	for (i = 0; i < MAX_BULLETS * 8; i += 8)
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

	for (i = 0; i < MAX_BULLETS * 16; ++i)
		mBulletCol[i] = 1;

	for (i = 0; i < MAX_BULLETS * 4; ++ i)
		mBulletIndices[i] = i;

	// Set up beams
	for (i = 0; i < MAX_QUADS * 8; i += 8)
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

	for (i = 0; i < MAX_QUADS * 16; ++i)
		mQuadCol[i] = 1;

	for (i = 0; i < MAX_QUADS * 4; ++ i)
		mQuadIndices[i] = i;

	// Set up ellipses
	for (i = 0; i < MAX_ELLIPSE_POINTS; ++ i)
		mEllipseIndices[i] = i;

	for (i = 0; i < MAX_ELLIPSE_POINTS * 4; ++i)
		mEllipseCol[i] = 1.0f;

	// Set up arcs
	for (i = 0; i < MAX_ARC_POINTS * 4; ++i)
		mArcCol[i] = 1.0f;

	mArcIndices[0] = 0;
	mArcIndices[1] = 2;
	mArcIndices[2] = 3;
	mArcIndices[3] = 1;
	for (i = 4; i < MAX_ARC_POINTS; i += 4)
	{
		mArcIndices[i + 0] = mArcIndices[i - 4] + 2;
		mArcIndices[i + 1] = mArcIndices[i - 3] + 2;
		mArcIndices[i + 2] = mArcIndices[i - 2] + 2;
		mArcIndices[i + 3] = mArcIndices[i - 1] + 2;
	}
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

	// Create beam sprite
	TGALoader ballLoader ("ball1.tga");
	mEllipseTexture = ballLoader.loadToVRAM (bwidth, bheight);
	if (mEllipseTexture == 0)
		return false;

	// Create arc sprite
	TGALoader arcLoader ("arc.tga");
	mArcTexture = arcLoader.loadToVRAM (bwidth, bheight);
	if (mArcTexture == 0)
		return false;

	// Create unit sprites
	TGALoader unitLoader ("ship1.tga");
	mUnit1Texture = unitLoader.loadToVRAM (bwidth, bheight);
	if (mUnit1Texture == 0)
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
void RendererGL::addBullet (const Bullet& b)
{
	if (mNumBullets >= MAX_BULLETS)
	{
		renderBulletBatch();
		mNumBullets = 0;
	}

	float x = b.x;
	float y = b.y;
	float rd = b.red;
	float gr = b.green;
	float bl = b.blue;
	float alpha = b.alpha;

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

	mBulletCol[cOffset + 0] = rd;
	mBulletCol[cOffset + 1] = gr;
	mBulletCol[cOffset + 2] = bl;
	mBulletCol[cOffset + 3] = alpha;
	mBulletCol[cOffset + 4] = rd;
	mBulletCol[cOffset + 5] = gr;
	mBulletCol[cOffset + 6] = bl;
	mBulletCol[cOffset + 7] = alpha;
	mBulletCol[cOffset + 8] = rd;
	mBulletCol[cOffset + 9] = gr;
	mBulletCol[cOffset + 10] = bl;
	mBulletCol[cOffset + 11] = alpha;
	mBulletCol[cOffset + 12] = rd;
	mBulletCol[cOffset + 13] = gr;
	mBulletCol[cOffset + 14] = bl;
	mBulletCol[cOffset + 15] = alpha;

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

	float sinAngle = sin((a->angle - 180) * bs::DEG_TO_RAD);
	float cosAngle = cos((a->angle - 180) * bs::DEG_TO_RAD);

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

	mQuadCol[cOffset + 3] = a->alpha;
	mQuadCol[cOffset + 7] = a->alpha;
	mQuadCol[cOffset + 11] = a->alpha;
	mQuadCol[cOffset + 15] = a->alpha;

	mNumQuads += 2;
}
// --------------------------------------------------------------------------------
void RendererGL::addEllipseArea(Area* a)
{
	// Work out how many points to use based on its size
	int size = a->w + a->h;
	int numPoints = size / 8;

	// +1 for the central vertex
	if ((numPoints + 1) >= MAX_ELLIPSE_POINTS)
		return;

	float w2 = a->w / 2;
	float h2 = a->h / 2;

	mEllipsePos[0] = a->x;
	mEllipsePos[1] = a->y;
	mEllipseTex[0] = 0.5f;
	mEllipseTex[1] = 0.5f;
	mEllipseCol[3] = a->alpha;

	float arcLength = a->end - a->start;
	float delta = arcLength / (numPoints - 1);

	// start angle = a->angle + a->start
	// each loop, add delta

	float angle = a->angle + a->start;
	for (int i = 0, j = 0; i < numPoints * 2; i += 2)
	{
		float sinAngle = sin(angle * bs::DEG_TO_RAD);
		float cosAngle = cos(angle * bs::DEG_TO_RAD);

		// Pos
		mEllipsePos[2 + i + 0] = a->x + sinAngle * w2;
		mEllipsePos[2 + i + 1] = a->y + cosAngle * h2;
		// UVs
		mEllipseTex[2 + i + 0] = sinAngle / 2.0f + 0.5;
		mEllipseTex[2 + i + 1] = cosAngle / 2.0f + 0.5;
		// Colour
		mEllipseCol[7 + j * 4] = a->alpha;

		angle += delta;
		j++;
	}

	// Render
	glBindTexture (GL_TEXTURE_2D, mEllipseTexture);

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
void RendererGL::addArcArea(Area* a)
{
	// Work out how many points to use based on its size
	int size = a->w + a->h;
	int numPoints = size / 8;

	// *2 for inner vertices
	if ((numPoints * 2) >= MAX_ELLIPSE_POINTS)
		return;

	float w2o = a->w / 2;
	float h2o = a->h / 2;

	float w2i = w2o - a->innerw;
	float h2i = h2o - a->innerh;

	float arcLength = a->end - a->start;
	float delta = arcLength / numPoints;

	float angle = a->angle + a->start;
	for (int i = 0; i <= numPoints; ++i)
	{
		float sinAngle = sin(angle * bs::DEG_TO_RAD);
		float cosAngle = cos(angle * bs::DEG_TO_RAD);

		// Outer Pos
		mArcPos[i * 4 + 0] = a->x + sinAngle * w2o;
		mArcPos[i * 4 + 1] = a->y + cosAngle * h2o;
		// UVs
		mArcTex[i * 4 + 0] = (float) i / numPoints;
		mArcTex[i * 4 + 1] = 1.0f;
		// Colour
		mArcCol[i * 8 + 3] = a->alpha;

		// Inner Pos
		mArcPos[i * 4 + 2] = a->x + sinAngle * w2i;
		mArcPos[i * 4 + 3] = a->y + cosAngle * h2i;
		// UVs
		mArcTex[i * 4 + 2] = (float) i / numPoints;
		mArcTex[i * 4 + 3] = 0.0f;
		// Colour
		mArcCol[i * 8 + 7] = a->alpha;

		angle += delta;
	}

	glBindTexture (GL_TEXTURE_2D, mArcTexture);

	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glEnableClientState (GL_COLOR_ARRAY);

	glVertexPointer (2, GL_FLOAT, 0, mArcPos);
	glTexCoordPointer (2, GL_FLOAT, 0, mArcTex);
	glColorPointer (4, GL_FLOAT, 0, mArcCol);

	glDrawElements (GL_QUADS, 4 * numPoints, GL_UNSIGNED_SHORT, mArcIndices);

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
void RendererGL::renderUnit(float x, float y)
{
	glBindTexture(GL_TEXTURE_2D, mUnit1Texture);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
			glTexCoord2i(0, 0);
			glVertex2f(x - 32, y - 32);
			glTexCoord2i(1, 0);
			glVertex2f(x + 32, y - 32);
			glTexCoord2i(1, 1);
			glVertex2f(x + 32, y + 32);
			glTexCoord2i(0, 1);
			glVertex2f(x - 32, y + 32);
	}
	glEnd();
}
// --------------------------------------------------------------------------------

#endif
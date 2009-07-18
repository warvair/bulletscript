#include <iostream>
#include "RendererGL.h"

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
	mTextureId (0)
{
	for (int i = 0; i < MAX_BULLETS * 8; i += 8)
	{
		mBulletTex[i + 0] = 0.0f;
		mBulletTex[i + 1] = 0.0f;
		mBulletTex[i + 2] = 1.0f;
		mBulletTex[i + 3] = 0.0f;
		mBulletTex[i + 4] = 1.0f;
		mBulletTex[i + 5] = 1.0f;
		mBulletTex[i + 6] = 0.0f;
		mBulletTex[i + 7] = 1.0f;
	}

	for (int i = 0; i < MAX_BULLETS * 4; ++ i)
		mIndices[i] = i;
}
// --------------------------------------------------------------------------------
bool RendererGL::initialise (int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;

	SDL_WM_SetCaption ("Shmuppet BulletScript", "");
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
	TGALoader sprLoader ("bullet1.tga");
	int bwidth, bheight;
	mTextureId = sprLoader.loadToVRAM (bwidth, bheight);
	if (mTextureId == 0)
		return false;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapBuffers();

	return true;
}
// --------------------------------------------------------------------------------
void RendererGL::startRendering ()
{
	mNumBullets = 0;
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
// --------------------------------------------------------------------------------
void RendererGL::finishRendering ()
{
	// Draw bullets
	glBindTexture (GL_TEXTURE_2D, mTextureId);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);

	glVertexPointer (2, GL_FLOAT, 0, mBulletPos);
	glTexCoordPointer (2, GL_FLOAT, 0, mBulletTex);

	glDrawElements (GL_QUADS, 4 * mNumBullets, GL_UNSIGNED_SHORT, mIndices);

	glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);

	SDL_GL_SwapBuffers ();
}
// --------------------------------------------------------------------------------
void RendererGL::addBullet (float x, float y)
{
	if (mNumBullets >= MAX_BULLETS)
		return;

	int bOffset = mNumBullets * 8;

	mBulletPos[bOffset + 0] = x - BULLET_RADIUS;
	mBulletPos[bOffset + 1] = y - BULLET_RADIUS;
	mBulletPos[bOffset + 2] = x + BULLET_RADIUS;
	mBulletPos[bOffset + 3] = y - BULLET_RADIUS;
	mBulletPos[bOffset + 4] = x + BULLET_RADIUS;
	mBulletPos[bOffset + 5] = y + BULLET_RADIUS;
	mBulletPos[bOffset + 6] = x - BULLET_RADIUS;
	mBulletPos[bOffset + 7] = y + BULLET_RADIUS;
	mNumBullets ++;
}
// --------------------------------------------------------------------------------
void RendererGL::renderQuickQuad(float x0, float y0, float x1, float y1, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2i(0, 0);
		glVertex2f(x0, y0);
		glTexCoord2i(1, 0);
		glVertex2f(x1, y0);
		glTexCoord2i(1, 1);
		glVertex2f(x1, y1);
		glTexCoord2i(0, 1);
		glVertex2f(x0, y1);
	}
	glEnd();
}
// --------------------------------------------------------------------------------
void RendererGL::renderQuickQuad(float x0, float y0, float x1, float y1, 
								 float x2, float y2, float x3, float y3, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2i(0, 0);
		glVertex2f(x0, y0);
		glTexCoord2i(1, 0);
		glVertex2f(x1, y1);
		glTexCoord2i(1, 1);
		glVertex2f(x2, y2);
		glTexCoord2i(0, 1);
		glVertex2f(x3, y3);
	}
	glEnd();
}
// --------------------------------------------------------------------------------
void RendererGL::renderQuickUVQuad(float x0, float y0, float x1, float y1, 
								   float u0, float v0, float u1, float v1, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(u0, v0);
		glVertex2f(x0, y0);
		glTexCoord2f(u1, v0);
		glVertex2f(x1, y0);
		glTexCoord2f(u1, v1);
		glVertex2f(x1, y1);
		glTexCoord2f(u0, v1);
		glVertex2f(x0, y1);
	}
	glEnd();
}
// --------------------------------------------------------------------------------
void RendererGL::renderQuickTriangle(float x0, float y0, float x1, float y1, float x2, 
									 float y2, float alpha, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1.0f, 1.0f, 1.0f, alpha);
	glBegin(GL_TRIANGLES);
	{
		glTexCoord2i(0, 0);
		glVertex2f(x0, y0);
		glTexCoord2i(1, 0);
		glVertex2f(x1, y1);
		glTexCoord2i(1, 1);
		glVertex2f(x2, y2);
	}
	glEnd();
}
// --------------------------------------------------------------------------------
void RendererGL::renderQuickLines(const std::vector<float>& points, int numPoints, float alpha)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4f(1.0f, 1.0f, 1.0f, alpha);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < numPoints * 2; i += 2)
		glVertex2f(points[i + 0], points[i + 1]);
	glEnd();	
}
// --------------------------------------------------------------------------------
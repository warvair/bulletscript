#include <cmath>
#include <iostream>
#include "RendererGL.h"
#include "AreaSystem.h"

#define GLYPH_START		32
#define NUM_GLYPHS		95

struct DebugGlyph
{
	int x, y, w, h;
	float u0, v0, u1, v1;
};

// Goes from codes 32 to 125
static DebugGlyph glyphs[NUM_GLYPHS] = {
	{1,		1,		6,		16}, // Space
	{8,		1,		6,		16}, // !
	{15,	1,		8,		16}, // "
	{24,	1,		10,		16}, // #
	{35,	1,		10,		16}, // $
	{46,	1,		13,		16}, // %
	{60,	1,		11,		16}, // &
	{72,	1,		6,		16}, // '
	{79,	1,		6,		16}, // (
	{86,	1,		6,		16}, // )
	{93,	1,		8,		16}, // *
	{102,	1,		10,		16}, // +
	{113,	1,		6,		16}, // ,
	{120,	1,		6,		16}, // -
	{127,	1,		6,		16}, // .
	{134,	1,		6,		16}, // /
	{141,	1,		10,		16}, // 0
	{152,	1,		10,		16}, // 1
	{163,	1,		10,		16}, // 2
	{174,	1,		10,		16}, // 3
	{185,	1,		10,		16}, // 4
	{196,	1,		10,		16}, // 5
	{207,	1,		10,		16}, // 6
	{218,	1,		10,		16}, // 7
	{229,	1,		10,		16}, // 8
	{240,	1,		10,		16}, // 9
	{1,		18,		6,		16}, // :
	{8,		18,		6,		16}, // ;
	{15,	18,		10,		16}, // <
	{26,	18,		10,		16}, // =
	{37,	18,		10,		16}, // >
	{48,	18,		10,		16}, // ?
	{59,	18,		16,		16}, // @
	{76,	18,		10,		16}, // A
	{87,	18,		12,		16}, // B
	{100,	18,		11,		16}, // C
	{112,	18,		12,		16}, // D
	{125,	18,		11,		16}, // E
	{137,	18,		10,		16}, // F
	{148,	18,		12,		16}, // G
	{161,	18,		12,		16}, // H
	{174,	18,		6,		16}, // I
	{181,	18,		10,		16}, // J
	{191,	18,		11,		16}, // K
	{203,	18,		10,		16}, // L
	{214,	18,		14,		16}, // M
	{229,	18,		12,		16}, // N
	{242,	18,		12,		16}, // O
	{1,		35,		11,		16}, // P
	{13,	35,		12,		16}, // Q
	{26,	35,		12,		16}, // R
	{39,	35,		11,		16}, // S
	{51,	35,		10,		16}, // T
	{62,	35,		12,		16}, // U
	{75,	35,		10,		16}, // V
	{86,	35,		16,		16}, // W
	{103,	35,		11,		16}, // X
	{115,	35,		12,		16}, // Y
	{128,	35,		11,		16}, // Z
	{140,	35,		6,		16}, // [
	{147,	35,		6,		16}, // '\'
	{154,	35,		6,		16}, // ]
	{161,	35,		7,		16}, // ^
	{169,	35,		10,		16}, // _
	{180,	35,		7,		16}, // `
	{188,	35,		10,		16}, // a
	{199,	35,		10,		16}, // b
	{210,	35,		9,		16}, // c
	{220,	35,		10,		16}, // d
	{231,	35,		10,		16}, // e
	{242,	35,		6,		16}, // f
	{1,		52,		10,		16}, // g
	{12,	52,		10,		16}, // h
	{23,	52,		6,		16}, // i
	{30,	52,		6,		16}, // j
	{37,	52,		9,		16}, // k
	{47,	52,		6,		16}, // l
	{54,	52,		14,		16}, // m
	{69,	52,		10,		16}, // n
	{80,	52,		10,		16}, // o
	{91,	52,		10,		16}, // p
	{102,	52,		10,		16}, // q
	{113,	52,		7,		16}, // r
	{121,	52,		10,		16}, // s
	{132,	52,		6,		16}, // t
	{139,	52,		10,		16}, // u
	{150,	52,		10,		16}, // v
	{161,	52,		12,		16}, // w
	{174,	52,		10,		16}, // x
	{185,	52,		10,		16}, // y
	{196,	52,		10,		16}, // z
	{207,	52,		7,		16}, // {
	{215,	52,		6,		16}, // |
	{222,	52,		7,		16}, // }
	{230,	52,		7,		16}, // ~
};

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
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
	mFontTexture(0),
	mNumBullets (0),
	mNumQuads(0),
	mBulletTexture(0),
	mBeamTexture(0),
	mBeamTipTexture(0),
	mArcTexture(0),
	mFragmentShader(0),
	mFragmentProgram(0),
	mVertexShader(0),
	mVertexProgram(0)
{
	int i;

	// Set up bullets
	mBulletInfo[0].width = 4;
	mBulletInfo[0].height = 4;
	mBulletInfo[0].vHeight = 0.5f;
	mBulletInfo[1].width = 6;
	mBulletInfo[1].height = 12;
	mBulletInfo[1].vHeight = 1.0f;

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
bool RendererGL::initialise (int width, int height, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;

	SDL_WM_SetCaption ("BulletScript", "");
	SDL_GL_SetAttribute (SDL_GL_SWAP_CONTROL, 0);  // No vsync

	if (fullScreen)
		SDL_SetVideoMode (width, height, 32, SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	else
		SDL_SetVideoMode (width, height, 32, SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF/* | SDL_FULLSCREEN*/);

	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, width, 0, height, -1, 1);

	glEnable (GL_TEXTURE_2D);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_BLEND);

	// Create font
	TGALoader fontLoader("font.tga");
	int fWidth, fHeight;
	mFontTexture = fontLoader.loadToVRAM(fWidth, fHeight);
	if (mFontTexture == 0)
		return false;

	for (int i = 0; i < NUM_GLYPHS; ++ i)
	{
		glyphs[i].u0 = glyphs[i].x / 256.0f;
		glyphs[i].v0 = glyphs[i].y / 128.0f;
		glyphs[i].u1 = (glyphs[i].x + glyphs[i].w) / 256.0f;
		glyphs[i].v1 = (glyphs[i].y + glyphs[i].h) / 128.0f;
	}

	// Create bullet sprites
	TGALoader bulletLoader("bullets.tga");
	int bwidth, bheight;
	mBulletTexture = bulletLoader.loadToVRAM (bwidth, bheight);
	if (mBulletTexture == 0)
		return false;

	// Create beam sprite
	TGALoader beamLoader("beam1.tga");
	mBeamTexture = beamLoader.loadToVRAM (bwidth, bheight);
	if (mBeamTexture == 0)
		return false;

	TGALoader beamTipLoader("beam2.tga");
	mBeamTipTexture = beamTipLoader.loadToVRAM (bwidth, bheight);
	if (mBeamTipTexture == 0)
		return false;

	// Create beam sprite
	TGALoader ballLoader("ball1.tga");
	mEllipseTexture = ballLoader.loadToVRAM (bwidth, bheight);
	if (mEllipseTexture == 0)
		return false;

	// Create arc sprite
	TGALoader arcLoader("arc.tga");
	mArcTexture = arcLoader.loadToVRAM (bwidth, bheight);
	if (mArcTexture == 0)
		return false;

	// Init other stuff
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapBuffers();

	SDL_ShowCursor(SDL_DISABLE);

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
void RendererGL::print(int x, int y, const char* str)
{
	const char *textPtr = str;
	glBindTexture(GL_TEXTURE_2D, mFontTexture);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	while (*textPtr)
	{
		DebugGlyph& glyph = glyphs[*textPtr - GLYPH_START];

		glTexCoord2f(glyph.u0, 1.0f - glyph.v0);
		glVertex2i(x, y + glyph.h);
		glTexCoord2f(glyph.u1, 1.0f - glyph.v0);
		glVertex2i(x + glyph.w, y + glyph.h);
		glTexCoord2f(glyph.u1, 1.0f - glyph.v1);
		glVertex2i(x + glyph.w, y);
		glTexCoord2f(glyph.u0, 1.0f - glyph.v1);
		glVertex2i(x, y);

		x += glyph.w;
		x --;
		textPtr ++;
	}
	glEnd();
}
// --------------------------------------------------------------------------------
void RendererGL::addBullet(const Bullet& b)
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

	int texId = (int) (b._texture * 2);
	const BulletInfo& bi = mBulletInfo[texId];

	mBulletPos[bOffset + 0] = x - bi.width;
	mBulletPos[bOffset + 1] = y - bi.height;
	mBulletPos[bOffset + 2] = x + bi.width;
	mBulletPos[bOffset + 3] = y - bi.height;
	mBulletPos[bOffset + 4] = x + bi.width;
	mBulletPos[bOffset + 5] = y + bi.height;
	mBulletPos[bOffset + 6] = x - bi.width;
	mBulletPos[bOffset + 7] = y + bi.height;

	mBulletTex[bOffset + 0] = b._texture;
	mBulletTex[bOffset + 1] = 1;
	mBulletTex[bOffset + 2] = b._texture + 0.5f;
	mBulletTex[bOffset + 3] = 1;
	mBulletTex[bOffset + 4] = b._texture + 0.5f;
	mBulletTex[bOffset + 5] = 1 - bi.vHeight;
	mBulletTex[bOffset + 6] = b._texture;
	mBulletTex[bOffset + 7] = 1 - bi.vHeight;

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

	float sinAngle = (float) sin((a->angle - 180) * bs::DEG_TO_RAD);
	float cosAngle = (float) cos((a->angle - 180) * bs::DEG_TO_RAD);

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
	int size = (int) (a->w + a->h);
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
		float sinAngle = (float) sin(angle * bs::DEG_TO_RAD);
		float cosAngle = (float) cos(angle * bs::DEG_TO_RAD);

		// Pos
		mEllipsePos[2 + i + 0] = a->x + sinAngle * w2;
		mEllipsePos[2 + i + 1] = a->y + cosAngle * h2;
		// UVs
		mEllipseTex[2 + i + 0] = sinAngle / 2.0f + 0.5f;
		mEllipseTex[2 + i + 1] = cosAngle / 2.0f + 0.5f;
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
	int size = (int) (a->w + a->h);
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
		float sinAngle = (float) sin(angle * bs::DEG_TO_RAD);
		float cosAngle = (float) cos(angle * bs::DEG_TO_RAD);

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

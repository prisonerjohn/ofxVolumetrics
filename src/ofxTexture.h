#pragma once

#include "ofMain.h"

class ofxTextureData
	: public ofTextureData
{
public:
	ofxTextureData() 
	{
		textureID = 0;

		glInternalFormat = GL_RGB8;
		glType = GL_RGB;
		pixelType = GL_UNSIGNED_BYTE;

		tex_t = 0;
		tex_u = 0;
		tex_v = 0;

		tex_w = 0;
		tex_h = 0;
		tex_d = 0;
		
		width = 0;
		height = 0;
		depth = 0;

		bFlipTexture = false;
		compressionType = OF_COMPRESS_NONE;
		bAllocated = false;
	}

	float tex_v;
	float tex_d;
	float depth;
	
	int glType;
	int pixelType;
};

class ofxTexture
{
public:
	ofxTexture();
	virtual ~ofxTexture();

	virtual void allocate(int w, int h, int d, int internalGlDataType) = 0;
	void clear();

	void loadData(const unsigned char * data, int w, int h, int d, int xOffset, int yOffset, int zOffset, int glFormat);
	void loadData(const float* data, int w, int h, int d, int xOffset, int yOffset, int zOffset, int glFormat);
	void loadData(const unsigned short* data, int w, int h, int d, int xOffset, int yOffset, int zOffset, int glFormat);
	void loadData(const ofPixels & pix, int d, int xOffset, int yOffset, int zOffset);
	void loadData(const ofShortPixels & pix, int d, int xOffset, int yOffset, int zOffset);
	void loadData(const ofFloatPixels & pix, int d, int xOffset, int yOffset, int zOffset);

	void bind();
	void unbind();

	void generateMipmaps();
	void setMinMagFilters(GLenum min, GLenum mag);

	ofxTextureData texData;

protected:
	virtual void loadData(const void * data, int w, int h, int d, int xOffset, int yOffset, int zOffset, int glFormat) = 0;

	void ofRetain();
	void ofRelease();
};

#include "ofxTexture.h"
#include "ofTexture.cpp"

//----------------------------------------------------------
ofxTexture::ofxTexture()
{}

//----------------------------------------------------------
ofxTexture::~ofxTexture()
{
	clear();
}

//----------------------------------------------------------
void ofxTexture::ofRetain()
{
	retain(texData.textureID);
}

//----------------------------------------------------------
void ofxTexture::ofRelease()
{
	release(texData.textureID);
}

//----------------------------------------------------------
void ofxTexture::clear()
{
	ofRelease();
	texData.textureID = 0;
	texData.bAllocated = false;
}

//----------------------------------------------------------
void ofxTexture::loadData(const unsigned char * data, int w, int h, int d, int xOffset, int yOffset, int zOffset, int glFormat)
{
	loadData((const void*)data, w, h, d, xOffset, yOffset, zOffset, glFormat);
}

//----------------------------------------------------------
void ofxTexture::loadData(const float* data, int w, int h, int d, int xOffset, int yOffset, int zOffset, int glFormat)
{
	loadData((const void*)data, w, h, d, xOffset, yOffset, zOffset, glFormat);
}

//----------------------------------------------------------
void ofxTexture::loadData(const unsigned short* data, int w, int h, int d, int xOffset, int yOffset, int zOffset, int glFormat)
{
	loadData((const void*)data, w, h, d, xOffset, yOffset, zOffset, glFormat);
}

//----------------------------------------------------------
void ofxTexture::loadData(const ofPixels & pix, int d, int xOffset, int yOffset, int zOffset)
{
	loadData(pix.getData(), pix.getWidth(), pix.getHeight(), d, xOffset, yOffset, zOffset, ofGetGlFormat(pix));
}

//----------------------------------------------------------
void ofxTexture::loadData(const ofShortPixels & pix, int d, int xOffset, int yOffset, int zOffset)
{
	loadData(pix.getData(), pix.getWidth(), pix.getHeight(), d, xOffset, yOffset, zOffset, ofGetGlFormat(pix));
}

//----------------------------------------------------------
void ofxTexture::loadData(const ofFloatPixels & pix, int d, int xOffset, int yOffset, int zOffset)
{
	loadData(pix.getData(), pix.getWidth(), pix.getHeight(), d, xOffset, yOffset, zOffset, ofGetGlFormat(pix));
}

//----------------------------------------------------------
void ofxTexture::bind()
{
	glActiveTexture((GLuint)texData.textureID);
	glBindTexture(texData.textureTarget, (GLuint)texData.textureID);
}

//----------------------------------------------------------
void ofxTexture::unbind()
{
	glActiveTexture(0);
}

//----------------------------------------------------------
void ofxTexture::generateMipmaps(){
	bind();
	glGenerateMipmap(texData.textureTarget);
	unbind();
}

//----------------------------------------------------------
void ofxTexture::setMinMagFilters(GLenum min, GLenum mag){
	texData.magFilter = mag;
	texData.minFilter = min;
	bind();
	glTexParameterf(texData.textureTarget, GL_TEXTURE_MAG_FILTER, texData.magFilter);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_MIN_FILTER, texData.minFilter);
	unbind();
}

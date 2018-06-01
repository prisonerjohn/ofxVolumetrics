#pragma once

/* ofxVolumetrics - render volumetric data on the GPU

 Written by Timothy Scaffidi (http://timothyscaffidi.com)
 Volumetric rendering algorithm adapted from Peter Trier (http://www.daimi.au.dk/~trier/?page_id=98)

*/
#include "ofMain.h"
#include "ofxTexture.h"

class ofxVolumetrics
{
public:
	ofxVolumetrics();
	virtual ~ofxVolumetrics();

	virtual void setup(int w, int h, int d, const ofDefaultVec3 & voxelSize, bool usePowerOfTwoTexSize = false) = 0;
	void setup(ofxTexture * texture, const ofDefaultVec3 & voxelSize);
	void setup(ofxTexture * texture, const ofDefaultVec3 & voxelSize, ofShader shader);

	void clear();

	virtual void updateTexture(ofxTexture * texture, const ofDefaultVec3 & voxelSize);
	ofxTexture * getTexture() const;

	virtual void updateVolumeData(const unsigned char * data, int w, int h, int d, int xOffset, int yOffset, int zOffset);
	virtual void updateVolumeData(const float * data, int w, int h, int d, int xOffset, int yOffset, int zOffset);

	void drawVolume(float x, float y, float z, float size, int zTexOffset) const;
	void drawVolume(float x, float y, float z, float w, float h, float d, int zTexOffset) const;

	bool isInitialized() const;

	int getVolumeWidth() const;
	int getVolumeHeight() const;
	int getVolumeDepth() const;

	const ofFbo & getFboReference() const;
	int getRenderWidth() const;
	int getRenderHeight() const;

	float getXyQuality() const;
	float getZQuality() const;
	float getThreshold() const;
	float getDensity() const;

	void setXyQuality(float q);
	void setZQuality(float q);
	void setThreshold(float t);
	void setDensity(float d);

	void setRenderSettings(float xyQuality, float zQuality, float dens, float thresh);
	void setVolumeTextureFilterMode(GLint filterMode);

protected:
	void setupVbo();
	virtual void setupShader() = 0;
	virtual void updateShaderUniforms(int zOffset) const;

	void drawRGBCube() const;

	ofFbo fboRender;
	ofShader volumeShader;

	ofxTexture * volumeTexture;
	bool bOwnsTexture;

	ofVbo volVbo;

	ofDefaultVec3 voxelRatio;
	bool bInitialized;
	int volWidth, volHeight, volDepth;
	int volTexWidth, volTexHeight, volTexDepth;
	bool bIsPowerOfTwo;
	ofDefaultVec3 quality;
	float threshold;
	float density;
	int renderWidth, renderHeight;
};

#pragma once

#include "ofMain.h"

#include "ofxVolumetrics.h"
#include "ofxTexture3d.h"

class ofxVolumetrics3D
	: public ofxVolumetrics
{
public:
	ofxVolumetrics3D();

	void setup(int w, int h, int d, ofVec3f voxelSize, bool usePowerOfTwoTexSize = false) override;
	using ofxVolumetrics::setup;

protected:
	void setupShader() override;
	void updateShaderUniforms(int zOffset) override;
};

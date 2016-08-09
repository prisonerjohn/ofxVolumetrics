#pragma once

#include "ofMain.h"

#include "ofxVolumetrics.h"
#include "ofxTextureArray.h"

class ofxVolumetricsArray
	: public ofxVolumetrics
{
public:
	ofxVolumetricsArray();

	void setup(int w, int h, int d, ofVec3f voxelSize, bool usePowerOfTwoTexSize=false) override;
	using ofxVolumetrics::setup;
protected:
	void setupShader() override;
};

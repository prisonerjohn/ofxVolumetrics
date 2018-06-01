#pragma once

#include "ofxVolumetrics.h"

class ofxVolumetrics3D
	: public ofxVolumetrics
{
public:
	ofxVolumetrics3D();

	void setup(int w, int h, int d, const ofDefaultVec3 & voxelSize, bool usePowerOfTwoTexSize = false) override;
	using ofxVolumetrics::setup;

protected:
	void setupShader() override;
};

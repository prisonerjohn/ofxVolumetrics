#pragma once

#include "ofMain.h"

#include "ofxVolumetrics.h"
#include "ofxTextureArray.h"

class ofxVolumetricsArray
	: public ofxVolumetrics
{
public:
	ofxVolumetricsArray();

	void setup(int w, int h, int d, const ofDefaultVec3 & voxelSize, bool usePowerOfTwoTexSize=false) override;
	void setup(ofxTextureArray * texture, const ofDefaultVec3 & voxelSize);

protected:
	void setupShader() override;
	void updateShaderUniforms(int zOffset) override;
};

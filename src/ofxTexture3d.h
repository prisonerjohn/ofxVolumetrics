#pragma once

#include "ofxTexture.h"

class ofxTexture3d
	: public ofxTexture
{
    public:
        ofxTexture3d();

		void allocate(int w, int h, int d, int internalGlDataType) override;

		using ofxTexture::loadData;

protected:
	void loadData(void * data, int w, int h, int d, int xOffset, int yOffset, int zOffset, int glFormat) override;
};

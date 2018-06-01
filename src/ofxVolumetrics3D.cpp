#include "ofxVolumetrics3D.h"

#define STRINGIFY(A) #A

//--------------------------------------------------------------
ofxVolumetrics3D::ofxVolumetrics3D()
	: ofxVolumetrics()
{}

//--------------------------------------------------------------
void ofxVolumetrics3D::setupShader()
{
	std::string vertexShaderFixed =
#include "shaders/gl/vert.glsl"
	std::string fragmentShaderFixed =
#include "shaders/gl/frag.glsl"

	std::string vertexShaderProgrammable =
#include "shaders/gl3/vert.glsl"
	std::string fragmentShaderProgrammable =
#include "shaders/gl3/frag.glsl"

	std::string vertexShader = ofIsGLProgrammableRenderer() ? vertexShaderProgrammable : vertexShaderFixed;
	std::string fragmentShader = ofIsGLProgrammableRenderer() ? fragmentShaderProgrammable : fragmentShaderFixed;

	volumeShader.unload();
	volumeShader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
	volumeShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
	volumeShader.linkProgram();
}

//--------------------------------------------------------------
void ofxVolumetrics3D::setup(int w, int h, int d, const ofDefaultVec3 & voxelSize, bool usePowerOfTwoTexSize)
{
	clear();

	volumeTexture = new ofxTexture3d();
	volumeTexture->allocate(w, h, d, GL_RGBA);
	bOwnsTexture = true;

	volTexWidth = volWidth = renderWidth = w;
	volTexHeight = volHeight = renderHeight = h;
	volTexDepth = volDepth = d;

	if (bIsPowerOfTwo)
	{
		volTexWidth = ofNextPow2(volTexWidth);
		volTexHeight = ofNextPow2(volTexHeight);
		volTexDepth = ofNextPow2(volTexDepth);

		ofLogVerbose(__FUNCTION__) << "Using power of two texture size. Requested: " << w << "x" << h << "x" << d << ". Actual: " << volTexWidth << "x" << volTexHeight << "x" << volTexDepth;

		// If using cropped power of two, blank out the extra memory.
		unsigned char * d;
		d = new unsigned char[volTexWidth*volTexHeight*volTexDepth * 4];
		memset(d, 0, volTexWidth*volTexHeight*volTexDepth * 4);
		volumeTexture->loadData(d, volTexWidth, volTexHeight, volTexDepth, 0, 0, 0, GL_RGBA);

		// Free the memory used to blank the texture.
		delete[] d;
	}

	voxelRatio = voxelSize;

	if (fboRender.getWidth() != volTexWidth || fboRender.getHeight() != volTexHeight)
	{
		fboRender.allocate(volTexWidth, volTexHeight, GL_RGBA);
	}

	setupShader();

	bInitialized = true;
}

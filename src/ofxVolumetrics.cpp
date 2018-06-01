#include "ofxVolumetrics.h"

#include "glm/gtx/matrix_decompose.hpp"

//--------------------------------------------------------------
ofxVolumetrics::ofxVolumetrics()
	: volumeTexture(nullptr)
	, bOwnsTexture(false)
	, quality(ofDefaultVec3(1.0f))
	, threshold(1.0f / 255.0f)
	, density(1.0f)
	, volWidth(0)
	, volHeight(0)
	, volDepth(0)
	, renderWidth(0)
	, renderHeight(0)
	, bInitialized(false)
{
	setupVbo();
}

//--------------------------------------------------------------
ofxVolumetrics::~ofxVolumetrics()
{
	clear();
}

//--------------------------------------------------------------
void ofxVolumetrics::setupVbo()
{
	ofDefaultVec3 volVerts[24];
	ofDefaultVec3 volNormals[24];
	ofIndexType volIndices[36];

	/* Front side */
	volNormals[0] = ofDefaultVec3(0.0, 0.0, 1.0);
	volNormals[1] = ofDefaultVec3(0.0, 0.0, 1.0);
	volNormals[2] = ofDefaultVec3(0.0, 0.0, 1.0);
	volNormals[3] = ofDefaultVec3(0.0, 0.0, 1.0);

	volVerts[0] = ofDefaultVec3(1.0, 1.0, 1.0);
	volVerts[1] = ofDefaultVec3(0.0, 1.0, 1.0);
	volVerts[2] = ofDefaultVec3(0.0, 0.0, 1.0);
	volVerts[3] = ofDefaultVec3(1.0, 0.0, 1.0);

	volIndices[0] = 0;
	volIndices[1] = 1;
	volIndices[2] = 2;

	volIndices[3] = 2;
	volIndices[4] = 3;
	volIndices[5] = 0;

	/* Right side */
	volNormals[4] = ofDefaultVec3(1.0, 0.0, 0.0);
	volNormals[5] = ofDefaultVec3(1.0, 0.0, 0.0);
	volNormals[6] = ofDefaultVec3(1.0, 0.0, 0.0);
	volNormals[7] = ofDefaultVec3(1.0, 0.0, 0.0);

	volVerts[4] = ofDefaultVec3(1.0, 1.0, 1.0);
	volVerts[5] = ofDefaultVec3(1.0, 0.0, 1.0);
	volVerts[6] = ofDefaultVec3(1.0, 0.0, 0.0);
	volVerts[7] = ofDefaultVec3(1.0, 1.0, 0.0);

	volIndices[6] = 4;
	volIndices[7] = 5;
	volIndices[8] = 6;

	volIndices[9] = 6;
	volIndices[10] = 7;
	volIndices[11] = 4;

	/* Top side */
	volNormals[8] = ofDefaultVec3(0.0, 1.0, 0.0);
	volNormals[9] = ofDefaultVec3(0.0, 1.0, 0.0);
	volNormals[10] = ofDefaultVec3(0.0, 1.0, 0.0);
	volNormals[11] = ofDefaultVec3(0.0, 1.0, 0.0);

	volVerts[8] = ofDefaultVec3(1.0, 1.0, 1.0);
	volVerts[9] = ofDefaultVec3(1.0, 1.0, 0.0);
	volVerts[10] = ofDefaultVec3(0.0, 1.0, 0.0);
	volVerts[11] = ofDefaultVec3(0.0, 1.0, 1.0);

	volIndices[12] = 8;
	volIndices[13] = 9;
	volIndices[14] = 10;

	volIndices[15] = 10;
	volIndices[16] = 11;
	volIndices[17] = 8;

	/* Left side */
	volNormals[12] = ofDefaultVec3(-1.0, 0.0, 0.0);
	volNormals[13] = ofDefaultVec3(-1.0, 0.0, 0.0);
	volNormals[14] = ofDefaultVec3(-1.0, 0.0, 0.0);
	volNormals[15] = ofDefaultVec3(-1.0, 0.0, 0.0);

	volVerts[12] = ofDefaultVec3(0.0, 1.0, 1.0);
	volVerts[13] = ofDefaultVec3(0.0, 1.0, 0.0);
	volVerts[14] = ofDefaultVec3(0.0, 0.0, 0.0);
	volVerts[15] = ofDefaultVec3(0.0, 0.0, 1.0);

	volIndices[18] = 12;
	volIndices[19] = 13;
	volIndices[20] = 14;

	volIndices[21] = 14;
	volIndices[22] = 15;
	volIndices[23] = 12;

	/* Bottom side */
	volNormals[16] = ofDefaultVec3(0.0, -1.0, 0.0);
	volNormals[17] = ofDefaultVec3(0.0, -1.0, 0.0);
	volNormals[18] = ofDefaultVec3(0.0, -1.0, 0.0);
	volNormals[19] = ofDefaultVec3(0.0, -1.0, 0.0);

	volVerts[16] = ofDefaultVec3(0.0, 0.0, 0.0);
	volVerts[17] = ofDefaultVec3(1.0, 0.0, 0.0);
	volVerts[18] = ofDefaultVec3(1.0, 0.0, 1.0);
	volVerts[19] = ofDefaultVec3(0.0, 0.0, 1.0);

	volIndices[24] = 16;
	volIndices[25] = 17;
	volIndices[26] = 18;

	volIndices[27] = 18;
	volIndices[28] = 19;
	volIndices[29] = 16;

	/* Back side */
	volNormals[20] = ofDefaultVec3(0.0, 0.0, -1.0);
	volNormals[21] = ofDefaultVec3(0.0, 0.0, -1.0);
	volNormals[22] = ofDefaultVec3(0.0, 0.0, -1.0);
	volNormals[23] = ofDefaultVec3(0.0, 0.0, -1.0);

	volVerts[20] = ofDefaultVec3(1.0, 0.0, 0.0);
	volVerts[21] = ofDefaultVec3(0.0, 0.0, 0.0);
	volVerts[22] = ofDefaultVec3(0.0, 1.0, 0.0);
	volVerts[23] = ofDefaultVec3(1.0, 1.0, 0.0);

	volIndices[30] = 20;
	volIndices[31] = 21;
	volIndices[32] = 22;

	volIndices[33] = 22;
	volIndices[34] = 23;
	volIndices[35] = 20;

	volVbo.setVertexData(volVerts, 24, GL_STATIC_DRAW);
	volVbo.setNormalData(volNormals, 24, GL_STATIC_DRAW);
	volVbo.setAttributeData(ofShader::COLOR_ATTRIBUTE, (float *)volVerts, 3, 24, GL_STATIC_DRAW);
	volVbo.setAttributeData(ofShader::TEXCOORD_ATTRIBUTE, (float *)volVerts, 3, 24, GL_STATIC_DRAW);
	volVbo.setIndexData(volIndices, 36, GL_STATIC_DRAW);
}

void ofxVolumetrics::setup(ofxTexture * texture, const ofDefaultVec3 & voxelSize)
{
	clear();

	setupShader();  // Default shader.
	updateTexture(texture, voxelSize);

	bInitialized = true;
}

void ofxVolumetrics::setup(ofxTexture * texture, const ofDefaultVec3 & voxelSize, ofShader shader)
{
	clear();

	volumeShader = shader;
	updateTexture(texture, voxelSize);

	bInitialized = true;
}

void ofxVolumetrics::clear()
{
	volumeShader.unload();

	if (bOwnsTexture)
	{
		volumeTexture->clear();
		delete volumeTexture;
	}
	volumeTexture = nullptr;

	volTexWidth = volWidth = renderWidth = 0;
	volTexHeight = volHeight = renderHeight = 0;
	volTexDepth = volDepth = 0;

	bInitialized = false;
}

void ofxVolumetrics::updateTexture(ofxTexture * texture, const ofDefaultVec3 & voxelSize)
{
	if (bOwnsTexture)
	{
		volumeTexture->clear();
		delete volumeTexture;
	}

	volumeTexture = texture;
	bOwnsTexture = false;

	volTexWidth = volWidth = renderWidth = volumeTexture->texData.width;
	volTexHeight = volHeight = renderHeight = volumeTexture->texData.height;
	volTexDepth = volDepth = volumeTexture->texData.depth;

	voxelRatio = voxelSize;

	if (fboRender.getWidth() != volTexWidth || fboRender.getHeight() != volTexHeight)
	{
		fboRender.allocate(volTexWidth, volTexHeight, GL_RGBA);
	}
}

ofxTexture * ofxVolumetrics::getTexture() const
{
	return volumeTexture;
}

void ofxVolumetrics::updateVolumeData(const unsigned char * data, int w, int h, int d, int xOffset, int yOffset, int zOffset)
{
	volumeTexture->loadData(data, w, h, d, xOffset, yOffset, zOffset, GL_RGBA);
}

void ofxVolumetrics::updateVolumeData(const float * data, int w, int h, int d, int xOffset, int yOffset, int zOffset) {
	volumeTexture->loadData(data, w, h, d, xOffset, yOffset, zOffset, GL_R32F);
}

void ofxVolumetrics::updateShaderUniforms(int zOffset) const
{
	volumeShader.setUniform3f("vol_d", (float)volWidth, (float)volHeight, (float)volDepth); //dimensions of the volume
	volumeShader.setUniform3f("vol_tex_d", (float)volTexWidth, (float)volTexHeight, (float)volTexDepth); //dimensions of the volume texture

	volumeShader.setUniform1f("zoffset", zOffset); // used for animation so that we dont have to upload the entire volume every time
	volumeShader.setUniform1f("quality", quality.z); // 0 ... 1
	volumeShader.setUniform1f("density", density); // 0 ... 1
	volumeShader.setUniform1f("threshold", threshold);//(float)mouseX/(float)ofGetWidth());
	volumeShader.setUniformTexture("volume_tex", volumeTexture->texData.textureTarget, volumeTexture->texData.textureID, 1);
}

void ofxVolumetrics::drawVolume(float x, float y, float z, float size, int zTexOffset) const
{
	glm::vec3 volumeSize = voxelRatio * glm::vec3(volWidth, volHeight, volDepth);
	float maxDim = max(max(volumeSize.x, volumeSize.y), volumeSize.z);
	volumeSize = volumeSize * size / maxDim;

	drawVolume(x, y, z, volumeSize.x, volumeSize.y, volumeSize.z, zTexOffset);
}

void ofxVolumetrics::drawVolume(float x, float y, float z, float w, float h, float d, int zTexOffset) const
{
	glm::vec3 cubeSize = glm::vec3(w, h, d);

	volumeShader.begin();
	{
		updateShaderUniforms(zTexOffset);
		ofPushMatrix();
		{
			ofTranslate(x - cubeSize.x / 2, y - cubeSize.y / 2, z - cubeSize.z / 2);
			ofScale(cubeSize.x, cubeSize.y, cubeSize.z);

			drawRGBCube();
		}
		ofPopMatrix();
	}
	volumeShader.end();
}

void ofxVolumetrics::drawRGBCube() const
{
	volVbo.drawElements(GL_TRIANGLES, 36);
}

void ofxVolumetrics::setXyQuality(float q)
{
	quality.x = MAX(q, 0.01);
}
void ofxVolumetrics::setZQuality(float q)
{
	quality.z = MAX(q, 0.01);
}
void ofxVolumetrics::setThreshold(float t)
{
	threshold = ofClamp(t, 0.0, 1.0);
}
void ofxVolumetrics::setDensity(float d)
{
	density = MAX(d, 0.0);
}
void ofxVolumetrics::setRenderSettings(float xyQuality, float zQuality, float dens, float thresh)
{
	setXyQuality(xyQuality);
	setZQuality(zQuality);
	setDensity(dens);
	setThreshold(thresh);
}

void ofxVolumetrics::setVolumeTextureFilterMode(GLint filterMode)
{
	if (filterMode != GL_NEAREST && filterMode != GL_LINEAR) return;

	volumeTexture->bind();
	glTexParameteri(volumeTexture->texData.textureTarget, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(volumeTexture->texData.textureTarget, GL_TEXTURE_MAG_FILTER, filterMode);
	volumeTexture->unbind();
}

bool ofxVolumetrics::isInitialized() const
{
	return bInitialized;
}
int ofxVolumetrics::getVolumeWidth() const
{
	return volWidth;
}
int ofxVolumetrics::getVolumeHeight() const
{
	return volHeight;
}
int ofxVolumetrics::getVolumeDepth() const
{
	return volDepth;
}
int ofxVolumetrics::getRenderWidth() const
{
	return renderWidth;
}
int ofxVolumetrics::getRenderHeight() const
{
	return renderHeight;
}
float ofxVolumetrics::getXyQuality() const
{
	return quality.x;
}
float ofxVolumetrics::getZQuality() const
{
	return quality.z;
}
float ofxVolumetrics::getThreshold() const
{
	return threshold;
}
float ofxVolumetrics::getDensity() const
{
	return density;
}
const ofFbo & ofxVolumetrics::getFboReference() const
{
	return fboRender;
}

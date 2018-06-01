#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0);

	// Cat animation sheet taken from Cortona docs: https://docs.coronalabs.com/guide/media/spriteAnimation/index.html
	ofDirectory framesDir("frames");
	framesDir.allowExt("png");
	framesDir.listDir();
	numLayers = framesDir.size();

	ofImage frameImage;
	frameImage.setUseTexture(false);

	for (int i = 0; i < numLayers; ++i)
	{
		frameImage.load(framesDir.getPath(i));
		if (i == 0)
		{
			textureArray.allocate(frameImage.getWidth(), frameImage.getHeight(), numLayers, GL_RGBA8);
		}

		textureArray.loadData(frameImage.getPixels(), 1, 0, 0, i);
	}

	// Build a mesh to render a quad.
	quadMesh.clear();
	quadMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

	float quadWidth = ofGetWidth();
	float quadHeight = quadWidth * textureArray.texData.height / textureArray.texData.width;

	quadMesh.addVertex(ofDefaultVec3(0, 0, 0));
	quadMesh.addVertex(ofDefaultVec3(quadWidth, 0, 0));
	quadMesh.addVertex(ofDefaultVec3(quadWidth, quadHeight, 0));
	quadMesh.addVertex(ofDefaultVec3(0, quadHeight, 0));

	quadMesh.addTexCoord(ofDefaultVec2(0, 0));
	quadMesh.addTexCoord(ofDefaultVec2(1, 0));
	quadMesh.addTexCoord(ofDefaultVec2(1, 1));
	quadMesh.addTexCoord(ofDefaultVec2(0, 1));

	ofSetWindowShape(quadWidth, quadHeight);

	shader.load("shaders/frame");

	currLayer = 0;
}

//--------------------------------------------------------------
void ofApp::update()
{
	ofSetWindowTitle(ofToString(ofGetFrameRate()));

	currLayer += ofClamp(ofGetMouseX() / (float)ofGetWidth(), 0.0, 1.0);
	while (currLayer >= numLayers)
	{
		currLayer -= numLayers;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetColor(ofColor::white);

	shader.begin();
	shader.setUniformTexture("uTexArray", textureArray.texData.textureTarget, textureArray.texData.textureID, 1);
	shader.setUniform1f("uLayer", currLayer);
	{
		quadMesh.draw();
	}
	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

#pragma once

//#define USE_VOLUMETRICS_3D 1

#include "ofBaseApp.h"
#include "ofEasyCam.h"
#include "ofImage.h"

#include "ofxImageSequencePlayer.h"

#ifdef USE_VOLUMETRICS_3D
#include "ofxVolumetrics3D.h"
#else
#include "ofxVolumetricsArray.h"
#endif

class ofApp 
	: public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofEasyCam cam;

#ifdef USE_VOLUMETRICS_3D
	ofxVolumetrics3D myVolume;
#else
	ofxVolumetricsArray myVolume;
#endif

	unsigned char * volumeData;
	int volWidth, volHeight, volDepth;
	ofImage background;
	ofxImageSequencePlayer imageSequence;
	bool linearFilter;
};

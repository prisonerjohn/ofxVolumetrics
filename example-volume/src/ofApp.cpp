#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetLogLevel(OF_LOG_VERBOSE);
	background.allocate(1024, 768, OF_IMAGE_COLOR);
	background.load("background.png");
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	imageSequence.init("volumes/head/cthead-8bit", 3, ".tif", 1);
	volWidth = imageSequence.getWidth();
	volHeight = imageSequence.getHeight();
	volDepth = imageSequence.getSequenceLength();

	ofLogNotice(__FUNCTION__) << "Setting up volume data buffer at " << volWidth << "x" << volHeight << "x" << volDepth;

	volumeData = new unsigned char[volWidth*volHeight*volDepth * 4];

	for (int z = 0; z<volDepth; z++)
	{
		imageSequence.loadFrame(z);
		for (int x = 0; x<volWidth; x++)
		{
			for (int y = 0; y<volHeight; y++)
			{
				// convert from greyscale to RGBA, false color
				int i4 = ((x + volWidth * y) + z * volWidth*volHeight) * 4;
				int sample = imageSequence.getPixels()[x + y * volWidth];
				ofColor c;
				c.setHsb(sample, 255 - sample, sample);

				volumeData[i4] = c.r;
				volumeData[i4 + 1] = c.g;
				volumeData[i4 + 2] = c.b;
				volumeData[i4 + 3] = sample;
			}
		}
	}

	myVolume.setup(volWidth, volHeight, volDepth, ofVec3f(1, 1, 2), true);
	myVolume.updateVolumeData(volumeData, volWidth, volHeight, volDepth, 0, 0, 0);
	myVolume.setRenderSettings(1.0, 1.0, 0.75, 0.1);

	linearFilter = false;

	cam.setDistance(1000);
	cam.enableMouseInput();
	cam.disableInertia();
	cam.setUpAxis(glm::vec3(0, 0, -1));
}

//--------------------------------------------------------------
void ofApp::update()
{}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetColor(255, 255, 255, 255);
	background.draw(0, 0, ofGetWidth(), ofGetHeight());

	cam.begin();
	myVolume.drawVolume(0, 0, 0, ofGetHeight(), 0);
	cam.end();

	ofSetColor(0, 0, 0, 64);
	ofDrawRectangle(0, 0, 270, 90);
	ofSetColor(255, 255, 255, 255);

	ofDrawBitmapString("volume dimensions: " + ofToString(myVolume.getVolumeWidth()) + "x" + ofToString(myVolume.getVolumeHeight()) + "x" + ofToString(myVolume.getVolumeDepth()) + "\n" +
		"FBO quality (q/Q): " + ofToString(myVolume.getRenderWidth()) + "x" + ofToString(myVolume.getRenderHeight()) + "\n" +
		"Z quality (z/Z):   " + ofToString(myVolume.getZQuality()) + "\n" +
		"Threshold (t/T):   " + ofToString(myVolume.getThreshold()) + "\n" +
		"Density (d/D):     " + ofToString(myVolume.getDensity()) + "\n" +
		"Filter mode (l/n): " + (linearFilter ? "linear" : "nearest") + "\n" +
		"Fps: " + ofToString(ofGetFrameRate()), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
	case 't':
		myVolume.setThreshold(myVolume.getThreshold() - 0.01);
		break;
	case 'T':
		myVolume.setThreshold(myVolume.getThreshold() + 0.01);
		break;
	case 'd':
		myVolume.setDensity(myVolume.getDensity() - 0.01);
		break;
	case 'D':
		myVolume.setDensity(myVolume.getDensity() + 0.01);
		break;
	case 'q':
		myVolume.setXyQuality(myVolume.getXyQuality() - 0.01);
		break;
	case 'Q':
		myVolume.setXyQuality(myVolume.getXyQuality() + 0.01);
		break;
	case 'z':
		myVolume.setZQuality(myVolume.getZQuality() - 0.01);
		break;
	case 'Z':
		myVolume.setZQuality(myVolume.getZQuality() + 0.01);
		break;
	case 'l':
		myVolume.setVolumeTextureFilterMode(GL_LINEAR);
		linearFilter = true;
		break;
	case 'n':
		myVolume.setVolumeTextureFilterMode(GL_NEAREST);
		linearFilter = false;
		break;
	case OF_KEY_UP:
	{
		auto target = cam.getTarget();
		target.boom(-5);
		cam.setTarget(target);
		break;
	}
	case OF_KEY_DOWN:
	{
		auto target = cam.getTarget();
		target.boom(5);
		cam.setTarget(target);
		break;
	}
	case OF_KEY_LEFT:
	{
		auto target = cam.getTarget();
		target.truck(-5);
		cam.setTarget(target);
		break;
	}
	case OF_KEY_RIGHT:
	{
		auto target = cam.getTarget();
		target.truck(5);
		cam.setTarget(target);
		break;
	}
	}
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

#pragma once

#include "ofMain.h"

class ofxImageSequencePlayer 
	: public ofImage 
{
public:
	ofxImageSequencePlayer()
	{};

	void init(const std::string & prefix, int digits, const std::string & extension, int start)
	{
		curFrame = start;
		startFrame = start;
		fPrefix = prefix;
		fExt = extension;
		numDigits = digits;
		initialized = load(generateFullFilename());

		if (!initialized) {
			ofLogWarning(__FUNCTION__) << "Unable to load inital image in the sequence: " << generateFullFilename();
			return;
		}

		totalFrames = 0;
		ofFile testFile;
		while (testFile.open(generateFullFilename()))
		{
			totalFrames++;
			curFrame++;
			testFile.close();
		}
		testFile.close();
		curFrame = startFrame;
	};

	bool loadNextFrame()
	{
		bool worked = load(generateFullFilename());
		if (worked)
			curFrame++;
		return worked;
	};

	bool loadPreviousFrame()
	{
		bool worked = load(generateFullFilename());
		if (worked)
			curFrame = curFrame > 0 ? curFrame - 1 : 0;
		return worked;
	};

	bool loadFrame(int n)
	{
		curFrame = startFrame + n;
		bool worked = load(generateFullFilename());
		if (worked)
			curFrame++;
		return worked;
	};

	unsigned int getCurrentFrameNumber() { return curFrame - startFrame; }
	void setCurrentFrameNumber(unsigned int i) { curFrame = startFrame + i; }
	unsigned int getSequenceLength() { return totalFrames; }
	bool isInitialized() { return initialized; }

	std::string generateFullFilename()
	{
		std::ostringstream ss;
		ss << std::setw(numDigits) << std::setfill('0') << curFrame;
		std::string result = ss.str();
		if (result.length() > numDigits)
		{
			result.erase(0, result.length() - numDigits);
		}
		return fPrefix + ss.str() + fExt;
	};

private:
	bool initialized;
	unsigned int curFrame, startFrame;
	std::string fPrefix, fExt;
	unsigned int numDigits;
	unsigned int totalFrames;
};

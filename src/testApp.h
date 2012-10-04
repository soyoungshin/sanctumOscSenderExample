#pragma once


#include "ofMain.h"

#define DEFAULT_HOST "localhost"
#define DEFAULT_PORT 12345

#include "ofxOsc.h"

// add positionings as necessary.
// this is kept in sync with the enum in ofxComposition/ofxVideoWrapper.h
// TODO: since this sketch is a standin for a Supercollider script,
//		figure out how to share this enum.
enum e_videoPosition {
		HF_UPPER_LEFT,
		HF_UPPER_RIGHT,
		HF_CENTER_LEFT,
		HF_CENTER_RIGHT,
		HF_LOWER_LEFT,
		HF_LOWER_RIGHT,
		HF_UPPER_THIRD,
		HF_CENTER_THIRD,
		HF_LOWER_THIRD,
		HF_LEFT_HALF,
		HF_RIGHT_HALF,
		HF_FULL_SCREEN
};

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxOscSender sender;

private:
	void sendSampleCompositionBundle();
	void sendPopOne();
	void sendPopFive();
	void sendFlush();
	void addVideoMessage(ofxOscBundle* bundle, char* address, char* filePath, int position,
						int compStartTime, int compDuration, int clipStartTime, int clipDuration,
						int ofLoopType);
	void addSubtitleMessage(ofxOscBundle* bundle, char* address, char* message,
						int compStartTime, int compDuration, int x, int y);
};


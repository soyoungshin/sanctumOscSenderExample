#include "testApp.h"

// fill with paths to movie files on receiving end.
char* fileNames[] = {
	"big_buck_bunny_720p_h264.mov",
	"big_buck_bunny_720p_h264 (copy).mov",
	"big_buck_bunny_720p_h264 (another copy).mov",
	"big_buck_bunny_720p_h264 (3rd copy).mov",
	"big_buck_bunny_720p_h264 (4th copy).mov",
	"big_buck_bunny_720p_h264 (5th copy).mov",
};

//--------------------------------------------------------------
void testApp::setup(){
	sender.setup(DEFAULT_HOST, DEFAULT_PORT);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0x000000);
	ofDrawBitmapString("press '1' to send sample message bundle\n      '2' to pop one composition\n      '3' to pop five compositions\n      '4' to flush everything", 50, 50);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	switch (key) {
		case '1':
			sendSampleCompositionBundle();
			break;
		case '2':
			sendPopOne();
			break;
		case '3':
			sendPopFive();
			break;
		case '4':
			sendFlush();
			break;
		default:
			break;
	}
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

void testApp::sendPopOne() {
	ofxOscMessage m;
	m.setAddress("/pop");
	sender.sendMessage(m);
}

void testApp::sendPopFive() {
	ofxOscMessage m;
	m.setAddress("/pop");
	m.addIntArg(5);
	sender.sendMessage(m);
}

void testApp::sendFlush() {
	ofxOscMessage m;
	m.setAddress("/flush");
	sender.sendMessage(m);
}

// just a test function
void testApp::sendSampleCompositionBundle(){
	ofxOscBundle bundle;

/*
    //this plays a 12 second loop for 3 minutes.
	addVideoMessage(&bundle, "/addComposition", fileNames[0], HF_FULL_SCREEN, 0, 180, rand()%540, 12, OF_LOOP_NORMAL);
*/



    // a more complicated scenario.

    // one video that fills all six screens for ten seconds
	addVideoMessage(&bundle, "/addComposition", fileNames[4], HF_FULL_SCREEN, 0, 10, rand()%540, 3, OF_LOOP_NORMAL);

	// followed by six videos, one per screen
	int idx;
	for(idx = 0; idx < 6; idx++) {
		addVideoMessage(&bundle, "/addComposition", fileNames[idx], idx, 10, 20, rand()%540, rand() % 10, OF_LOOP_NORMAL);
	}

	// followed by another video filling the screen that does not loop
	addVideoMessage(&bundle, "/addComposition", fileNames[3], HF_FULL_SCREEN, 20, 30, rand()%540, 5, OF_LOOP_NONE);

    addVideoMessage(&bundle, "/addComposition", fileNames[rand() % 6], HF_UPPER_THIRD, 25, 35, rand()%540, rand() % 10, OF_LOOP_NORMAL);
    addVideoMessage(&bundle, "/addComposition", fileNames[rand() % 6], HF_CENTER_THIRD, 30, 35, rand()%540, rand() % 10, OF_LOOP_NORMAL);
    addVideoMessage(&bundle, "/addComposition", fileNames[rand() % 6], HF_LOWER_THIRD, 30, 35, rand()%540, rand() % 10, OF_LOOP_NORMAL);

    addVideoMessage(&bundle, "/addComposition", fileNames[rand() % 6], HF_LEFT_HALF, 35, 50, rand()%540, rand() % 10, OF_LOOP_NORMAL);
    addVideoMessage(&bundle, "/addComposition", fileNames[rand() % 6], HF_RIGHT_HALF, 35, 50, rand()%540, rand() % 10, OF_LOOP_NORMAL);

    addVideoMessage(&bundle, "/addComposition", fileNames[rand() % 6], HF_FULL_SCREEN, 50, 75, rand()%540, rand() % 10, OF_LOOP_NORMAL);

    // some subititles, this one lasts for ten seconds, and is placed at these x/y coordiates
	addSubtitleMessage(&bundle, "/addSubtitle", "yo yo yo!!!", 0000, 10000, 400, 600);

    // this lasts six seconds.
	addSubtitleMessage(&bundle, "/addSubtitle", "fro fro fro", 10000, 16000, 200, 200);
	addSubtitleMessage(&bundle, "/addSubtitle", "fro fro fro", 10000, 16000, 600, 200);


	sender.sendBundle(bundle);
}

/**
 sets osc message arguments for a video in a composition.

 m:				message to set arguments in.
 address:		path for this osc message.
 filePath:		path to the video on the receiving computer.
 position:		positioning of the video when displayed. see ofxVideoWrapper.cpp for this enumeration.
 compStartTime:	time in the composition to start this video.
 compDuration:	duration of this video within the composition.
 clipStartTime:	time at which _this video_ start.
 clipDuration:	amount of time to play _this video_
 ofLoopType:	looping type for this video.

 */
void testApp::addVideoMessage(ofxOscBundle* bundle, char* address, char* filePath, int position,
							int compStartTime, int compDuration, int clipStartTime, int clipDuration,
							int ofLoopType) {
    ofxOscMessage m;

	m.setAddress(address);
	m.addStringArg(filePath);
	m.addIntArg(position);
	m.addIntArg(compStartTime);
	m.addIntArg(compDuration);
	m.addIntArg(clipStartTime);
	m.addIntArg(clipDuration);
	m.addIntArg(ofLoopType);

    bundle->addMessage(m);
}

//duration in MILLIS
void testApp::addSubtitleMessage(ofxOscBundle* bundle, char* address, char* message,
						int compStartTime, int compDuration, int x, int y) {
    ofxOscMessage m;

	m.setAddress(address);
	m.addStringArg(message);
	m.addIntArg(compStartTime);
	m.addIntArg(compDuration);
	m.addIntArg(x);
	m.addIntArg(y);

	bundle->addMessage(m);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

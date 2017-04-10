#pragma once

#include "ofMain.h"
#include "ofxHapPlayer.h"
#include "ofxGui.h"

#define SPEED_MINIMUM_X 0
#define SPEED_MINIMUM_Y 0

#define SPEED_MAXIMUM_X 30
#define SPEED_MAXIMUM_Y 30

#define FRAME_RATE 60

class ScrollPlayer{
public:
    vector<shared_ptr<ofxHapPlayer>> players;
    int rightViewId;
    ofVec2f rightViewPosition;
    ofVec2f movingSpeed;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    void guiMovingSpeedChanged(ofVec2f &guiMovingSpeed);
    
    // debug
    void drawAllPlayers();
    
    ScrollPlayer scrollPlayer;
    
    // gui
    bool showGui;
    ofxPanel panel;
    ofParameter<ofVec2f> guiMovingSpeed;
    ofParameter<string> guiFps;
    ofParameter<bool> enableDrawAllPlayers;
    ofxLabel shortCutInfo;
};

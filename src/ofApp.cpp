#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // gui
    // we add this listener before setting up so the initial circle resolution is correct
    guiMovingSpeed.addListener(this, &ofApp::guiMovingSpeedChanged);
    
    showGui = true;
    panel.setup();
    panel.add(guiFps.set("FPS", ""));
    panel.add(enableDrawAllPlayers.set("drawAllPlayers", false));
    panel.add(guiMovingSpeed.set("moving speed", ofVec2f(10, 0), ofVec2f(SPEED_MINIMUM_X, SPEED_MINIMUM_Y), ofVec2f(SPEED_MAXIMUM_X, SPEED_MAXIMUM_Y)));
    panel.add(shortCutInfo.setup("hide/show GUI", "type h"));
    
    //some path, may be absolute or relative to bin/data
    string path = "movies";
    ofDirectory dir(path);
    //only show png files
    dir.allowExt("mov");
    //populate the directory object
    dir.listDir();
    
    scrollPlayer.rightViewId = 0;
    
    //go through and print out all the paths
    for(int i = 0; i < (int)dir.size(); i++){
        // set scrollPlayer
        shared_ptr<ofxHapPlayer> player = std::make_shared<ofxHapPlayer>();
        player->load(dir.getPath(i));
        if(i != 0) player->setVolume(0);
        player->play();
        scrollPlayer.players.push_back(player);
        
        // debug
        ofLogNotice(dir.getPath(i));
    }
    scrollPlayer.rightViewPosition.set(0, 0);
    scrollPlayer.movingSpeed.set(guiMovingSpeed);
    
    // set window
    if (scrollPlayer.players[0]->isLoaded()) {
        ofSetWindowShape(scrollPlayer.players[0]->getWidth(), scrollPlayer.players[0]->getHeight());
        ofSetWindowPosition(0, 0);
    }
    
    ofSetFrameRate(FRAME_RATE);
}

void ofApp::guiMovingSpeedChanged(ofVec2f &guiMovingSpeed){
    scrollPlayer.movingSpeed = guiMovingSpeed;
}

//--------------------------------------------------------------
void ofApp::update(){
    // update position
    scrollPlayer.rightViewPosition += scrollPlayer.movingSpeed * (ofGetTargetFrameRate() * ofGetLastFrameTime());
    
    // when the rightViewPosition has reached/passed the end point
    if(scrollPlayer.rightViewPosition.x >= scrollPlayer.players[0]->getWidth()){
        // update rightViewId
        scrollPlayer.rightViewId = (scrollPlayer.rightViewId+1)%(int)scrollPlayer.players.size();
        // update rightViewPosition
        scrollPlayer.rightViewPosition -= ofVec2f(scrollPlayer.players[0]->getWidth(), 0);
    }
    
    // update 3 of players which are right view, left view, standby view.
    for(int i = scrollPlayer.rightViewId; i < scrollPlayer.rightViewId+3; i++){
        int playerIndex = i%(int)scrollPlayer.players.size();
        if(playerIndex != 0) scrollPlayer.players[playerIndex]->setPosition(scrollPlayer.players[0]->getPosition());
        scrollPlayer.players[playerIndex]->update();
    }
    
    // gui
    guiFps = ofToString(ofGetFrameRate(), 0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw 3 of players which are right view, left view, stadnby view.
    for(int i = scrollPlayer.rightViewId; i < scrollPlayer.rightViewId+3; i++){
        int playerIndex = i%(int)scrollPlayer.players.size();
        ofVec2f playerPosition(scrollPlayer.rightViewPosition-(i-scrollPlayer.rightViewId)*ofVec2f(scrollPlayer.players[0]->getWidth(),0));
        scrollPlayer.players[playerIndex]->draw(playerPosition.x, playerPosition.y);
    }
    
    // debug
    if(enableDrawAllPlayers)ofApp::drawAllPlayers();
    
    // gui
    if(showGui)panel.draw();
}

void ofApp::drawAllPlayers(){
    // draw background
    // rightView
    ofSetColor(255);
    ofVec2f rightViewPosition = getPlayerPosition(scrollPlayer.rightViewId);
    ofDrawRectangle(rightViewPosition.x-1, rightViewPosition.y-1, DEBUG_PLAYER_WIDTH+2, DEBUG_PLAYER_HEIGHT+2);
    
    // second right view
    int secondRightViewId = (scrollPlayer.rightViewId+1)%(int)scrollPlayer.players.size();
    ofVec2f secondRightViewPosition = getPlayerPosition(secondRightViewId);
    ofSetColor(127);
    ofDrawRectangle(secondRightViewPosition.x-1, secondRightViewPosition.y-1, DEBUG_PLAYER_WIDTH+2, DEBUG_PLAYER_HEIGHT+2);
    
    // third right view
    int thirdRightViewId = (scrollPlayer.rightViewId+2)%(int)scrollPlayer.players.size();
    ofVec2f thirdRightViewPosition = getPlayerPosition(thirdRightViewId);
    ofSetColor(64);
    ofDrawRectangle(thirdRightViewPosition.x-1, thirdRightViewPosition.y-1, DEBUG_PLAYER_WIDTH+2, DEBUG_PLAYER_HEIGHT+2);
    
    // reset the color
    ofSetColor(255);
    
    // draw players
    for (int i = 0; i < (int)scrollPlayer.players.size(); i++){
        if (scrollPlayer.players[i]->isLoaded()) {
            ofVec2f playerPosition = getPlayerPosition(i);
            scrollPlayer.players[i]->draw(playerPosition.x, playerPosition.y, DEBUG_PLAYER_WIDTH, DEBUG_PLAYER_HEIGHT);
        }
    }
}

ofVec2f ofApp::getPlayerPosition(int playerIndex) {
    ofVec2f origin = panel.getShape().getBottomLeft() + ofPoint(0, 10);
    return (ofVec2f(origin.x+playerIndex%5*(DEBUG_PLAYER_WIDTH+20), origin.y+playerIndex/5*(DEBUG_PLAYER_HEIGHT+20)));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'h': // hide or show gui
            showGui = !showGui;
            showGui ? ofShowCursor() : ofHideCursor();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

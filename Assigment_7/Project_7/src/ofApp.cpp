#include "ofApp.h"

//Center position

int r = 50;
int emotionCounter = 0;
ofSoundPlayer bgm;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(75,0,255);


    
//    soundVolume.addListener(this,  &ofApp::changeBGMV);
    rotateEmotion.addListener(this, &ofApp::rotateEmotionPressed);
    
    int screenWidth = ofGetWidth();
    int screenHeight = ofGetHeight();
    
    gui.setup();
    gui.add(soundVolume.setup("Sound Volume",50,0,100));//float slider - volume
    gui.add(rotateEmotion.setup("Next Emotion"));
    gui.add(faceCenter.setup("Move the position",{ofGetWidth()/2,ofGetHeight()/4},{0,0},{ofGetWidth(),ofGetHeight()}));
    gui.add(color.setup("color",ofColor(255,100,100,255),ofColor(0,0,0,0),ofColor(255,255,255,255)));
    gui.add(emotionDegree.setup("Emotion Degree",50,40,80));
    gui.add(infoBroad.setup("Information Broad", "Hello, This is the Project 7 from Shuhao"));
   

    bgm.load("friend.mp3");
    bgm.play();
    bgm.setLoop(true);
    bgm.setVolume(soundVolume);

    
}
void ofApp::exit(){
//    soundVolume.removeListener(this,  &ofApp::changeBGMV);
    rotateEmotion.removeListener(this, &ofApp::rotateEmotionPressed);
}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    
    if (emotionCounter == 1){
        
    }
    if (emotionCounter == 1){
        drawHappy();
    }
    if (emotionCounter == 2){
        drawSad();
    }
    
    if (emotionCounter == 3){
        drawAngry();
    }
    
    if (emotionCounter == 4){
        drawSuprise();
    }
    
    if (emotionCounter == 5){
        emotionCounter=0;
    }
    
//    drawHappy();
//    drawSad();
//    drawAngry();
//    drawSuprise();
//
   
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

void ofApp::changeBGMV(){
    bgm.setVolume(soundVolume);
}

//-----------
void ofApp::rotateEmotionPressed(){
    emotionCounter++;
}




//------------------------------------------------

void ofApp::drawHappy(){
    
    //Peter's head
    ofSetCircleResolution(100);
    ofSetColor(color);
    ofDrawCircle(faceCenter,emotionDegree);
    
    //Peter's eye
    ofSetColor(255,255,255);
    ofDrawEllipse(faceCenter+ofVec2f(-0.5*emotionDegree,0),35,35);
    ofSetColor(42,64,238);
    ofDrawCircle(faceCenter+ofVec2f(-0.5*emotionDegree,0),10);

    ofSetColor(255,255,255);
    ofDrawEllipse(faceCenter+ofVec2f(0.5*emotionDegree,0),35,35);
    ofSetColor(42,64,238);
    ofDrawCircle(faceCenter+ofVec2f(0.5*emotionDegree,0),10);

    //Peter's mouth
    ofSetColor(255,210,0);
    ofDrawBezier(faceCenter->x-emotionDegree/4,faceCenter->y+emotionDegree/4,faceCenter->x-emotionDegree/4+5,faceCenter->y+emotionDegree/4+10,faceCenter->x-emotionDegree/4+emotionDegree/2-5,faceCenter->y+emotionDegree/4+10,faceCenter->x-emotionDegree/4+emotionDegree/2,faceCenter->y+emotionDegree/4);
    
}

void ofApp::drawSad(){
    //Peter's head
    ofSetCircleResolution(100);
    ofSetColor(color);
    ofDrawCircle(faceCenter,emotionDegree);
    
    ofSetColor(255,255,255);
    ofDrawEllipse(faceCenter+ofVec2f(-0.5*emotionDegree,0),35,15);

    ofSetColor(42,64,238);
    ofDrawCircle(faceCenter+ofVec2f(-0.5*emotionDegree+3,3),7);

    
    ofSetColor(255,255,255);
    ofDrawEllipse(faceCenter+ofVec2f(0.5*emotionDegree,0),35,15);
    ofSetColor(42,64,238);
    ofDrawCircle(faceCenter+ofVec2f(0.5*emotionDegree+3,3),7);
    
       ofSetColor(42,64,238);
    ofDrawBezier(faceCenter->x-emotionDegree/4,faceCenter->y+emotionDegree/4,faceCenter->x-emotionDegree/4+5,faceCenter->y+emotionDegree/4-10,faceCenter->x-emotionDegree/4+emotionDegree/2-5,faceCenter->y+emotionDegree/4-10,faceCenter->x-emotionDegree/4+emotionDegree/2,faceCenter->y+emotionDegree/4);


}

void ofApp::drawAngry(){
    //Peter's head
    ofSetCircleResolution(100);
    ofSetColor(color);
    ofDrawCircle(faceCenter,emotionDegree);
    
    ofSetColor(0,0,0);
    ofDrawBezier(faceCenter->x-emotionDegree/4,faceCenter->y+emotionDegree/2,faceCenter->x-emotionDegree/4+5,faceCenter->y+emotionDegree/4-10,faceCenter->x-emotionDegree/4+emotionDegree/2-5,faceCenter->y+emotionDegree/4-10,faceCenter->x-emotionDegree/4+emotionDegree/2,faceCenter->y+emotionDegree/2);
            
    ofSetColor(255,255,255);
    ofDrawEllipse(faceCenter+ofVec2f(-0.5*emotionDegree,0),emotionDegree-10,emotionDegree-15);

    
    ofSetColor(42,64,238);
    ofDrawCircle(faceCenter+ofVec2f(-0.5*emotionDegree,-8),emotionDegree/5);

            
    ofSetColor(255,255,255);
    ofDrawEllipse(faceCenter+ofVec2f(0.5*emotionDegree,0),emotionDegree-10,emotionDegree-15);

    ofSetColor(42,64,238);
    ofDrawCircle(faceCenter+ofVec2f(0.5*emotionDegree,-8),emotionDegree/5);

}

void ofApp::drawSuprise(){
    //Peter's head
    ofSetCircleResolution(100);
    ofSetColor(color);
    ofDrawCircle(faceCenter,emotionDegree);
    
    ofSetColor(164,255,0);
    ofDrawEllipse(faceCenter+ofVec2f(0,emotionDegree/2),emotionDegree-25,emotionDegree-15);

    
    
    ofSetColor(255,255,255);
    ofDrawEllipse(faceCenter+ofVec2f(-0.5*emotionDegree,0),emotionDegree-15,emotionDegree-15);

    ofSetColor(42,64,238);
    ofDrawCircle(faceCenter+ofVec2f(-0.5*emotionDegree,0),emotionDegree/5);

    ofSetColor(255,255,255);
    ofDrawEllipse(faceCenter+ofVec2f(0.5*emotionDegree,0),emotionDegree-15,emotionDegree-15);

    
    ofSetColor(42,64,238);
    ofDrawCircle(faceCenter+ofVec2f(0.5*emotionDegree,0),emotionDegree/5);
}

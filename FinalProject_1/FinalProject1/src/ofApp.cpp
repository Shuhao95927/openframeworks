#include "ofApp.h"

int foxCenterPosX = 1350;
int foxCenterPosY = 560;
int foxEyeR = 50;
int rabCenterPosX = 1200;
int rabCenterPosY = 500;
int rabEyeR = 50;

int jpgTimes = 6;

//control
int slideNumber = 0;
float currentTime = 0;
float countFrame = ofGetFrameNum();

ofImage FoxHead;
ofImage FoxBody;
ofImage FoxLowLimb;
ofImage FoxShoe;
ofImage FoxRHdef; //Default right hand
ofImage FoxLHdef; //Default left hand
ofVec2f foxCenter(foxCenterPosX,foxCenterPosY);

ofImage RabbitHead;
ofImage RabbitBody;
ofImage RabbitREar;
ofImage RabbitLEar;
ofImage RabbitRHdef;
ofImage RabbitLHdef;
ofImage RabbitShoe;
ofVec2f rabbitCenter(rabCenterPosX, rabCenterPosY);

ofImage SceneIntro;// First scene to introduce the character and backgrond.

ofVec2f currVecFox(0,0);
ofVec2f targetVecFox;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(120);
    
    FoxHead.load("character/foxHead.png"); // 927 * 751
    FoxBody.load("character/foxBody.png"); // 492 * 499
    FoxLowLimb.load("character/foxLowerlimb.png"); // 387 * 266
    FoxShoe.load("character/foxShoe.png"); // 135 * 95
    FoxRHdef.load("character/foxRHdef.png"); // 87 * 113
    FoxLHdef.load("character/foxLHdef.png"); // 87 * 113
    
    RabbitHead.load("character/rabbitHead.png");
    RabbitBody.load("character/rabbitBody.png");
    RabbitShoe.load("character/rabbitShoe.png");
    RabbitREar.load("character/rabbitREar.png");
    RabbitLEar.load("character/rabbitLEar.png");
    RabbitRHdef.load("character/rabbitRHdef.png");
    RabbitLHdef.load("character/rabbitLHdef.png");

    
    SceneIntro.load("scene/Scene1-1.png");
    
}

//--------------------------------------------------------------
void ofApp::update(){
   

    if(ofGetFrameNum() % 60 == 0){
        if(slideNumber > 2){
            slideNumber = 0;
        }else{
            slideNumber++;
            currentTime = ofGetFrameNum();
            cout<<currentTime<<endl;
        }

    }

    if(targetVecFox != currVecFox){
        currVecFox = currVecFox + (targetVecFox - currVecFox) * 0.3;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(190,233,255);
    drawFirstScene();
    drawFoxDef();
    drawRabDef();

    if(slideNumber == 0){
        drawFoxForwardA();
    }
    
    if(slideNumber == 1){
        drawFoxForwardB();
    }
    
    if(slideNumber == 2){
        drawFoxForwardA();
    }
    
    if(slideNumber == 3){
        drawFoxForwardB();
    }
    
}

//--------------------------------------------------------------

void ofApp::drawFoxDef(){
    //draw hands
    FoxLHdef.draw(foxCenter + ofVec2f(-30,480/jpgTimes),(87+10)/jpgTimes,(113+10)/jpgTimes);
    FoxRHdef.draw(foxCenter + ofVec2f(580/jpgTimes,480/jpgTimes),(87+10)/jpgTimes,(113+10)/jpgTimes);
    ofSetColor(47,189,191);
    ofSetLineWidth(12);
    ofNoFill();
    
    ofDrawBezier(foxCenterPosX + 100/jpgTimes, foxCenterPosY + 100/jpgTimes, foxCenterPosX - 30/jpgTimes, foxCenterPosY + 100/jpgTimes, foxCenterPosX - 125/jpgTimes, foxCenterPosY + 400/jpgTimes, foxCenterPosX - 21, foxCenterPosY + 500/jpgTimes);
    
    ofDrawBezier(foxCenterPosX + 370/jpgTimes, foxCenterPosY + 100/jpgTimes, foxCenterPosX + 470/jpgTimes, foxCenterPosY + 150/jpgTimes, foxCenterPosX + 600/jpgTimes, foxCenterPosY + 300/jpgTimes, foxCenterPosX + 600/jpgTimes, foxCenterPosY + 500/jpgTimes);

    //
    ofSetColor(255);// Is this necessary?
    FoxLowLimb.draw(foxCenter + ofVec2f(5,62),387/jpgTimes,227/jpgTimes);
    FoxBody.draw(foxCenter,492/jpgTimes,499/jpgTimes);
    FoxHead.draw(foxCenter + ofVec2f(-35, -100),927/jpgTimes,751/jpgTimes);
    // ofDrawBezier((foxCenter + ofVec2f(17,0)),(foxCenter + ofVec2f(-30,17)), (foxCenter + ofVec2f(-21,500/6)), (foxCenter + ofVec2f(-21,300/6)));

    ofSetColor(255);
    
}

void ofApp::drawFoxForwardA(){
    //Left leg forward
    
    ofSetColor(19,84,84);
    ofSetLineWidth(15);
    ofNoFill();
    
    ofDrawBezier(foxCenterPosX + 170/jpgTimes, foxCenterPosY + 500/jpgTimes, foxCenterPosX + 100/jpgTimes, foxCenterPosY + 580/jpgTimes, foxCenterPosX, foxCenterPosY + 880/jpgTimes, foxCenterPosX, foxCenterPosY + 1000/jpgTimes);
    
    ofDrawBezier(foxCenterPosX + 350/jpgTimes, foxCenterPosY + 500/jpgTimes, foxCenterPosX + 350/jpgTimes, foxCenterPosY + 600/jpgTimes, foxCenterPosX + 400/jpgTimes, foxCenterPosY + 900/jpgTimes, foxCenterPosX + 450/jpgTimes, foxCenterPosY + 1000/jpgTimes);
   
    ofSetColor(255);

    FoxShoe.draw(foxCenter + ofVec2f(-100/jpgTimes,1000/jpgTimes),160/jpgTimes, 120/jpgTimes);
    FoxShoe.draw(foxCenter + ofVec2f(350/jpgTimes,1000/jpgTimes),160/jpgTimes, 120/jpgTimes);

}

void ofApp::drawFoxForwardB(){
    //draw legs
    ofSetColor(19,84,84);
    ofSetLineWidth(15);
    ofNoFill();
    //left leg stand
    ofDrawBezier(foxCenterPosX + 170/jpgTimes, foxCenterPosY + 500/jpgTimes, foxCenterPosX + 100/jpgTimes, foxCenterPosY + 600/jpgTimes, foxCenterPosX + 100/jpgTimes, foxCenterPosY + 900/jpgTimes, foxCenterPosX + 170/jpgTimes, foxCenterPosY + 1000/jpgTimes);
    //right leg stand
    ofDrawBezier(foxCenterPosX + 350/jpgTimes, foxCenterPosY + 500/jpgTimes, foxCenterPosX + 280/jpgTimes, foxCenterPosY + 600/jpgTimes, foxCenterPosX + 280/jpgTimes, foxCenterPosY + 900/jpgTimes, foxCenterPosX + 350/jpgTimes, foxCenterPosY + 1000/jpgTimes);
    
    ofSetColor(255);

    FoxShoe.draw(foxCenter + ofVec2f(60/jpgTimes,1000/jpgTimes),160/jpgTimes, 120/jpgTimes);
    FoxShoe.draw(foxCenter + ofVec2f(240/jpgTimes,1000/jpgTimes),160/jpgTimes, 120/jpgTimes);

}
//-----------------------------------

void ofApp::drawRabDef(){
    ofSetColor(255);
    
    RabbitLEar.draw(rabbitCenter + ofVec2f(150/jpgTimes, -850/jpgTimes),243/jpgTimes,400/jpgTimes);
    RabbitREar.draw(rabbitCenter + ofVec2f(400/jpgTimes, -840/jpgTimes),306/jpgTimes,400/jpgTimes);
    RabbitHead.draw(rabbitCenter + ofVec2f(-100/jpgTimes, -500/jpgTimes),716/jpgTimes,526/jpgTimes);
    RabbitBody.draw(rabbitCenter,468/jpgTimes,551/jpgTimes);
}

void ofApp::drawRabForwardA(){
    
}

void ofApp::drawRabForwardB(){
    
}

//-----------------------------------

void ofApp::drawFirstScene(){
    SceneIntro.draw(0,0,1920,1080);//(jpgTimes/5
    
}

//-----------------------------------

void ofApp::keyPressed(int key){
    int step = 10;
    if(key == 'a'){
        foxCenter.x = foxCenter.x - step;
        foxCenterPosX = foxCenterPosX - step;
        
        foxCenter.y = foxCenter.y - (step - 6);
        foxCenterPosY = foxCenterPosY - (step - 6);
        
    }
//    if(key == 'd'){
//        foxCenter.x = foxCenter.x + step;
//        foxCenterPosX = foxCenterPosX + step;
//
//        foxCenter.y = foxCenter.y + (step - 6);
//        foxCenterPosY = foxCenterPosY + (step - 6);
//
//    }

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

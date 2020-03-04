#include "ofApp.h"

//Basic draw
int w = 500;
int h = 250;
int r = 50;
int CenterPosX = 500; // changed screen size
int CenterPosY = 500;
int CenterR = 200;
int CenterR1 = CenterR/4;

//Start Point
float happyPosX = 1000/6;//ofGetWidth()/6;
float happyPosY = 1000/6;
float sadPosX = 1000*5/6;
float sadPosY = 1000/6;
float angryPosX = 1000/6;
float angryPosY = 1000*5/6;
float suprisePosX = 1000*5/6;
float suprisePosY = 1000*5/6;

//control
int slideNumber = 0;
float currentTime = 0;
float CountFrame = ofGetFrameNum();

//Sound play
ofSoundPlayer drum;

//Move
//int startPosX = CenterPosX;
//int startPosY = CenterPosY;
//int endHappyPosX = CenterPosX - CenterR/6;
//int endHappyPosY = CenterPosY-CenterR1*2.5/5;
//
//ofVec2f centerEye(startPosX,startPosY);
//ofVec2f happyEye(endHappyPosX,endHappyPosY);
//ofVec2f sadEye(-endHappyPosX,endHappyPosY);
//ofVec2f angryEye(endHappyPosX,-endHappyPosY);
//ofVec2f supriseEye(-endHappyPosX,-endHappyPosY);



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0,140,147);
    
    drum.load("drum.wav");

}

//--------------------------------------------------------------
void ofApp::update(){
    if((ofGetFrameNum() % 120) == 0){
            drum.play();
        
        if(slideNumber > 2){
            slideNumber = 0;
        }else{
            slideNumber++;
            currentTime = ofGetFrameNum();
            cout<<currentTime<<endl;
            
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    drawCenterEye(10,10);
    
    if(slideNumber == 0){
        drawHappy(10,10);
    }
    
    if(slideNumber == 1){
        drawSad(20,20);

    }
    
    if(slideNumber == 2){
        drawAngry(30, 30);
    }
    
    if(slideNumber == 3){
        drawSuprise(40, 40);
    }
    
}
void ofApp::drawCenterEye(int x, int y){
    //Sun outside
    ofSetLineWidth(8.0);
    ofSetColor(0,100,100);

    ofPolyline sun;
    sun.addVertex(CenterPosX,CenterPosY-CenterR); // 1
    sun.addVertex(CenterPosX+CenterR/4,CenterPosY-CenterR*2/4); // 2
    sun.addVertex(CenterPosX+CenterR*3/4,CenterPosY-CenterR*3/4); // 3
    sun.addVertex(CenterPosX+CenterR*2/4,CenterPosY-CenterR/4); // 4
    sun.addVertex(CenterPosX+CenterR,CenterPosY);// 5
    sun.addVertex(CenterPosX+CenterR*2/4,CenterPosY+CenterR/4); // 4 - 1
    sun.addVertex(CenterPosX+CenterR*3/4,CenterPosY+CenterR*3/4); // 3 - 1
    sun.addVertex(CenterPosX+CenterR/4,CenterPosY+CenterR*2/4); // 2 - 1
    sun.addVertex(CenterPosX,CenterPosY+CenterR); // 1 - 1
    sun.addVertex(CenterPosX-CenterR/4,CenterPosY+CenterR*2/4); // 2 - 2
    sun.addVertex(CenterPosX-CenterR*3/4,CenterPosY+CenterR*3/4); // 3 - 2
    sun.addVertex(CenterPosX-CenterR*2/4,CenterPosY+CenterR/4); // 4 - 2
    sun.addVertex(CenterPosX-CenterR,CenterPosY);// 5 - 2
    sun.addVertex(CenterPosX-CenterR*2/4,CenterPosY-CenterR/4); // 4 - 3
    sun.addVertex(CenterPosX-CenterR*3/4,CenterPosY-CenterR*3/4); // 3 - 3
    sun.addVertex(CenterPosX-CenterR/4,CenterPosY-CenterR*2/4); // 2 - 3
    sun.addVertex(CenterPosX,CenterPosY-CenterR); // 1 - 3

    sun.close();
    sun.draw();
    ofSetColor(255,255,255);
    ofDrawCircle(CenterPosX,CenterPosY,CenterR/2);

    //Center Eye
    ofSetLineWidth(6.0);
    ofSetColor(0,100,100);
    ofPolyline eye;
    eye.addVertex(CenterPosX,CenterPosY-CenterR1); // 1
    eye.addVertex(CenterPosX+CenterR/6,CenterPosY-CenterR1*4/5); // 2
    eye.addVertex(CenterPosX+CenterR/3,CenterPosY-CenterR1*2.5/5); // 3
    eye.addVertex(CenterPosX+CenterR/2,CenterPosY); //4
    eye.addVertex(CenterPosX+CenterR/3,CenterPosY+CenterR1*2.5/5); // 3 - 1
    eye.addVertex(CenterPosX+CenterR/6,CenterPosY+CenterR1*4/5); // 2 - 1
    eye.addVertex(CenterPosX,CenterPosY+CenterR1); // 1 - 1
    eye.addVertex(CenterPosX-CenterR/6,CenterPosY+CenterR1*4/5); // 2 - 2
    eye.addVertex(CenterPosX-CenterR/3,CenterPosY+CenterR1*2.5/5); // 3 - 2
    eye.addVertex(CenterPosX-CenterR/2,CenterPosY); //4 - 2
    eye.addVertex(CenterPosX-CenterR/3,CenterPosY-CenterR1*2.5/5); // 3 - 3
    eye.addVertex(CenterPosX-CenterR/6,CenterPosY-CenterR1*4/5); // 2 - 3
    eye.addVertex(CenterPosX,CenterPosY-CenterR1); // 1 - 3

    eye.draw();
    //Eyeball
    
    ofDrawCircle(CenterPosX, CenterPosY,40);
    

}

//void ofApp::moveCH(){
//
//    float distanceCH = centerEye.distance(happyEye);
//    float vCH = distanceCH / 120;
//
//    float eyeBalPosX = startPosX;
//    float eyeBalPosY = startPosY;
//
//    eyeBalPosX += vCH;
//    eyeBalPosY += vCH;
//
//    ofSetColor(0, 0, 0);
//    ofDrawCircle(eyeBalPosX, eyeBalPosY,15);
//}

void ofApp::drawHappy(int x, int y){
    
    //Peter's head
    ofSetCircleResolution(100);
    ofSetColor(255,67,152);
    ofDrawCircle(happyPosX,happyPosY,r);
    
    //Peter's eye
    ofSetColor(255,255,255);
    ofDrawEllipse(happyPosX-0.5*r, happyPosY, 35, 25);
    ofSetColor(42,64,238);
    ofDrawCircle(happyPosX-0.5*r,happyPosY,10);

    ofSetColor(255,255,255);
    ofDrawEllipse(happyPosX+0.5*r, happyPosY, 35, 25);
    ofSetColor(42,64,238);
    ofDrawCircle(happyPosX+0.5*r,happyPosY,10);

    //Peter's mouth
    ofSetColor(255,210,0);
    ofDrawBezier(happyPosX-r/4, happyPosY+r/4, happyPosX-r/4+5, happyPosY+r/4+10,happyPosX-r/4+r/2-5, happyPosY+r/4+10,happyPosX-r/4+r/2, happyPosY+r/4);


}

void ofApp::drawSad(int x, int y){
    //Peter's head
    ofSetCircleResolution(100);
    ofSetColor(255,67,152);
    ofDrawCircle(sadPosX,sadPosY,r);
    
    ofSetColor(42,64,238);
    ofDrawBezier(sadPosX-r/4, sadPosY+r/4, sadPosX-r/4+5, sadPosY+r/4-10,sadPosX-r/4+r/2-5, sadPosY+r/4-10,sadPosX-r/4+r/2, sadPosY+r/4); //Sadness
    
    ofSetColor(255,255,255);
    ofDrawEllipse(sadPosX-0.5*r, sadPosY, 35, 15);
    ofSetColor(42,64,238);
    ofDrawCircle(sadPosX-0.5*r+3,sadPosY+3,7);
    
    ofSetColor(255,255,255);
    ofDrawEllipse(sadPosX+0.5*r, sadPosY, 35, 15);
    ofSetColor(42,64,238);
    ofDrawCircle(sadPosX+0.5*r+3,sadPosY+3,7);
}

void ofApp::drawAngry(int x, int y){
    //Peter's head
    ofSetCircleResolution(100);
    ofSetColor(255,67,152);
    ofDrawCircle(angryPosX,angryPosY,r);
    
    ofSetColor(0,0,0);
    ofDrawBezier(angryPosX-r/4, angryPosY+r/2, angryPosX-r/4+5, angryPosY+r/4-10,angryPosX-r/4+r/2-5, angryPosY+r/4-10,angryPosX-r/4+r/2, angryPosY+r/2); //Angry
            
    ofSetColor(255,255,255);
    ofDrawEllipse(angryPosX-0.5*r, angryPosY, 40, 35);
    ofSetColor(42,64,238);
    ofDrawCircle(angryPosX-0.5*r,angryPosY-8,10);
            
    ofSetColor(255,255,255);
    ofDrawEllipse(angryPosX+0.5*r, angryPosY, 40, 35);
    ofSetColor(42,64,238);
    ofDrawCircle(angryPosX+0.5*r,angryPosY-8,10);
}

void ofApp::drawSuprise(int x, int y){
    //Peter's head
    ofSetCircleResolution(100);
    ofSetColor(255,67,152);
    ofDrawCircle(suprisePosX,suprisePosY,r);
    
    ofSetColor(164,255,0);
    ofDrawEllipse(suprisePosX, suprisePosY+r/2, 25, 35);//suprise
    
    ofSetColor(255,255,255);
    ofDrawEllipse(suprisePosX-0.5*r, suprisePosY, 35, 35);
    ofSetColor(42,64,238);
    ofDrawCircle(suprisePosX-0.5*r,suprisePosY,10);
    
    ofSetColor(255,255,255);
    ofDrawEllipse(suprisePosX+0.5*r, suprisePosY, 35, 35);
    ofSetColor(42,64,238);
    ofDrawCircle(suprisePosX+0.5*r,suprisePosY,10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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

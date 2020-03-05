#include "ofApp.h"
ofVec2f HaoCenter;
ofVec2f HaoShoot;
ofVec2f currVec(0,0);
ofVec2f targetVec;
ofVec2f People(ofRandom(0,1200),ofRandom(0,1200));

int haoR = 10;
int starR = 10;
int PeopleR = ofRandom(5,20);

int speedX = ofRandom(1,5);
int speedY = ofRandom(1,5);

int rotateDegrees = 0;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0,32,122);
    
    title = "Where are you?";
    intro = "Opss! I found something...";
    font1.load("Prompt-Bold.ttf",35);
    font2.load("Prompt-ExtraLight.ttf",20);
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA); // higher precision alpha (no artifacts)
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();


}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
    ofFill();
    ofSetColor(0,32,122,50);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());

    drawStar();
    drawHao();
    drawShoot();
    drawStringTitle();
//    drawSurronding();
    drawPedestrain();
    
    fbo.end();
    //
    
    People.x = People.x + speedX;
    People.y = People.y + speedY;
    
    if(People.x > ofGetWidth() || People.x < 0){
        People.x = ofRandom(200,1000);
        People.y = 0;
        speedX = ofRandom(1,5);
        speedY = ofRandom(1,5);
        PeopleR = ofRandom(5,20);

    }
    if(People.y > ofGetHeight() || People.y < 0){
        People.y = ofRandom(200,1000);
        People.x = 0;
        speedX = ofRandom(1,5);
        speedY = ofRandom(1,5);
        PeopleR = ofRandom(5,20);

    }
    //bullet move
    if(targetVec != currVec){
        currVec = currVec + (targetVec - currVec) * 0.3;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofSetColor(255, 0, 0);
//    ofDrawCircle(HaoCenter,40);
    if (useFbo) {
        fbo.draw(0,0);
       } else {
        drawStar();
        drawHao();
        drawShoot();
        drawStringTitle();
//        drawSurronding();
        drawPedestrain();
       }
}

void ofApp::drawHao(){
    //Body
    ofSetColor(255,100,100);
    ofDrawTriangle(HaoCenter+ofVec2f(0,-50),HaoCenter+ofVec2f(-40,40),HaoCenter+ofVec2f(40,40));
    //Eye
    ofSetColor(255);
    ofDrawEllipse(HaoCenter+ofVec2f(-15,5), 2*haoR, haoR);
    ofDrawEllipse(HaoCenter+ofVec2f(15,5), 2*haoR, haoR);
    //EyeBall
    ofSetColor(53,25,157);
    ofDrawCircle(HaoCenter+ofVec2f(-10,5), 0.6*haoR);
    ofDrawCircle(HaoCenter+ofVec2f(20,5), 0.6*haoR);
    //nose
    ofSetColor(255,50,50);
    ofDrawTriangle(HaoCenter,HaoCenter+ofVec2f(10,20),HaoCenter+ofVec2f(0,20));
    
}

void ofApp::drawStar(){
    ofVec2f StarCenter(ofGetWidth()*0.9,ofGetHeight()*0.9);
    ofVec2f RotateStar = (StarCenter+ofVec2f(0,-15)).rotate(rotateDegrees++,StarCenter);
    
    ofSetColor(255);
    ofDrawTriangle(RotateStar+ofVec2f(-25,20),RotateStar+ofVec2f(-3,0),RotateStar+ofVec2f(-25,-20));
    ofDrawTriangle(RotateStar+ofVec2f(25,20),RotateStar+ofVec2f(3,0),RotateStar+ofVec2f(25,-20));

}

void ofApp::drawShoot(){
    ofSetColor(255, 194, 20);
    ofDrawCircle(currVec, 5);
}

void ofApp::drawSurronding(){
    ofVec2f surCenter(ofGetWidth()/3, ofGetHeight()/2);
    //Buildings
    ofSetColor(103, 205,207);
    ofDrawRectangle(surCenter, 70,60);
    ofDrawRectangle(surCenter+ofVec2f(500,-180),150,300);
    ofDrawRectangle(surCenter+ofVec2f(40,80),100,100);
}

void ofApp::drawPedestrain(){
    ofSetColor(255,205,80);
    ofDrawCircle(People,PeopleR);
}

void ofApp::drawStringTitle(){
    ofSetColor(255);
    font1.drawString(title, ofGetWidth() * 0.08, ofGetHeight() * 0.9);
    font2.drawString(intro, ofGetWidth() * 0.08, ofGetHeight() * 0.94);

}






//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int step = 10;
    if(key == 'w') HaoCenter.y = HaoCenter.y - step;
    if(key == 's') HaoCenter.y = HaoCenter.y + step;
    if(key == 'a') HaoCenter.x = HaoCenter.x - step;
    if(key == 'd') HaoCenter.x = HaoCenter.x + step;
    if(key == 'f'){
        useFbo = !useFbo;
        fbo.begin();
            ofClear(255,255,255, 0);
        fbo.end();
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    targetVec.x = x;
    targetVec.y = y;
//    HaoCenter.x = x;
//    HaoCenter.y = y;

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    targetVec.x = x;
    targetVec.y = y;
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

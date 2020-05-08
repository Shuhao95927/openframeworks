#include "ofApp.h"
#include "ofxJSON.h"

ofxJSONElement root;

//int elapsedTime = ofGetElapsedTimeMillis();

int ASTposX = 0;
int ASTposY = 0;
ofVec2f AST(ASTposX,ASTposY);

int earthPosX, earthPosY;
ofVec2f earthCenter(earthPosX,earthPosY);

int ASTspeed = ofRandom(1,10);
int missDistance = 0;

int countNum = 0;
int rotateDegrees = 0;
int asteroidVelocity = 0;

bool pressedKey = false;

int asteroidID[281]; //how many asteroid data = 281

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(10);
    
    font1.load("Prompt-Bold.ttf",35);
    font2.load("Prompt-ExtraLight.ttf",20);
    
    std::string url = "https://api.nasa.gov/neo/rest/v1/neo/3542519?api_key=gf31JndEhgfWs2EXpnH40eyRLccnweVPqqjqOIip";
    bool parsingSuccessful = root.open(url);
    if(parsingSuccessful){
        ofLogNotice("ofApp::setup") << root.getRawString(true);
    }else{
        ofLogNotice("ofApp::setup") << "Failed to pare JSON.";
    }
    
    gui.setup();
    gui.add(size.setup("Size of the object (km)",10,5,26));// 115,260 m
    gui.add(velocity.setup("Velocity of the object (km/s)",30,10,100));// km/s
    gui.add(missDistance.setup("Miss distance (km)",50,0,100)); // ???
    gui.add(color.setup("Color of the system",ofColor(255,100,100),ofColor(0,0,0),ofColor(255,255,255)));
    gui.add(shape.setup("Shape of the object - Next one"));
    
    // size
}

//--------------------------------------------------------------
void ofApp::update(){
    //-----
    if(pressedKey == true){
        ASTposX +=  asteroidVelocity;
        ASTposY = ASTposX * ofGetHeight()/ofGetWidth() - missDistance;
//      ASTposX += missDistance * asteroidVelocity;
//      ASTposY += 1 * asteroidVelocity; //d
    }
    
}

std::ostringstream text;

//--------------------------------------------------------------
void ofApp::draw(){
    
//    std::string summary = root["close_approach_data"][1]["close_approach_date"].asString();
//    intro = root["close_approach_data"][1]["close_approach_date"].asString();
    
    gui.draw();
    drawEarth();
//    cout << countFrame << endl;
    float countFrame = ofGetFrameNum();
//    cout << countFrame << endl;
    
    ofSetColor(255,100,100);
    ofDrawBitmapString(text.str(),20,40);
    
    if(pressedKey == true){
        drawObjects();
    }

    
}


void ofApp::drawEarth(){
    
    ofVec2f earthCenter(ofGetWidth()/2,ofGetHeight()/2); //
    
    ofVec2f rotateLunar = earthCenter + ofVec2f(50,50);
    
    ofVec2f lunar = rotateLunar.rotate(rotateDegrees++,earthCenter);
    
    ofSetColor(255,50);
    ofDrawEllipse(earthCenter,100,100);
    
    ofSetColor(255);
    ofDrawEllipse(lunar,10,10);
    
    ofSetColor(50,50,255);
    ofDrawEllipse(earthCenter,40,40);
    
}

void ofApp::drawObjects(){
    
//    int asteroidSizeMin = ofToInt(root["estimated_diameter"]["kilometers"]["estimated_diameter_min"].asString())*100;
//    int asteroidSizeMax = ofToInt(root["estimated_diameter"]["kilometers"]["estimated_diameter_max"].asString())*100;
     
    
    asteroidVelocity = ofToInt(root["close_approach_data"][countNum]["relative_velocity"]["kilometers_per_second"].asString()) / 5;
    missDistance = ofToInt(root["close_approach_data"][countNum]["miss_distance"]["lunar"].asString());
    
//  ofDrawEllipse(ofRandom(ofGetWidth()), 100, 50, 50);
//    ofVec2f startPointA(0,0);
//    ofVec2f startPointB(0,ofGetHeight());
//    ofVec2f startPointC(ofGetWidth(),0);
//    ofVec2f startPointD(ofGetWidth(),ofGetHeight());
//
//    ofVec2f startPoints [] = {startPointA,startPointB,startPointC,startPointD};
    ofSetColor(color);
    ofDrawEllipse(ASTposX, ASTposY, size, size);
    //startPoints[int(ofRandom(4))]
//    cout << ASTposX << endl;
}

void ofApp::distDetect(){
    float distance = AST.distance(earthCenter);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ' && countNum <= 281){
        
        if(ASTposY >= ofGetHeight()){
            countNum++;
            ASTposX = 0;
            ASTposY = 0;
        }
        
        text.str("");
        
        std::string summary = root["close_approach_data"][countNum]["close_approach_date"].asString();
        text << "Time: " << summary << "Count Number" << countNum;
//        cout << countNum << endl;
        font1.drawString(summary, ofGetWidth() * 0.08, ofGetHeight() * 0.9);
        
        pressedKey = true;
        cout << "This is "<< countNum <<"times, and the velocity is " << asteroidVelocity << endl;

    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
//    if(key == ' '){
//        pressedKey = false;
//        cout<< pressedKey << endl;
//    }

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

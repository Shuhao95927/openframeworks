#include "ofApp.h"
#include "ofxJSON.h"

ofxJSONElement root;

int ASTposX;
int ASTposY;
ofVec2f AST(ASTposX,ASTposY);

int ASTspeed = ofRandom(1,10);
int missDistance = 0;

int countNum = 0;
int rotateDegrees = 0;
int asteroidVelocity = 0;

int detectWaveSize = 0;
int explosionSize = 15;

ofSoundPlayer laser;
ofSoundPlayer music;


bool pressedKey = false;
bool detect = false;

int asteroidID[281]; //how many asteroid data = 281

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(10);
    
    font1.load("Prompt-Bold.ttf",10);
    font2.load("Prompt-ExtraLight.ttf",10);
    
    
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
//    gui.add(shape.setup("Shape of the object - Next one"));
    
    laser.load("laser.wav");
    music.load("LST - Sun In The Screen.mp3");
        
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA); // higher precision alpha (no artifacts)
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    music.setLoop(true);
    music.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    //-----
    if(pressedKey == true){
        ASTposX +=  asteroidVelocity;
        ASTposY = ASTposX * ofGetHeight()/ofGetWidth() - missDistance;
        AST = ofVec2f(ASTposX,ASTposY);
        
        if(detectWaveSize <= 200){
            detectWaveSize = detectWaveSize + 5;
        }else{
            detectWaveSize = 0;
        }
        if(detect == true){
            if(explosionSize <= 30){
                explosionSize = explosionSize + 1.5;
            }
        }else{
            explosionSize = 15;
        }
//        cout << AST << endl;

    }
    
    fbo.begin();
    ofFill();
    ofSetColor(0,25);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    drawStars();
    
    drawObjects();
//    distDetect();
    drawEarth();
    
    fbo.end();
    
}
std::ostringstream text;

//--------------------------------------------------------------
void ofApp::draw(){
    
    gui.draw();
    float countFrame = ofGetFrameNum();
    
    fbo.draw(0,0);
    
    
    if(pressedKey == true){
        drawObjects();
        distDetect();
        drawIntro();
    }
    
    drawEarth();
    drawStars();

}


void ofApp::drawEarth(){
    
    ofVec2f earthCenter(ofGetWidth()/2,ofGetHeight()/2); //
    
    ofVec2f rotateLunar = earthCenter + ofVec2f(50,50);
    
    ofVec2f lunar = rotateLunar.rotate(rotateDegrees++,earthCenter);
    
    ofSetCircleResolution(100);
    ofSetColor(100,200-detectWaveSize);
    ofDrawEllipse(earthCenter,detectWaveSize,detectWaveSize);
    
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

    ofSetColor(color);
    ofDrawEllipse(ASTposX, ASTposY, size, size);
    //startPoints[int(ofRandom(4))]
//    cout << ASTposX << endl;
}

void ofApp::distDetect(){
    float distance = AST.distance(ofVec2f(ofGetWidth()/2,ofGetHeight()/2));
    cout<< distance << endl;
    if(distance <= 120){
        detect = true;
        if(ASTposX <= ofGetWidth()/2){
            laser.play();
            ofSetColor(0,200,255);
            ofSetLineWidth(2);
            ofDrawLine(ASTposX,ASTposY,ofGetWidth()/2,ofGetHeight()/2);
            size = 0;
            
            ofSetColor(255,200,0, 240 - explosionSize*8);
            ofDrawSphere(ASTposX, ASTposY, explosionSize);
            ofSetColor(255,255,0, 240 - explosionSize*8);
            ofDrawSphere(ASTposX, ASTposY, explosionSize-12);
        }
    }else{
        detect = false;
    }
    
}

void ofApp::drawIntro(){
    intro = "The close approch date is " + root["close_approach_data"][countNum]["close_approach_date"].asString() + "\n" + "The relative velocity is " + root["close_approach_data"][countNum]["relative_velocity"]["kilometers_per_second"].asString() + " km / s" + "\n" + "The miss distance is " + root["close_approach_data"][countNum]["miss_distance"]["kilometers"].asString() + " km";
    
    ofSetColor(255);
    font1.drawString(intro, ofGetWidth() * 0.03, ofGetHeight() * 0.9);
}

void ofApp::drawStars(){
    int sx,sy;
    
    if(ofGetFrameNum() % 6 == 0){
        sx = ofRandom(ofGetWidth());
        sy = ofRandom(ofGetHeight());
    }
        ofVec2f starPos(sx,sy);
        ofSetColor(255);
        ofDrawSphere(starPos.x, starPos.y, ofRandom(1,3));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ' && countNum <= 281){
        
        if(ASTposY >= ofGetHeight()){
            countNum++;
            ASTposX = 0;
            ASTposY = 0;
            size = 10;
//            cout << AST << endl;

        }
        
        pressedKey = true;
        time = ofGetElapsedTimeMillis();

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

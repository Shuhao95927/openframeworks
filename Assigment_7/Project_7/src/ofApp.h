#pragma once
#include "ofxGui.h"


#include "ofMain.h"

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
    
    void rotateEmotionPressed();
    void changeBGMV();
    void exit();
   
    void drawHappy();
    void drawSad();
    void drawSuprise();
    void drawAngry();
    
    
    ofxPanel gui;
    ofxFloatSlider soundVolume;
    ofxButton rotateEmotion;
    ofxVec2Slider faceCenter;
    ofxColorSlider color;
    ofxIntSlider emotionDegree;
    ofxLabel infoBroad;
    
    
    
		
};

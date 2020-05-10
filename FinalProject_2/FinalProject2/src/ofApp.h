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
		
    void drawEarth();
    void drawObjects();
    void distDetect();
    void drawIntro();
    void drawStars();
    uint64_t time;
    
    ofTrueTypeFont font1;
    ofTrueTypeFont font2;
    string intro;
    
    ofxPanel gui;
    ofxFloatSlider size;
    ofxFloatSlider velocity;
    ofxFloatSlider missDistance;
    ofxColorSlider color;
//    ofxButton shape;
    
    ofFbo fbo;

};

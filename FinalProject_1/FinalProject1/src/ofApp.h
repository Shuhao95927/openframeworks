#pragma once

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
    
    //-------------------------
    int mouseX;
    int mouseY;
    int shotSize = 100;
    int alpha = 255;
    uint64_t time;
    
    void drawCameraShot();
    //-------------------------
    
    void drawFoxDef();
    void drawFoxStand();
    void drawFoxForwardA();
    void drawFoxForwardB();
    
    void drawFoxArmsA1(); //Arms - in main scene - fox
    
    void drawFoxEyeA();//open
    void drawFoxEyeB();//close
    
    //-------------------------
    
    void drawRabDef();
    void drawRabStand();
    void drawRabForwardA();
    void drawRabForwardB();
    
    void drawRabArms(); //Arms - in main scene - fox
    
    void drawRabEyeA();//open
    void drawRabEyeB();//close
    
    //-------------------------

    void drawFoxEyeA1();//open - in main scene - fox
    void drawRabEyeA1();//open - in main scene - rab
    
    void drawFoxEyeB1();//close - in main scene - fox
    void drawRabEyeB1();//close - in main scene - rab

    //-------------------------

    void drawFirstScene();
    void drawMainSceneA();

    
    bool useFbo = false;
    ofFbo fbo;

		
};

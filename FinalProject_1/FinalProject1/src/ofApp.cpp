#include "ofApp.h"


int foxCenterPosX = 1350;
int foxCenterPosY = 560;
int foxStandCenterPosX = 1600;
int foxStandCenterPosY = 800;
int foxFinalPosX = 480 - 170;
int foxFinalPosY = 530;

int foxEyeR = 15;

//define the fox's arm in the main scene
int foxArmSTX;
int foxArmSTY;
int foxArmSMX;
int foxArmSMY;
int foxArmEMX;
int foxArmEMY;
int foxArmETX;
int foxArmETY;
//

int rabCenterPosX = 1200;
int rabCenterPosY = 500;
int rabStandCenterPosX = 1300;
int rabStandCenterPosY = 630;
int rabFinalPosX = 1440 - 100;
int rabFinalPosY = 600;

int rabEyeR = 14;

int jpgTimes = 6;

//scene switch
int movePosX;

int detectWaveSize = 0;
int rotateDegrees = 0;
int rotateDegreesA = 100;
int rotateDegreesB = 80;

ofColor BG1(190,233,255);


bool shot = false;


//control
//int Current_elapsedTime = ofGetElapsedTimeMillis();
int slideNumber = 0;
float currentTime = 0;
float countFrame = ofGetFrameNum();

ofImage FoxHead;
ofImage FoxBody;
ofImage FoxLowLimb;
ofImage FoxShoe;
ofImage FoxRHdef; //Default right hand
ofImage FoxLHdef; //Default left hand
ofImage FoxStandRH;
ofImage FoxStandLH;
ofImage FoxCamera;
ofVec2f foxCenter(foxCenterPosX,foxCenterPosY);
ofVec2f foxStandCenter(foxStandCenterPosX, foxStandCenterPosY);
ofVec2f foxFinalCenter(foxFinalPosX,foxFinalPosY);

ofImage RabbitHead;
ofImage RabbitBody;
ofImage RabbitREar;
ofImage RabbitLEar;
ofImage RabbitRHdef;
ofImage RabbitLHdef;
ofImage RabbitShoe;
ofVec2f rabbitCenter(rabCenterPosX, rabCenterPosY);
ofVec2f rabbitStandCenter(rabStandCenterPosX,rabStandCenterPosY);
ofVec2f rabFinalCenter(rabFinalPosX,rabFinalPosY);


ofImage SceneIntro;// First scene to introduce the character and backgrond.
ofImage SceneIntroA,SceneIntroB,SceneIntroC;
ofImage SceneMain,SceneMainA,SceneMainB,SceneMainC;
ofImage SceneLastA,SceneLastB;


ofVec2f currVecFox(0,0);
ofVec2f targetVecFox;

ofVec2f foxEyePos;
ofVec2f foxEyePosA;
ofVec2f foxEyePosLast;
ofVec2f foxEyePosLastA;


ofVec2f rabEyePos;
ofVec2f rabEyePosA;
ofVec2f rabEyePosLast;
ofVec2f rabEyePosLastA;




//Sound
ofSoundPlayer doveFault;
ofSoundPlayer StopTheWorld;
ofSoundPlayer cameraSound;




//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetCircleResolution(100);
    
    fbo.allocate(ofGetWidth(), ofGetHeight(),GL_RGBA);
    fbo.begin();
    ofClear(255,255,255,0);
    fbo.end();
    
    FoxHead.load("character/foxHead.png"); // 927 * 751
    FoxBody.load("character/foxBody.png"); // 492 * 499
    FoxLowLimb.load("character/foxLowerlimb.png"); // 387 * 266
    FoxShoe.load("character/foxShoe.png"); // 135 * 95
    FoxRHdef.load("character/foxRHdef.png"); // 87 * 113
    FoxLHdef.load("character/foxLHdef.png"); // 87 * 113
    FoxStandRH.load("character/foxStandRHand.png"); // 84 * 113
    FoxStandLH.load("character/foxStandLHand.png"); // 84 * 113
    FoxCamera.load("character/camera.png");
    
    RabbitHead.load("character/rabbitHead.png");
    RabbitBody.load("character/rabbitBody.png");
    RabbitShoe.load("character/rabbitShoe.png");
    RabbitREar.load("character/rabbitREar.png");
    RabbitLEar.load("character/rabbitLEar.png");
    RabbitRHdef.load("character/rabbitRHdef.png"); // 80 * 80
    RabbitLHdef.load("character/rabbitLHdef.png"); // 80 * 80

    
    SceneIntro.load("scene/Scene1-1.png");
    SceneIntroA.load("scene/scene1-01.png");
    SceneIntroB.load("scene/scene1-02.png");
    SceneIntroC.load("scene/scene1-03.png");
    SceneMain.load("scene/scene2.jpg");
    SceneMainA.load("scene/scene2-1.png");
    SceneMainB.load("scene/scene2-2.png");
    SceneMainC.load("scene/scene2-3.png");
    SceneLastA.load("scene/scene3-Center.png");
    SceneLastB.load("scene/scene3-BG.png");

    
    doveFault.load("music/Lee MacDougall,Sharon Wheatley - The Dover Fault.mp3");
    StopTheWorld.load("music/Lee MacDougall,'Come From Away' Company,Sharon Wheatley - Stop the World.mp3");
    cameraSound.load("music/cameraClick.mp3");
    font1.load("fonts/Prompt-Bold.ttf",15 );
    font2.load("fonts/Prompt-ExtraLight.ttf",10);
    
    doveFault.play();
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA); // higher precision alpha (no artifacts)
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();

}

//--------------------------------------------------------------
void ofApp::update(){
   

    if(ofGetFrameNum() % 60 == 0){
        if(slideNumber > 3){
            slideNumber = 1;
        }else{
            slideNumber++;
            currentTime = ofGetFrameNum();
//            cout<<currentTime<<endl;
        }

    }

    if(targetVecFox != currVecFox){
        currVecFox = currVecFox + (targetVecFox - currVecFox) * 0.3;
    }

    if (shot == true){

        if(ofGetElapsedTimeMillis() >= time + 200){
            shot = false;
        }
    }
    
    if(detectWaveSize <= 200){
               detectWaveSize = detectWaveSize + 5;
           }else{
               detectWaveSize = 0;
           }
    
    cout<<ofGetElapsedTimeMillis()<<endl;
    
    fbo.begin();
    ofFill();
    ofSetColor(0,25);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    drawStars();
    drawEndScene();
    fbo.end();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(BG1);
    

    if(ofGetElapsedTimeMillis()/1000 >= 32 && ofGetElapsedTimeMillis()/1000<= 90 && foxCenterPosX + 751/jpgTimes <= 0){ //1740
        doveFault.stop();
        
        drawMainSceneA();
        
        if(slideNumber == 1){
            drawFoxStand();
            drawFoxArmsA1();
            drawFoxEyeB1();
        }else{
            drawFoxStand();
            drawFoxArmsA1();
            drawFoxEyeA1();
        }
        
        if(slideNumber == 3){
            drawRabStand();
            drawRabEyeB1();
        }else{
            drawRabStand();
            drawRabEyeA1();
        }
        
    }else{
        drawFirstScene(); //1st Scene
    }
    
    if(currentTime == 1740){
        StopTheWorld.play();
    }
    
    if(currentTime < 600){
        drawFoxForwardA();
        drawRabForwardA();

    }
    
    
    if(currentTime >= 600){
        if(slideNumber == 0){
            drawFoxForwardA();
            drawRabForwardA();
            drawRabEyeA();

    }
    
        if(slideNumber == 1){
            drawFoxForwardB();
            drawRabForwardB();
    }
    
        if(slideNumber == 2){
            drawFoxForwardA();
            drawRabForwardA();

    }
    
        if(slideNumber == 3){
            drawFoxForwardB();
            drawRabForwardB();

    }
        if(slideNumber == 4){
            drawFoxForwardA();
            drawRabForwardA();
        }
}


    if(ofGetElapsedTimeMillis()/1000 >= 32 && ofGetElapsedTimeMillis()/1000 <= 90){
        drawCameraShot();
    }else if(ofGetElapsedTimeMillis()/1000 > 90 && ofGetElapsedTimeMillis()/1000 <= 121){
        SceneLastB.draw(0,0, 1920, 1080);
        SceneLastA.draw(ofGetWidth()/2-1753/10,ofGetHeight()/2-1877/10,1753/5,1877/5);
        
        ofFill();
        ofSetColor(255);
        ofDrawSphere(ofGetWidth()* 1/4 - 50, ofGetHeight()/2, 100);
        ofDrawSphere(ofGetWidth()* 3/4 + 50, ofGetHeight()/2, 100);
        
        FoxHead.draw(foxFinalCenter + ofVec2f(-35, -100),927/jpgTimes * 1.5,751/jpgTimes * 1.5);
        drawFoxFinalEye();
        
        RabbitLEar.draw(rabFinalCenter + ofVec2f(150/jpgTimes * 1.5, -850/jpgTimes * 1.5),243/jpgTimes * 1.5,400/jpgTimes * 1.5);
        RabbitREar.draw(rabFinalCenter + ofVec2f(400/jpgTimes * 1.5, -840/jpgTimes * 1.5),306/jpgTimes * 1.5,400/jpgTimes * 1.5);
        RabbitHead.draw(rabFinalCenter + ofVec2f(-100/jpgTimes * 1.5, -500/jpgTimes * 1.5),716/jpgTimes * 1.5,526/jpgTimes * 1.5);
        drawRabFinalEye();
        
        ofSetColor(255,200-detectWaveSize);
        ofDrawEllipse(ofGetWidth()/2,ofGetHeight()/2,detectWaveSize,detectWaveSize);
        
    }else if(ofGetElapsedTimeMillis()/1000 > 121){
        ofFill();
        ofBackground(0);
        
        fbo.draw(0,0);
        drawStars();
        
        ofSetColor(20,190,185);
        ofDrawSphere(ofGetWidth()* 1/4 - 50, ofGetHeight()/2, 100);
        ofDrawSphere(ofGetWidth()* 3/4 + 50, ofGetHeight()/2, 100);
        
        ofSetColor(255);
        FoxHead.draw(foxFinalCenter + ofVec2f(-35, -100),927/jpgTimes * 1.5,751/jpgTimes * 1.5);
        drawFoxFinalEye();
        
        RabbitLEar.draw(rabFinalCenter + ofVec2f(150/jpgTimes * 1.5, -850/jpgTimes * 1.5),243/jpgTimes * 1.5,400/jpgTimes * 1.5);
        RabbitREar.draw(rabFinalCenter + ofVec2f(400/jpgTimes * 1.5, -840/jpgTimes * 1.5),306/jpgTimes * 1.5,400/jpgTimes * 1.5);
        RabbitHead.draw(rabFinalCenter + ofVec2f(-100/jpgTimes * 1.5, -500/jpgTimes * 1.5),716/jpgTimes * 1.5,526/jpgTimes * 1.5);
        drawRabFinalEye();
        
        drawEndScene();

    }
                                                                                                                                                //
    if(slideNumber == 3){
        drawRabDef();
        drawRabEyeB();
    }else{
        drawRabDef();
        drawRabEyeA();
    }
    
    if(slideNumber == 1){
        drawFoxDef();
        drawFoxEyeB();
    }else{
        drawFoxDef();
        drawFoxEyeA();
    }
    
    
    timeString = "Time is " + ofToString(ofGetElapsedTimeMillis()/1000);  //ofGetElapsedTimeMillis()/1000
    ofSetColor(255);
    font1.drawString(lyrics, ofGetWidth() * 0.03, ofGetHeight() * 0.9);
//    font1.drawString(timeString, ofGetWidth() * 0.03, ofGetHeight() * 0.8);
//PART1
    if(ofGetElapsedTimeMillis()/1000>32 && ofGetElapsedTimeMillis()/1000<35 ){
        lyrics = "Stop the world";
    }else if(ofGetElapsedTimeMillis()/1000>35 && ofGetElapsedTimeMillis()/1000<37){
        lyrics = "Take a picture";
    }else if(ofGetElapsedTimeMillis()/1000>37 && ofGetElapsedTimeMillis()/1000<39){
        lyrics = "Try to capture";
    }else if(ofGetElapsedTimeMillis()/1000>39 && ofGetElapsedTimeMillis()/1000<41){
        lyrics = "To ensure this moment lasts";
    }else if(ofGetElapsedTimeMillis()/1000>41 && ofGetElapsedTimeMillis()/1000<43){
        lyrics = "We're still in it, but";
    }else if(ofGetElapsedTimeMillis()/1000>43 && ofGetElapsedTimeMillis()/1000<45){
        lyrics = "In a minute -";
    }else if(ofGetElapsedTimeMillis()/1000>45 && ofGetElapsedTimeMillis()/1000<47){
        lyrics = "That's the limit -";
    }else if(ofGetElapsedTimeMillis()/1000>47 && ofGetElapsedTimeMillis()/1000<49){
        lyrics = "And this present will be past";
    }else if(ofGetElapsedTimeMillis()/1000>49 && ofGetElapsedTimeMillis()/1000<52){
        lyrics = "So here we are";
    }else if(ofGetElapsedTimeMillis()/1000>52 && ofGetElapsedTimeMillis()/1000<57){
        lyrics = "Where the world has come together";
    }else if(ofGetElapsedTimeMillis()/1000>57 && ofGetElapsedTimeMillis()/1000<61){
        lyrics = "So here she will be";
    }else if(ofGetElapsedTimeMillis()/1000>61 && ofGetElapsedTimeMillis()/1000<65){
        lyrics = "In this picture, forever";
    }else if(ofGetElapsedTimeMillis()/1000>65 && ofGetElapsedTimeMillis()/1000<89){
        lyrics = " ";//PART2
    }else if(ofGetElapsedTimeMillis()/1000>89 && ofGetElapsedTimeMillis()/1000<91){
        lyrics = "Stop the world";
    }else if(ofGetElapsedTimeMillis()/1000>92 && ofGetElapsedTimeMillis()/1000<94){
        lyrics = "Seize the moment";
    }else if(ofGetElapsedTimeMillis()/1000>94 && ofGetElapsedTimeMillis()/1000<98){
        lyrics = "But the minute he goes you're alone, and it's through";
    }else if(ofGetElapsedTimeMillis()/1000>98 && ofGetElapsedTimeMillis()/1000<100){
        lyrics = "Pinch yourself";
    }else if(ofGetElapsedTimeMillis()/1000>100 && ofGetElapsedTimeMillis()/1000<102){
        lyrics = "Tell yourself:";
    }else if(ofGetElapsedTimeMillis()/1000>102 && ofGetElapsedTimeMillis()/1000<106){
        lyrics = "You're just dreaming, that means he'll forget about you";
    }else if(ofGetElapsedTimeMillis()/1000>106 && ofGetElapsedTimeMillis()/1000<109){
        lyrics = "But here we are";
    }else if(ofGetElapsedTimeMillis()/1000>109 && ofGetElapsedTimeMillis()/1000<113){
        lyrics = "Where the continents once crashed together";
    }else if(ofGetElapsedTimeMillis()/1000>113 && ofGetElapsedTimeMillis()/1000<121){
        lyrics = "Before they went their separate ways forever, so"; //PART3
    }else if(ofGetElapsedTimeMillis()/1000>121 && ofGetElapsedTimeMillis()/1000<127){
        lyrics = "Stop the world";
    }else if(ofGetElapsedTimeMillis()/1000>127 && ofGetElapsedTimeMillis()/1000<129){
        lyrics = "From spinning 'round";
    }else if(ofGetElapsedTimeMillis()/1000>129 && ofGetElapsedTimeMillis()/1000<132){
        lyrics = "I wanna look out";
    }else if(ofGetElapsedTimeMillis()/1000>132 && ofGetElapsedTimeMillis()/1000<134){
        lyrics = "Overlooking something";
    }else if(ofGetElapsedTimeMillis()/1000>134 && ofGetElapsedTimeMillis()/1000<136){
        lyrics = "Worth taking the time";
    }else if(ofGetElapsedTimeMillis()/1000>136 && ofGetElapsedTimeMillis()/1000<138){
        lyrics = "to stop flying by (And look down)";
    }else if(ofGetElapsedTimeMillis()/1000>138 && ofGetElapsedTimeMillis()/1000<140){
        lyrics = "And look down (Stop the world)";
    }else if(ofGetElapsedTimeMillis()/1000>140 && ofGetElapsedTimeMillis()/1000<142){
        lyrics = "Stopping to stare, (And look 'round)";
    }else if(ofGetElapsedTimeMillis()/1000>142 && ofGetElapsedTimeMillis()/1000<144){
        lyrics = "And look 'round. (Stop the world)";
    }else if(ofGetElapsedTimeMillis()/1000>144 && ofGetElapsedTimeMillis()/1000<146){
        lyrics = "Just tell them, (Ahhhh) NOW";
    }else if(ofGetElapsedTimeMillis()/1000>146 && ofGetElapsedTimeMillis()/1000<148){
        lyrics = "and look down";
    }else if(ofGetElapsedTimeMillis()/1000>=148 && ofGetElapsedTimeMillis()/1000<=149){
        lyrics = "Take a picture";
    }else if(ofGetElapsedTimeMillis()/1000>149 && ofGetElapsedTimeMillis()/1000<=151){
        lyrics = "Of the scenery";
    }else if(ofGetElapsedTimeMillis()/1000>151 && ofGetElapsedTimeMillis()/1000<=152){
        lyrics = "Of a lookout";
    }else if(ofGetElapsedTimeMillis()/1000>152 && ofGetElapsedTimeMillis()/1000<=153){
        lyrics = "Of a moment";
    }else if(ofGetElapsedTimeMillis()/1000>153 && ofGetElapsedTimeMillis()/1000<=154){
        lyrics = "Which is over";
    }else if(ofGetElapsedTimeMillis()/1000>154 && ofGetElapsedTimeMillis()/1000<=156){
        lyrics = "Of the ocean";
    }else if(ofGetElapsedTimeMillis()/1000>156 && ofGetElapsedTimeMillis()/1000<158){
        lyrics = "Of the river";
    }else if(ofGetElapsedTimeMillis()/1000>158 && ofGetElapsedTimeMillis()/1000<160){
        lyrics = "Of the trees";
    }else if(ofGetElapsedTimeMillis()/1000>160 && ofGetElapsedTimeMillis()/1000<164){
        lyrics = " ";
    }else if(ofGetElapsedTimeMillis()/1000>164 && ofGetElapsedTimeMillis()/1000<168){
        lyrics = "Stop the world";
    }else if(ofGetElapsedTimeMillis()/1000>168 && ofGetElapsedTimeMillis()/1000<174){
        lyrics = "Please";
    }
}

//------------------------------//
//             Fox              //
//------------------------------//

void ofApp::drawFoxDef(){
    //draw hands
    FoxLHdef.draw(foxCenter + ofVec2f(-30,480/jpgTimes),(87+10)/jpgTimes,(113+10)/jpgTimes);
    FoxRHdef.draw(foxCenter + ofVec2f(580/jpgTimes,480/jpgTimes),(87+10)/jpgTimes,(113+10)/jpgTimes);

    //draw arms
    ofSetColor(47,189,191);
    ofSetLineWidth(12);
    ofNoFill();
    
    ofDrawBezier(foxCenterPosX + 100/jpgTimes, foxCenterPosY + 100/jpgTimes, foxCenterPosX - 30/jpgTimes, foxCenterPosY + 100/jpgTimes, foxCenterPosX - 125/jpgTimes, foxCenterPosY + 400/jpgTimes, foxCenterPosX - 21, foxCenterPosY + 500/jpgTimes);
    
    ofDrawBezier(foxCenterPosX + 370/jpgTimes, foxCenterPosY + 100/jpgTimes, foxCenterPosX + 470/jpgTimes, foxCenterPosY + 150/jpgTimes, foxCenterPosX + 600/jpgTimes, foxCenterPosY + 300/jpgTimes, foxCenterPosX + 600/jpgTimes, foxCenterPosY + 500/jpgTimes);

    //
    ofSetColor(255);
    
    FoxLowLimb.draw(foxCenter + ofVec2f(5,62),387/jpgTimes,227/jpgTimes);
    FoxBody.draw(foxCenter,492/jpgTimes,499/jpgTimes);
    FoxHead.draw(foxCenter + ofVec2f(-35, -100),927/jpgTimes,751/jpgTimes);

    ofSetColor(255);
    
}

void ofApp::drawFoxStand(){
    
    FoxLowLimb.draw(foxStandCenter + ofVec2f(5,62),387/jpgTimes,227/jpgTimes);
    FoxBody.draw(foxStandCenter,492/jpgTimes,499/jpgTimes);
    FoxHead.draw(foxStandCenter + ofVec2f(-35, -100),927/jpgTimes,751/jpgTimes);

    ofSetColor(255);
    
     //draw legs
     ofSetColor(19,84,84);
     ofSetLineWidth(15);
     ofNoFill();
     //left leg stand
     ofDrawBezier(foxStandCenterPosX + 170/jpgTimes, foxStandCenterPosY + 500/jpgTimes, foxStandCenterPosX + 100/jpgTimes, foxStandCenterPosY + 600/jpgTimes, foxStandCenterPosX + 100/jpgTimes, foxStandCenterPosY + 900/jpgTimes, foxStandCenterPosX + 170/jpgTimes, foxStandCenterPosY + 1000/jpgTimes);
     //right leg stand
     ofDrawBezier(foxStandCenterPosX + 350/jpgTimes, foxStandCenterPosY + 500/jpgTimes, foxStandCenterPosX + 280/jpgTimes, foxStandCenterPosY + 600/jpgTimes, foxStandCenterPosX + 280/jpgTimes, foxStandCenterPosY + 900/jpgTimes, foxStandCenterPosX + 350/jpgTimes, foxStandCenterPosY + 1000/jpgTimes);
     
     ofSetColor(255);

     FoxShoe.draw(foxStandCenter + ofVec2f(60/jpgTimes,1000/jpgTimes),160/jpgTimes, 120/jpgTimes);
     FoxShoe.draw(foxStandCenter + ofVec2f(240/jpgTimes,1000/jpgTimes),160/jpgTimes, 120/jpgTimes);
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

void ofApp::drawFoxEyeA(){ //open eyes
    
     ofFill();
     
     ofSetColor(255);
     ofDrawCircle(foxCenter + ofVec2f(50/jpgTimes,-120/jpgTimes), foxEyeR);
     ofDrawCircle(foxCenter + ofVec2f(340/jpgTimes,-120/jpgTimes), foxEyeR);
    
     ofSetColor(0);
     ofDrawCircle(foxCenter + ofVec2f(40/jpgTimes,-120/jpgTimes), foxEyeR-5);
     ofDrawCircle(foxCenter + ofVec2f(330/jpgTimes,-120/jpgTimes), foxEyeR-5);
     
     ofSetColor(255);
    

}

void ofApp::drawFoxEyeB(){ //close eyes
    ofSetColor(211, 184, 155);
    ofSetLineWidth(5);
    ofNoFill();
      
    ofDrawBezier(foxCenterPosX - 25/jpgTimes, foxCenterPosY - 120/jpgTimes, foxCenterPosX - 25/jpgTimes, foxCenterPosY - 50/jpgTimes, foxCenterPosX + 115/jpgTimes, foxCenterPosY - 50/jpgTimes,foxCenterPosX + 115/jpgTimes, foxCenterPosY - 120/jpgTimes );
      
    ofDrawBezier(foxCenterPosX + 280/jpgTimes, foxCenterPosY - 120/jpgTimes, foxCenterPosX + 280/jpgTimes, foxCenterPosY - 50/jpgTimes, foxCenterPosX + 420/jpgTimes, foxCenterPosY - 50/jpgTimes,foxCenterPosX + 420/jpgTimes, foxCenterPosY - 120/jpgTimes );
      
    ofSetColor(255);
    
}

void ofApp::drawFoxEyeA1(){ // Main Scene Eyes
    ofFill();
    
    ofSetColor(255);
    ofDrawCircle(foxEyePos, foxEyeR);
    ofDrawCircle(foxEyePos + ofVec2f(320/jpgTimes,0), foxEyeR);

    ofSetColor(0);
    ofDrawCircle(foxEyePosA + ofVec2f(-10/jpgTimes,0), foxEyeR-5);
    ofDrawCircle(foxEyePosA + ofVec2f(310/jpgTimes,0), foxEyeR-5);
    
    ofSetColor(255);

}

void ofApp::drawFoxEyeB1(){
    ofSetColor(211, 184, 155);
    ofSetLineWidth(5);
    ofNoFill();
      
    ofDrawBezier(foxStandCenterPosX - 25/jpgTimes, foxStandCenterPosY - 120/jpgTimes, foxStandCenterPosX - 25/jpgTimes, foxStandCenterPosY - 50/jpgTimes, foxStandCenterPosX + 115/jpgTimes, foxStandCenterPosY - 50/jpgTimes,foxStandCenterPosX + 115/jpgTimes, foxStandCenterPosY - 120/jpgTimes );
      
    ofDrawBezier(foxStandCenterPosX + 280/jpgTimes, foxStandCenterPosY - 120/jpgTimes, foxStandCenterPosX + 280/jpgTimes, foxStandCenterPosY - 50/jpgTimes, foxStandCenterPosX + 420/jpgTimes, foxStandCenterPosY - 50/jpgTimes,foxStandCenterPosX + 420/jpgTimes, foxStandCenterPosY - 120/jpgTimes );
      
    ofSetColor(255);
}

void ofApp::drawFoxFinalEye(){
    
    ofFill();
    
    ofSetColor(255);
    ofDrawCircle(foxEyePosLast + ofVec2f(23,35), foxEyeR * 1.5);
    ofDrawCircle(foxEyePosLast + ofVec2f(320/jpgTimes * 1.4 + 23,35), foxEyeR * 1.5);

    ofSetColor(0);
    ofDrawCircle(foxEyePosLastA + ofVec2f(-10/jpgTimes * 1.4 + 23,35), (foxEyeR-5) * 1.5);
    ofDrawCircle(foxEyePosLastA + ofVec2f(310/jpgTimes * 1.4 + 23,35), (foxEyeR-5) * 1.5);
    
    ofSetColor(255);

    
//    ofFill();
//
//    ofSetColor(255);
//    ofDrawCircle(rabEyePosLast + ofVec2f(7,-22), rabEyeR * 1.5);
//    ofDrawCircle(rabEyePosLast + ofVec2f(260/jpgTimes * 1.5 + 7,-22), rabEyeR * 1.5);
//
//    ofSetColor(0);
//    ofDrawCircle(rabEyePosLastA + ofVec2f(-10/jpgTimes * 1.5 + 7,-22), (rabEyeR-5)* 1.5);
//    ofDrawCircle(rabEyePosLastA + ofVec2f(250/jpgTimes * 1.5 + 7,-22), (rabEyeR-5)* 1.5);
//
//    ofSetColor(255);
}


void ofApp::drawFoxArmsA1(){

    //draw arms
    ofSetColor(47,189,191);
    ofSetLineWidth(12);
    ofNoFill();
    
    ofDrawBezier(foxArmSTX,foxArmSTY,foxArmSMX,foxArmSMY,foxArmEMX,foxArmEMY,foxArmETX,foxArmETY);
    ofDrawBezier(foxArmSTX + 300/jpgTimes,foxArmSTY,foxArmSMX + 300/jpgTimes,foxArmSMY,foxArmEMX + 300/jpgTimes,foxArmEMY,foxArmETX + 300/jpgTimes,foxArmETY);
    //
    ofSetColor(255);
    
    FoxStandLH.draw(foxArmETX - 50/jpgTimes, foxArmETY - 50/jpgTimes,(84+10)/jpgTimes,(113+10)/jpgTimes);
    FoxStandRH.draw(foxArmETX + 250/jpgTimes, foxArmETY - 50/jpgTimes,(84+10)/jpgTimes,(113+10)/jpgTimes);
    
    FoxCamera.draw(foxArmETX + 30/jpgTimes, foxArmETY - 100/jpgTimes, (305-50)/jpgTimes,(205-50)/jpgTimes);
    
}


//------------------------------//
//          Rabbit              //
//------------------------------//

void ofApp::drawRabDef(){
    //draw hands
    RabbitLHdef.draw(rabbitCenter + ofVec2f(-210/jpgTimes,480/jpgTimes),(80+10)/jpgTimes,(80+10)/jpgTimes);
    RabbitRHdef.draw(rabbitCenter + ofVec2f(630/jpgTimes,480/jpgTimes),(80+10)/jpgTimes,(80+10)/jpgTimes);
    
    //draw arms
    ofSetColor(255,173,41);
    ofSetLineWidth(13);
    ofNoFill();
    ofDrawBezier(rabCenterPosX + 100/jpgTimes, rabCenterPosY + 100/jpgTimes, rabCenterPosX - 100/jpgTimes, rabCenterPosY +200/jpgTimes, rabCenterPosX - 100/jpgTimes, rabCenterPosY + 400/jpgTimes, rabCenterPosX - 150/jpgTimes, rabCenterPosY + 500/jpgTimes);
    
    ofDrawBezier(rabCenterPosX + 380/jpgTimes, rabCenterPosY + 100/jpgTimes, rabCenterPosX + 610/jpgTimes, rabCenterPosY +200/jpgTimes, rabCenterPosX + 610/jpgTimes, rabCenterPosY + 400/jpgTimes, rabCenterPosX + 660/jpgTimes, rabCenterPosY + 500/jpgTimes);
    
    ofSetColor(255);
    
    RabbitLEar.draw(rabbitCenter + ofVec2f(150/jpgTimes, -850/jpgTimes),243/jpgTimes,400/jpgTimes);
    RabbitREar.draw(rabbitCenter + ofVec2f(400/jpgTimes, -840/jpgTimes),306/jpgTimes,400/jpgTimes);
    RabbitHead.draw(rabbitCenter + ofVec2f(-100/jpgTimes, -500/jpgTimes),716/jpgTimes,526/jpgTimes);
    RabbitBody.draw(rabbitCenter, 468/jpgTimes, 551/jpgTimes);
    
}

void ofApp::drawRabStand(){
    //
    ofSetColor(0);
    ofSetLineWidth(15);
    ofNoFill();
    
    ofDrawBezier(rabStandCenterPosX + 120/jpgTimes, rabStandCenterPosY + 500/jpgTimes, rabStandCenterPosX + 90/jpgTimes, rabStandCenterPosY + 600/jpgTimes, rabStandCenterPosX + 90/jpgTimes, rabStandCenterPosY + 720/jpgTimes, rabStandCenterPosX + 120/jpgTimes,rabStandCenterPosY + 850/jpgTimes);
    
    ofDrawBezier(rabStandCenterPosX + 340/jpgTimes, rabStandCenterPosY + 500/jpgTimes, rabStandCenterPosX + 310/jpgTimes, rabStandCenterPosY + 600/jpgTimes, rabStandCenterPosX + 310/jpgTimes, rabStandCenterPosY + 720/jpgTimes, rabStandCenterPosX + 340/jpgTimes, rabStandCenterPosY + 850/jpgTimes);
    
    ofSetColor(255);
    
    //Shoes
    RabbitShoe.draw(rabbitStandCenter + ofVec2f(50/jpgTimes,850/jpgTimes),(108+10)/jpgTimes,(77+10)/jpgTimes);
    RabbitShoe.draw(rabbitStandCenter + ofVec2f(270/jpgTimes,850/jpgTimes),(108+10)/jpgTimes,(77+10)/jpgTimes);
    
    //draw hands
    RabbitLHdef.draw(rabbitStandCenter + ofVec2f(-210/jpgTimes,480/jpgTimes),(80+10)/jpgTimes,(80+10)/jpgTimes);
    RabbitRHdef.draw(rabbitStandCenter + ofVec2f(630/jpgTimes,480/jpgTimes),(80+10)/jpgTimes,(80+10)/jpgTimes);
    
    //draw arms
    ofSetColor(255,173,41);
    ofSetLineWidth(13);
    ofNoFill();
    ofDrawBezier(rabStandCenterPosX + 100/jpgTimes, rabStandCenterPosY + 100/jpgTimes, rabStandCenterPosX - 100/jpgTimes, rabStandCenterPosY +200/jpgTimes, rabStandCenterPosX - 100/jpgTimes, rabStandCenterPosY + 400/jpgTimes, rabStandCenterPosX - 150/jpgTimes, rabStandCenterPosY + 500/jpgTimes);
    
    ofDrawBezier(rabStandCenterPosX + 380/jpgTimes, rabStandCenterPosY + 100/jpgTimes, rabStandCenterPosX + 610/jpgTimes, rabStandCenterPosY +200/jpgTimes, rabStandCenterPosX + 610/jpgTimes, rabStandCenterPosY + 400/jpgTimes, rabStandCenterPosX + 660/jpgTimes, rabStandCenterPosY + 500/jpgTimes);
    
    ofSetColor(255);
    
    //arms
    
    
    
    RabbitLEar.draw(rabbitStandCenter + ofVec2f(150/jpgTimes, -850/jpgTimes),243/jpgTimes,400/jpgTimes);
    RabbitREar.draw(rabbitStandCenter + ofVec2f(400/jpgTimes, -840/jpgTimes),306/jpgTimes,400/jpgTimes);
    RabbitHead.draw(rabbitStandCenter + ofVec2f(-100/jpgTimes, -500/jpgTimes),716/jpgTimes,526/jpgTimes);
    RabbitBody.draw(rabbitStandCenter, 468/jpgTimes, 551/jpgTimes);

    
}

void ofApp::drawRabForwardA(){
    ofSetColor(0);
    ofSetLineWidth(15);
    ofNoFill();
    
    ofDrawBezier(rabCenterPosX + 150/jpgTimes, rabCenterPosY + 500/jpgTimes, rabCenterPosX + 120/jpgTimes, rabCenterPosY + 600/jpgTimes, rabCenterPosX + 120/jpgTimes, rabCenterPosY + 720/jpgTimes, rabCenterPosX + 150/jpgTimes,rabCenterPosY + 850/jpgTimes);
    
    ofDrawBezier(rabCenterPosX + 370/jpgTimes, rabCenterPosY + 500/jpgTimes, rabCenterPosX + 340/jpgTimes, rabCenterPosY + 600/jpgTimes, rabCenterPosX + 340/jpgTimes, rabCenterPosY + 720/jpgTimes, rabCenterPosX + 370/jpgTimes,rabCenterPosY + 850/jpgTimes);
    
    ofSetColor(255);
    
    //Shoes
    RabbitShoe.draw(rabbitCenter + ofVec2f(80/jpgTimes,850/jpgTimes),(108+10)/jpgTimes,(77+10)/jpgTimes);
    RabbitShoe.draw(rabbitCenter + ofVec2f(300/jpgTimes,850/jpgTimes),(108+10)/jpgTimes,(77+10)/jpgTimes);
    
}

void ofApp::drawRabForwardB(){
    ofSetColor(0);
    ofSetLineWidth(15);
    ofNoFill();
       
    ofDrawBezier(rabCenterPosX + 150/jpgTimes, rabCenterPosY + 500/jpgTimes, rabCenterPosX + 100/jpgTimes, rabCenterPosY + 600/jpgTimes, rabCenterPosX + 90/jpgTimes, rabCenterPosY + 720/jpgTimes, rabCenterPosX + 80/jpgTimes,rabCenterPosY + 850/jpgTimes);
       
    ofDrawBezier(rabCenterPosX + 370/jpgTimes, rabCenterPosY + 500/jpgTimes, rabCenterPosX + 370/jpgTimes, rabCenterPosY + 600/jpgTimes, rabCenterPosX + 380/jpgTimes, rabCenterPosY + 720/jpgTimes, rabCenterPosX + 420/jpgTimes,rabCenterPosY + 850/jpgTimes);
       
    ofSetColor(255);
    
    //Shoes
    RabbitShoe.draw(rabbitCenter + ofVec2f(10/jpgTimes,850/jpgTimes),(108+10)/jpgTimes,(77+10)/jpgTimes);
    RabbitShoe.draw(rabbitCenter + ofVec2f(350/jpgTimes,850/jpgTimes),(108+10)/jpgTimes,(77+10)/jpgTimes);
}

void ofApp::drawRabEyeA(){ //Open Eye
    ofFill();
    
    ofSetColor(255);
    ofDrawCircle(rabbitCenter + ofVec2f(80/jpgTimes,-300/jpgTimes), rabEyeR);
    ofDrawCircle(rabbitCenter + ofVec2f(330/jpgTimes,-300/jpgTimes), rabEyeR);
   
    ofSetColor(0);
    ofDrawCircle(rabbitCenter + ofVec2f(70/jpgTimes,-300/jpgTimes), rabEyeR-5);
    ofDrawCircle(rabbitCenter + ofVec2f(320/jpgTimes,-300/jpgTimes), rabEyeR-5);
    
    ofSetColor(255);
    
}

void ofApp::drawRabEyeB(){ //Close Eye
    ofSetColor(183, 131, 152);
    ofSetLineWidth(5);
    ofNoFill();
    
    ofDrawBezier(rabCenterPosX + 30/jpgTimes, rabCenterPosY - 300/jpgTimes, rabCenterPosX + 30/jpgTimes, rabCenterPosY - 250/jpgTimes, rabCenterPosX + 160/jpgTimes, rabCenterPosY - 250/jpgTimes,rabCenterPosX + 160/jpgTimes, rabCenterPosY - 300/jpgTimes );
    
    ofDrawBezier(rabCenterPosX + 260/jpgTimes, rabCenterPosY - 300/jpgTimes, rabCenterPosX + 260/jpgTimes, rabCenterPosY - 250/jpgTimes, rabCenterPosX + 390/jpgTimes, rabCenterPosY - 250/jpgTimes,rabCenterPosX + 390/jpgTimes, rabCenterPosY - 300/jpgTimes );

    
    ofSetColor(255);

}

void ofApp::drawRabEyeA1(){
    ofFill();
    
    ofSetColor(255);
    ofDrawCircle(rabEyePos, rabEyeR);
    ofDrawCircle(rabEyePos + ofVec2f(260/jpgTimes,0), rabEyeR);

    ofSetColor(0);
    ofDrawCircle(rabEyePosA + ofVec2f(-10/jpgTimes,0), rabEyeR-5);
    ofDrawCircle(rabEyePosA + ofVec2f(250/jpgTimes,0), rabEyeR-5);
    
    ofSetColor(255);
}

void ofApp::drawRabFinalEye(){
    ofFill();
     
    ofSetColor(255);
    ofDrawCircle(rabEyePosLast + ofVec2f(7,-22), rabEyeR* 1.5);
    ofDrawCircle(rabEyePosLast + ofVec2f(260/jpgTimes * 1.5 + 7,-22), rabEyeR * 1.5);

    ofSetColor(0);
    ofDrawCircle(rabEyePosLastA + ofVec2f(-10/jpgTimes * 1.5 + 7,-22), (rabEyeR-5)* 1.5);
    ofDrawCircle(rabEyePosLastA + ofVec2f(250/jpgTimes * 1.5 + 7,-22), (rabEyeR-5)* 1.5);
    
    ofSetColor(255);
}


void ofApp::drawRabEyeB1(){
    ofSetColor(183, 131, 152);
    ofSetLineWidth(5);
    ofNoFill();
    
    ofDrawBezier(rabStandCenterPosX + 30/jpgTimes, rabStandCenterPosY - 300/jpgTimes, rabStandCenterPosX + 30/jpgTimes, rabStandCenterPosY - 250/jpgTimes, rabStandCenterPosX + 160/jpgTimes, rabStandCenterPosY - 250/jpgTimes,rabStandCenterPosX + 160/jpgTimes, rabStandCenterPosY - 300/jpgTimes );
    
    ofDrawBezier(rabStandCenterPosX + 260/jpgTimes, rabStandCenterPosY - 300/jpgTimes, rabStandCenterPosX + 260/jpgTimes, rabStandCenterPosY - 250/jpgTimes, rabStandCenterPosX + 390/jpgTimes, rabStandCenterPosY - 250/jpgTimes,rabStandCenterPosX + 390/jpgTimes, rabStandCenterPosY - 300/jpgTimes );

    ofSetColor(255);
    
}
//-----------------------------------

void ofApp::drawCameraShot(){
    if(shot == false){
//        ofSetColor(255,0,0);
//        ofSetLineWidth(3);
//        ofNoFill();
//        ofDrawRectangle(mouseX,mouseY,shotSize*2,shotSize);
    }
    
    if(shot == true){
        ofFill();
        ofSetColor(255,255,255,alpha);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        cameraSound.play();
    }
}

//-----------------------------------

void ofApp::drawFirstScene(){
//    SceneIntro.draw(0,0,1920,1080);//(jpgTimes/5
    SceneIntroC.draw(0,0, 1920, 1080);
    SceneIntroB.draw(0,0, 1920, 1080);
    SceneIntroA.draw(0,0, 1920, 1080);
}

void ofApp::drawMainSceneA(){
    
    SceneMainB.draw(-movePosX*0.5,373,1920*1.1,707*1.1);
    SceneMainC.draw(movePosX*0.5,293,1920*1.1,170*1.1);
    SceneMainA.draw(346,530,1554,550);

}

void ofApp::drawEndScene(){
        
    ofVec2f earthCenter(ofGetWidth()/2,ofGetHeight()/2); //
        
        
    ofVec2f rotateLunar = earthCenter + ofVec2f(50,50);
    ofVec2f rotateLunarA = earthCenter + ofVec2f(100,100);
    ofVec2f rotateLunarB = earthCenter + ofVec2f(150,150);
    ofVec2f rotateLunarC = earthCenter + ofVec2f(200,200);
    ofVec2f rotateLunarD = earthCenter + ofVec2f(270,270);



    ofVec2f lunar = rotateLunar.rotate(rotateDegrees++,earthCenter);
    ofVec2f lunarA = rotateLunarA.rotate(rotateDegreesA++,earthCenter);
    ofVec2f lunarB = rotateLunarB.rotate(rotateDegreesB++,earthCenter);
    ofVec2f lunarC = rotateLunarC.rotate((rotateDegreesB++)*0.5,earthCenter);
    ofVec2f lunarD = rotateLunarD.rotate((rotateDegrees++)*1.1,earthCenter);

        
        ofSetCircleResolution(100);
    
        ofSetColor(238,36,83);
        ofDrawEllipse(lunar,14,14);
    
        ofSetColor(255);
        ofDrawEllipse(lunarA,10,10);
        
        ofSetColor(255,206,0);
        ofDrawEllipse(lunarB,8,8);
    
        ofSetColor(255,206,0);
        ofDrawEllipse(lunarC,8,8);
        
        ofSetColor(97,153,52);
        ofDrawEllipse(lunarD,6,6);
        
        ofSetColor(50,60,255);
        ofDrawEllipse(earthCenter,50,50);
        ofSetColor(255);

        
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


//-----------------------------------

void ofApp::keyPressed(int key){
    int stepFox = 10;
    int stepRab = 15;
    if(key == 'a'){
        if(ofGetElapsedTimeMillis()/1000 < 32 || foxCenterPosX + 751/jpgTimes >= 0 ){
            
        foxCenter.x = foxCenter.x - stepFox;
        foxCenterPosX = foxCenterPosX - stepFox;
        
        foxCenter.y = foxCenter.y - (stepFox - 6);
        foxCenterPosY = foxCenterPosY - (stepFox - 6);
        
        rabbitCenter.x = rabbitCenter.x - stepRab;
        rabCenterPosX = rabCenterPosX - stepRab;
        
        rabbitCenter.y = rabbitCenter.y - (stepRab - 9);
        rabCenterPosY = rabCenterPosY - (stepRab - 9);
        }
        
        if(ofGetElapsedTimeMillis()/1000 >= 32 && ofGetElapsedTimeMillis()/1000<= 90 && foxCenterPosX + 751/jpgTimes <= 0){
            rabbitStandCenter.x = rabbitStandCenter.x - (stepRab - 9);
            rabStandCenterPosX = rabStandCenterPosX - (stepRab - 9);
        }
        
    }
    if(foxCenterPosX <= 1300){
    if(key == 'd'){
        if(ofGetElapsedTimeMillis()/1000 < 32 && foxCenterPosX + 751/jpgTimes >= 0 ){
            foxCenter.x = foxCenter.x + stepFox;
            foxCenterPosX = foxCenterPosX + stepFox;

            foxCenter.y = foxCenter.y + 4;
            foxCenterPosY = foxCenterPosY + 4;
        }
        
        if(ofGetElapsedTimeMillis()/1000 >= 32 && ofGetElapsedTimeMillis()/1000<= 90 && foxCenterPosX + 751/jpgTimes <= 0){
            rabbitStandCenter.x = rabbitStandCenter.x + (stepRab - 9);
            rabStandCenterPosX = rabStandCenterPosX + (stepRab - 9);
        }
        
    }
        
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    mouseX = x;
    mouseY = y;
    
    
    int posX = ofMap(x,0,ofGetWidth(),30/jpgTimes,50/jpgTimes);
    int posY = ofMap(y,0,ofGetHeight(), -140/jpgTimes,-100/jpgTimes);
    
    int posXA = ofMap(x,0,ofGetWidth(),20/jpgTimes,70/jpgTimes);
    int posYA = ofMap(y,0,ofGetHeight(), -150/jpgTimes, -90/jpgTimes);
    
    foxEyePos = foxStandCenter + ofVec2f(posX, posY);
    foxEyePosA = foxStandCenter + ofVec2f(posXA, posYA);
    
    foxEyePosLast = foxFinalCenter + ofVec2f(posX, posY);
    foxEyePosLastA = foxFinalCenter + ofVec2f(posXA, posYA);
    
    rabEyePos = rabbitStandCenter + ofVec2f(posX + 5, posY - 30);
    rabEyePosA = rabbitStandCenter + ofVec2f(posXA + 5, posYA - 30);
    
    rabEyePosLast = rabFinalCenter + ofVec2f(posX + 5, posY - 30);
    rabEyePosLastA = rabFinalCenter + ofVec2f(posXA + 5, posYA - 30);

    
    //draw Arms in the main scene
    int ArmSTPosX = ofMap(x,0,ofGetWidth(), 0, 0); // ArmST = foxStandCenter + ofVec2f(100/jpgTimes,100/jpgTimes);
    int ArmSTPosY = ofMap(y,0,ofGetHeight(), 0, 0);
    
    int ArmSMPosX = ofMap(x,0,ofGetWidth(), -30/jpgTimes, 30/jpgTimes ); //foxStandCenterPosX
    int ArmSMPosY = ofMap(y,0,ofGetHeight(), 100/jpgTimes, 150/jpgTimes );

    int ArmEMPosX = ofMap(x,0,ofGetWidth(), -130/jpgTimes, 30/jpgTimes );
    int ArmEMPosY = ofMap(y,0,ofGetHeight(), 230/jpgTimes, 300/jpgTimes );

    int ArmETPosX = ofMap(x,0,ofGetWidth(), -330/jpgTimes, -130/jpgTimes );
    int ArmETPosY = ofMap(y,0,ofGetHeight(), 150/jpgTimes, 400/jpgTimes );
    
    foxArmSTX = foxStandCenterPosX + 100/jpgTimes + ArmSTPosX;
    foxArmSTY = foxStandCenterPosY + 100/jpgTimes + ArmSTPosY;
    foxArmSMX = foxStandCenterPosX + 100/jpgTimes + ArmSMPosX;
    foxArmSMY = foxStandCenterPosY + 100/jpgTimes + ArmSMPosY;
    foxArmEMX = foxStandCenterPosX + 100/jpgTimes + ArmEMPosX;
    foxArmEMY = foxStandCenterPosY + 100/jpgTimes + ArmEMPosY;
    foxArmETX = foxStandCenterPosX + 100/jpgTimes + ArmETPosX;
    foxArmETY = foxStandCenterPosY + 100/jpgTimes + ArmETPosY;
    
    //----
    int switchPosX = ofMap(x,0,ofGetWidth(),-10,10);
    movePosX = switchPosX;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    time = ofGetElapsedTimeMillis();
    
    if(button == 0){
        shot = true;
        time = ofGetElapsedTimeMillis();
    }
    
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

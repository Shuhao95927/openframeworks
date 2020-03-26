#include "ofApp.h"
#include "ofxJSON.h"

#include <time.h>

ofxJSONElement root;

ofImage NewYork;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(140);

    std::string url = "https://api.darksky.net/forecast/7717b6b4635bdf3564f2b91e234ce0f5/42.3601,-71.0589";
    bool parsingSuccessful = root.open(url);
    if(parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << root.getRawString(true);
    }else{
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
    }
    
    
    gui.setup();
    gui.add(SunriseTime.setup("Sunrise Time",6,0,12));
    gui.add(SunsetTime.setup("Sunset Time",18,13,24));
    gui.add(currentTime.setup("Current Time",10,0,24));
    gui.add(temperature.setup("Temperature",39.7,-100,100));
    gui.add(windSpeed.setup("Wind Speed",9.04,0,30));
    gui.add(cloudCover.setup("Cloud Cover",0.31,0,5));
    
    
    ofSetWindowShape(1280, 1000);
    
    NewYork.load("images/NewYork1.png");
    

}




//--------------------------------------------------------------
void ofApp::update(){

}
std::ostringstream text;

//--------------------------------------------------------------
void ofApp::draw(){
    
    std::string summary = root["currently"]["summary"].asString();
    float temperature = root["currently"]["temperature"].asFloat();
    float windSpeed = root["currently"]["windSpeed"].asFloat();
    float cloudCover = root["currently"]["cloudCover"].asFloat();
    //draw time
    int sampleTime = root["currently"]["time"].asInt(); //time
    int sunriseTime = root["daily"]["data"][1]["sunriseTime"].asInt();
    int sunsetTime = root["daily"]["data"][0]["sunsetTime"].asInt();
    
    //
    int year = sampleTime/31556926+1970;
    int month = (sampleTime%31556926)/2629743+1;
    int day = (sampleTime%2629743)/86400+2;
    int hour = (sampleTime%86400)/3600-4;
    if(hour<0){
        hour += 24;
        day -= 1;
    }
    int minute = (sampleTime%3600)/60;
    //
    int sunriseTimeHour = (sunriseTime%86400)/3600-4;
    if(sunriseTimeHour < 0){
        sunriseTimeHour += 24;
    }
    int sunriseTimeMinute = (sunriseTime%3600)/60;
    
    
    int sunsetTimeHour = (sunsetTime%86400)/3600-4;
    if(sunsetTimeHour < 0){
        sunsetTimeHour += 24;
    }
    int sunsetMinute = (sunsetTime%3600)/60;
    
    //
    ofColor moring = ofColor(206,232,249);
    ofColor evening = ofColor(34,34,78);
    ofColor sunset = ofColor(234,84,64);
    
    ofColor cloud = ofColor(255);
    ofColor light = ofColor(255,150,40);
    
    if(currentTime >=0 && currentTime<= 12){
        if(currentTime < SunriseTime){
            ofSetColor(evening);
        } else if(currentTime >= SunriseTime && currentTime <= (SunriseTime+2)){
            ofColor daytimeLerp = evening.lerp(moring,(currentTime-SunriseTime)*0.5f);
            ofSetColor(daytimeLerp);
        }else{
            ofSetColor(moring);
        }
    }
    
    if(currentTime >= 12 && currentTime <= 24){
        if(currentTime< (SunsetTime - 2)) {
            ofSetColor(moring);
        }else if(currentTime >= (SunsetTime - 3) && currentTime <= (SunsetTime-1)){
            ofColor sunsetLerp = moring.lerp(sunset,currentTime-(SunsetTime-2));
            ofSetColor(sunsetLerp);
        }else if(currentTime>=(SunsetTime - 1) && currentTime <= (SunsetTime+1)){
            ofColor nighttimeLerp = sunset.lerp(evening,(currentTime-(SunsetTime-1))*0.5);
            ofSetColor(nighttimeLerp);
        }else{
            ofSetColor(evening);
        }
    }
    
    
    cout<<SunriseTime<<endl;
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    NewYork.draw(0,700,1280,300);
    
    gui.draw();
    
    if (ofGetFrameNum() == 1){
        text << "Date: " << month << "/" << day << "/" << year << endl;
        text << "Time: " << hour << ":" << minute << endl;
        text << "Temperature: " << temperature << endl;
        text << "Wind Speed: " << windSpeed << endl;
        text << "Cloud Cover: " << cloudCover << endl;
        text << "Sunrise Time: " << sunriseTimeHour << ":" << sunriseTimeMinute << endl;
        text << "Sunset Time: " << sunsetTimeHour << ":" << sunsetMinute << endl;
    }
    ofSetColor(0);
    ofDrawBitmapString(text.str(),20,500);
    
    

    
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

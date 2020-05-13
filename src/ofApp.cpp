#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup(){
    
    //camera stuff starts
    vector<ofVideoDevice> devices = cam.listDevices();
    for(int i=0; i < devices.size(); i++)
    {
        ofLogNotice() << devices[i].id << ":" << devices[i].deviceName;
    }
    
    
    cam.setDeviceID(0);
    cam.initGrabber(1280, 720);
    tracker.setup();
    //camera stuff finishes
    
    //FFT example edap starts
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);

    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    // the higher the value, the more accurate will be the fft analysis
    fftSize = 1024;
    fft.setup(fftSize, 512, 256);
    /* this has to happen at the end of setup - it switches on the DAC */
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    //FFT example edapt finishes
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //camera stuff
    cam.update();
    if(cam.isFrameNew())
    {
        tracker.update(toCv(cam));
        if(tracker.getFound()){
            facePoints = tracker.getImagePoints();
            facePos = tracker.getPosition();
            mouthHeight= tracker.getGesture(ofxFaceTracker::JAW_OPENNESS);
            
            
            
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //camera stuff
    /*
    int nBands = 60;
    float *mySpectrum=ofSoundGetSpectrum(nBands);
    float width=ofGetWidth()/nBands;
     */
    
    ofSetColor(255);
    cam.draw(0,0);
    
    //FFT example edap starts
       
    if(tracker.getFound()){
       int numObjects = 64;//numObjects we want to draw
       int jump=fftSize/numObjects;
       for(int i = 0; i < fftSize ;i+=jump){
           float x = ofMap(i,0,fftSize,0,ofGetWidth());
           float width = ofGetWidth()/numObjects;
           ofSetColor(ofMap(i,0,numObjects/2,200,255),ofMap(facePos.x,0,ofGetWidth(),25,255),ofMap(i,0,numObjects/2,25,255));
           ofDrawCircle(facePoints[i], (fft.magnitudes[i]) * ofGetHeight());
           
       }
       //FFT example edapt finishes
    
    }
    
   
    /*
     if(tracker.getFound()){
         
           //tracker.draw();
         
    for (int i=0;i<nBands;i++){
        
        ofSetColor(ofMap(i,0,nBands,200,255),ofMap(facePos.x,0,ofGetWidth(),25,255),ofMap(i,0,nBands,25,255));
        
        float radius=mySpectrum[i]*(i+1)*ofGetHeight();
        
        ofDrawCircle(facePoints[i],radius/200);
        //ofDrawBitmapString(i,facePoints[i]);
        
        
        }
         
     }
     ofSetColor(0,146,255);
     ofDrawBitmapString("press 's' to stop the audio\n'p' to play the audio", 31, 92);
    ofDrawBitmapString("Move your face\n to change color and audio speed", 31, 122);
    
    
    //camera stuff
    */
    
    
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    //FFT example edap starts
    double input0, input1;
    for (int i = 0; i < bufferSize; i++){
        //fft
        input0 = input[i*2    ];
        input1 = input[i*2 + 1];

        if(fft.process(input0)){
            fft.magsToDB();
        }
        if(fft.process(input1)){
            fft.magsToDB();
        }
    }
    //FFT example edap starts
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

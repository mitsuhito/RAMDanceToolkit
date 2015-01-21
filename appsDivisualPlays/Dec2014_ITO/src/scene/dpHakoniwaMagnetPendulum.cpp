//
//  dpHakoniwaMagnetPendulum.cpp
//  example-ramMotionExtractor
//
//  Created by itotaka on 1/16/15.
//
//

#include "dpHakoniwaMagnetPendulum.h"

void dpHakoniwaMagnetPendulum::setupControlPanel() {
    
    mMotionExtractor.setupControlPanel(this,ofPoint(340,30));
//    mMotionExtractor.load("motionExt_dpHMagPendulum.xml");
    ramGetGUI().addToggle("Test mode", &bTestMode);
    
    ramGetGUI().addSeparator();
    ramGetGUI().addButton("ALL MAGNETS ON");
    ramGetGUI().addButton("ALL MAGNETS OFF");
    
    for (int i = 0; i < NMAGNETS; i++ ) {
        ramGetGUI().addToggle("ON/OFF_MAGNET"+ofToString(i+1), &bOn[i]);
    }

    ramGetGUI().addSeparator();
    ramGetGUI().addButton("INVERSE ALL");
    ramGetGUI().addButton("RESTORE ALL");

    for (int i = 0; i < NMAGNETS; i++ ) {
        ramGetGUI().addToggle("INVERSE_MAGNET"+ofToString(i+1), &bInversed[i]);
    }
    
    ramGetGUI().addSlider("Distance Threshold", 2.0f, 200.0f, &distanceThreshold);

    vector<string> modename;
    modename.push_back("ALL 3DANCERS MODE");
    modename.push_back("2EACH 3DANCERS MODE");
    
    ramGetGUI().addRadioGroup("mode", modename, &mode);
    
    bTestMode = true;
    distanceThreshold = 20.0f;
    
    ofAddListener(ramGetGUI().getCurrentUIContext()->newGUIEvent,this,&dpHakoniwaMagnetPendulum::guiEvent);
    
}

void dpHakoniwaMagnetPendulum::setup() {
    
    mSenderOnOff.setup("192.168.20.52",8528);
    mSenderInverse.setup("192.168.20.72", 8528);

    bHideNodeView = true;
    
}

void dpHakoniwaMagnetPendulum::sendOsc() {
    
    {
        ofxOscMessage m;
        m.setAddress("/dp/hakoniwa/magpen");
        
        for (int i = 0; i < NMAGNETS; i++) {
            m.addIntArg(bOn[i]); // Magnets ON/OFF (1:ON, 0:OFF)
        }
        
        mSenderOnOff.sendMessage(m);
    }
    
    {
        ofxOscMessage m;
        m.setAddress("/dp/hakoniwa/magpen");
        
        for (int i = 0; i < NMAGNETS; i++) {
            m.addIntArg(bInversed[i]); // Magnets Inversed (1: Inversed, 0: Normal)
        }
        
        mSenderInverse.sendMessage(m);
    }
}

void dpHakoniwaMagnetPendulum::guiEvent(ofxUIEventArgs &e) {

    string name = e.widget->getName();
    
    if (name == "ALL MAGNETS ON") {
        for (int i = 0; i < NMAGNETS; i++) {
            bOn[i] = true;
        }
    } else if (name == "ALL MAGNETS OFF") {
        for (int i = 0; i < NMAGNETS; i++) {
            bOn[i] = false;
        }
    } else if (name == "INVERSE ALL") {
        for (int i = 0; i < NMAGNETS; i++) {
            bInversed[i] = true;
        }
    } else if (name == "RESTORE ALL") {
        for (int i = 0; i < NMAGNETS; i++) {
            bInversed[i] = false;
        }
    }
}

void dpHakoniwaMagnetPendulum::update() {
    
    mMotionExtractor.update();
    
    if (!bTestMode) {
        
        float d1 = mMotionExtractor.getDistanceAt(0, 1);
        float d2 = mMotionExtractor.getDistanceAt(2, 3);
        float d3 = mMotionExtractor.getDistanceAt(4, 5);

        if (mode == 1) {

            if (d1 < distanceThreshold && d1 != 0.0f) {
                bOn[0] = true;
                bOn[1] = true;
            } else {
                bOn[0] = false;
                bOn[1] = false;
            }
            if (d2 < distanceThreshold && d2 != 0.0f) {
                bOn[2] = true;
                bOn[3] = true;
            } else {
                bOn[2] = false;
                bOn[3] = false;
            }
            if (d3 < distanceThreshold && d3 != 0.0f) {
                bOn[4] = true;
                bOn[5] = true;
            } else {
                bOn[4] = false;
                bOn[5] = false;
            }
        } else if (mode == 0) {
            
            if (d1 > distanceThreshold &&
                d2 > distanceThreshold &&
                d3 > distanceThreshold) {
                for (int i = 0; i < 6; i++) bOn[i] = false;
            } else {
                for (int i = 0; i < 6; i++) bOn[i] = true;
            }
            
        }
    }
    
    if (ofGetKeyPressed(49)){
        bHideNodeView = !bHideNodeView;
    }
    
    sendOsc();
    
}

void dpHakoniwaMagnetPendulum::drawActor(const ramActor &actor){
    ramDrawBasicActor(actor);
}

void dpHakoniwaMagnetPendulum::draw(){
    
    ramSetViewPort(dpGetFirstScreenViewPort()); //１枚目のscreenを描画に指定。ここの仕様変わります。
    ramBeginCamera();
    
    mMotionExtractor.draw();
//    twFinder.debugDraw(mMotionExtractor);
//    debugDraw();
//    
    
    ramEndCamera();

    
    if (bHideNodeView) example_drawDump();
    
}

void dpHakoniwaMagnetPendulum::example_drawDump(){
    
    ofPushMatrix();
    ofTranslate(800, 10);
    
    for (int i = 0;i < mMotionExtractor.getNumPort();i++){
        ofPushMatrix();
        ofTranslate(0, i*90);
        
        ofVec3f vec = mMotionExtractor.getVelocityAt(i);
        float speed = mMotionExtractor.getVelocitySpeedAt(i);
        
        ofNoFill();
        ofRect(0, 0, 200, 80);
        ofFill();
        
        string info = "";
        info += "Port  :" + ofToString(i) + "\n";
        info += "Actor :" + mMotionExtractor.getActorNameAt(i) + "\n";
        info += "Joint :" + mMotionExtractor.getJointNameAt(i) + "\n";
        info += "Speed :" + ofToString(mMotionExtractor.getVelocitySpeedAt(i)) + "\n";
        
        ofSetColor(100);
        ofRect(10, 45, mMotionExtractor.getVelocitySpeedAt(i)*10.0, 15);
        
        ofSetColor(255);
        ofDrawBitmapString(info, 10, 15);
        
        ofPopMatrix();
    }
    
    ofPopMatrix();
}






#pragma once

#include "ofMain.h"
#include "ofxSvg.h"
#include "ofMesh.h"

class Vector : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxSVG svg;
    float step;
    vector<ofPolyline> outlines;
    
    ofMesh mesh;
    ofMesh side;
    vector<ofMesh> meshes;
    
    int plateDepth;
    
    // LDU Convertion
    float ldu;
    // BRICK SIZE
    float brickWidth;
    float brickHeight;
    float plateHeight;
    float studDiameter;
    float studHeight;
    
    
    ofQuaternion curRot;
    ofVec2f lastMouse;
    float dampen;
};

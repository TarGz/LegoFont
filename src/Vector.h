#pragma once

#include "ofMain.h"
#include "ofxSvg.h"
#include "ofMesh.h"
//#include "ofxMesh.h"
#include "ofTessellator.h"
#include "ofxSTL.h"


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
    
    void drawInteractionArea();
    ofxSVG svg;
    float step;
    ofVbo vbo;
    vector<ofPolyline> outlines;
    
    bool shift;
    ofMesh mesh;
    ofMesh shape;
    ofMesh front;
    ofMesh back;
    ofMesh side;
    ofLight light;
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
    
    ofEasyCam cam;
    
    ofxSTLImporter stlImporter;
	ofxSTLExporter stlExporter;
    bool bSaveModel;
};

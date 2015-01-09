#pragma once
#include "ofMain.h"
#include "ofxSTL.h"

const int X = 300;
const int Y = 20;
const int Z = 70;

//This is the data for the vertices, which keeps the data as simple as possible:
//static GLfloat vdata[12][3] = {
//    {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
//    {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
//    {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} };


static GLfloat vdata[8][3] = {
    {-X, -Y, Z},    // 0
    {X, -Y, Z},     // 1
    {-X, Y, Z},     // 2
    {X, Y, Z},      // 3
    {-X, -Y, -Z},   // 4
    {X, -Y, -Z},    // 5
    {-X, Y, -Z},    // 6
    {X, Y, -Z},    // 7
    };


//data for the indices, representing the index of the vertices
//that are to be connected into the triangle.
//You’ll notice that for 12 vertices you need 20 indices of 3 vertices each:
static GLint indices[12][3] = {
    {0,1,2},
    {2,1,3},
    {0,1,4},
    {4,5,1},
    {1,5,3},
    {7,5,3},
    {4,5,6},
    {5,6,7},
    {2,6,7},
    {2,7,3},
    {2,4,6},
    {0,2,4},
};

class icosahedron : public ofBaseApp{
    
public:
    float ang;
    ofMesh mesh;
    void setup();
    void update();
    void draw();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    void keyReleased(int key);
    void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c);
    void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d);
    //current state of the rotation
    ofQuaternion curRot;
    
    //a place to store the mouse position so we can measure incremental change
    ofVec2f lastMouse;
	
	//slows down the rotation 1 = 1 degree per pixel
	float dampen;
    
    // Export
    ofxSTLExporter stlExporter;
    ofxSTLImporter stlImporter;
    
    ofVec3f vertex;
};

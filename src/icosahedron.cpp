#include "icosahedron.h"

void icosahedron::setup()
{
    dampen = .4;
    ofColor color(255, 0, 0); float hue = 254.f;
    
    //Here’s where we finally add all the vertices to our mesh and add a color at each vertex:
    for (int i = 0; i< sizeof(vdata) ; ++i)
    {
        mesh.addVertex( ofVec3f( vdata[i][0], vdata[i][1], vdata[i][2] ));
        mesh.addColor(color);
        color.setHue( hue );
        hue -= 10.f;
    }
    
    for (int i = 0; i< 12 ; ++i)
    {
        mesh.addIndex(indices[i][0]);
        mesh.addIndex(indices[i][1]);
        mesh.addIndex(indices[i][2]);
    }
}

// give it a little spin
void icosahedron::update(){
//    ang+=1.5;
}

void icosahedron::draw()
{
    
    ofBackground(122,122,122);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 40);
    
    ofVec3f axis;
    float angle;
    curRot.getRotate(angle, axis);
    
    ofRotate(angle, axis.x, axis.y, axis.z);
    //Now it’s time to draw the mesh. The ofMesh has three drawing methods: drawFaces(),
    //which draws all the faces of the mesh filled; drawWireframe(), which draws lines
    //along each triangle; and drawVertices(), which draws a point at each vertex.
    //Since we want to see the colors we’re drawing, we’ll draw all the faces:
//    mesh.drawFaces();
    mesh.drawWireframe();
    ofPopMatrix();
}

//--------------------------------------------------------------
void icosahedron::mouseDragged(int x, int y, int button){
	
	//every time the mouse is dragged, track the change
	//accumulate the changes inside of curRot through multiplication
    ofVec2f mouse(x,y);
    ofQuaternion yRot((x-lastMouse.x)*dampen, ofVec3f(0,1,0));
    ofQuaternion xRot((y-lastMouse.y)*dampen, ofVec3f(-1,0,0));
    curRot *= yRot*xRot;
    lastMouse = mouse;
    
    ofLog(OF_LOG_NOTICE, "drag " + ofToString(mouse.x) + ":" + ofToString(mouse.y));
}

//--------------------------------------------------------------
void icosahedron::mousePressed(int x, int y, int button){
    //store the last mouse point when it's first pressed to prevent popping
	lastMouse = ofVec2f(x,y);
}

//--------------------------------------------------------------
void icosahedron::keyPressed(int key){

    vector<ofxSTLFacet>& facets = mesh.getFacets();
    int numFacets = facets.size();
    stlExporter.beginModel("some model");
    for(int i=0; i<numFacets; i++){
        stlExporter.addTriangle(facets[i].vert1, facets[i].vert2, facets[i].vert3, facets[i].normal);
    }
    stlExporter.useASCIIFormat(true); //export as ASCII (default is binary)
    stlExporter.saveModel("testASCII.stl");
    stlExporter.useASCIIFormat(false); //export as binary
    stlExporter.saveModel("testBin.stl");
}

//--------------------------------------------------------------
void icosahedron::keyReleased(int key){
    
}
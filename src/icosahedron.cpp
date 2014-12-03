#include "icosahedron.h"

void icosahedron::setup()
{
    dampen = .4;
    mesh.enableNormals();
    
    
    
    ofColor color(255, 0, 0); float hue = 254.f;
    
    //Here’s where we finally add all the vertices to our mesh and add a color at each vertex:
    for (int i = 0; i < sizeof(vdata) ; ++i)
    {
        vertex = ofVec3f( vdata[i][0], vdata[i][1], vdata[i][2] );
        mesh.addVertex(vertex );
        mesh.addColor(color);
        color.setHue( hue );
        hue -= 20.f;
    }
    
    for (int i = 0; i< 12 ; ++i)
    {
        mesh.addIndex(indices[i][0]);
        mesh.addIndex(indices[i][1]);
        mesh.addIndex(indices[i][2]);

    }
    
//    // FRONT
//    addFace(mesh,
//            ofVec3f(-X,-Y,Z),
//            ofVec3f(X,-Y,Z),
//            ofVec3f(-X,Y,Z),
//            ofVec3f(X,Y,Z)
//            );
//    // BACK
//    addFace(mesh,
//            ofVec3f(-X,-Y,-Z),
//            ofVec3f(X,-Y,-Z),
//            ofVec3f(-X,Y,-Z),
//            ofVec3f(X,Y,-Z)
//            );
//    // RIGHT
//    addFace(mesh,
//            ofVec3f(X,-Y,Z),
//            ofVec3f(X,Y,Z),
//            ofVec3f(X,-Y,-Z),
//            ofVec3f(X,Y,-Z)
//            
//            );
//    // LEFT
//    addFace(mesh,
//            ofVec3f(-X,-Y,Z),
//            ofVec3f(-X,Y,Z),
//            ofVec3f(-X,-Y,-Z),
//            ofVec3f(-X,Y,-Z)
//            );
//    // TOP
//    addFace(mesh,
//            ofVec3f(-X,-Y,Z),
//            ofVec3f(X,-Y,Z),
//            ofVec3f(-X,-Y,-Z),
//            ofVec3f(X,-Y,-Z)
//            );
//    // BOTTOM
//    addFace(mesh,
//            ofVec3f(-X,Y,Z),
//            ofVec3f(X,Y,Z),
//            ofVec3f(-X,Y,-Z),
//            ofVec3f(X,Y,-Z)
//            );
    
    
    
    
    
    
    
//    // BLANC
//    
//    addFace(mesh,
//            ofVec3f(-X,-Y,Z),
//            ofVec3f(X,-Y,Z),
//            ofVec3f(-X,Y,Z),
//            ofVec3f(X,Y,Z)
//            );
//    
//    // VERT
//    
//    addFace(mesh,
//            ofVec3f(X,-Y,Z),
//            ofVec3f(X,Y,Z),
//            ofVec3f(X,-Y,-Z),
//            ofVec3f(X,Y,-Z)
//            );
//    // ROUGE
//    addFace(mesh,
//            ofVec3f(-X,-Y,Z),
//            ofVec3f(X,-Y,Z),
//            ofVec3f(-X,-Y,-Z),
//            ofVec3f(X,-Y,-Z)
//            );
//
//    // JAUNE
//    addFace(mesh,
//            ofVec3f(-X,-Y,-Z),
//            ofVec3f(X,-Y,-Z),
//            ofVec3f(-X,Y,-Z),
//            ofVec3f(X,Y,-Z)
//            );
//    
//    // BLEU
//    addFace(mesh,
//            ofVec3f(-X,-Y,Z),
//            ofVec3f(-X,Y,Z),
//            ofVec3f(-X,-Y,-Z),
//            ofVec3f(-X,Y,-Z)
//            
//            );
//    
//    // ORANGE
//    addFace(mesh,
//            ofVec3f(-X,Y,Z),
//            ofVec3f(X,Y,Z),
//            ofVec3f(-X,Y,-Z),
//            ofVec3f(X,Y,-Z)
//            
//            
//            );
//    
//    addFace(mesh,
//            ofVec3f(,,),
//            ofVec3f(,,),
//            ofVec3f(,,),
//            ofVec3f(,,)
//            );
//
    
    
    
    
    
    
//    ofEnableDepthTest();
}



//--------------------------------------------------------------
void icosahedron::addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c) {
	ofVec3f normal = ((b - a).cross(c - a)).normalize();
	mesh.addNormal(normal);
	mesh.addVertex(a);
  
    ofLog(OF_LOG_NOTICE, ofToString(mesh.getNumVertices()));
    
	mesh.addNormal(normal);
	mesh.addVertex(b);
    ofLog(OF_LOG_NOTICE, ofToString(mesh.getNumVertices()));
    
	mesh.addNormal(normal);
	mesh.addVertex(c);
//    mesh.addIndex(mesh.getNumVertices());
    ofLog(OF_LOG_NOTICE, ofToString(mesh.getNumVertices()));
    
    
    

}

//--------------------------------------------------------------
void icosahedron::addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
	addFace(mesh, a, b, c);
	addFace(mesh, b, c, d);
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

// mesh.drawFaces();
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
    
//    ofLog(OF_LOG_NOTICE, "drag " + ofToString(mouse.x) + ":" + ofToString(mouse.y));
}

//--------------------------------------------------------------
void icosahedron::mousePressed(int x, int y, int button){
    //store the last mouse point when it's first pressed to prevent popping
	lastMouse = ofVec2f(x,y);
}

//--------------------------------------------------------------
void icosahedron::keyPressed(int key){
    ofLog(OF_LOG_NOTICE, "saving " +  ofToString(key));
    mesh.save("test.ply",false);
}

//--------------------------------------------------------------
void icosahedron::keyReleased(int key){
    
}
#include "Vector.h"

//--------------------------------------------------------------
void Vector::setup(){
	ofSetVerticalSync(true);
	dampen = .4;
    plateDepth  =20;
    
    // LDU Convertion
    ldu = 0.4;
    // BRICK SIZE
    brickWidth = 20*ldu;
    brickHeight = 24*ldu;
    plateHeight = 8*ldu;
    float studDiameter;
    float studHeight;
    
     ofLog(OF_LOG_NOTICE, "brickWidth " + ofToString(brickWidth));
    
    
	ofBackground(100, 100, 100);
    ofEnableAlphaBlending();
	ofSetColor(255,255,255,100);
	
    
    // PLATE
	svg.load("map_all.svg");
	for (int i = 0; i < svg.getNumPath(); i++){
		ofPath p = svg.getPathAt(i);
        

        ofLog(OF_LOG_NOTICE, "hasOutline " + ofToString(p.hasOutline()));
        vector<ofPolyline> outline = p.getOutline();
        
        front = p.getTessellation();
        back = front;

        
        ofVec3f* v = back.getVerticesPointer();
        ofVec3f* u = front.getVerticesPointer();
        
        // push the vertices of the back face back by depth
        for(int j=0; j< front.getNumVertices(); j++)
        {
            v[j].z += plateHeight;
        }
        
        
        //make side mesh by using outlines
        ofVec3f zOffset(0,0,plateHeight);
        for (int k=0; k<outline.size(); k++) {
            ofLog(OF_LOG_NOTICE, "outline " + ofToString(k));
            int iMax = outline[k].getVertices().size();
            
            for (int i=0; i<iMax; i++) {
                
                ofVec3f a = outline[k].getVertices()[i];
                ofVec3f b = outline[k].getVertices()[i] + zOffset;
                ofVec3f c = outline[k].getVertices()[(i+1) % iMax] + zOffset;
                ofVec3f d = outline[k].getVertices()[(i+1) % iMax];
                
                side.addVertex(a);
                side.addVertex(b);
                side.addVertex(c);
                
                side.addVertex(a);
                side.addVertex(c);
                side.addVertex(d);
                
//                side.addTriangle(i-2,i-1,i);
            }
        }
        // Push sides
        meshes.push_back( front );
        meshes.push_back( back );
        meshes.push_back( side );
        
//        for (int m=0; m<meshes.size(); m++) {
//            int vmax = meshes[m].getVertices().size();
//            
//            for (int n=0; n<vmax; n++) {
//                mesh.addVertex(meshes[m].getVertex(n));
//            }
//        }

	}
}


//--------------------------------------------------------------
void Vector::update(){

}

//--------------------------------------------------------------
void Vector::draw(){
	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 40);
    
    ofVec3f axis;
    float angle;
    curRot.getRotate(angle, axis);
    ofRotate(angle, axis.x, axis.y, axis.z);

    ofNoFill();
    for (int i = 0; i < meshes.size(); i++){
        meshes[i].drawWireframe();
        meshes[i].drawFaces();
    }
    
//    mesh.drawFaces();
	ofPopMatrix();
}

//--------------------------------------------------------------
void Vector::keyPressed(int key){
//    for (int i = 0; i < meshes.size(); i++){
//        meshes[i].save("mesh"+ofToString(i)+".ply");
//    }
    front.save("front.ply");
    back.save("back.ply");
    side.save("side.ply");
}

//--------------------------------------------------------------
void Vector::keyReleased(int key){
    ofLog(OF_LOG_NOTICE, "saving " +  ofToString(key));
//    mesh.save("3d.ply",false);
}

//--------------------------------------------------------------
void Vector::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void Vector::mouseDragged(int x, int y, int button){
	
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
void Vector::mousePressed(int x, int y, int button){
    //store the last mouse point when it's first pressed to prevent popping
	lastMouse = ofVec2f(x,y);
}

//--------------------------------------------------------------
void Vector::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void Vector::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void Vector::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void Vector::dragEvent(ofDragInfo dragInfo){
	
}

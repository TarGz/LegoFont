#include "Vector.h"

//--------------------------------------------------------------
void Vector::setup(){
	ofSetVerticalSync(true);
	dampen = .4;
    depth  =20;
	ofBackground(100, 100, 100);
	ofSetColor(255);
	
    
    // PLATE
	svg.load("map_all.svg");
	for (int i = 0; i < svg.getNumPath(); i++){
		ofPath p = svg.getPathAt(i);
        
        
        ofMesh front = p.getTessellation();
        ofMesh back = front;
        ofMesh side;
        
        ofVec3f* v = back.getVerticesPointer();
        ofVec3f* u = front.getVerticesPointer();
        
        // push the vertices of the back face back by depth
        for(int j=0; j< back.getNumVertices(); j++)
        {
            
            v[j].z += depth;
            
            ofPoint p1 = u[j];
            ofPoint p2 = v[j];

            side.addVertex(p1);
            side.addVertex(p2);
            side.addVertex(ofPoint(p1.x, p1.y, p1.z+depth));
            
//            side.addVertex(ofPoint(p1.x, p1.y, p1.z+depth));
//            side.addVertex(ofPoint(p2.x, p2.y, p2.z+depth));
//            side.addVertex(p2);
        }
        
        meshes.push_back( front );
        meshes.push_back( back );
        meshes.push_back( side );
        
        
		// svg defaults to non zero winding which doesn't look so good as contours
//		p.setPolyWindingMode(OF_POLY_WINDING_ODD);
//		vector<ofPolyline>& lines = p.getOutline();
//		for(int j=0;j<(int)lines.size();j++){
//			outlines.push_back(lines[j].getResampledBySpacing(1));
//		}
	}
}


//--------------------------------------------------------------
void Vector::update(){
	step += 0.001;
	if (step > 1) {
		step -= 1;
	}
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
//	ofRotate(mouseX);
//	float scale = ofMap(mouseY, 0, ofGetHeight(), .5, 10);
//	ofScale(scale, scale, scale);
//	ofTranslate(-250, -250);
//	if(ofGetMousePressed()) {
//		ofNoFill();
//		for (int i = 0; i < (int)outlines.size(); i++){
//			meshs[i].drawWireframe();
//		}
//	} else {
//		svg.draw();
//	}
//
    ofNoFill();
    for (int i = 0; i < meshes.size(); i++){
        meshes[i].drawWireframe();
    }
	ofPopMatrix();
}

//--------------------------------------------------------------
void Vector::keyPressed(int key){
	
}

//--------------------------------------------------------------
void Vector::keyReleased(int key){
	
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

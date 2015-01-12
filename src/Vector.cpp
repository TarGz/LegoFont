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
    plateHeight = 8*ldu*5;
    float studDiameter;
    float studHeight;
    
     ofLog(OF_LOG_NOTICE, "brickWidth " + ofToString(brickWidth));
    
    // CAM
    cam.setDistance(3000);
    
    
	ofBackground(100, 100, 100);
    ofEnableAlphaBlending();
	ofSetColor(255,255,255,100);
	
    
    // PLATE
	svg.load("map_all.svg");
	for (int i = 0; i < svg.getNumPath(); i++){
        ofMesh shape;
        ofMesh front;
        ofMesh back;
        ofMesh side;
        
        ofLog(OF_LOG_NOTICE, "i: " + ofToString(i));
        // GET PATH
		ofPath p = svg.getPathAt(i);
        // TESSELATE FRONT
        front = p.getTessellation();
        // BACK
        back = front;

        // VERTICES
        ofVec3f* v = back.getVerticesPointer();
        ofVec3f* u = front.getVerticesPointer();
        
        // push the vertices of the back face back by depth
        for(int j=0; j< front.getNumVertices(); j++)
        {
            
            v[j].z += plateHeight;
        }
        
        // OUTLINE
        vector<ofPolyline> outline = p.getOutline();
        ofVec3f zOffset(0,0,plateHeight);
        

        for (int k=0; k<outline.size(); k++) {
//            ofLog(OF_LOG_NOTICE, "k: " + ofToString(k));
//            ofLog(OF_LOG_NOTICE, "outline: " + ofToString(outline[0].getVertices()));
            int iMax = outline[k].getVertices().size();
            
            for (int j=0; j<iMax; j++) {
                ofLog(OF_LOG_NOTICE, "iMax: " + ofToString(j));
                ofVec3f a = outline[k].getVertices()[j];
                ofVec3f b = outline[k].getVertices()[j] + zOffset;
                ofVec3f c = outline[k].getVertices()[(j+1) % iMax] + zOffset;
                ofVec3f d = outline[k].getVertices()[(j+1) % iMax];
                
                side.addVertex(a);
                side.addVertex(b);
                side.addVertex(c);
                
                side.addVertex(a);
                side.addVertex(c);
                side.addVertex(d);
            }
        }
        // Push sides
        meshes.push_back( front );
        meshes.push_back( back  );
        meshes.push_back( side );

	}
}


//--------------------------------------------------------------
void Vector::update(){

}

//--------------------------------------------------------------
void Vector::draw(){
    cam.begin();
    
	ofRotateX(ofRadToDeg(.5));
	ofRotateY(ofRadToDeg(-.5));
	
	
	

    
//	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
//    ofPushMatrix();
//    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 40);
//    
//    ofVec3f axis;
//    float angle;
//    curRot.getRotate(angle, axis);
//    ofRotate(angle, axis.x, axis.y, axis.z);

//    ofNoFill();
    for (int i = 0; i < meshes.size(); i++){
        meshes[i].drawWireframe();
        meshes[i].drawFaces();
        
    }
    cam.end();
    drawInteractionArea();
}
//--------------------------------------------------------------
void Vector::drawInteractionArea(){
	ofRectangle vp = ofGetCurrentViewport();
	float r = MIN(vp.width, vp.height) * 0.5f;
	float x = vp.width * 0.5f;
	float y = vp.height * 0.5f;
	
	ofPushStyle();
	ofSetLineWidth(3);
	ofSetColor(255, 255, 0);
	ofNoFill();
	glDepthMask(false);
	ofCircle(x, y, r);
	glDepthMask(true);
	ofPopStyle();
}
//--------------------------------------------------------------
void Vector::keyPressed(int key){
    ofLog(OF_LOG_NOTICE, "key: " +  ofToString(key));
    
    if(key == 2305){
        shift = true;
    }
    
	switch(key) {
		case 'C':
		case 'c':
			if(cam.getMouseInputEnabled()) cam.disableMouseInput();
			else cam.enableMouseInput();
			break;
			
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
		case 'H':
		case 'h':
		
			break;
	}
    
    //front.save("front.ply");
    //back.save("back.ply");
    //side.save("side.ply");
}

//--------------------------------------------------------------
void Vector::keyReleased(int key){
    shift = false;
}

//--------------------------------------------------------------
void Vector::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void Vector::mouseDragged(int x, int y, int button){
	
    
    
    
//    // Drag if shift
//    if(shift){
//        ofLog(OF_LOG_NOTICE, "SHIFT");
//        ofTranslate(lastMouse.x - x , lastMouse.y - y);
//    }else{
//        //every time the mouse is dragged, track the change
//        //accumulate the changes inside of curRot through multiplication
//        
//        ofQuaternion yRot((x-lastMouse.x)*dampen, ofVec3f(0,1,0));
//        ofQuaternion xRot((y-lastMouse.y)*dampen, ofVec3f(-1,0,0));
//        curRot *= yRot*xRot;
//    }
//    ofVec2f mouse(x,y);
//    lastMouse = mouse;
    
}

//--------------------------------------------------------------
void Vector::mousePressed(int x, int y, int button){
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

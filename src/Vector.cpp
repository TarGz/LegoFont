#include "Vector.h"

//--------------------------------------------------------------
void Vector::setup(){
    
    ofEnableDepthTest();
    
    
	ofSetVerticalSync(true);
	dampen = .4;
    plateDepth  =20;
    
    // LDU Convertion
    ldu = 0.4;
    // BRICK SIZE
    brickWidth = 20*ldu;
    brickHeight = 24*ldu;
    plateHeight = 8*ldu*50;
    float studDiameter;
    float studHeight;
    
//     ofLog(OF_LOG_NOTICE, "brickWidth " + ofToString(brickWidth));
    
    // CAM
    cam.setDistance(3000);
    
    // MESH MODE
//    mesh.setMode(OF_PRIMITIVE_POINTS);
    
	ofBackground(100, 100, 100);
    ofEnableAlphaBlending();
	ofSetColor(255,255,255,250);
    
    // LIGTH
//    light.enable();
//    light.setDiffuseColor(ofColor::fromHsb(255, 255, 255));
//    light.setAmbientColor(ofColor::fromHsb(255, 255, 255));
    
    // MODE
    // OF_PRIMITIVE_TRIANGLES, OF_PRIMITIVE_TRIANGLE_STRIP, OF_PRIMITIVE_TRIANGLE_FAN, OF_PRIMITIVE_LINES, OF_PRIMITIVE_LINE_STRIP, OF_PRIMITIVE_LINE_LOOP, OF_PRIMITIVE_POINTS
    ofPrimitiveMode mode=OF_PRIMITIVE_TRIANGLES;
    front.setMode(mode);
    back.setMode(mode);
    side.setMode(mode);
    mesh.setMode(mode);
    
    ofMesh box;
    box = ofMesh::box(200.0, 200.0, 200.0);
//    mesh.append(box);
    // PLATE
	svg.load("map_all.svg");
    
	for (int i = 0; i < svg.getNumPath(); i++){
         ofLog(OF_LOG_NOTICE, "PATH N°" +ofToString(i));
        
        
        // TMP MESH
        ofMesh tmpSide;
        ofMesh tmpFront;
        ofMesh tmpBack;
        // MODE
        tmpSide.setMode(mode);
        tmpFront.setMode(mode);
        tmpBack.setMode(mode);

        // GET PATH
		ofPath p = svg.getPathAt(i);
        
        // FRONT
        tmpFront = p.getTessellation();
        ofLog(OF_LOG_NOTICE, "front normal : " + ofToString(front.getNormals()));
        ofVec3f frontNormal(0, 0, 1);
        tmpFront.addNormal(frontNormal);
        ofLog(OF_LOG_NOTICE, "front norma II: " + ofToString(front.getNormals()));
        ofVec3f* u = front.getVerticesPointer();
        
        // BACK
        tmpBack = tmpFront;
//        ofVec3f backNormal(0, 0, -1);
//        tmpBack.addNormal(backNormal);
        ofLog(OF_LOG_NOTICE, "back normal: " + ofToString(back.getNormals()));
        ofVec3f* v = tmpBack.getVerticesPointer();
        for(int j=0; j< tmpFront.getNumVertices(); j++)
        {
            v[j].z += plateHeight;
        }
        
        // SIDE
        vector<ofPolyline> outline = p.getOutline();
        ofVec3f zOffset(0,0,plateHeight);
        
        ofLog(OF_LOG_NOTICE, "OUTLINE size " +ofToString(outline.size()));
        
        int k = 0;

        ofLog(OF_LOG_NOTICE, "SIDE Vetresses" + ofToString(outline[k].getVertices()));
        int iMax = outline[k].getVertices().size();
        
        
        for (int j=0; j<iMax; j++) {
            ofVec3f a = outline[k].getVertices()[j];
            ofVec3f b = outline[k].getVertices()[j] + zOffset;
            ofVec3f c = outline[k].getVertices()[(j+1) % iMax] + zOffset;
            ofVec3f d = outline[k].getVertices()[(j+1) % iMax];
                
            tmpSide.addVertex(a);
            tmpSide.addVertex(b);
            tmpSide.addVertex(c);
                
            tmpSide.addVertex(a);
            tmpSide.addVertex(c);
            tmpSide.addVertex(d);
        }

        // Push sides
//        meshes.push_back( front );
//        meshes.push_back( side  );

//        mesh.append( side  );
        side.append( tmpSide  );
        front.append(tmpFront);
        back.append(tmpBack);
        


	}
    
    
//    mesh.append(front);
//    mesh.append(side);
}


//--------------------------------------------------------------
void Vector::update(){

}

//--------------------------------------------------------------
void Vector::draw(){
    cam.begin();
    
    ofRotateX(180);
	
    for (int i = 0; i < meshes.size(); i++){
//        meshes[i].drawWireframe();
//        meshes[i].drawFaces();
//        meshes[i].drawVertices();
    }
    
//    mesh.drawFaces();
    front.drawWireframe();
    side.drawWireframe();
    back.drawWireframe();
    cam.end();

}

//--------------------------------------------------------------
void Vector::keyPressed(int key){
    ofLog(OF_LOG_NOTICE, "key: " +  ofToString(key));
    
    
	switch(key) {
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
		case 'S':
		case 's':
            front.save("front.ply");
            back.save("back.ply");
            side.save("side.ply");
//            mesh.save("map.ply");
//            for (int i = 0; i < meshes.size(); i++){
//                meshes[i].save("map_"+ofToString(i)+".ply");
//            }
			break;
	}
    

}

//--------------------------------------------------------------
void Vector::keyReleased(int key){
    
}

//--------------------------------------------------------------
void Vector::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void Vector::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void Vector::mousePressed(int x, int y, int button){

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

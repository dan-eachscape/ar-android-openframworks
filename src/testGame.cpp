#include "testGame.h"


//--------------------------------------------------------------
void testGame::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	
    sender.setup(HOST, PORT);
    
	// enable depth->video image calibration
	kinect.setRegistration(true);
    
    
	//kinect.init();
	//kinect.init(true); // shows infrared instead of RGB video image
	kinect.init(false, false); // disable video image (faster fps)
	kinect.open();
	
#ifdef USE_TWO_KINECTS
	kinect2.init();
	kinect2.open();
#endif
    
    
	
    bCaptureBackground = true;
    
    depth.allocate(kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
    
    colorView.allocate(kinect.width, kinect.height);
    
    greyView.allocate(kinect.width, kinect.height);
    greyView_bg.allocate(kinect.width, kinect.height);
    
    greyDepth.allocate(kinect.width, kinect.height);
    greyDepth_bg.allocate(kinect.width, kinect.height);
    
    greyDiff.allocate(kinect.width, kinect.height);
    
    floatDepth.allocate(kinect.width, kinect.height);
    floatDepth_bg.allocate(kinect.width, kinect.height);
    floatDepthGrey.allocate(kinect.width, kinect.height);
    
	bThreshWithOpenCV = true;
	
	// zero the tilt on startup
	angle = 0;
	kinect.setCameraTiltAngle(angle);
	
	// start from the front
	bDrawPointCloud = false;
    bDrawGame = true;
    bDrawTrackerConfig = false;;
    
    
    thresDiff = 150.0;
    
	// Setup window
	ofSetFrameRate(100);	
}




//--------------------------------------------------------------
void testGame::update() {
	
	ofBackground(100, 100, 100);
    int i = 0; 
    int x = 0; 
    int y = 0;
    int inc= 6;
	kinect.update();
    if(kinect.isFrameNew()){
        floatDepth.setFromPixels(kinect.getDistancePixels(), kinect.width, kinect.height);
        
        ofxOscMessage m;
        m.addIntArg(kinect.width*kinect.height);
        m.setAddress( "/test" );
        string line; 
        while(i < floatDepth.getFloatPixelsRef().size()){
            float temp = kinect.getDistanceAt(x, y);
            
            if(x < kinect.width-1){
                x+=inc;
            }else{
                x = 0; 
                y+-inc;
                
            }
            i+=inc;
        }
        sender.sendMessage( m );
    }
}
            
//        floatDepth.setFromPixels(kinect.getDistancePixels(), kinect.width, kinect.height);
//        //colorView.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
//        //greyView.setFromColorImage(colorView);
//        
//        floatDepthGrey.setFromFloatImage(floatDepth);
//        
//         inpainter.inpaint(floatDepthGrey);
//        
//        //greyView.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
//        if(bCaptureBackground){
//            while(i < floatDepth.getFloatPixelsRef().size()){
//                float temp = floatDepth.getFloatPixelsRef()[i];
//                //float m = ofMap(temp, 0 , 10000, 0, 255);
//                floatDepth_bg.getFloatPixelsRef()[i] = temp;
//                //floatDepth.getFloatPixelsRef()[i] = m;
//                depth_k[x][y] = temp;
//                if(x < kinect.width-1){
//                    x+=3;
//                }else{
//                    x = 0; 
//                    y+-3;
//                }
//                i+=3;
//            }
//            greyView_bg = greyView;
//            floatDepth_bg.flagImageChanged();
//            floatDepth.flagImageChanged();
//        }
//        
//        
//        i = 0; 
//        x = 0; 
//        y = 0;
//        while(i < floatDepth.getFloatPixelsRef().size()){
//            float temp = floatDepth.getFloatPixelsRef()[i];
//            float ma = ofMap(temp, 0, 10000, 0, 500);
//            
//            if(temp > depth_k[x][y] - 250 && temp < depth_k[x][y] + 250){
//                floatDepth.getFloatPixelsRef()[i] = 0;
//                depth.getPixelsRef()[i] = 0;
//            }else{
//                depth.getPixelsRef()[i] = char(temp);
////                floatDepth.getFloatPixelsRef()[i] = temp;
//                ofxOscMessage m;
//                m.setAddress( "/test" );
//                m.addIntArg(x);
//                m.addIntArg(y);
//                m.addFloatArg(ma);
//                sender.sendMessage( m );
////            }
//            if(x < kinect.width-1){
//                x+=5;
//            }else{
//                x = 0; 
//                y+=5;
//            }
//            i+=5;
//        }
//        
//        floatDepth.flagImageChanged();
//        //depth.reloadTexture();
//        greyDepth.setFromPixels(depth.getPixels(), depth.width, depth.height);
//        //greyDepth.setFromFloatImage(floatDepth);
//        
//        
//       
//    
//        
//    
//        
//        //if(bCaptureBackground){
//        //    bCaptureBackground = false;
//        //    greyDepth_bg = greyDepth;
//        //}
//     
//        //greyView.absDiff(greyView_bg);
//        //greyView.blur(11);
//        //greyView.threshold(30);
//        
//        //greyDiff.absDiff(greyDepth_bg, greyDepth);
//        //greyDepth.blur(11);
//        //greyDiff.threshold(80);
//        
//        //contourFinderView.findContours(greyView, 200, (kinect.width*kinect.height)/2, 20, false, true);
//        //contourFinderDepth.findContours(greyDiff, 200, (kinect.width*kinect.height)/2, 20, false, true);


//--------------------------------------------------------------
void testGame::draw() {
	
	ofSetColor(255, 255, 255);
	
	if(bDrawPointCloud) {
		easyCam.begin();
		drawPointCloud();
		easyCam.end();
	} if(bDrawTrackerConfig){
		//drawConfig();
    
#ifdef USE_TWO_KINECTS
		kinect2.draw(420, 320, 400, 300);
#endif
	} if(bDrawGame){
        drawTracking();
    } else{
    
    }
	
	// draw instructions
//	ofSetColor(255, 255, 255);
//	stringstream reportStream;
//	reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
//	<< ofToString(kinect.getMksAccel().y, 2) << " / "
//	<< ofToString(kinect.getMksAccel().z, 2) << endl
//	<< "press p to switch between images and point cloud, rotate the point cloud with //the mouse" << endl
	//<< "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
//	<< "set near threshold " << nearThreshold << " (press: + -)" << endl
//	<< "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs
//	<< ", fps: " << ofGetFrameRate() << endl
//	<< "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl
//	<< "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl;
//	ofDrawBitmapString(reportStream.str(),20,652);
}


void testGame::filterBackgroundDebug(){
    
    //greyView.draw(0,0,640,480);
    //contourFinderView.draw(0,0,640,480);
    //greyDepth.draw(640,0,640,480);
    //contourFinderDepth.draw(640, 0,640,480);
    //greyView_bg.draw(0, 480, 320, 240);
    //floatDepth_bg.draw(320, 480, 320, 240);
    floatDepth.draw(640, 0, 640, 480);
    kinect.drawDepth(0, 0, 640, 480);
    //floatDepthGrey.draw(960, 480, 320, 240);

}
    //grayImage_L2.draw(360, 640, 320, 240);pth(){


void testGame::resetGame(){
    bCaptureBackground = true;
    for(int i = 0 ; i < 640; i++){
        for(int j = 0 ; j < 480; j++){
            depth_k[i][j] = 0;
            image_k[i][j] = 8;
        }
    }
}

void testGame::drawTracking(){
    filterBackgroundDebug();
}


void testGame::drawPointCloud() {
	int w = 640;
	int h = 480;
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_POINTS);
	int step = 1;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
            float temp =kinect.getDistanceAt(x,y);
            
			if(temp > nearThreshold && temp < farThreshold*20) {
				mesh.addColor(1.0);
				mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
			}
		}
	}
	glPointSize(3);
	ofPushMatrix();
	// the projected points are 'upside down' and 'backwards' 
	ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
	glEnable(GL_DEPTH_TEST);
	mesh.drawVertices();
	glDisable(GL_DEPTH_TEST);
	ofPopMatrix();
}

//--------------------------------------------------------------
void testGame::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
	
#ifdef USE_TWO_KINECTS
	kinect2.close();
#endif
}

//--------------------------------------------------------------
void testGame::keyPressed (int key) {
	switch (key) {
			
		case'p':
			bDrawPointCloud = !bDrawPointCloud;
            if(bDrawTrackerConfig) 
                bDrawTrackerConfig = !bDrawTrackerConfig;
            if(bDrawGame)
                bDrawGame = !bDrawGame;
            
			break;
			
		case '>':
		case '.':
			farThreshold ++;
			if (farThreshold > 255) farThreshold = 255;
			break;
			
		case '<':
		case ',':
			farThreshold --;
			if (farThreshold < 0) farThreshold = 0;
			break;
			
		case '+':
		case '=':
			nearThreshold ++;
			if (nearThreshold > 255) nearThreshold = 255;
			break;
			
		case '-':
			nearThreshold --;
			if (nearThreshold < 0) nearThreshold = 0;
			break;
			
		case 'w':
			kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
			break;
			
		case 'o':
			kinect.setCameraTiltAngle(angle); // go back to prev tilt
			kinect.open();
			break;
			
		case 'c':
			kinect.setCameraTiltAngle(0); // zero the tilt
			kinect.close();
			break;
            
        case 'a':
            farT2 = farThreshold;
            nearT2 = nearThreshold;
            break;
            
        case 'b':
            farT3 = farThreshold;
            nearT3 = nearThreshold;
            break;
        case ' ':
            bCaptureBackground = true;
            break;
        case 'g':
            bDrawGame = !bDrawGame;
            
            if(bDrawPointCloud)
                bDrawPointCloud = !bDrawPointCloud;
            if(bDrawTrackerConfig) 
                bDrawTrackerConfig = !bDrawTrackerConfig;
            resetGame();
            break;
        case 'd':
            bDrawTrackerConfig = !bDrawTrackerConfig;
            if(bDrawPointCloud)
                bDrawPointCloud = !bDrawPointCloud;
            if(bDrawGame)
                bDrawGame = !bDrawGame;
            break;
            
        case OF_KEY_LEFT:
            thresDiff-=2;
            break;
            
        case OF_KEY_RIGHT:
            thresDiff+= 2;
            break;
            
 		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
	}
}

//--------------------------------------------------------------
void testGame::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void testGame::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void testGame::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void testGame::windowResized(int w, int h)
{}

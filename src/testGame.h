#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxOsc.h"
#include "ofxKinect.h"
#include "ofxCvMain.h"
#include "ofxCvBlobTracker.h"
#include "ofxCvTrackedBlob.h"
#include "ofxCvConstants_Track.h"
#include "ofxKinectInpainter.h"


#define HOST "192.168.1.30"
#define PORT 12345

// uncomment this to read from two kinects simultaneously
//#define USE_TWO_KINECTS

class testGame : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void drawPointCloud();
    void drawTracking();
    void drawGame();
    void drawConfig();
	
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
    void filterBackgroundDebug();
    void resetGame();
	ofxKinect kinect;
	
    
#ifdef USE_TWO_KINECTS
	ofxKinect kinect2;
#endif
    
    ofxOscSender sender;

	ofxCvColorImage colorView;
    ofxCvColorImage colorView_bg;
    
    
    ofxCvGrayscaleImage colorView_R;
    ofxCvGrayscaleImage colorView_G;
    ofxCvGrayscaleImage colorView_B;
    
    ofxCvGrayscaleImage colorView_R_bg;
    ofxCvGrayscaleImage colorView_G_bg;
    ofxCvGrayscaleImage colorView_B_bg;
    
    ofxKinectInpainter inpainter;
    
    ofxCvGrayscaleImage greyView;
    ofxCvGrayscaleImage greyView_bg;
    
    ofxCvGrayscaleImage greyDepth;
    ofxCvGrayscaleImage greyDepth_bg;
    ofxCvGrayscaleImage greyDiff;
    
    ofxCvGrayscaleImage floatDepthGrey;
    ofxCvGrayscaleImage floatDepthGrey_bg;
    
    
    ofxCvFloatImage floatDepth;
    ofxCvFloatImage floatDepth_bg;
    
    ofxCvShortImage rawCV;
    ofxCvShortImage rawCV_bg;
    
    ofxCvGrayscaleImage rawGray;
    ofxCvGrayscaleImage rawGray_bg;
    
    ofShortImage rawDepth;
    ofShortImage rawDepth_bg;

    ofImage depth;
    
    ofxCvContourFinder contourFinderDepth;
    ofxCvContourFinder contourFinderView;
    
	bool bThreshWithOpenCV;
	bool bDrawPointCloud;
    bool bDrawTrackerConfig;
    bool bDrawGame;
    
    bool bCaptureBackground;
	
	int nearThreshold;
	int farThreshold;
    int farT2;
    int nearT2;
    int farT3;
    int nearT3;
	float depth_k[640][480];
    float depth_l[640][480];
    float depth_x[640][480];
  
    int image_k[640][480];
	int angle;
	float thresDiff;
    
	// used for viewing the point cloud
	ofEasyCam easyCam;
};

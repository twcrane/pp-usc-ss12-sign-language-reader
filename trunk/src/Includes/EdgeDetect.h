/*
 * EdgeDetect.h
 *
 *  Created on: 04-Mar-2010
 *      Author: parth
 */
#include "Prerequs.h"

#ifndef EDGEDETECT_H_
#define EDGEDETECT_H_


class EdgeDetect : FeatureDetector{

public:
	/**
	 * Detect the hand in the image and return it
	 */
	CvRect detect(IplImage* InputImage){

	}
	/**
	 *
	 */
	IplImage* detect(IplImage* InputImage){
		// Do the detection and return the detected image
		IplImage* Dest = cvCreateImage(cvSize(InputImage->width,InputImage->height),IPL_DEPTH_8U,1);
		cvCanny(InputImage,Dest,0.5,1);
		cvReleaseImage(InputImage);
		return Dest;
	}
	/**
	 *
	 */
	void load(string filename){
		// load the settings from the given filename

	}

};

#endif /* EDGEDETECT_H_ */

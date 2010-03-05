/*
 * NoDetector.h
 *
 *  Created on: 04-Mar-2010
 *      Author: parth
 */
#include "Prerequs.h"
#ifndef NODETECTOR_H_
#define NODETECTOR_H_

class NoDetector{

	/**
	 * Detect the hand in the image and return it
	 */
	CvRect detect(IplImage* InputImage){
		// Do Nothing
	}
	/**
	 *
	 */
	IplImage* detect(IplImage* InputImage){
		// Do the detection and return the detected image
		IplImage *temp= cvCreateImage(cvSize(InputImage->width,InputImage->height),IPL_DEPTH_8U,1);
		cvCopy(InputImage,temp);
		cvReleaseImage(InputImage);
		return temp;
	}
	/**
	 *
	 */
	void load(string filename){
		// load the settings from the given filename

		// Do nothing for now
	}

};

#endif /* NODETECTOR_H_ */

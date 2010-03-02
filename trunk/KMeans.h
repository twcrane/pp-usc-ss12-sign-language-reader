/*
 * KMeans.h
 *
 *  Created on: 27-Feb-2010
 *      Author: parth
 */

#include "cv.h"
#include "highgui.h"
#include "ml.h"
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <iostream>

#ifndef KMEANS_H_
#define KMEANS_H_

using namespace std;

#define IMGWIDTH 128
#define IMGHEIGHT 96
#define IMGSIZE 128*96

class KMeans{

	CvKNearest Knearest;
    // 2D Matrix storing values
    CvMat* Matrix;
    CvMat* Labels;
    CvMat* Clusters;
    int Length;
public:
    /**
     * ReadDirectories
     */
    void ReadDirectories(vector<string> &, string );
    /**
	 * Flatten Images into the Matrix
	 * TOBECHECKED
	 */
	IplImage** flattenImage(IplImage* , int& );
	/**
	 * ProcessImage
	 */
	IplImage* ProcessImage(IplImage* );
	/**
	 * Process Directory
	 */
	void ProcessDirectory(string , int &, int );
    /**
     * Constructor
     */
	KMeans(string , int );

	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void Train();
	/**
	 * Test the Image
	 */
	float Test(IplImage* );
	//float Test(IplImage*);
	//**********************************************************************************************************************/
	~KMeans();
};

#endif /* KMEANS_H_ */

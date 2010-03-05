/*
 * NN.h
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
//#include "BlobRecognition/BlobRecognizer.h"

#ifndef NN_H_
#define NN_H_

using namespace std;

//#define IMGWIDTH 128
//#define IMGHEIGHT 96
#define IMGWIDTH 32
#define IMGHEIGHT 24

#define IMGSIZE IMGHEIGHT*IMGWIDTH

class NN{

	CvANN_MLP NNModel;
    // 2D Matrix storing values
    CvMat* Matrix;
    CvMat* Labels;
    //CvMat* Clusters;
    int Length;

    //BlobRecognizer b;
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
	NN(string , int );

	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void Train();
	/**
	 * Test the Image
	 */
	float Test(IplImage* );
	float Test(string);

	float save (string filename);
	float Load (string filename);
	//**********************************************************************************************************************/
	~NN();
};

#endif /* NN_H_ */

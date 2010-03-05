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

class NN : ML{

	CvANN_MLP NNModel;
    // 2D Matrix storing values
    CvMat* Matrix;
    CvMat* Labels;
    //CvMat* Clusters;
    int Length;

    //BlobRecognizer b;
public:

	NN(string , int );

	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void Train();
	/**
	 * Test the Image
	 */
	float test(IplImage* );
	float test(string);
	void create(int nLayers);
	float save (string filename);
	float load (string filename);
	//**********************************************************************************************************************/
	~NN();
};

#endif /* NN_H_ */

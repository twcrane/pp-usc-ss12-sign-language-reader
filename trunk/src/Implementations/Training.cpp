#include "ml.h"
#include "interfaces/InputReader.h"

/*
 * Training.cpp
 *
 *  Created on: 04-Mar-2010
 *      Author: parth patel
 */

class Training{

    CvMat* Matrix;
    int Counter;

    CvMat* Labels;

public:
	/**
	 *  Read the training dataset
	 */
    Training(InputReader reader, FeatureDetector fd, ML ml){

    	Counter = 0;
    	// Get the Number of Images
    	int NumberOfImages = reader.numberofimages();

    	// Initialize Matrix.
		Matrix = cvCreateMat(NumberOfImages,IMGSIZE,CV_32FC1);
		Labels = cvCreateMat(NumberOfImages,1,CV_32FC1);

		//////


	}


	/**
	 * Flatten the Image into the Matrix
	 */
	void FlattenImage(IplImage* Image, int Label){
		for (int i=0; i< Image->height; i++)
			for (int j=0; j< Image->width; j++)
				cvSetReal2D(Matrix, Counter,i*Image->width + j,cvGetReal2D(Image,i,j));

		cvSetReal1D(Labels,Counter,Label);
		Counter ++ ;
	}
};

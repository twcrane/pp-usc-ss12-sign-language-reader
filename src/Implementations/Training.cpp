
/*
 * Training.cpp
 *
 *  Created on: 04-Mar-2010
 *      Author: parth patel
 */
#include "Training.h"

Training::Training(InputReader reader, FeatureDetector fd, ML ml){

    	Counter = 0;
    	// Get the Number of Images
    	int NumberOfImages = reader.numberofimages();

    	// Initialize Matrix.
		Matrix = cvCreateMat(NumberOfImages,IMGSIZE,CV_32FC1);
		Labels = cvCreateMat(NumberOfImages,1,CV_32FC1);
		int classNumber=0;
		while((IplImage* img=reader.next(classNumber))!=NULL)
		{
			img=fd.detect(img);
			FlattenImage(img,classNumber);
		}
		ml.train(Matrix,Labels);
		ml.save("MLTraining");
}
/**
 * Flatten the Image into the Matrix
 */
void Training::FlattenImage(IplImage* Image, int Label){
	for (int i=0; i< Image->height; i++)
		for (int j=0; j< Image->width; j++)
			cvSetReal2D(Matrix, Counter,i*Image->width + j,cvGetReal2D(Image,i,j));

	cvSetReal1D(Labels,Counter,Label);
	Counter ++ ;
}

/*
 * Training.h
 *
 *  Created on: 05-Mar-2010
 *      Author: parth
 */

#ifndef TRAINING_H_
#define TRAINING_H_

#include "Prerequs.h"
#include "KNN.h"
#include "FolderReader.h"

class Training{

    CvMat* Matrix;
    int Counter;
    CvMat* Labels;
    ML* StoredML;

public:
	/**
	 *  Read the training dataset
	 */
    Training(InputReader *reader, FeatureDetector *fd, ML *ml);
	/**
	 * Flatten the Image into the Matrix
	 */
	void FlattenImage(IplImage* Image, int Label);
	/**
	 * Test the image using the learned model
	 */
	int test(IplImage*);

};

#endif /* TRAINING_H_ */

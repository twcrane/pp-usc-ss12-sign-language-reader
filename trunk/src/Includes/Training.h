/*
 * Training.h
 *
 *  Created on: 05-Mar-2010
 *      Author: parth
 */
#include "interfaces/InputReader.h"
#include "interfaces/ML.h"
#include "interfaces/FeatureDetector.h"

#ifndef TRAINING_H_
#define TRAINING_H_
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
	int test(IplImage*);

};

#endif /* TRAINING_H_ */

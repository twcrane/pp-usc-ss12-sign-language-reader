/*
 * KMeans.h
 *
 *  Created on: 27-Feb-2010
 *      Author: parth
 */

#include "Prerequs.h"

#ifndef KMEANS_H_
#define KMEANS_H_

using namespace std;

class KMeans : ML{

	CvKNearest Knearest;
    // 2D Matrix storing values
    CvMat* Matrix;
    CvMat* Labels;
//    CvMat* Clusters;
    int Length;
public:

	KMeans(string , int );
	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void train();
	/**
	 * Test the Image
	 */
	float test(IplImage* );
	//float Test(IplImage*);
	//**********************************************************************************************************************/
	~KMeans();
	/**
	 *
	 */
	void save(string filename);
	/**
	 *
	 */
	void load(string filename);
};

#endif /* KMEANS_H_ */

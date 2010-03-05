/*
 * KMeans.h
 *
 *  Created on: 27-Feb-2010
 *      Author: parth
 */

#include "Prerequs.h"

#include "Prerequs.h"
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

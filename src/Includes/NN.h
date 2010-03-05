/*
 * NN.h
 *
 *  Created on: 27-Feb-2010
 *      Author: parth
 */

#include "Prerequs.h"

#ifndef NN_H_
#define NN_H_

using namespace std;

class NN : ML{

	CvANN_MLP NNModel;
    // 2D Matrix storing values
    CvMat* Matrix;
    CvMat* Labels;
    //CvMat* Clusters;
    int Length;

    //BlobRecognizer b;
public:

	NN();

	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void train();
	/**
	 * Test the Image
	 */
	float test(IplImage* );
	float test(string);
	void create(int nLayers);
	void save (string filename);
	void load (string filename);
	//**********************************************************************************************************************/
	~NN();
};

#endif /* NN_H_ */

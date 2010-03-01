/*
 * VotingFrameWork.h
 *
 *  Created on: 28-Feb-2010
 *      Author: parth
 */

#include "math.h"
#include "stdio.h"
#include <vector>
#include <fstream>
#include <iostream>

#include "NN.h"
#include "KMeans.h"


#ifndef VOTINGFRAMEWORK_H_
#define VOTINGFRAMEWORK_H_

class VotingFrameWork{
	NN *NeuralNet;
	KMeans *kmeans;
public:
	/**
	 *
	 */
	VotingFrameWork(){
		NeuralNet = new NN("../DataNN",atoi(argv[1]));
		kmeans = new KMeans("../Data",atoi(argv[1]));
	}
	/**
	 *
	 */
	void Train(){
		NeuralNet->Train();
		kmeans->Train();
	}
	/**
	 *
	 */
	void Load(){
		NeuralNet->Load("Models","NN");
		kmeans->Load("Models","KNN");
	}
	/**
	 *
	 */
	void Save(){
		NeuralNet->Save("Models","NN");
		kmeans->Save("Models","KNN");
	}
	/**
	 * Test
	 */
	int Test(IplImage* Image){
		cout << NeuralNet->Test(Image) << endl;
		cout << kmeans->Test(Image) << endl;
	}
	/**
	 * Test
	 */
	int Test(string FileName){
		cout << NeuralNet->Test(FileName) << endl;
		cout << kmeans->Test(FileName) << endl;
	}

};

#endif /* VOTINGFRAMEWORK_H_ */

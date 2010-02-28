/*
 * KMeans.h
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

#ifndef KMEANS_H_
#define KMEANS_H_

using namespace std;

#define IMGWIDTH 64
#define IMGHEIGHT 48
#define IMGSIZE 64*48

class KMeans{

	CvKNearest Knearest;
    // 2D Matrix storing values
    CvMat* Matrix;
    CvMat* Labels;
    CvMat* Clusters;
public:
    /**
     * ReadDirectories
     */
    void ReadDirectories(vector<string> &q, string Dir);
    /**
	 * Flatten Images into the Matrix
	 * TOBECHECKED
	 */
	IplImage** flattenImage(IplImage* Image, int& Counter);
	/**
	 * ProcessImage
	 */
	IplImage* ProcessImage(IplImage* im_gray){

		 IplImage *resized = cvCreateImage(cvSize(IMGWIDTH,IMGHEIGHT),IPL_DEPTH_8U,1);
		 cvResize(im_gray,resized,0);
		 cvReleaseImage(&im_gray);
		 // Normalize
		 cvNorm(resized, NULL, CV_L1);
		 // Return
  		 return resized;
	}
	/**
	 * Process Directory
	 */
	void ProcessDirectory(string directory, int &Counter, int Label){
		  directory += "/";

		  DIR* dir = opendir(directory.c_str());
		  struct dirent* d_entry;

		  string Temp;

		  // Loop for all the entries into the directory
		  while((d_entry=readdir(dir))!=NULL){
			 // Read the Image
			     Temp = directory;
				 Temp += d_entry->d_name;
				 IplImage *im_gray = cvLoadImage(Temp.c_str(),0);

			 // Read the image, change to grayscale and resize it
				 cvReleaseImage(    flattenImage(       ProcessImage(im_gray), Counter  )  );
                 // Set the Label
                 cvSetReal1D(Labels,Counter,Label);
                 // Increment the Counter
                 Counter++;
		 }
	}

    /**
     * Constructor
     */
	KMeans(string Dir, int NumberOfImages){
		// Initialize matrices
			Matrix = cvCreateMat(NumberOfImages,IMGSIZE,CV_8UC1);
			Labels = cvCreateMat(NumberOfImages,1,CV_8UC1);
		//
			vector<string> Directories;
			ReadDirectories(Directories, Dir);

	    // Process one directory at a time
            int MatCounter = 0;

            for (int i=0; i<Directories.size(); i++)
                 ProcessDirectory(Directories[i],MatCounter,atoi(Directories[i].c_str()));

        // Allocate the clusters finally
            Clusters = cvCreateMat(Directories.size(),IMGSIZE,CV_8UC1);
	}


	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void Train(){
		Knearest.train(Matrix,Labels,NULL,false,Labels->width,false);
	}
	/**
	 * Test the Image
	 */
	float Test(IplImage* Image){

		CvMat* Sample = cvCreateMat(1,IMGSIZE,IPL_DEPTH_8U);
		Image = ProcessImage(Image);

		for (int i=0; i< Image->width; i++)
			for (int j=0; j< Image->height; j++)
				cvSet2D(Sample,0,i*Image->width + j,cvGet2D(Image,i,j));

		return Knearest.find_nearest(Sample,1);
	}

	//**********************************************************************************************************************/
	~KMeans(){	}
};

#endif /* KMEANS_H_ */

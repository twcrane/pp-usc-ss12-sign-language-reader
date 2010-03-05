#include "KNN.h"
//#include "BlobRecognition/BlobRecognizer.h"

 	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void KNN::train(CvMat* Matrix, CvMat* Labels){
			Knearest.train(Matrix,Labels,NULL,false,Max_K,false);
	}
	/**
	 * Test the Image
	 */
	float KNN::test(IplImage *Image)
	{
		// Process the Image
		IplImage *tempImg = cvCreateImage(cvSize(Image->width,Image->height),8,1);
		cvCvtColor(Image,tempImg,CV_BGR2GRAY);

		CvMat* Sample = cvCreateMat(1,IMGSIZE,CV_32FC1);

		IplImage *resized = cvCreateImage(cvSize(IMGWIDTH,IMGHEIGHT),Image->depth,1);
		cvResize(tempImg,resized,0);
		cvReleaseImage(&tempImg);

		// flatten it
		for (int i=0; i< tempImg->height; i++)
			for (int j=0; j< tempImg->width; j++)
				cvSet2D(Sample,0,i*resized->width + j,cvGet2D(resized,i,j));

		// test it
		return Knearest.find_nearest(Sample,1);
	}

	//**********************************************************************************************************************/
	KNN::~KNN(){ }

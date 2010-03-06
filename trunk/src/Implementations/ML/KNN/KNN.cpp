#include "KNN.h"
//#include "BlobRecognition/BlobRecognizer.h"

 	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void KNN::train(CvMat* Matrix, CvMat* Labels){

		cout << Max_K <<endl;
			Knearest.train(Matrix,Labels,NULL,false,Max_K,false);
	}
	/**
	 * Test the Image
	 */
	float KNN::test(IplImage *Image)
	{
		cout << __FILE__<<"-"<<__LINE__ << endl;

		// Process the Image
		IplImage *tempImg = cvCreateImage(cvSize(Image->width,Image->height),8,1);
		cvCvtColor(Image,tempImg,CV_BGR2GRAY);

		CvMat* Sample = cvCreateMat(1,IMGSIZE,CV_32FC1);

		IplImage *resized = cvCreateImage(cvSize(IMGWIDTH,IMGHEIGHT),Image->depth,1);
		cvResize(tempImg,resized,0);
		cvReleaseImage(&tempImg);

		// flatten it
		for (int i=0; i< resized->height; i++)
			for (int j=0; j< resized->width; j++)
				cvSet2D(Sample,0,i*resized->width + j,cvGet2D(resized,i,j));


		cout << __FILE__<<"-"<<__LINE__ << endl;
		// test it
		return Knearest.find_nearest(Sample,1);
	}

	/**
	 *
	 */
	void KNN::save(string filename){

	}
	/**
	 *
	 */
	void KNN::load(string filename){

	}

	//**********************************************************************************************************************/
	KNN::~KNN(){ }

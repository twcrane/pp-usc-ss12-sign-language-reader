#include "KNN.h"
//#include "BlobRecognition/BlobRecognizer.h"

    /**
     * Constructor
     */
	KNN::KNN(){}
	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void KNN::train(){
		cout << "what \n";
		try{
			cout << Matrix->width << " - " << Matrix->height << "-"<< Length<< "-" << Labels->height << endl;
			Knearest.train(Matrix,Labels,NULL,false,Length,false);
		}catch(exception e){
			cout << e.what() <<endl;
		}
		cout << Length << endl;
	}
	/**
	 * Test the Image
	 */
	float KNN::test(IplImage *Image)
	{
		IplImage *tempImg = cvCreateImage(cvSize(Image->width,Image->height),8,1);
		cvCvtColor(Image,tempImg,CV_BGR2GRAY);

		CvMat* Sample = cvCreateMat(1,IMGSIZE,CV_32FC1);

		///tempImg = ProcessImage(tempImg);

		IplImage *resized = cvCreateImage(cvSize(IMGWIDTH,IMGHEIGHT),im_gray->depth,1);
		cvResize(tempImg,resized,0);
		cvReleaseImage(&tempImg);


		for (int i=0; i< tempImg->height; i++)
			for (int j=0; j< tempImg->width; j++)
				cvSet2D(Sample,0,i*resized->width + j,cvGet2D(resized,i,j));

		return Knearest.find_nearest(Sample,1);
	}

	//**********************************************************************************************************************/
	KNN::~KNN(){ }

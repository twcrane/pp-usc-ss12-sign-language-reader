#include "NN.h"

    /**
     * Constructor
     */
	NN::NN(){	}


	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void NN::train(){
		cout << Matrix->width << " - " << Matrix->height << "-"<< Length<< "-" << Labels->height << endl;
		int layer_sz[] = { Matrix->cols, int(Matrix->cols/4), Length };
		CvMat layer_sizes =	cvMat( 1, (int)(sizeof(layer_sz)/sizeof(layer_sz[0])), CV_32S, layer_sz );
		NNModel.create( &layer_sizes, CvANN_MLP::SIGMOID_SYM );
		NNModel.train( Matrix, Labels, 0, 0,
			CvANN_MLP_TrainParams(cvTermCriteria(CV_TERMCRIT_ITER,10000,0.001),
			CvANN_MLP_TrainParams::RPROP,0.01));
		cout << Length << endl;
		save("NNModel");
	}
	/**
	 * Test the Image
	 */
	float NN::test(IplImage* Image){

		CvMat* Sample = cvCreateMat(1,IMGSIZE,CV_8U);

		IplImage *resized = cvCreateImage(cvSize(IMGWIDTH,IMGHEIGHT),Image->depth,1);
		cvResize(Image,resized,0);
		cvReleaseImage(&Image);

		for (int i=0; i< Image->width; i++)
			for (int j=0; j< Image->height; j++)
				cvSet2D(Sample,0,i*resized->width + j,cvGet2D(resized,i,j));

		cvReleaseImage(&resized);

		 CvMat *output = cvCreateMat(1,Length,CV_32F);
		 NNModel.predict(Sample,output);

		 int min = 10000;
		 for (int i=0; i<Length;i++)
		 {
			 cout << cvGetReal2D(output,0,i) << "  ";
			 if (min > cvGetReal2D(output,0,i))
				 min = i;
		 }

		 return min;
	}
	/*
	 *
	 */
	void NN::save (string filename){
		NNModel.save(filename.c_str(),"wht");
	}

	/*
	 *
	 */
	void NN::load (string filename){
		NNModel.load(filename.c_str(),"wht");
	}
	/**
	 *
	 */
	void NN::create(int nLayers) {

	}
	//**********************************************************************************************************************/
	NN::~NN(){	}

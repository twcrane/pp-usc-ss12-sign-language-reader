#include "NN.h"

    /**
     * Constructor
     */
	NN::NN(string Dir, int NumberOfImages){
		// Initialize matrices
			Matrix = cvCreateMat(NumberOfImages,IMGSIZE,CV_32FC1);
		//
			vector<string> Directories;
			ReadDirectories(Directories, Dir);
			Length = Directories.size();

			Labels = cvCreateMat(NumberOfImages,Length,CV_32FC1);

	    // Process one directory at a time
            int MatCounter = 0;
        	cout<<"Size" << Directories.size()<<endl;

            for (int i=0; i<Directories.size(); i++)
                 ProcessDirectory(Dir + "/" + Directories[i],MatCounter,atoi(Directories[i].c_str()));
	}


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

		CvMat* Sample = cvCreateMat(1,IMGSIZE,IPL_DEPTH_8U);
		Image = ProcessImage(Image);

		for (int i=0; i< Image->width; i++)
			for (int j=0; j< Image->height; j++)
				cvSet2D(Sample,0,i*Image->width + j,cvGet2D(Image,i,j));

		cvReleaseImage(&Image);

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
	float NN::save (string filename){
		NNModel.save(filename.c_str(),"wht");
	}

	/*
	 *
	 */
	float NN::load (string filename){
		NNModel.load(filename.c_str(),"wht");
	}
	/**
	 *
	 */
	void NN::create(int nLayers) {

	}
	/**
	 * Test the Image
	 */
	float NN::test(string FileName){

		IplImage* Image;
		CvMat* Sample = cvCreateMat(1,IMGSIZE,CV_32F);
		Image = ProcessImage(cvLoadImage(FileName.c_str(),0));

		for (int i=0; i< Image->height; i++)
			for (int j=0; j< Image->width; j++)
				cvSet2D(Sample,0,i*Image->width + j,cvGet2D(Image,i,j));

		cvReleaseImage(&Image);

		 cout<< "Testing\n";

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

	//**********************************************************************************************************************/
	NN::~NN(){	}

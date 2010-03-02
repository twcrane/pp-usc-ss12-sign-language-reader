#include "NN.h"
    /**
     * ReadDirectories
     */
    void NN::ReadDirectories(vector<string> &q, string Dir){
		// Read all the directories
		DIR *dir = opendir(Dir.c_str());
		cout << Dir << endl;
		if (!dir)
			return;
		struct dirent *d_entry;

		while ((d_entry=readdir(dir))!=NULL)
			if (strcmp(d_entry->d_name,".") != 0 && strcmp(d_entry->d_name,"..") != 0)
				q.push_back(d_entry->d_name);
		closedir(dir);
    }
    /**
	 * Flatten Images into the Matrix
	 * TOBECHECKED
	 */
	IplImage** NN::flattenImage(IplImage* Image, int& Counter){

		for (int i=0; i< Image->height; i++)
			for (int j=0; j< Image->width; j++)
				cvSetReal2D(Matrix, Counter,i*Image->width + j,cvGetReal2D(Image,i,j));
		return &Image;
    }
	/**
	 * ProcessImage
	 */
	IplImage* NN::ProcessImage(IplImage* im_gray){
		 //cout << __LINE__ << endl;
		 //im_gray = b.Runit(im_gray);
		 //cout << __LINE__ << endl;
		 IplImage *resized = cvCreateImage(cvSize(IMGWIDTH,IMGHEIGHT),IPL_DEPTH_8U,1);
		 cvResize(im_gray,resized,0);
			 cvReleaseImage(&im_gray);
			 //cout << __LINE__ << endl;
	     // Return
  		 return resized;
	}
	/**
	 * Process Directory
	 */
	void NN::ProcessDirectory(string directory, int &Counter, int Label){
		//cout << __LINE__ << endl;
		  directory += "/";
		  //cout << "Inside Process"  << directory << endl;
		  DIR* dir = opendir(directory.c_str());
		  struct dirent* d_entry;
		  string Temp("");
		  //cout << __LINE__ << endl;

		  // Loop for all the entries into the directory
		  while((d_entry=readdir(dir))!=NULL){
			  if (strcmp(d_entry->d_name,".")==0 || strcmp(d_entry->d_name,"..")==0)
				  continue;
			 // Read the Image
			     Temp = directory;
				 Temp += d_entry->d_name;
				 IplImage *im_gray = cvLoadImage(Temp.c_str(),0);
				 cvReleaseImage(    flattenImage(       ProcessImage(im_gray), Counter  )  );//

				 for (int i=0; i<Length;i++)
					 cvSetReal2D(Labels,Counter,i,0);

				 cvSetReal2D(Labels,Counter,Label,1);

                 Counter++; // Counter
                 if (Counter >= Labels->height)
                	 break;
		 }
		  closedir(dir);
	}

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
	void NN::Train(){
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
	float NN::Test(IplImage* Image){

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
	float NN::Load (string filename){
		NNModel.load(filename.c_str(),"wht");
	}

	/**
	 * Test the Image
	 */
	float NN::Test(string FileName){

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

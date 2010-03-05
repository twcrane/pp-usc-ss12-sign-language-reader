#include "KMeans.h"
//#include "BlobRecognition/BlobRecognizer.h"

    /**
     * Constructor
     */
	KMeans::KMeans(string Dir, int NumberOfImages){
		// Initialize matrices
			Matrix = cvCreateMat(NumberOfImages,IMGSIZE,CV_32FC1);
			Labels = cvCreateMat(NumberOfImages,1,CV_32FC1);
		//
			vector<string> Directories;
			ReadDirectories(Directories, Dir);
			Length = Directories.size();

	    // Process one directory at a time
            int MatCounter = 0;

        	cout<<"Size" << Directories.size()<<endl;

            for (int i=0; i<Directories.size(); i++)
                 ProcessDirectory(Dir + "/" + Directories[i],MatCounter,atoi(Directories[i].c_str()));

        // Allocate the clusters finally
            Clusters = cvCreateMat(Directories.size(),IMGSIZE,CV_32FC1);
            cout << " trained \n";
	}


	//************************************************Main Prediction and training Functions********************************/
	/**
	 * Train the Image
	 */
	void KMeans::train(){
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
	/*float KMeans::Test(IplImage* Image){

		CvMat* Sample = cvCreateMat(1,IMGSIZE,IPL_DEPTH_8U);
		Image = ProcessImage(Image);

		for (int i=0; i< Image->width; i++) // Erro here .. see width and height
			for (int j=0; j< Image->height; j++)
				cvSet2D(Sample,0,i*Image->width + j,cvGet2D(Image,i,j));

		return Knearest.find_nearest(Sample,1);
	}*/
	/**
	 * Test the Image
	 */
	float KMeans::test(IplImage *Image)
	{
		IplImage *tempImg = cvCreateImage(cvSize(Image->width,Image->height),8,1);
		//cvCopy(Image,tempImg,0);
		cvCvtColor(Image,tempImg,CV_BGR2GRAY);

		CvMat* Sample = cvCreateMat(1,IMGSIZE,CV_32FC1);

		tempImg = ProcessImage(tempImg);
		//printf("\nGoogle %d %d\n",tempImg->depth,tempImg->nChannels);

		for (int i=0; i< tempImg->height; i++)
			for (int j=0; j< tempImg->width; j++)
				cvSet2D(Sample,0,i*tempImg->width + j,cvGet2D(tempImg,i,j));
		//printf("\nI am here\n");
		return Knearest.find_nearest(Sample,1);
	}

	//**********************************************************************************************************************/
	KMeans::~KMeans(){	}

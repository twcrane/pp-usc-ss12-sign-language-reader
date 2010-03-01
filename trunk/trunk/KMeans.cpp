#include "KMeans.h"
//#include "BlobRecognition/BlobRecognizer.h"
    /**
     * ReadDirectories
     */
    void KMeans::ReadDirectories(vector<string> &q, string Dir){
		// Read all the directories
		DIR *dir = opendir(Dir.c_str());
		cout << Dir << endl;
		if (!dir)
			return;
		struct dirent *d_entry;

		while ((d_entry=readdir(dir))!=NULL)
			if (strcmp(d_entry->d_name,".") != 0 && strcmp(d_entry->d_name,"..") != 0)
				q.push_back(d_entry->d_name);

		cout << q.size() << endl;
		closedir(dir);
    }
    /**
	 * Flatten Images into the Matrix
	 * TOBECHECKED
	 */
	IplImage** KMeans::flattenImage(IplImage* Image, int& Counter){

		for (int i=0; i< Image->height; i++)
		{
			for (int j=0; j< Image->width; j++)
			{
				cvSetReal2D(Matrix, Counter,i*Image->width + j,cvGetReal2D(Image,i,j));
				//cout << cvGetReal2D(Image,i,j) << " ";
			}
			//cout<<endl;
		}


		return &Image;
    }
	/**
	 * ProcessImage
	 */
	IplImage* KMeans::ProcessImage(IplImage* im_gray)
	{

		 //BlobRecognizer b;
		 // im_gray = b.Runit(im_gray);

		 //cvNamedWindow("sdf");
		 //cvShowImage("sdf",im_gray);
		 //cvWaitKey();
		 //cvDestroyAll	Windows();
		//printf("I am here \n");
		//printf("\I am here .."
//printf("grascale data : %d %d",im_gray->depth,im_gray->nChannels);
		 IplImage *resized = cvCreateImage(cvSize(IMGWIDTH,IMGHEIGHT),im_gray->depth,1);
		 cvResize(im_gray,resized,0);
		 cvReleaseImage(&im_gray);
		 //printf("\nI am also here..");
		 // Normalize
		 //cvNorm(resized, NULL, CV_L1);
		 // Return
  		 return resized;
	}
	/**
	 * Process Directory
	 */
	void KMeans::ProcessDirectory(string directory, int &Counter, int Label){
		  directory += "/";
		  cout << "Inside Process"  << directory << endl;
		  DIR* dir = opendir(directory.c_str());
		  struct dirent* d_entry;
		  string Temp("");

		  // Loop for all the entries into the directory
		  while((d_entry=readdir(dir))!=NULL){
			  if (strcmp(d_entry->d_name,".")==0 || strcmp(d_entry->d_name,"..")==0)
				  continue;
			 // Read the Image
			     Temp = directory;
				 Temp += d_entry->d_name;

				 IplImage *im_gray = cvLoadImage(Temp.c_str(),0);
				 //cout<< Temp.c_str() << endl;
			 // Read the image, change to grayscale and resize it
				 cvReleaseImage(    flattenImage(       ProcessImage(im_gray), Counter  )  );
                 // Set the Label
                 cvSetReal1D(Labels,Counter,Label);
                 // Increment the Counter
                 Counter++;
                 //cout << Counter << endl;
		 }
	}

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
	void KMeans::Train(){
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
	float KMeans::Test(IplImage *Image)
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

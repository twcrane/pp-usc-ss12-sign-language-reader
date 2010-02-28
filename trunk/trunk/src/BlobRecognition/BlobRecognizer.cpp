/*
 * BlobRecognizer.cpp
 *
 *  Created on: Oct 2, 2009
 *      Author: parth
 */

#include "BlobRecognizer.h"
BlobPoint<int> click, secondPoint;

/**
 * Constructor for initializing the main variables in the class
 */
BlobRecognizer::BlobRecognizer() {
	// TODO Auto-generated constructor stub
	 for (int i=0;i<3;i++)
	 {
		t.colors[i] = 0;
		t.var[i]=0;
	 }
	 t.area = 0;
	 normalizer=0;
	 StickIndex = 0;

}
/**
 * Destructor for the class
 */
BlobRecognizer::~BlobRecognizer(){}
/**
 * Load the images
 */
void BlobRecognizer::LoadImage(char* filename){

	IplImage* Image = cvLoadImage(filename,1);

	frame=cvCreateImage(cvGetSize(Image), IPL_DEPTH_8U, 3 );
	cvSmooth(Image,frame,CV_GAUSSIAN,21,21);

	// Resultant image
	result=cvCreateImage( cvGetSize(frame), 8, 1 );

	// If we failed to load the image then exit
	if(frame==NULL ) {
		puts("unable to load the frame");
		exit(0);
	}

	height = frame->height;
	width = frame->width;

	step =frame->widthStep;
	channels = frame->nChannels;
	imageData = (uchar *)frame->imageData;

	stepr=result->widthStep;
	channelsr=result->nChannels;
	imageDatar = (uchar *)result->imageData;

}
/**
 * Load the images
 */
void BlobRecognizer::LoadImage(IplImage* Image){

	//IplImage* Image = cvLoadImage(filename,1);

	frame=cvCreateImage(cvGetSize(Image), IPL_DEPTH_8U, 1 );
	cvSmooth(Image,frame,CV_GAUSSIAN,21,21);

	// Resultant image
	result=cvCreateImage( cvGetSize(frame), 8, 1 );

	// If we failed to load the image then exit
	if(frame==NULL ) {
		puts("unable to load the frame");
		exit(0);
	}

	height = frame->height;
	width = frame->width;

	step =frame->widthStep;
	channels = frame->nChannels;
	imageData = (uchar *)frame->imageData;

	stepr=result->widthStep;
	channelsr=result->nChannels;
	imageDatar = (uchar *)result->imageData;
}

/**
 * Clear the Image
 */
void BlobRecognizer::ClearImage(){
   height = 0;width = 0;step = 0;channels = 0;stepr = 0;channelsr = 0;
   imageData = NULL;imageDatar = NULL;
   for (int i=0;i<3;i++)
  	 {
  		t.colors[i] = 0;
  		t.var[i]=0;
  	 }
  	 t.area = 0;
  	 normalizer=0;
  	 StickIndex = 0;
}
/**
 * Clear the Image
 */
void BlobRecognizer::SaveImage(char *filename){
	   cvSaveImage(filename,result);
}

/**
 *
 */
void BlobRecognizer::LoadTheValues(char* filename){

	fstream f;
	f.open(filename,ios::in);
	for (int i=0;i<3;i++)
	{
		f >> t.colors[i];
		cout<< t.colors[i] << " ";
	}
	for (int i=0;i<3;i++)
	{
		f >> t.var[i];
		cout << t.var[i] << " ";
	}

	f >> t.area;

	f.close();

}
/**
 *
 */
void BlobRecognizer::SaveTheValues(char* filename){

	fstream f;
	f.open(filename,ios::out);
	for (int i=0;i<3;i++)
		f << t.colors[i] << " ";
	f << "\n";
	for (int i=0;i<3;i++)
			f << t.var[i] << " ";
	f << "\n";
	f << t.area << " ";

	f.close();
}

/******************************* Training Part *********************************/

/**
 * MouseHandler Event
 */
 void mouseHandler(int event, int x, int y, int flags, void* param)
{
  switch(event){
	case CV_EVENT_LBUTTONDOWN:
		 click.x = x;
		 click.y = y;
		 click.Filled = true;
	  break;

	case CV_EVENT_LBUTTONUP:
		 secondPoint.x = x;
		 secondPoint.y = y;
		 secondPoint.Filled = true;
	  break;
  }
}

 /**
 *	findTheMedians
 */
 void BlobRecognizer::findTheMedians(){
		/** get the median of the data*/
		for( int i=click.y ; i < secondPoint.y ; i++ )
		{
			for( int j=click.x ; j <secondPoint.x ; j++ )
			{
				t.colors[0]+=imageData[i*step+j*channels];
				t.colors[1]+=imageData[i*step+j*channels+1];
				t.colors[2]+=imageData[i*step+j*channels+2];
			}
		}
	    /** normalizer for that imageData	*/
		normalizer = ( secondPoint.y-click.y ) * (secondPoint.x-click.x);
		for(int i=0;i<3;i++)
			t.colors[i]/=normalizer;
 }

/**
 *	findTheVariance
 */
 void BlobRecognizer::findTheVariance(){
	   /** finding the variance */
	   for(int i=click.y;i < secondPoint.y;i++)
		{
			for(int j=click.x;j <secondPoint.x;j++)
			{
				t.var[0] += (t.colors[0] - imageData[i*step+j*channels])*(t.colors[0] - imageData[i*step+j*channels]);
				t.var[1] += (t.colors[1] - imageData[i*step+j*channels+1])*(t.colors[1] - imageData[i*step+j*channels+1]);
				t.var[2] += (t.colors[2] - imageData[i*step+j*channels+2]) * (t.colors[2] - imageData[i*step+j*channels+2]);
			}
		}
	   /** finding the normalizer */
	   normalizer = ( secondPoint.y-click.y ) * (secondPoint.x-click.x);

	   for (int i=0;i<3;i++)
		   t.var[i] = sqrt(t.var[i]/normalizer);
 }

/**
 * This function trains our model to recognize a sample object
 */
void BlobRecognizer::train(int name){
	// now we are gonna train on the given object
	// and save the training parameters to a file

	   // Create Window for original image
	   cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
	   // Window for resultant image
	   cvNamedWindow("Result",CV_WINDOW_AUTOSIZE);

	   //// prepare for the recognizing part
	   // Show the original Image
	   cvShowImage("original",frame);
	   int mouseParam=5;
	   cvSetMouseCallback("original",mouseHandler,&mouseParam);
	   ////

	   /// Wait for an event
		   cvWaitKey(0);
	   ///

	   /// Now trigger learning
		   //this->trigger();
			 t.colors[0]=t.colors[1]=t.colors[2]=0;
			 t.area = abs((secondPoint.x - click.x) * (secondPoint.y-click.y));
		 	 findTheMedians();
		 	 // For debugging purposes dummy values
#ifdef debug
		 	 t.colors[0] = 26.4116;
		 	 t.colors[1] = 70.2677;
		 	 t.colors[2] = 71.3147;
#endif
		 	 findTheVariance();
		 	 // For now dummy values
#ifdef debug
		 	 t.var[0] = 0.52*9;
		 	 t.var[1] = 1.07*9;
		 	 t.var[2] = 0.8*9;
#endif
	   ///
		 	 this->SaveTheValues("Default");
		 	 BlobPoint<long> point = this->recognize();
	   /// wait until user is done
	   cvWaitKey(0);
	   cvDestroyWindow("original");
	   cvDestroyWindow("Result");
}
/***************************** Rest of the Part ********************************/

/***************************** Blob Detection Part *****************************/

/**
 * This function a given parameter name recognizes(atleast tries to recognize)
 * the object
 */
BlobPoint<long> BlobRecognizer::recognize(){

	 this->LoadTheValues("Default");

	 bool condition;
	   for(int i=0;i < (height);i++)
	      {
	      	for(int j=0;j <(width);j++)
	      	{
	      		condition = true;

	      		for (int k=0; k<3;k++)
	      			condition = condition && ((imageData[i*step+j*channels+k]) > t.colors[k]-t.var[k]) && ((imageData[i*step+j*channels+k]) < t.colors[k] + t.var[k]) ;

	      	    if( condition )
	      	    	imageDatar[i*stepr+j*channelsr]=255;
	      	    else
	      	    	imageDatar[i*stepr+j*channelsr]=0;
	      	}
	      }

	   //cout << endl;

	   //cvShowImage("Result",result);
	   //cvSaveImage("result.jpg",result);

	   BlobPoint<long> s;
	   getSegment(s);

	   return s;
}

/**
 *  Get the segments out of the resulting image
 *  @param seg BlobPoint from which we need to get the segment
 */
void BlobRecognizer::getSegment(BlobPoint<long>& seg){

	  // List of all the segments
	  vector<BlobPoint<long> > segments;

	  // Temporary segment variable
	  BlobPoint<int> s;

	  // List of all the points that were detected for the temporary segment
	  vector<BlobPoint<int> > list;

	  // A Point in Image
		 BlobPoint<int> p;
		 // Blob Point for storing blob as a point
		 BlobPoint<long> sum;
			sum.x=0;
			sum.y=0;
			sum.numberOfPoints = 0;
			sum.maxX = sum.maxY = 0;
			sum.minY = 10000000; sum.minX = 1000000;
			sum.height = sum.width = 0;

	 /**
	  * Iterate over each and every point and check if it is white or not ?
	  * if it is white then detect all the connected points, add it to segments
	  * and remove it from the image as their corresponding segments have already been
	  * detected
	  */
	 for(int i=0;i<(height);i++)
	  {
		for(int j=0;j<(width);j++)
		{

			// If the point was detected while blob detection
			// then search for all the adjascent white points in the
			// image and make a segment out of it.
			if (imageDatar[i*stepr+j*channelsr]==255){

				// X and Y coordinate
				p.x = j;
				p.y = i;

				// Let's get all the other adjascent points in the
				// list variable
				/// This will be a recursive function call
				goGetIt(p,sum, true);
				// Now we have the list and we can weighted average it
				// to get the center of mass
				if (sum.numberOfPoints !=0 ){
					sum.x /= sum.numberOfPoints;
					sum.y /= sum.numberOfPoints;
				}
				//showResult();
				// Push the calculated segment back on to the
				// segments vector
				segments.push_back(sum);

				sum.x=0;
				sum.y=0;
				sum.numberOfPoints = 0;
				sum.maxX = sum.maxY = 0;
				sum.minY = 10000000; sum.minX = 1000000;
				sum.height = sum.width = 0;

			}
		}
	  }
	 // Since now we have the segments list, we can calculate the
	 // one with the most similarity to the stick statistics that we have

	 double min_area = 1000000000;
	 int minIndex = 0;

	 for (int i=0; i < segments.size(); i++){

		 // Calculate the width and height of the segment
		 segments[i].width = segments[i].maxX - segments[i].minX + 1;
		 segments[i].height = segments[i].maxY - segments[i].minY + 1;

		 CvScalar s = cvScalar(30);
	     cvDrawRect(result, cvPoint(segments[i].minX,segments[i].minY) ,cvPoint(segments[i].maxX,segments[i].maxY),  s);
	     //showResult();
		 // Error between the statistics of stick and identified segment
		 /// Parameters that can be calculated for the error
		 /// 1) Error in Height and Width added to the area error with
		 ///    an appropriate weight
		 double error = abs((segments[i].width) * (segments[i].height) - t.area);

		 // Is this the minimum area we have received so far?
		 if (error < min_area)
		 {
			 min_area = error;
			 minIndex = i;
		 }
	 }


     cvDrawRect(result,cvPoint(segments[minIndex].minX,segments[minIndex].minY), cvPoint(segments[minIndex].maxX,segments[minIndex].maxY), cvScalar(255));
     seg = segments[minIndex];

     //showResult();
     //cvSaveImage("result2.jpg",result);
}

/**
 * Function : goGetIt
 * @param p Point to be considered for getting the blob
 * @param sum Sum of all the points
 * @return sum
 */
void BlobRecognizer::goGetIt(BlobPoint<int> p, BlobPoint<long> &sum, bool column=false){
	BlobPoint<int> p1;
	if (imageDatar[p.y*stepr+p.x*channelsr]==255){
		/// Add up the X and Y
		sum.x += p.x;
		sum.y += p.y;
		if (p.x < sum.minX)
			sum.minX = p.x;
		if (p.x > sum.maxX)
			sum.maxX = p.x;
		if (p.y < sum.minY)
			sum.minY = p.y;
		if (p.y > sum.maxY)
			sum.maxY = p.y;

		/// Increment the total number of points
		sum.numberOfPoints++;
		/// make that point void now as we have already considered it
		imageDatar[p.y*stepr+p.x*channelsr]=0;
		// Now take the next point in row and iterate over the points
		p1 = p; p1.x--;
		if (p1.x >= 0 )
			goGetIt(p1, sum, true);
		// Now take the next point in column and iterate over the points from there on
		p1 = p; p1.y--;
		if (p1.y >= 0 )
		{
			goGetIt(p1, sum, true);
			p1.x--;
			if (p1.x >= 0 )
				goGetIt(p1, sum, true);
		}
		// Now take the next point in row and iterate over the points
		p1 = p; p1.x++;
		if (p1.x <= width)
			goGetIt(p1, sum, true);
		// Now take the next point in column and iterate over the points from there on
		p1 = p; p1.y++;
		if (p1.y <= height)
		{
			goGetIt(p1, sum, true);
			p1.x++;
			if (p1.x <= width)
				goGetIt(p1, sum, true);
		}


	}
 }
void BlobRecognizer::showResult(){
	 cvNamedWindow("Result",CV_WINDOW_AUTOSIZE);
     cvShowImage("Result",result);
	 cvWaitKey(0);
	 cvDestroyAllWindows();
}

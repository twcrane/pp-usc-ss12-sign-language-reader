//============================================================================
// Name        : Gattaca.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "cv.h"
#include "highgui.h"

using namespace std;

int main() {


	  CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
	  if( !capture ) {
	    fprintf( stderr, "ERROR: capture is NULL \n" );
	    getchar();
	    return -1;
	  }

	  // Create a window in which the captured images will be presented
	  cvNamedWindow("mywindow", CV_WINDOW_AUTOSIZE);

	  // Show the image captured from the camera in the window and repeat
	  while( 1 ) {
	    // Get one frame
	    IplImage* frame = cvQueryFrame( capture );
	    if( !frame ) {
	      fprintf( stderr, "ERROR: frame is null...\n" );
	      getchar();
	      break;
	    }
	    // New Window
	    cvShowImage( "mywindow", frame );

	    if( (cvWaitKey(10) & 255) == 27 ) break;
	  }

	  // Release the capture device housekeeping
	  cvReleaseCapture( &capture );
	  cvDestroyWindow( "mywindow" );

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!


	/////////////////////////////////// BOOSTING /////////////////////////////////














	//////////////////////////////////////////////////////////////////////////////




	return 0;
}

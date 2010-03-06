// SS-12: Sign Language Reader
#include "KNN.h"
#include "EdgeDetect.h"
#include "Training.h"
#include "FolderReader.h"
#include "GUI.h"

using namespace std;

#define UPIXEL(img, i, j, k)	(*( (unsigned char*) ( (img)->imageData + (img)->widthStep * (j) + (img)->nChannels * (i) + (k)) ))
#define PIXEL(img, i, j, k)		(*( (char*)          ( (img)->imageData + (img)->widthStep * (j) + (img)->nChannels * (i) + (k)) ))

double THRESHOLD = 10.0;
double ALPHA = 0.0;//0.0*1.0/3.0;

IplImage* bgMean ;

/***************************** Umag GUI ***********************/

/******************************************/
double distance(unsigned char *thisFrame, unsigned char *bg, int nChannels)
{
	//Can be faster if you don't use double calculations. use ints.
	double thf[3] = {double(thisFrame[0]),double(thisFrame[1]),double(thisFrame[2])};
	double bgf[3] = {double(bg[0]),double(bg[1]),double(bg[2])};
	if(nChannels == 3)
		return (0.299 * (thf[2]-bgf[2])) + (0.587 * (thf[1]-bgf[1])) + (0.114 * (thf[0]-bgf[0]) );
	else 
		return double(thisFrame[0] - bg[0]);
}

int checkBlack(IplImage *src,int x,int y)
{
	int th=-128;
	return !((int)PIXEL(src,x,y,0)==th && (int)PIXEL(src,x,y,1)==th && (int)PIXEL(src,x,y,2)==th);

}

#define EPSILON 1e-9

void segmentFrame(IplImage *thisFrame, IplImage *changeMask)
{
	int i, j;
	double dist=0;
	for(i=0; i<thisFrame->width; ++i)
	{
		for(j=0; j<thisFrame->height; ++j)
		{
			dist =distance( &UPIXEL(thisFrame, i, j, 0), &UPIXEL(bgMean, i, j, 0), bgMean->nChannels);
			if(dist< THRESHOLD )
			{
				for(int k = 0; k < bgMean->nChannels; ++k)
					UPIXEL(bgMean, i, j, k) = (unsigned char) (ALPHA * (UPIXEL(thisFrame, i, j, k)) + (1.0-ALPHA) * (UPIXEL(bgMean, i, j, k)));
				PIXEL(changeMask, i, j, 0) = 0;
			}
			else
				PIXEL(changeMask, i, j, 0) = 0xFF;
		}
	}
}

void OverlayImg(IplImage* RawImg, IplImage *SilhImg)
{
	int bufsize = RawImg->width *  RawImg->height;
	unsigned char *silhBuf = (unsigned char *)SilhImg->imageData;
	unsigned char* outBuf = (unsigned char*)RawImg->imageData;
	unsigned char *RawBuf = (unsigned char*)RawImg->imageData;

	for(int i=0; i<bufsize; i++ ) 
	{
         if( silhBuf[0]>0)
		 {
			outBuf[0] = 128;//RawBuf[0]/2;
			outBuf[1] = 128;//RawBuf[1]/2;
			outBuf[2] = 128;//128; //SILH_RED;
        } 
		else 
		{
            outBuf[0] = 0;//RawBuf[0];
            outBuf[1] = 0;//RawBuf[1];
            outBuf[2] = 0;//RawBuf[2];
        }
        RawBuf += 3;
        outBuf += 3;
        silhBuf+=3;
    }
}

/**
 *
 */
int main() 
{

	cout << "Folder Reader \n";
	FolderReader *fd = new FolderReader("Data");
	cout << "Edge Detect \n";
	EdgeDetect *ed = new EdgeDetect();
	cout << "KNN \n";
	KNN *knn = new KNN();

	// Create a training instance.
	cout << "Training\n";
	Training *training = new Training(fd,ed,knn);
    cout << "Training Complete\n";

	//
	CvRect cvROIRect;//(20,50,250,320);
    cvROIRect.x = 100;
    cvROIRect.y = 200;
    cvROIRect.width = 250;
    cvROIRect.height = 320;

	CvCapture* capture = cvCaptureFromCAM(0);

      if( capture==NULL )
	  {
        fprintf( stderr, "ERROR: capture is NULL \n" );
        getchar();
        return -1;
      }

	IplImage* bgMean2 = cvQueryFrame(capture);
	int bufsize = bgMean2->width *  bgMean2->height;
	for(int i=0;i<30;i++)
	{
		IplImage*bgMean3 = cvQueryFrame(capture);
		unsigned char* bgBuf2 = (unsigned char*)bgMean2->imageData;
		unsigned char* bgBuf3 = (unsigned char*)bgMean3->imageData;
		for(int j=0; j<bufsize; j++ )
		{
			bgBuf2[0]=(bgBuf2[0]/2 + bgBuf3[0]/2);
			bgBuf2[1]=(bgBuf2[1]/2 + bgBuf3[1]/2);
			bgBuf2[2]=(bgBuf2[2]/2 + bgBuf3[2]/2);
			bgBuf2+=3;
			bgBuf3+=3;
		}
	}
	bgMean = cvCreateImage(cvSize(bgMean2->width,bgMean2->height),bgMean2->depth,bgMean2->nChannels);
	cvCopy(bgMean2,bgMean);
    // Create a window in which the captured images will be presented
    cvNamedWindow( "OrigImage", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "CalculatedImage", CV_WINDOW_AUTOSIZE );

	IplImage *changeMask=cvCreateImage(cvSize(bgMean->width,bgMean->height),bgMean->depth,bgMean->nChannels),*curr_img;
	//IplImage *resize_img = cvCreateImage(cvSize(bgMean->width/10,bgMean->height/10),bgMean->depth,bgMean->nChannels);

	//char fname[50]={0};
	int counter=0;
	cvSaveImage("BGImage.bmp",bgMean);
	float old_class=-2.0f;

	//
	GUI gui;

	cvMoveWindow("OrigImage",360,0);
	cvMoveWindow("CalculatedImage",700,220);

	while( 1 ) 
	{
		// Get one frame
		curr_img = cvQueryFrame( capture );

		if( !curr_img ) 
		{
		  fprintf( stderr, "ERROR: frame is null...\n" );
		  getchar();
		  break;
		}

		IplImage *temp_disp = cvCreateImage(cvSize(320,240),curr_img->depth,curr_img->nChannels);
		cvResize(curr_img,temp_disp,0);
		cvShowImage( "OrigImage", temp_disp );

		segmentFrame(curr_img, changeMask);

		OverlayImg(curr_img,changeMask);
		cvZero(changeMask);
		cvShowImage( "CalculatedImage", curr_img );
		counter++;

		if(counter%2==0)
		{

			float class_detected = training->test(curr_img);
			if((int)old_class==(int)class_detected)
			{
				int temp2 = (int)old_class;
				cout<<"Detected = "<<class_detected<<endl;

				if(temp2>=1 && temp2<=5)
					gui.showImage(temp2);

				cvWaitKey(1);
			}
			old_class=class_detected;

		}

		if( (cvWaitKey(1) & 255) == 27 ) break;
	}

	// Release the capture device housekeeping
	cvReleaseCapture( &capture );

	cvDestroyWindow( "CalculatedImage" );
	cvDestroyWindow( "OrigImage" );
	cvDestroyWindow( "BGMEAN" );

    cout << "!!!Hello World!!!" << endl;
    return 0;
}



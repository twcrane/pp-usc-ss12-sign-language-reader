// SS-12: Sign Language Reader
#include "Prerequs.h"
#include "KNN.h"
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

void BlobDetect(IplImage *src,IplImage **dest)
{
	int minX=-1,minY=-1,maxX=-1,maxY=-1;
	/* Firs rectangle */
	int flag=0;
	IplImage *thisFrame = src;

	for(int x=0; x<thisFrame->width && !flag; ++x)
	{
		for(int y=0; y<thisFrame->height && !flag; ++y)
		{
			if(checkBlack(thisFrame,x,y))
			{
				minX = x;
				flag=1;
			}
		}
	}

	if(flag==0)
	{
		*dest = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
		cvCopy(src,dest,0);
		printf("maa ka bhosda %d %d %d %d",minX,minY,minX,minX);
		return;
	}

	//MaxY
	for(int x=thisFrame->width-1,flag=0; x>=0 && !flag; --x)
	{
		for(int y=0; y<thisFrame->height && !flag; ++y)
		{
			if(checkBlack(thisFrame,x,y))
			{
				maxX = x;
				flag=1;
			}
		}
	}

	//MaxY
	for(int y=thisFrame->height-1,flag=0; y>=0 && !flag; --y)
	{
		for(int x=0; x<thisFrame->width && !flag; ++x)
		{
			if(checkBlack(thisFrame,x,y))
			{
				maxY = y;
				flag=1;
			}
		}
	}

	//MinY
	for(int y=0,flag=0; y<thisFrame->height && !flag; ++y)
	{
		for(int x=0; x<thisFrame->width && !flag; ++x)
		{
			if(checkBlack(thisFrame,x,y))
			{
				minY = y;
				flag=1;
			}
		}
	}
	cvSetImageROI(src,cvRect(minX,minY,maxX-minX+1,maxY-minY+1));

	*dest = cvCreateImage(cvSize(maxX-minX,maxY-minY),src->depth,src->nChannels);

	cvResize(src,*dest,0);
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

int main() 
{

	// Create a training instance.

	CvRect cvROIRect;//(20,50,250,320);
    cvROIRect.x = 100;
    cvROIRect.y = 200;
    cvROIRect.width = 250;
    cvROIRect.height = 320;

    KMeans kmeans("../Data",3534);
    kmeans.Train();

    cout << "Training Complete\n";

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
	//
	printf("\nDone");
	cvCopy(bgMean2,bgMean);
    // Create a window in which the captured images will be presented
    cvNamedWindow( "OrigImage", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "CalculatedImage", CV_WINDOW_AUTOSIZE );

	IplImage *changeMask=cvCreateImage(cvSize(bgMean->width,bgMean->height),bgMean->depth,bgMean->nChannels),*curr_img;
	IplImage *resize_img = cvCreateImage(cvSize(bgMean->width/10,bgMean->height/10),bgMean->depth,bgMean->nChannels);

	char fname[50]={0};
	int counter=0;
	cvSaveImage("BGImage.bmp",bgMean);
	float old_class=-2.0f;
	IplImage* img_GUI[6];

	img_GUI[0]= cvLoadImage( "GUI/GUI1.jpg" );
	img_GUI[1]= cvLoadImage( "GUI/GUI2.jpg" );
	img_GUI[2]= cvLoadImage( "GUI/GUI3.jpg" );
	img_GUI[3]= cvLoadImage( "GUI/GUI4.jpg" );
	img_GUI[4]= cvLoadImage( "GUI/GUI5.jpg" );
	img_GUI[5]= cvLoadImage( "GUI/GUI6.jpg" );

	cvNamedWindow("IconPane",CV_WINDOW_AUTOSIZE);

	cvShowImage("IconPane",img_GUI[0]);
	cvMoveWindow("IconPane",0,0);
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

/*		IplImage *temp;
		BlobDetect(curr_img,&temp);
		cvShowImage("newWindows",temp);*/

		if(counter%2==0)
		{

			float class_detected = kmeans.Test(curr_img);
			if((int)old_class==(int)class_detected)
			{
				int temp2 = (int)old_class;
				cout<<"Detected = "<<class_detected<<endl;

				if(temp2>=1 && temp2<=5)
					cvShowImage("IconPane",img_GUI[temp2]);
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



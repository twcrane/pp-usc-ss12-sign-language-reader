/*
 * GUI.cpp
 *
 *  Created on: 04-Mar-2010
 *      Author: parth
 */

#include "GUI.h"

/**
 *
 */
GUI::GUI(){
		img_GUI[0]= cvLoadImage( "GUI/GUI1.jpg" );
		img_GUI[1]= cvLoadImage( "GUI/GUI2.jpg" );
		img_GUI[2]= cvLoadImage( "GUI/GUI3.jpg" );
		img_GUI[3]= cvLoadImage( "GUI/GUI4.jpg" );
		img_GUI[4]= cvLoadImage( "GUI/GUI5.jpg" );
		img_GUI[5]= cvLoadImage( "GUI/GUI6.jpg" );

		cvNamedWindow("IconPane",CV_WINDOW_AUTOSIZE);

		cvShowImage("IconPane",img_GUI[0]);
		cvMoveWindow("IconPane",0,0);
}
/**
 *
 */
void GUI::showImage(int temp2){
	 cvShowImage("IconPane",img_GUI[temp2]);
}
/**
 *
 */
GUI::~GUI(){
		cvDestroyWindow("IconPane");
		for (int i=0; i<6; i++)
			if (img_GUI[i])
				cvReleaseImage(&img_GUI[i]);
}

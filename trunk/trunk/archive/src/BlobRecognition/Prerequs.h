/*
 * Prerequs.h
 *
 *  Created on: Oct 2, 2009
 *      Author: parth
 */

#ifndef PREREQUS_H_
#define PREREQUS_H_


   /*ALL the necessary header files*/
    #include "math.h"
    #include"cv.h"
    #include"highgui.h"
    #include"stdio.h"
	#include<cvaux.h>
	#include<vector>

	#include <fstream>
	#include <iostream>

	using namespace std;

	 /**  click and secondPoint for the mouse events */
	 template <class T>
	 struct BlobPoint{
		 T x,y;
		 T width,height;
		 int minX, minY;
		 int maxX,maxY;
		 T numberOfPoints;
		 bool Filled;
	 };

/*
	 struct points{
	  int x,y;
	  bool filled;
	 };
*/

	 struct trainingData{
		 /**  Colors  */
		 double colors[3];
		 /** The Variance Container */
		 long double var[3];
		 double area;
	 };
#endif /* PREREQUS_H_ */

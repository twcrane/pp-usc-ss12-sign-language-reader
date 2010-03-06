/*
 * GUI.h
 *
 *  Created on: 06-Mar-2010
 *      Author: parth
 */

#ifndef GUI_H_
#define GUI_H_

#include "Prerequs.h"

class GUI{

	IplImage* img_GUI[6];

public:
	GUI();
	void showImage(int);
	~GUI();
};

#endif /* GUI_H_ */

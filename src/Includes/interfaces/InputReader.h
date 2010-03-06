#ifndef _INPUTREADER_
#define _INPUTREADER_

#include "cv.h"
#include <string>

using namespace std;

class InputReader{

public:
	virtual IplImage* next(int&){return NULL;};
	virtual void reset(){};
	virtual void end(){};
	virtual int numberofimages(){return 0;};
};

#endif

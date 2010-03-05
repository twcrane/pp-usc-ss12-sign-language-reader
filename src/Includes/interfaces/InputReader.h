#ifndef _INPUTREADER_
#define _INPUTREADER_

#include "cv.h"
#include <string>

using namespace std;

class InputReader{

public:
	virtual IplImage* next(int&);
	virtual void reset();
	virtual void end();
	virtual int numberofimages();
};

#endif

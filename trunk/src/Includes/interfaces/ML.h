#ifndef _ML_
#define _ML_

#include "cv.h"
#include <string>

using namespace std;

class ML{

public:

	virtual void create(int){};
	virtual void train(CvMat*,CvMat*){};
	virtual float test(IplImage*){return 0;};

	virtual void save(string){};
	virtual void load(string){};

};

#endif

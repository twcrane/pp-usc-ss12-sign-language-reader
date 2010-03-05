#include "Prerequs.h"

/**
 *
 */
class FeatureDetector{

public:
	//
	virtual CvRect detect();
	virtual IplImage* detect(IplImage*);
	virtual void load();

};

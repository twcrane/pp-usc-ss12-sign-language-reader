#include "Prerequs.h"

/**
 *
 */
class FeatureDetector{

public:
	//
	virtual CvRect detect();
	virtual void detect(IplImage*);
	virtual void load();

};

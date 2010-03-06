#ifndef _FEATUREDETECTOR_
#define _FEATUREDETECTOR_

/**
 *
 */
class FeatureDetector{

public:
	//
	virtual IplImage* detect(IplImage*){ return NULL;};
	virtual void load(){};

};

#endif

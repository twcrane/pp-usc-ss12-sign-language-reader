#ifndef _FEATUREDETECTOR_
#define _FEATUREDETECTOR_

/**
 *
 */
class FeatureDetector{

public:
	//
	virtual IplImage* detect(IplImage*);
	virtual void load();

};

#endif

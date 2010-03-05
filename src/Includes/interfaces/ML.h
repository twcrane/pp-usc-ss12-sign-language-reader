#include "Prerequs.h"

class ML{

public:
	// virtual somefunction();

	virtual void create(int);
	virtual void train(CvMat*,CvMat*);
	virtual float test(IplImage*);

	virtual void save(string);
	virtual void load(string);

};

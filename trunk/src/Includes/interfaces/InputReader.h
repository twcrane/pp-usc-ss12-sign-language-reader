class InputReader{

public:
	virtual IplImage* next();
	virtual void reset();
	virtual void end();
	virtual int numberofimages();
};

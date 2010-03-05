class InputReader{

public:
	virtual IplImage* next(int );
	virtual void reset();
	virtual void end();
	virtual int numberofimages();
};

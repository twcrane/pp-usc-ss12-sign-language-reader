/*
 * BlobRecognizer.h
 *
 *  Created on: Oct 2, 2009
 *      Author: parth
 */
#include "Prerequs.h"
#ifndef BLOBRECOGNIZER_H_
#define BLOBRECOGNIZER_H_


class BlobRecognizer {
	 trainingData t;
	 /**   */
	 IplImage *frame, *result;
	 /**   */
	 int height,width,step,channels;
	 /**   */
	 int stepr,channelsr;
	 /**   */
	 uchar *imageData, *imageDatar;
	 /**   */
	 int normalizer;
	 /**  Segment container and pointer to the candidates */
	 vector<struct BlobPoint<int> > SegList;
	 int StickIndex;

public:
	BlobRecognizer();
	virtual ~BlobRecognizer();
	/// Image/Statistics loading and removal part
		void LoadImage(char*);
		void LoadImage(IplImage*);
		void ClearImage();
		void SaveImage(char*);
		void LoadTheValues(char*);
		void SaveTheValues(char*);
	///
	/// Image training part
		void findTheMedians();
		void findTheVariance();
		void train(int);
	///
	/// Recognizer
		BlobPoint<long> recognize();
		/// Segmentation part
			void goGetIt(BlobPoint<int>, BlobPoint<long>&, bool);
			void getSegment(BlobPoint<long>& );
		///
    ///
			void showResult();
};

#endif /* BLOBRECOGNIZER_H_ */

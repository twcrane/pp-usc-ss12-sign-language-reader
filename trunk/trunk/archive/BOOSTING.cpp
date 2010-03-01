/*
 * BOOSTING.cpp
 *
 *  Created on: 27-Feb-2010
 *      Author: parth patel
 */

#include "cv.h"

class Sign{
	int id;
	string SignName;
};

class BOOSTING {
  // data base variable
	CvBoost boostDataBase;
	int varCount = 0;
    //CvMat*

  public:
	BOOSTING(){

		CvMat* var_type = cvCreateMat( 640, 480, CV_32FC3); //CV_var_count + 2, 1, CV_8U );
		cvSet( var_type, cvScalarAll(CV_VAR_ORDERED) );
		// the last indicator variable, as well
		// as the new (binary) response are categorical
		cvSetReal2D( var_type, 0, CV_VAR_CATEGORICAL );
		cvSetReal2D( var_type, var_count+1, CV_VAR_CATEGORICAL );
		// Train the classifier
		//
		boostDataBase.train( new_data,
		CV_ROW_SAMPLE,
		responses,
		0,
		0,
		var_type,
		0,
		CvBoostParams( CvBoost::REAL, 100, 0.95, 5, false, 0 )
		);
		cvReleaseMat( &new_data );
		cvReleaseMat( &new_responses );
	}
	/**
	 *
	 */
	BOOSTING(CvImage** Input, int Number, CvMat* Y){
            CvMat* var_type = cvCreateMat( var_count + 2, 1, CV_8U );
			cvSet( var_type, cvScalarAll(CV_VAR_ORDERED) );
			// the last indicator variable, as well
			// as the new (binary) response are categorical
			//
			cvSetReal1D( var_type, var_count, CV_VAR_CATEGORICAL );
			cvSetReal1D( var_type, var_count+1, CV_VAR_CATEGORICAL );
			// Train the classifier
			//
			boost.train(
			new_data,
			CV_ROW_SAMPLE,
			responses,
			0,
			0,
			var_type,
			0,
			CvBoostParams( CvBoost::REAL, 100, 0.95, 5, false, 0 )
			);
			cvReleaseMat( &new_data );
			cvReleaseMat( &new_responses );
    }

    void TrainingPhase(CvImage** Input, int Number, CvMat* Y);
    int CheckImage();


};

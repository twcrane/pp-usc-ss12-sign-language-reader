#include "Prerequs.h"
#include "FeatureDetector.h"

class DirectoryIterator {

	string Directory;
	DIR *RootDir;

	vector<string> ClassDirs;

	int curClass;
	int curNum;



public:
	DirectoryIterator(string dirname){

		Directory = dirname;
		// Open that directory
		RootDir = opendir(dirname);
		chdir(dirname);
	}

	/**
	 *
	 */
	void next(){

	}
	/**
	 *
	 */
	void Reset(){
		end();
	}


	void end(){
		chdir("..");
	}

};

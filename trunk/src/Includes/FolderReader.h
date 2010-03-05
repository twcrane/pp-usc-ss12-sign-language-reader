#include "Prerequs.h"
#include "interfaces/FeatureDetector.h"
#include "interfaces/InputReader.h"

/**
 * Folder Reader class
 */
class FolderReader : InputReader {

	// Constants
	static const int IMGWIDTH = 128;
	static const int IMGHEIGHT = 96;
	static const int IMGSIZE = 128*96;

	// Root directory
	string Directory;
	DIR *RootDir;

	vector<string> ClassDirs;

	// Per Class
	    // Index in the Class Dirs
		int curClass;
		DIR *ClassDir;

public:
	FolderReader(string dirname){
		Directory = dirname;
		// Open that directory
		RootDir = opendir(dirname);
		if (!RootDir)
					cout << " Failed to Open the Directory : " << dirname;
		// Change Directory
		chdir(dirname);
		// Read all the directories
		   ReadDirectories();

		   curClass = -1;
		   ClassDir = NULL;

		 nextClass();
	}
	/**
	 * Read all the directories in
	 */
	void ReadDirectories(){

		if (!RootDir)
			return;
		//
		struct dirent *d_entry;
		//
		while ((d_entry=readdir(RootDir))!=NULL)
			if (strcmp(d_entry->d_name,".") != 0 && strcmp(d_entry->d_name,"..") != 0)
				ClassDirs.push_back(d_entry->d_name);

		closedir(dir);

	}

	/**
	 * Go to Next Class
	 */
	bool nextClass(){
		// Close the Current Directory
		if (ClassDir)
		{
			closedir(ClassDir);
			ClassDir = NULL;
		}
		// Open the new Directory
		curClass ++ ;
		if (curClass >= ClassDirs.size())
			return false;

		ClassDir = opendir(ClassDirs[curClass]);
		if(!ClassDir)
			return false;
		else
			return true;
	}
	/**
	 * next image from the list
	 */
	IplImage* next(int &ClassNumber){
		struct dirent *d_entry;

		// Iterate and retrive the next non ., .. or .DS_STORE file
		do {
			d_entry=readdir(ClassDir);
			if (d_entry == NULL && !nextClass())
				return NULL;
		}while (strcmp(d_entry->d_name,".DS_Store")==0 || strcmp(d_entry->d_name,".") == 0 || strcmp(d_entry->d_name,"..") == 0);

		string Temp = ClassDirs[curClass];
		Temp += "/";
		Temp += d_entry->d_name;

		// Open Image Preprocess it and return it.
		IplImage *im_gray = cvLoadImage(Temp.c_str(),0);
		IplImage *resized = cvCreateImage(cvSize(IMGWIDTH,IMGHEIGHT),im_gray->depth,1);
		cvResize(im_gray,resized,0);
		cvReleaseImage(&im_gray);

		ClassNumber = atoi(ClassDirs[curClass].c_str());
		return resized;
	}
	/**
	 *
	 */
	void Reset(){
		curClass = 0;
		if (ClassDir)
			closedir(ClassDir);
		ClassDir = NULL;
	}

	/**
	 *
	 */
	void end(){
		chdir("..");
		closedir(RootDir);
	}
	/**
	 * Returns Number Of Images
	 */
	int numberofimages(){

		int filecount = 0, temp = 0;
		FILE *in;

		for(int i= 0; i< ClassDirs.size(); i++){

			 chdir(ClassDirs[i]);
			  in = popen("ls -l | wc -l", "r");
			  fscanf(in, "%d", &temp);
			  pclose(in);

			  filecount += temp - 2;
			  temp = 0;
			 chdir("..");
		}

		return filecount;
	}
};

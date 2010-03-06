#include "FolderReader.h"


/**
 * folder reader constructor
 */
	FolderReader::FolderReader(string dirname){
		Directory = dirname;
		// Open that directory
		RootDir = opendir(dirname.c_str());
		if (!RootDir)
			cout << " Failed to Open the Directory : " << dirname;
		// Change Directory
		chdir(dirname.c_str());
		// Read all the directories
		   ReadDirectories();

		   curClass = -1;
		   ClassDir = NULL;

		 nextClass();
	}
	/**
	 * Read all the directories in
	 */
	void FolderReader::ReadDirectories(){

		if (!RootDir)
			return;
		//
		struct dirent *d_entry;
		//
		while ((d_entry=readdir(RootDir))!=NULL)
			if (strcmp(d_entry->d_name,".") != 0 && strcmp(d_entry->d_name,"..") != 0)
				ClassDirs.push_back(d_entry->d_name);

		closedir(RootDir);

	}

	/**
	 * Go to Next Class
	 */
	bool FolderReader::nextClass(){
		// Close the Current Directory
		if (ClassDir)
		{
			closedir(ClassDir);
			ClassDir = NULL;
		}
		// Open the new Directory
		curClass ++ ;
		if (curClass >= (int)ClassDirs.size())
			return false;

		ClassDir = opendir(ClassDirs[curClass].c_str());
		if(!ClassDir)
			return false;
		else
			return true;
	}
	/**
	 * next image from the list
	 */
	IplImage* FolderReader::next(int &ClassNumber){
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
		IplImage *resized;
		resized = cvCreateImage( cvSize( IMGWIDTH, IMGHEIGHT ) , im_gray->depth ,1);
		cvResize(im_gray,resized,0);
		cvReleaseImage(&im_gray);

		ClassNumber = atoi(ClassDirs[curClass].c_str());
		return resized;
	}
	/**
	 * Result
	 *
	 */
	void FolderReader::reset(){
		curClass = 0;
		if (ClassDir)
			closedir(ClassDir);
		ClassDir = NULL;
	}

	/**
	 *
	 */
	void FolderReader::end(){
		chdir("..");
		closedir(RootDir);
	}
	/**
	 * Returns Number Of Images
	 */
	int FolderReader::numberofimages(){

		int filecount = 0, temp = 0;

		DIR* temp_dir;
		struct dirent* dir_entry;
		/// Start diving into the directories and counting the files
		for (int i=0; i<(int)ClassDirs.size(); i++)
		{
			temp_dir = opendir(ClassDirs[i].c_str());
			chdir(ClassDirs[i].c_str());
			while((dir_entry=readdir(temp_dir))!=NULL){
				if (strcmp(dir_entry->d_name,".")!=0 && strcmp(dir_entry->d_name,"..")!=0)
				{
					cout << dir_entry->d_name << endl;
					filecount ++;
				}
			}
			chdir("..");
			closedir(temp_dir);
		}

		return filecount;
	}

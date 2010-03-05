#include "Prerequs.h"
#include "FeatureDetector.h"
#include "InputReader.h"

/**
 * Folder Reader class
 */
class FolderReader : InputReader {

	string Directory;
	DIR *RootDir;

	vector<string> ClassDirs;

	int curClass;
	int curNum;

public:
	FolderReader(string dirname){
		Directory = dirname;
		// Open that directory
		RootDir = opendir(dirname);
		if (!RootDir)
					cout << " Failed to Open the Directory : " << dirname;
		// Change Directory
		chdir(dirname);
	}

	/**
	 *
	 */
	void ReadDirectories(){
		// Read all the directories
		DIR *dir = opendir(Dir.c_str());
		cout << Dir << endl;
		if (!dir)
			return;
		struct dirent *d_entry;

		while ((d_entry=readdir(dir))!=NULL)
			if (strcmp(d_entry->d_name,".") != 0 && strcmp(d_entry->d_name,"..") != 0)
				q.push_back(d_entry->d_name);

		closedir(dir);

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
		closedir(RootDir);
	}

};

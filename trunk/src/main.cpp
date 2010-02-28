#include "KMeans.h"
/**
 * Main function of the program
 * All the functionality resides within the Blobrecognizer class
 * Here I am passing two commands mainly
 * first variable decides whether you are training or recognizing
 * first = 1 for train => whenever u run with this command a window will popup select the object that yo want to
 * identify in that scene using a rectangle(lines will not show up while selecting but rectangle will get selected)
 * Hit any key after that. It is trained. Now try another image with first = 2;
 *
 * first = 2 for recognize... make sure u have inserted the image path in b.LoadImage function
 * second does not have any meaning right now.
 */
int main(int argc,char* argv[]){

	if (argc <= 1)
		return -1;

	KMeans kmeans("../Data",atoi(argv[1]));
	kmeans.Train();

	cout << "Training Complete\n";
	DIR *dir = opendir("../test");

	if (!dir)
		return 0;
	cout << "non - Complete\n";

	struct dirent *d_entry;
    char c;
    cvNamedWindow("Image");
    IplImage* iplimage;
	while ((d_entry=readdir(dir))!=NULL){
		cout << (string("../test/")+d_entry->d_name) << " - ";
		if (strcmp(d_entry->d_name,".")!=0 && strcmp(d_entry->d_name,"..")!=0)
		{

			cout << "==>" << kmeans.Test( (string("../test/")+d_entry->d_name) ) << endl;
			iplimage = cvLoadImage((string("../test/")+d_entry->d_name).c_str(),0);
			cvShowImage("Image",iplimage);
			cvWaitKey();
		}
	}
	cvDestroyAllWindows();

	closedir(dir);

	return 0;
}


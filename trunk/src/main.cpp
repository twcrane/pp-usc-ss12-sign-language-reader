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

	KMeans kmeans("directory",atoi(argv[1]));
	kmeans.Train();

	return 0;
}


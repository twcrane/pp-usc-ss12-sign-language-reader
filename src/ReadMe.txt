For Programmers
---------------
Notice: There has been some changes in architecture 
        Follow it for keeping the code clean.   

Main.cpp will not compile until unless you change the include path of NN and Kmeans in the main.cpp file to compile it. 

Put all the .h files in the include folder for easy access


Sign Language Recognition
-------------------------

Index 
-----
1) Introduction
2) Folder Structure
3) Build
4) Install
5) Extending it.








1) Introduction 
---------------






















2) Folder Structure 
-------------------







3) 

Dependencies: OpenCV, G++ 

There are total of 4 cpp files. 
1 Main file and 3 files for Machine Learning Algorithms. 
All the hand tracking code is in the main.cpp file.

Kmeans.cpp file contains the K nearest neighbours algorithm. 
NN.cpp file contains the implementation for reading and testing the Neural Network. 

Voting FrameWork integrates both the methods via voting.
Voting framework collects all the Different techniques using voting to improve the performance. 


Structure of the Directories: 
Data directory is the 



COMPILATION: 

1) For compilation, create an eclipse project with dependency on opencv and then add all the cpp files into the folder.
   Compile it directly.



Run The Program :

Run the Executable from Debug folder. Make sure if you are training you have training images in Data Folder.
For Testing images you can put images in the test folder. 

For live demo, run the executable and let it connect to the webcam.

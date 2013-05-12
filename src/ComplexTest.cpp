#include "..\include\ComplexTest.h"
#include "../include/BackgroundSubstract.h"
#include <iostream>
using namespace std;

#include <cv.h>
#include <highgui.h>
using namespace cv;

ComplexTest::ComplexTest(void)
{
	//namedWindow("flow", 1);
    namedWindow("before sub", 1);
	namedWindow("after sub", 1);
	BackgroundSubstract sub;
	VideoCapture cap("cafe.mov");
	Container cont;

	if(!cap.isOpened())
        cout << "probleme ouverture fichier video" << endl;
	else
		cout << "ok" << endl;


    


    Mat frame;
    cap >> frame;
		
	
	for(;;)
	{
		cont.setNewFrame(frame);

		imshow("before sub", cont.getImg());
		sub.run(cont);
		imshow("after sub", cont.getImg());
		
		cvWaitKey(10);
		cap >> frame;
	}
	system("pause");

}


ComplexTest::~ComplexTest(void)
{
}

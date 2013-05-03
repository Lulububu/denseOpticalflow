#undef _GLIBCXX_DEBUG

#include "cv.h"
#include "highgui.h"


#include "./include/Records.h"
#include "./include/AlgorithmManager.h"
#include "./include/BackGroundSubstract.h"
#include "./include/HumanDetection.h"
#include "./include/MovementDetection.h"
#include "./include/ObjectFollowing.h"
#include "./include/DecisionCout.h"

#include <iostream>
using namespace std;

using namespace cv;


int main(int argc, char** argv)
{

    
    
    VideoCapture cap("sdetect/clignotement.mov");


    //VideoCapture cap(0);
    namedWindow("flow", 1);
    namedWindow("origin", 1);

	AlgorithmManager manager;

	BackgroundSubstract bgsub; 
	manager.addPreprocess(&bgsub);

	MovementDetection mdetect;
	//manager.addDetection(&mdetect);

	ObjectFollowing objFoll;
	manager.addDetection(&objFoll);

	HumanDetection hdetect;
	manager.addDetection(&hdetect);

	DecisionCout decision;
	manager.addDecision(&decision);

	

    if( !cap.isOpened() )
        return -1;



    Mat frame;
    cap >> frame;

	Container container(frame.size().width, frame.size().height, 0.1);

    do
    {
		container.setNewFrame(frame);


		manager.preProcRun(container);
		manager.detectionProcRun(container);
		
                

        
  		for(unsigned int u = 0; u < container.getRecords().getObjects().size(); u++)
        {
			Rect r = container.getRecords().getObjects().at(u).getCurrentPosition();
			if(r.x >= 0)
			{
            rectangle( frame,
                 cvPoint( r.x, r.y ),
                 cvPoint( r.x + r.width, r.y + r.height ),
                 CV_RGB( 255, 0, 0 ), 1, 8, 0 );
			}

        }
		imshow("origin", container.getImg());
		imshow("flow", frame);


        if(waitKey(30)>=0)
            break;

        cap >> frame;
    }while(!frame.empty());
	

	manager.decisionRun(container);

    return 0;






}



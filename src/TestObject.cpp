#include "..\include\TestObject.h"

#include <cv.h>
using namespace cv;
#include <iostream>
using namespace std;
TestObject::TestObject(void)
{
	Object obj(Rect(10,15,20,25));
	
	assert(obj.getCurrentPosition() == Rect(10,15,20,25));

	obj.updatePosition(Point(100,5), 115, 200);


	assert(obj.getCurrentPosition() == Rect(110, 20, 4,25));
	assert(obj.getMovementUpdateNumber() == 1);
	assert(obj.getDistance() == (int)sqrt(100*100 + 5*5));
		
	obj.updatePosition(Rect(30,30,20,20));
	assert(obj.getCurrentPosition() == Rect(30,30,20,20));

	obj.addDetection();
	assert(obj.getDetectionNumber() == 1);

	cout << "test de Object terminé sans erreurs" << endl;
}


TestObject::~TestObject(void)
{
}

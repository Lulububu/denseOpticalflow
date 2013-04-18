#include "../include/ObjectFollowing.h"
#include "cv.h"
using namespace cv;

ObjectFollowing::ObjectFollowing(void)
{
}


ObjectFollowing::~ObjectFollowing(void)
{
}

void ObjectFollowing::run(Container& container)
{
	Mat flow;
	if(container.getRecords().getObjects().size() == 0)
	{
		container.getDetectionTool().updateImage(container.getImg());
	}
	else
	{
		for(int i = 0; i < container.getRecords().getObjects().size(); i++)
		{
			flow = container.getDetectionTool().getMovementDirection(
				container.getImg(), 
				container.getRecords().getObjects().at(i).getCurrentPosition()
			);

			Point dir = DetectionTool::getDirectionFlow(flow);
			if(dir.x != 0 || dir.y != 0)
			{
				//cout << "update position " << dir.x<< " " << dir.y<<endl;
				//cout << "rect " << rect.x << " " << rect.y << " " << rect.width << " " << rect.height << endl;
				container.getRecords().getObjects().at(i).updatePosition(dir);
			}

			//container.getRecords().updatePosition(flow);
		}
	}
	
	
}
	
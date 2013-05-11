#include "../include/ObjectFollowing.h"
#include "cv.h"
using namespace cv;

ObjectFollowing::ObjectFollowing(void)
{
	previous_img_initiated = false;
}


ObjectFollowing::~ObjectFollowing(void)
{
}

void ObjectFollowing::run(Container& container)
{
	Mat flow;
	if(container.getRecords().getObjects().size() == 0)
	{
		updateImage(container.getImg());
	}
	else
	{
		for(int i = 0; i < container.getRecords().getObjects().size(); i++)
		{
			flow = getMovementDirection(
				container.getImg(), 
				container.getRecords().getObjects().at(i).getCurrentPosition()
			);

			Point dir = DetectionTool::getDirectionFlow(flow);
			if(dir.x != 0 || dir.y != 0)
			{
				//cout << "update position " << dir.x<< " " << dir.y<<endl;
				//cout << "rect " << rect.x << " " << rect.y << " " << rect.width << " " << rect.height << endl;
				container.getRecords().getObjects().at(i).updatePosition(dir, container.getImg().size().width, container.getImg().size().height);
			}

			//container.getRecords().updatePosition(flow);
		}
	}
	
	
}
	


std::string ObjectFollowing::getClassName()
{
	return "ObjectFollowing";
}

void ObjectFollowing::setParameters(std::map<std::string, std::string>)
{

}

void ObjectFollowing::updateImage(cv::Mat& img)
{
	cvtColor(img, previous_img, CV_RGB2GRAY);
    previous_img_initiated = true;
}


Mat ObjectFollowing::getMovementDirection(Mat& img, Rect zone)
{
    Mat flow;
    Mat img_gray;
	//Mat prev_roi = img(zone);

    cvtColor(img, img_gray, CV_RGB2GRAY);
	//Mat img_gray_roi = img_gray(zone);
	Mat img_gray_roi = img_gray(zone).clone();
	

    if(previous_img_initiated)
	{
		Mat prev_roi = previous_img(zone).clone();
        calcOpticalFlowFarneback(prev_roi, img_gray_roi, flow, 0.5, 2, 10, 2, 14, 2.0, cv::OPTFLOW_FARNEBACK_GAUSSIAN);
	}
	

    previous_img = img_gray;
    previous_img_initiated = true;

    return flow;
}


Mat ObjectFollowing::getMovementDirection(Mat& img)
{
	return getMovementDirection(img, Rect(0, 0, img.cols, img.rows));
}
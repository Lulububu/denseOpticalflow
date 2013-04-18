#include "..\include\Container.h"
#include "../include/Records.h"

Container::Container(float ceil_)
{
	rec = Records(ceil_);
}


Container::~Container(void)
{
}

cv::Mat& Container::getImg()
{
	return img;
}

void Container::setNewFrame(cv::Mat frame)
{
	img = frame;
}


std::vector<cv::Rect>& Container::getHumanDetections()
{
	return humanDetections;
}

Records& Container::getRecords()
{
	return rec;
}

DetectionTool& Container::getDetectionTool()
{
	return tool;
}

#include "..\include\Container.h"
#include "../include/Records.h"

Container::Container(int max_width, int max_height, float ceil_): rec(max_width, max_height, ceil_)
{
//	rec = Records(max_width, max_height, ceil_);
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

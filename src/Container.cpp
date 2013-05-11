#include "..\include\Container.h"


Container::Container()
{
}



Container::~Container(void)
{
}



cv::Mat& Container::getImg()
{
	return img;
}

void Container::setNewFrame(cv::Mat& frame)
{
	img = frame;
}

void Container::setResolution(int width, int height)
{
	rec.setResolution(width, height);
}

std::vector<cv::Rect>& Container::getHumanDetections()
{
	return humanDetections;
}

Records& Container::getRecords()
{
	return rec;
}

void Container::setVideoFileName(std::string file_name)
{
	video_file_name = file_name;
}

std::string Container::getVideoFileName()
{
	return video_file_name;
}
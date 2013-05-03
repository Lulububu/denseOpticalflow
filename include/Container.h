#pragma once
#include <cv.h>

#include "Records.h"
#include "DetectionTool.h"

class Container
{
public:
	Container(int max_width, int max_height, float ceil_ = 0.5);
	
	virtual ~Container(void);
	cv::Mat& getImg();
	void setNewFrame(cv::Mat frame);

	std::vector<cv::Rect>& getHumanDetections();
	Records& getRecords();

	DetectionTool& getDetectionTool();

private:
	cv::Mat img;

	std::vector<cv::Rect> humanDetections;

	Records rec;

	DetectionTool tool;
};


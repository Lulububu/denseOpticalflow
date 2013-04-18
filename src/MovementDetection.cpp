#include "..\include\MovementDetection.h"

#include <vector>
#include "cv.h"
#include "../include/DetectionTool.h"

MovementDetection::MovementDetection(void)
{
}


MovementDetection::~MovementDetection(void)
{
}

void MovementDetection::run(Container& container)
{
	std::vector<cv::Rect> zones;
    std::vector<cv::Point> directions;
	container.getDetectionTool().computeMovement(container.getImg(), zones, directions);

	container.getRecords().checkMatchMovement(zones, directions);
}
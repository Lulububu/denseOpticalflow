#include "..\include\HumanDetection.h"


HumanDetection::HumanDetection(void)
{
}


HumanDetection::~HumanDetection(void)
{
}

void HumanDetection::run(Container& container)
{
	container.getDetectionTool().detectShape(container.getImg(), container.getHumanDetections());

	for(unsigned int u = 0; u < container.getHumanDetections().size(); u++)
	{
		container.getRecords().checkMatchDetection(container.getHumanDetections().at(u));
	}


}

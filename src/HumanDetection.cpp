#include "..\include\HumanDetection.h"

#include "../include/FileAccessException.h"

using namespace cv;
#include <exception>
using namespace std;
HumanDetection::HumanDetection(void)
{
	xml_file = "haarcascade_mcs_upperbody.xml";
	scale_factor = 1.1;
	min_neighbours = 3;
	flags = 1;
	load = false;
	ceil_match = 0.1;
}


HumanDetection::~HumanDetection(void)
{
}

void HumanDetection::run(Container& container)
{
	if(!load)
	{
		if(!cas.load(xml_file))
			throw FileAccessException(xml_file);
	}

	load = true;
	

	detectShape(container.getImg(), container.getHumanDetections(), scale_factor, min_neighbours, flags);

	for(unsigned int u = 0; u < container.getHumanDetections().size(); u++)
	{
		container.getRecords().checkMatchDetection(container.getHumanDetections().at(u), ceil_match);
	}
	

}

std::string HumanDetection::getClassName()
{
	return "HumanDetection";
}

void HumanDetection::setParameters(std::map<std::string, std::string> parameters)
{
	xml_file = parameters["xml_file"];
	istringstream(parameters["scale_factor"]) >> scale_factor;
	istringstream(parameters["min_neighbours"]) >> min_neighbours;
	istringstream(parameters["flags"]) >> flags;
	istringstream(parameters["ceil_match"]) >> ceil_match;

}

void HumanDetection::detectShape( Mat& src, vector<Rect>& rect, double scale_factor, int min_neighbours, int flags)
{
    cas.detectMultiScale(src, rect, scale_factor, min_neighbours,0|flags);
}
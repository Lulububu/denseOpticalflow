#pragma once
#include "DetectionProcessing.h"
#include "DetectionTool.h"
class HumanDetection :
	public DetectionProcessing
{
public:
	HumanDetection(void);
	~HumanDetection(void);

	void run(Container&);

private:
};


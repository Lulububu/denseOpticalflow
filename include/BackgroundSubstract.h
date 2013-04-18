#pragma once

#include "PreProcessing.h"
#include "DetectionTool.h"

class BackgroundSubstract :
	public PreProcessing
{
public:
	BackgroundSubstract();
	virtual ~BackgroundSubstract();

	void run(Container& cont);


private:
	DetectionTool tool;
};


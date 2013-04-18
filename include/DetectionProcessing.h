#pragma once

#include "Container.h"
class DetectionProcessing
{
public:
	DetectionProcessing(void);
	~DetectionProcessing(void);

	virtual void run(Container&) = 0;

};


#pragma once

#include "Container.h"

class DecisionProcessing
{
public:
	DecisionProcessing(void);
	~DecisionProcessing(void);

	virtual void run(Container&) = 0;
};


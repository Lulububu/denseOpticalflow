#pragma once
#include "decisionprocessing.h"
class DecisionCout :
	public DecisionProcessing
{
public:
	DecisionCout(void);
	~DecisionCout(void);

	void run(Container&);
};


#pragma once
#include "DetectionProcessing.h"

class MovementDetection :
	public DetectionProcessing
{
public:
	MovementDetection(void);
	~MovementDetection(void);

	void run(Container&);
private:

};


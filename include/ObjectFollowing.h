#pragma once
#include "DetectionProcessing.h"
class ObjectFollowing :
	public DetectionProcessing
{
public:
	ObjectFollowing(void);
	~ObjectFollowing(void);

	void run(Container&);
};


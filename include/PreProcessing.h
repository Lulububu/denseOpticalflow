#pragma once

#include "Container.h"
#include "Process.h"

class PreProcessing{
public:
	PreProcessing(void);
	~PreProcessing(void);

	virtual void run(Container&) = 0;

private:
	
};


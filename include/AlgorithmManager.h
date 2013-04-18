#pragma once

#include <vector>
using namespace std;

#include "PreProcessing.h"
#include "DetectionProcessing.h"

class AlgorithmManager
{
public:
	AlgorithmManager(void);
	~AlgorithmManager(void);

	void preProcRun(Container& container);
	void addPreprocess(PreProcessing* preprocess);

	void addDetection(DetectionProcessing* detection);
	void detectionProcRun(Container&);

private:
	vector<PreProcessing*> preprocesses;

	vector<DetectionProcessing*> detectionsprocess;
};


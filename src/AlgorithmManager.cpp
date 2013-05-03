#include "..\include\AlgorithmManager.h"


AlgorithmManager::AlgorithmManager(void)
{
}


AlgorithmManager::~AlgorithmManager(void)
{
}

void AlgorithmManager::preProcRun(Container& container)
{
	for (vector<PreProcessing*>::iterator it = preprocesses.begin(); it!=preprocesses.end(); ++it)
		((*it))->run(container);
	
}

void AlgorithmManager::addPreprocess(PreProcessing* preprocess)
{
	preprocesses.push_back(preprocess);
}

void AlgorithmManager::addDetection(DetectionProcessing* detection)
{
	detectionsprocess.push_back(detection);
}
void AlgorithmManager::detectionProcRun(Container& container)
{
	for (vector<DetectionProcessing*>::iterator it = detectionsprocess.begin(); it!=detectionsprocess.end(); ++it)
		((*it))->run(container);
}

void AlgorithmManager::addDecision(DecisionProcessing* decision)
{
	decisionprocess.push_back(decision);
}
void AlgorithmManager::decisionRun(Container& container)
{
	for (vector<DecisionProcessing*>::iterator it = decisionprocess.begin(); it!=decisionprocess.end(); ++it)
		((*it))->run(container);
}

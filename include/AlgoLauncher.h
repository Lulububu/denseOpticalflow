#pragma once

#include "AlgorithmManager.h"

#include <highgui.h>
#include <cv.h>

#include <string>
using namespace std;

class AlgoLauncher
{
public:
	AlgoLauncher(string file_name);
	~AlgoLauncher(void);

	bool loadParameters(string file_name);
	void execute();

protected:
	AlgorithmManager manager;
	cv::Mat frame;
	cv::VideoCapture cap;
	Container container;
};


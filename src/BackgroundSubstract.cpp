#include "..\include\BackgroundSubstract.h"

#include <string>
using namespace std;
using namespace cv;

BackgroundSubstract::BackgroundSubstract()
{
	erode_iteration = 2;
	dilate_iteration = 17;
	bg_model_initiated = false;
}


BackgroundSubstract::~BackgroundSubstract()
{
}

void BackgroundSubstract::run(Container& cont)
{
	if(updateBackgroundModel(cont.getImg()))
	{
		cont.getImg() = getForeground(erode_iteration, dilate_iteration);
	}
}

std::string BackgroundSubstract::getClassName()
{
	return "BackgroundSubstraction";
}

void BackgroundSubstract::setParameters(map<string, string> parameters)
{
	istringstream(parameters["erode_iteration"]) >> erode_iteration;
	istringstream(parameters["dilate_iteration"]) >> dilate_iteration;
}

bool BackgroundSubstract::updateBackgroundModel(Mat& img)
{
    current_img = img;
    IplImage ipl = img;
    if(!bg_model_initiated)
    {
        background_model = cvCreateFGDStatModel(&ipl);
        bg_model_initiated= true;
		return false;
    }else
    {
        cvUpdateBGStatModel(&ipl,background_model);
		return true;
    }
}

Mat BackgroundSubstract::getForeground(int nb_erode, int nbdilate)
{
    Mat result = background_model->foreground;

    cvtColor(result, result, CV_GRAY2RGB);
    erode(result, result, Mat(),Point(-1, -1), nb_erode);
    dilate(result, result, Mat(), Point(-1, -1),  nbdilate);
    bitwise_and(result, current_img, result );
    return result;
}
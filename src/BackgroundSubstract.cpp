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
	
	//mise à jour du modèle d'arrière plan et modification de l'image
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
    {//initialisation du modèle d'arrière plan
        background_model = cvCreateFGDStatModel(&ipl);
        bg_model_initiated= true;
		return false;
    }else
    {
		//mise à jour
        cvUpdateBGStatModel(&ipl,background_model);
		return true;
    }
}

Mat BackgroundSubstract::getForeground(int nb_erode, int nbdilate)
{
	//on utilise le résultat du background model comme un masque sur l'image de la vidéo
    Mat result = background_model->foreground;

    cvtColor(result, result, CV_GRAY2RGB);

	//l'érosion dilatation permet de supprimer les zones trop petites
    erode(result, result, Mat(),Point(-1, -1), nb_erode);
    dilate(result, result, Mat(), Point(-1, -1),  nbdilate);

    bitwise_and(result, current_img, result );
    return result;
}
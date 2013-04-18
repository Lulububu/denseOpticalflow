#include "../include/DetectionTool.h"

using namespace std;
using namespace cv;


DetectionTool::DetectionTool()
{
    cas.load("haarcascade_mcs_upperbody.xml");
    bg_model_initiated = false;
    previous_img_initiated = false;
	first_frame = true;

}

DetectionTool::~DetectionTool()
{
    //dtor
}





bool DetectionTool::isFlowCorrect(Point2f u)
{
    return !cvIsNaN(u.x) && !cvIsNaN(u.y) && fabs(u.x) < 1e9 && fabs(u.y) < 1e9;
}


void DetectionTool::getMove(const Mat_<Point2f>& flow, Mat& dst, float minmotion, int color)
{
    dst.create(flow.size(), CV_8UC1);
    dst.setTo(Scalar::all(0));

    //Permet de ne pas calculer la racine carrée pour chaque longueur de vecteur de mouvement.
    //Si minmotion <= 0, on veut sélectionner tous les mouvements.
    if(minmotion > 0)
        minmotion *= minmotion;

    //Parcours de la matrice des mouvements
    for (int y = 0; y < flow.rows; ++y)
    {
        for (int x = 0; x < flow.cols; ++x)
        {
            Point2f u = flow(y, x);
            if (isFlowCorrect(u))
            {
                //la comparaison se fait sans la mise sous racine car on a élevé au carré minmotion
                if(u.x * u.x + u.y * u.y > minmotion)
                {
                    dst.at<char>(y, x) = color;
                }
            }
        }
    }
}


Point DetectionTool::getDirectionRectangle(const Mat_<Point2f>& flow, Point a, Point b)
{
    Point res(0.f,0.f);
	int nb_elem = 0;
    //Parcours des points à l'intérieur du rectangle
    for(int i = a.x; i < b.x; i++)
    {
        for(int j = a.y; j < b.y; j++)
        {
            //Sommation de chaque mouvement contenu dans le rectangle
            res.x += (float) (flow.at<Point2f>(j,i).x);
            res.y += (float) (flow.at<Point2f>(j,i).y);

			if(flow.at<Point2f>(j,i).x != 0 || flow.at<Point2f>(j,i).y !=0)
				nb_elem++;
        }
    }
    //float nb_elem = (float)((b.x - a.x) * (b.y - a.y));

    //nb_elem /= 2;

    //Le calcul étant une moyenne, on divise par le nombre d'élément que l'on a sommé
	if(nb_elem!=0)
		return Point(res.x/nb_elem, res.y/nb_elem);
	else
		return Point(0,0);
}

Point DetectionTool::getDirectionFlow(const Mat_<Point2f>& flow)
{
	return getDirectionRectangle(flow, Point(0,0), Point(flow.cols, flow.rows));
}


Point DetectionTool::getDirectionRectangle(const Mat_<Point2f>& flow, Rect_<int> rect)
{
    return getDirectionRectangle(flow, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y + rect.height));
}


Rect DetectionTool::getContainingRect(vector<Point> contours)
{
    if(contours.size() > 0)
    {
        Point mini = contours.at(0);
        Point maxi(0, 0);

        //recherche des coordonnées les plus extrèmes
        //Le premier point sert d'initialisation
        for(unsigned int j = 1; j < contours.size(); j++)
        {
            Point u = contours.at(j);
            if(u.x < mini.x)
                mini.x = u.x;
            if(u.x > maxi.x)
                maxi.x = u.x;
            if(u.y < mini.y)
                mini.y = u.y;
            if(u.y > maxi.y)
                maxi.y = u.y;
        }

        return Rect(mini.x, mini.y, maxi.x - mini.x, maxi.y - mini.y);
    }else
    {
        return Rect(0,0,0,0);
    }
}

void DetectionTool::detectShape( Mat& src, vector<Rect>& rect)
{
    cas.detectMultiScale(src, rect, 1.1, 3,0|CV_HAAR_DO_CANNY_PRUNING);
}


bool DetectionTool::updateBackgroundModel(Mat& img)
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

Mat DetectionTool::getForeground()
{
    Mat result = background_model->foreground;

    cvtColor(result, result, CV_GRAY2RGB);
    erode(result, result, Mat(),Point(-1, -1), 2);
    dilate(result, result, Mat(), Point(-1, -1),  17);
    bitwise_and(result, current_img, result );
    return result;
}

Mat DetectionTool::getMovementDirection(Mat& img, Rect zone)
{
    Mat flow;
    Mat img_gray;
	//Mat prev_roi = img(zone);

    cvtColor(img, img_gray, CV_RGB2GRAY);
	//Mat img_gray_roi = img_gray(zone);
	Mat img_gray_roi = img_gray(zone).clone();
	

    if(previous_img_initiated)
	{
		Mat prev_roi = previous_img(zone).clone();
        calcOpticalFlowFarneback(prev_roi, img_gray_roi, flow, 0.5, 2, 10, 2, 14, 2.0, cv::OPTFLOW_FARNEBACK_GAUSSIAN);
	}
	

    previous_img = img_gray;
    previous_img_initiated = true;

    return flow;
}

Mat DetectionTool::getMovementDirection(Mat& img)
{
	return getMovementDirection(img, Rect(0, 0, img.cols, img.rows));
}

void DetectionTool::computeMovement(Mat& img, vector<Rect>& zones, vector<Point>& directions)
{
    Mat flow,cflow;
    flow = getMovementDirection(img);

    if(!first_frame)
    {
        getMove(flow, cflow, 2, 255);
        vector<vector<Point> > contours;
        findContours(cflow, contours, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_SIMPLE );

        zones.clear();

        for(unsigned int i = 0; i < contours.size(); i++)
        {
            Rect zone = getContainingRect(contours.at(i));

            if(zone.size().width > 30 && zone.size().height > 30 )
            {
                Point dir = getDirectionRectangle(flow, zone);

                zones.push_back(zone);
                directions.push_back(dir);
            }

        }
    }else
    {
        first_frame = false;
    }
}


void DetectionTool::updateImage(cv::Mat img)
{
	cvtColor(img, previous_img, CV_RGB2GRAY);
    previous_img_initiated = true;
}
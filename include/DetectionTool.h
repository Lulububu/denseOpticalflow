#ifndef DetectionTool_H
#define DetectionTool_H


#include "cv.h"
#include "highgui.h"
#include "cvaux.h"

#include <iostream>
#include <vector>






class DetectionTool
{
    public:
        DetectionTool();
        virtual ~DetectionTool();






        static bool isFlowCorrect(cv::Point2f u);

        /**
         * Permet de r�cup�rer les zones ayant un mouvement sup�rieur � minmotion.
         * @param flow Contient les mouvements pour chaque point de l'image. R�sultat de la fonction calc() de la classe
         * d'OpenCV impl�mentant �Dual TV L1� Optical Flow DetectionTool.
         * @param dst cv::Matrice contenant le r�sultat du filtrage.
         * @param minmotion Le mouvement minimal qui sera conserv�.
         * @param color L'intensit� du pixel en nuance de gris qui indiquera la pr�sence de mouvement. (Esth�tique)
         **/
        void getMove(const cv::Mat_<cv::Point2f>& flow, cv::Mat& dst, float minmotion = -1, int color = 100);

        /**
         * Permet de calculer pour un rectangle un mouvement moyen.
         * @param flow Contient les mouvements pour chaque point de l'image. R�sultat de la fonction calc() de la classe
         * d'OpenCV impl�mentant �Dual TV L1� Optical Flow DetectionTool.
         * @param a Point sup�rieur gauche du rectangle.
         * @param b Point inf�rieur droit du rectangle.
         * @return Point repr�sentant la direction du mouvement moyen. La direction correspond au vecteur ayant comme
         * point initial (0,0) et point d'arriv�e le point r�tourn�.
         **/
        static cv::Point getDirectionRectangle(const cv::Mat_<cv::Point2f>& flow, cv::Point a, cv::Point b);

        /**
         * Adaptation avec Rect.
         **/
        static cv::Point getDirectionRectangle(const cv::Mat_<cv::Point2f>& flow, cv::Rect rect);

        /**
         * Renvoie le rectangle minimal contenant un ensemble de points.
         * @param contours Vecteur contenant les points � entourer.
         * @return Rectangle entourant les points contenus dans le vecteur.
         **/
        cv::Rect getContainingRect(std::vector<cv::Point> contours);


        /**
         * D�tecte les formes humaines contenues dans une image et place leurs coordonn�es dans le vecteur de rectangle.
         * @param src Image � analyser.
         * @param rect Vecteur contenant le r�sultat sous la forme des emplacements des formes d�tect�es.
         **/
        void detectShape( cv::Mat& src, std::vector<cv::Rect>& rect);

		/**
		 * Met � jour le mod�le du fond. Si c'est la premi�re fois que cette fonction est appel�e, 
		 * le mod�le est initialis� automatiquement.
		 * @param img L'image avec laquelle on souhaite mettre � jour le mod�le de fond.
		 * @return True si le mod�le �tait d�j� initialis� et donc que la soustraction est effective. False sinon.
		 **/
        bool updateBackgroundModel(cv::Mat& img);

		/**
		 * Renvoie l'image du premier plan correspondant au calcul effectu� dans la fonction updateBackgroundModel.
		 * @return Image repr�sentant le premier plan.
		 **/
        cv::Mat getForeground();

		/**
		 * Renvoie la matrice contenant pour chaque pixel le mouvement d�tect�.
		 * R�sultat du calcul par flot optique dense de cv::calcOpticalFlowFarneback().
		 * Le premier appel � la fonction ne renvoie qu'une matrice vide. 
		 * Il faut au moins deux appels pour que le r�sultat soit pertinent.
		 * @param img Image dont on veut calculer le mouvement. Calcul� par rapport � la pr�c�dente image.
		 * @return Matrice de direction de la taille de l'image pass� en param�tre.
		 **/
        cv::Mat getMovementDirection(cv::Mat& img, cv::Rect zone);

		/**
		 * Version de cv::Mat getMovementDirection(cv::Mat& img, cv::Rect zone) sur l'ensemble de l'image.
		 **/
		cv::Mat getMovementDirection(cv::Mat& img);

		/**
		 * Calcule les zones de mouvements coh�rents. Ces zones sont d�limit�es par des rectangles. 
		 * Chaque zone est associ�e � une direction moyenne.
		 * @param img Matrice contenant les directions des mouvements.
		 * @param zones Vecteur de Rectangle accueillant le r�sultat de la fonction. Correspond � l'ensemble des zones de mouvements.
		 * @param directions Vecteur correspondant � la direction moyenne de chacune des zones indiquer dans l'objet zones.
		 * La correspondance se fait par indice. La taille du vecteur est donc la m�me que le param�tre pr�c�dent.
		 **/
        void computeMovement(cv::Mat& img, std::vector<cv::Rect>& zones, std::vector<cv::Point>& directions);

		void updateImage(cv::Mat img);
		static cv::Point getDirectionFlow(const cv::Mat_<cv::Point2f>& flow);

    protected:
        cv::CascadeClassifier cas;
        CvBGStatModel* background_model;
        cv::Mat current_img;
        cv::Mat previous_img;

        bool bg_model_initiated;
        bool previous_img_initiated;
        bool first_frame;

    private:
};

#endif // DetectionTool_H

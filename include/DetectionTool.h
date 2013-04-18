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
         * Permet de récupérer les zones ayant un mouvement supérieur à minmotion.
         * @param flow Contient les mouvements pour chaque point de l'image. Résultat de la fonction calc() de la classe
         * d'OpenCV implémentant “Dual TV L1” Optical Flow DetectionTool.
         * @param dst cv::Matrice contenant le résultat du filtrage.
         * @param minmotion Le mouvement minimal qui sera conservé.
         * @param color L'intensité du pixel en nuance de gris qui indiquera la présence de mouvement. (Esthétique)
         **/
        void getMove(const cv::Mat_<cv::Point2f>& flow, cv::Mat& dst, float minmotion = -1, int color = 100);

        /**
         * Permet de calculer pour un rectangle un mouvement moyen.
         * @param flow Contient les mouvements pour chaque point de l'image. Résultat de la fonction calc() de la classe
         * d'OpenCV implémentant “Dual TV L1” Optical Flow DetectionTool.
         * @param a Point supérieur gauche du rectangle.
         * @param b Point inférieur droit du rectangle.
         * @return Point représentant la direction du mouvement moyen. La direction correspond au vecteur ayant comme
         * point initial (0,0) et point d'arrivée le point rétourné.
         **/
        static cv::Point getDirectionRectangle(const cv::Mat_<cv::Point2f>& flow, cv::Point a, cv::Point b);

        /**
         * Adaptation avec Rect.
         **/
        static cv::Point getDirectionRectangle(const cv::Mat_<cv::Point2f>& flow, cv::Rect rect);

        /**
         * Renvoie le rectangle minimal contenant un ensemble de points.
         * @param contours Vecteur contenant les points à entourer.
         * @return Rectangle entourant les points contenus dans le vecteur.
         **/
        cv::Rect getContainingRect(std::vector<cv::Point> contours);


        /**
         * Détecte les formes humaines contenues dans une image et place leurs coordonnées dans le vecteur de rectangle.
         * @param src Image à analyser.
         * @param rect Vecteur contenant le résultat sous la forme des emplacements des formes détectées.
         **/
        void detectShape( cv::Mat& src, std::vector<cv::Rect>& rect);

		/**
		 * Met à jour le modèle du fond. Si c'est la première fois que cette fonction est appelée, 
		 * le modèle est initialisé automatiquement.
		 * @param img L'image avec laquelle on souhaite mettre à jour le modèle de fond.
		 * @return True si le modèle était déjà initialisé et donc que la soustraction est effective. False sinon.
		 **/
        bool updateBackgroundModel(cv::Mat& img);

		/**
		 * Renvoie l'image du premier plan correspondant au calcul effectué dans la fonction updateBackgroundModel.
		 * @return Image représentant le premier plan.
		 **/
        cv::Mat getForeground();

		/**
		 * Renvoie la matrice contenant pour chaque pixel le mouvement détecté.
		 * Résultat du calcul par flot optique dense de cv::calcOpticalFlowFarneback().
		 * Le premier appel à la fonction ne renvoie qu'une matrice vide. 
		 * Il faut au moins deux appels pour que le résultat soit pertinent.
		 * @param img Image dont on veut calculer le mouvement. Calculé par rapport à la précédente image.
		 * @return Matrice de direction de la taille de l'image passé en paramètre.
		 **/
        cv::Mat getMovementDirection(cv::Mat& img, cv::Rect zone);

		/**
		 * Version de cv::Mat getMovementDirection(cv::Mat& img, cv::Rect zone) sur l'ensemble de l'image.
		 **/
		cv::Mat getMovementDirection(cv::Mat& img);

		/**
		 * Calcule les zones de mouvements cohérents. Ces zones sont délimitées par des rectangles. 
		 * Chaque zone est associée à une direction moyenne.
		 * @param img Matrice contenant les directions des mouvements.
		 * @param zones Vecteur de Rectangle accueillant le résultat de la fonction. Correspond à l'ensemble des zones de mouvements.
		 * @param directions Vecteur correspondant à la direction moyenne de chacune des zones indiquer dans l'objet zones.
		 * La correspondance se fait par indice. La taille du vecteur est donc la même que le paramètre précédent.
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

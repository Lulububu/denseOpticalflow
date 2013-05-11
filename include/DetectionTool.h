#ifndef DetectionTool_H
#define DetectionTool_H


#include "cv.h"
#include "highgui.h"
#include "cvaux.h"

#include <iostream>
#include <vector>


/**
 * Classe regroupant des outils pouvant être utilisé par plusieurs classe de détection.
 **/



class DetectionTool
{
    public:
        DetectionTool();
        virtual ~DetectionTool();

		/**
		 * Vérifie que le point (en fait une direction) est valide.
		 * @param u Point devant être vérifié.
		 * @return bool True si le Point est correct, False sinon.
		 **/
        static bool isFlowCorrect(cv::Point2f u);

        /**
         * Permet de récupérer les zones ayant un mouvement supérieur à minmotion.
         * @param flow Contient les mouvements pour chaque point de l'image. Résultat de la 
		 * fonction calc() de la classe d'OpenCV implémentant “Dual TV L1” Optical Flow DetectionTool.
         * @param dst cv::Matrice contenant le résultat du filtrage.
         * @param minmotion Le mouvement minimal qui sera conservé.
         * @param color L'intensité du pixel en nuance de gris qui indiquera la présence de mouvement. 
		 * (Esthétique)
         **/
        static void getMove(const cv::Mat_<cv::Point2f>& flow, cv::Mat& dst, float minmotion = -1, int color = 100);

        /**
         * Permet de calculer pour un rectangle un mouvement moyen.
         * @param flow Contient les mouvements pour chaque point de l'image. Résultat de la 
		 * fonction calc() de la classe d'OpenCV implémentant “Dual TV L1” Optical Flow DetectionTool.
         * @param a Point supérieur gauche du rectangle.
         * @param b Point inférieur droit du rectangle.
         * @return Point représentant la direction du mouvement moyen. La direction correspond au 
		 * vecteur ayant comme point initial (0,0) et point d'arrivée le point rétourné.
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
		 * Adaptaion de getDirectionRectangle() sur l'ensemble de l'image.
		 **/
		static cv::Point getDirectionFlow(const cv::Mat_<cv::Point2f>& flow);

};

#endif // DetectionTool_H

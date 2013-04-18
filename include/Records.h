#ifndef RECORDS_H
#define RECORDS_H

#include <vector>
#include <cv.h>

#include "Object.h"
/**
 * Classe de gestion des objets enregistrés au cours de la détection.  
 *
**/
class Records
{
    public:
		/**
		 * Contructeur unique.
		 * @param ceil Seuil à atteindre pour que deux rectangles soit considérés comme identiques. 
		 * Ce seuil est comparé au résultat du calcul de l'aire de l'intersection divisé par l'aire de l'union des rectangles.
		 **/
        Records(float ceil_ = 0.5);

        virtual ~Records();

		/**
		 * Vérifie si l'élément passé en paramètre correspond à une des zones déjà présentes dans l'objet.
		 * Si c'est le cas, une détection est ajouté à cette zone. Autrement, une nouvelle zone est ajoutée.
		 * @param coordinates Zone a comparé avec les zones existantes.
		 * @return True si correspondance, False si création. 
		 **/
        bool checkMatchDetection(cv::Rect& coordinates);

		/**
		 * Vérifie si l'élément passé en paramètre correspond à une des zones déjà présentes dans l'objet.
		 * Si c'est le cas, la position de l'objet est mise à jour avec la direction. Autrement, une nouvelle zone est ajoutée.
		 * @param coordinates Zone a comparé avec les zones existantes.
		 * @param direction Direction correspondant à la zone du paramètre précédent.
		 * @return True si correspondance, False si création. 
		 **/
        bool checkMatchMovement(cv::Rect& coordinates, cv::Point& direction);

		/**
		 * Méthode calculant les correspondance entre un ensemble de zones et les zones déjà surveillées. 
		 * @param Vecteur contenant l'ensemble des zones à faire correspondre.
		 * @param Vecteur de même taille contenant les directions correspondant aux zones.
		 **/
        void checkMatchMovement(std::vector<cv::Rect>& zones, std::vector<cv::Point>& dirs);


        void createObject(cv::Rect coordinates);

        std::vector<Object>& getObjects();

		void updatePosition(cv::Mat& flow);

    protected:
        std::vector<Object> objects;
        float ceil;

        void checkMatch(cv::Rect& coordinates, float& match_value, int& match_index);

    private:



};

#endif // RECORDS_H

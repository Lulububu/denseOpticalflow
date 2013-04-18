#ifndef RECORDS_H
#define RECORDS_H

#include <vector>
#include <cv.h>

#include "Object.h"
/**
 * Classe de gestion des objets enregistr�s au cours de la d�tection.  
 *
**/
class Records
{
    public:
		/**
		 * Contructeur unique.
		 * @param ceil Seuil � atteindre pour que deux rectangles soit consid�r�s comme identiques. 
		 * Ce seuil est compar� au r�sultat du calcul de l'aire de l'intersection divis� par l'aire de l'union des rectangles.
		 **/
        Records(float ceil_ = 0.5);

        virtual ~Records();

		/**
		 * V�rifie si l'�l�ment pass� en param�tre correspond � une des zones d�j� pr�sentes dans l'objet.
		 * Si c'est le cas, une d�tection est ajout� � cette zone. Autrement, une nouvelle zone est ajout�e.
		 * @param coordinates Zone a compar� avec les zones existantes.
		 * @return True si correspondance, False si cr�ation. 
		 **/
        bool checkMatchDetection(cv::Rect& coordinates);

		/**
		 * V�rifie si l'�l�ment pass� en param�tre correspond � une des zones d�j� pr�sentes dans l'objet.
		 * Si c'est le cas, la position de l'objet est mise � jour avec la direction. Autrement, une nouvelle zone est ajout�e.
		 * @param coordinates Zone a compar� avec les zones existantes.
		 * @param direction Direction correspondant � la zone du param�tre pr�c�dent.
		 * @return True si correspondance, False si cr�ation. 
		 **/
        bool checkMatchMovement(cv::Rect& coordinates, cv::Point& direction);

		/**
		 * M�thode calculant les correspondance entre un ensemble de zones et les zones d�j� surveill�es. 
		 * @param Vecteur contenant l'ensemble des zones � faire correspondre.
		 * @param Vecteur de m�me taille contenant les directions correspondant aux zones.
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

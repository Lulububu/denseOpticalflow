#ifndef OBJECT_H
#define OBJECT_H

#include <cv.h>

/**
 * Cette classe représente un objet qui a été détecté comme forme humaine au moins une fois
 * Tout au long de la vidéo, un suivi de cette objet est fait. A la fin on a toutes les informations
 * sur le comportement de cette objet durant la vidéo.
 **/
class Object
{
    public:
		Object();

		/**
		 * Initialisation avec une zone donnant les coordonnées de l'objet que l'on désire suivre.
		 * @param position de l'élément.
		 **/
        Object(cv::Rect position);

        virtual ~Object();

		/**
		 * Renvoie la dernière position connu de l'objet.
		 * @return Rect position de l'objet.
		 **/
        cv::Rect getCurrentPosition();

		/**
		 * Renvoie le nombre de détection qui ont été effectué sur cet objet.
		 * @return int nombre de détection.
		 **/
        unsigned int getDetectionNumber();

		/**
		 * Renvoie le nombre de mise à jour de position qui ont été effectué sur cet objet.
		 * Concerne les mise à jour par nouvelle détection et les mise à jour par détection de mouvement.
		 * @return int nombre de changement de position.
		 **/
        unsigned int getMovementUpdateNumber();

		/**
		 * Met à jour la position de l'objet en le faisant translaté par la valeur de direction.
		 * Si l'objet dépasse de la frame, le rectangle donnant les coordonnées de l'objet est "écrasé"
		 * sur les bords.
		 * @param direction Vecteur (représenté par un point) donnant la direction de déplacement.
		 * @param width_max largeur de la frame de la vidéo sur laquelle on travaille.
		 * @param height_max hauteur de la frame de la vidéo sur laquelle on travaille.
		 **/
        void updatePosition(cv::Point direction, int width_max, int height_max);

		/**
		 * Met à jour la position de l'objet avec les nouvelles coordonnées.
		 * @param pos Rectangle donnant l nouvelle position.
		 **/
		void updatePosition(cv::Rect pos);

		/**
		 * Incrémente le nombre de détection effectué sur cet objet.
		 **/
        void addDetection();

		/**
		 * Renvoie la distance parcourue jusqu'ici par l'objet.
		 * @return int distance parcourue.
		 **/
		unsigned int getDistance();


		


    protected:
        cv::Rect current_position;
        unsigned int detection_number;
		unsigned int distance;
        unsigned int movemement_update_number;

    private:
		/**
		 * Si le rectangle rect dépasse les bornes définies par les paramètres width et height, 
		 * ses valeurs sont rammenées pour ne plus dépasser. L'opération est effectuée
		 * directement sur le paramètre rect passé en référence. Le rectangle ne dépassera pas width-1 et height-1
		 * ceci car la résolution est égale à l'index maximal dans la matrice + 1.
		 * @param rect Référence vers le rectangle que l'on veut restreindre à une zone.
		 * @param width largeur de la zone autorisée.
		 * @param height hauteur de la zone autorisée.
		 **/
		static void checkPointBound(cv::Rect& rect, int width, int height);
};

#endif // OBJECT_H

#ifndef RECORDS_H
#define RECORDS_H

#include <vector>
#include <cv.h>

#include "Object.h"
/**
 * Classe de gestion des objets enregistrés au cours de la détection.  
**/
class Records
{
    public:
		/**
		 * Contructeur unique.
		 * @param max_width largeur des frames sur lesquelles on travaille.
		 * @param max_height hauteur des frames sur lesquelles on travaille.
		 **/
        Records();

        virtual ~Records();

		/**
		 * Renseigne la résolution de la vidéo sur laquelle on travaille.
		 * @param max_width largeur de l'image.
		 * @param max_height hauteur de l'image.
		 **/
		void setResolution(int max_width, int max_height);

		/**
		 * Vérifie si l'élément passé en paramètre correspond à une des zones déjà présentes dans l'objet.
		 * Si c'est le cas, une détection est ajouté à cette zone. Autrement, une nouvelle zone est ajoutée.
		 * @param coordinates Zone a comparé avec les zones existantes.
		 * @param ceil seuil indiquant si deux zones (Rect) peuvent être considérées comme identiques.
		 * @return True si correspondance, False si création. 
		 **/
        bool checkMatchDetection(cv::Rect& coordinates, float ceil);

		/**
		 * Vérifie si l'élément passé en paramètre correspond à une des zones déjà présentes dans l'objet.
		 * Si c'est le cas, la position de l'objet est mise à jour avec la direction. Autrement, une nouvelle zone est ajoutée.
		 * @param coordinates Zone a comparé avec les zones existantes.
		 * @param direction Direction correspondant à la zone du paramètre précédent.
		 * @param ceil seuil indiquant si deux zones (Rect) peuvent être considérées comme identiques.
		 * @return True si correspondance, False si création. 
		 **/
        bool checkMatchMovement(cv::Rect& coordinates, cv::Point& direction, float ceil);

		/**
		 * Méthode calculant les correspondance entre un ensemble de zones et les zones déjà surveillées. 
		 * @param Vecteur contenant l'ensemble des zones à faire correspondre.
		 * @param Vecteur de même taille contenant les directions correspondant aux zones.
		 * @param ceil seuil indiquant si deux zones (Rect) peuvent être considérées comme identiques.
		 **/
        void checkMatchMovement(std::vector<cv::Rect>& zones, std::vector<cv::Point>& dirs, float ceil);

		/**
		 * Ajoute un nouvel objet à la classe.
		 * @param coordinates coordonnées du nouvel objet.
		 **/
        void createObject(cv::Rect coordinates);

		/**
		 * Renvoie la liste de tous les objets contenus dans la classe.
		 * @return vector<Object> Référence vers la liste d'objets crées dans cette classe.
		 **/
        std::vector<Object>& getObjects();

		/**
		 * Met à jour la position de chaque objet suivi grâce à la détection de mouvement.
		 * @param flow Matrice contenant le mouvement de l'ensemble de l'image.
		 **/
		void updatePosition(cv::Mat& flow);

    protected:
        std::vector<Object> objects;
        
		/**
		 * Vérifie si un des objets déjà suivi correspond aux coordonnées de coordinates.
		 * Si c'est le case, on indique la valeur de correspondance dans match_value et 
		 * on indique l'indice de l'objet dans notre vecteurs (attributs objects).
		 * @param coordinates Coordonnées de la zone dont l'on veut vérifier si elle correspond
		 * à un objet déjà enregistré.
		 * @param match_value Référence qui va accueillir la valeur d'une éventuelle corrrespondance
		 * entre les coordonneés passées en paramètres et les objets déjà suivis. 0 si aucune correspondance 
		 * n'est trouvée.
		 * @param match_index Index de l'objet correspondant aux coordonnées passées en paramètre. 
		 * Cette index correspond à l'attribut objects de cette classe. -1 si aucune correspondance
		 * n'est trouvée.
		 **/
        void checkMatch(cv::Rect& coordinates, float& match_value, int& match_index);

		int max_width;
		int max_height;


};

#endif // RECORDS_H

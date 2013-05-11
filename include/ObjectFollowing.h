#pragma once
#include "DetectionProcessing.h"

#include "cv.h"
#include "highgui.h"
#include "cvaux.h"

/**
 * Classe gérant le suivi des objets déjà présent dans un objet Records.
 * Classe héritant de DetectionProcessing. Elle devra donc être ajouté à un AlgorithmManager 
 * pour être utilisée.
 **/


class ObjectFollowing :
	public DetectionProcessing
{
public:
	ObjectFollowing(void);
	~ObjectFollowing(void);

	/**
	 * Méthode implémentée issue de la classe Processing. 
	 * Voir la documentation sur le chargement des paramètres.
	 **/
	std::string getClassName();

	/**
	 * Méthode implémentée issue de la classe Processing.
	 * Voir la documentation sur le chargement des paramètres.
	 **/
	void setParameters(std::map<std::string, std::string>);

	/**
	 * Méthode implémentée issue de la classe Processing.
	 * Effectue l'ensemble du processus de décision. Appelée automatiquement par la classe 
	 * AlgorithManager.
	 **/
	void run(Container&);

	/**
	 * Met à jour la classe avec la dernière frame.
	 * @param img Frame courante.
	 **/
	void updateImage(cv::Mat& img);

	/**
	* Renvoie la matrice contenant pour chaque pixel à l'intérieur de la zone le mouvement détecté.
	* Résultat du calcul par flot optique dense de cv::calcOpticalFlowFarneback().
	* Le premier appel à la fonction ne renvoie qu'une matrice vide. 
	* Il faut au moins deux appels pour que le résultat soit pertinent.
	* @param img Image dont on veut calculer le mouvement. Calculé par rapport à la précédente image.
	* @param zone Rect représentant la zone dont on veut le mouvement.
	* @return Matrice de direction de la taille de la zone passée en paramètre.
	**/
	cv::Mat getMovementDirection(cv::Mat& img, cv::Rect zone);

	/**
	* Version de cv::Mat getMovementDirection(cv::Mat& img, cv::Rect zone) sur l'ensemble de l'image.
	**/
	cv::Mat getMovementDirection(cv::Mat& img);

	



private:
	cv::Mat previous_img;

	bool previous_img_initiated;
};


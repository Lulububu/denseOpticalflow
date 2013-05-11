#pragma once

#include "PreProcessing.h"
#include "DetectionTool.h"

#include "cv.h"
#include "highgui.h"
#include "cvaux.h"

#include <string>

/**
 * Classe gérant la soustraction de fond de la vidéo. Se base sur le mélange de Gaussienne implémenté dans OpenCV.
 * Hérite de la classe PreProcessing. Les méthodes de cette classe ne doivent pas être appelé en dehors d'un algorithManager.
 * Elles sont appelées automatiquement lors des différents appels dans l'algorithManager.
 **/

class BackgroundSubstract :
	public PreProcessing
{
public:
	BackgroundSubstract();
	virtual ~BackgroundSubstract();

	/**
	 * Méthode appelé par l'AlgorithManager. Lance tous les traitements.
	 * @param cont conteneur contenant l'image courant de la vidéo. Cette image remplacée par l'image correspondante mais sans fond.
	 **/
	void run(Container& cont);

	
	/**
	 * Méthode renvoyant le nom (identifiant) de la classe. Est utile pour le chargement de paramètre.
	 * Correspond au nom de la classe dans le fichier INI. Cette méthode est appelé par l'algorithmManager.
	 * @return string Nom de la classe (identifiant).
	 **/
	std::string getClassName();

	/**
	 * Permet de charger les paramètres. Appelé par la classe AlgorithManager.
	 * @param parameters map corrspondant aux valeurs chargées à partir du fichier de configuration.
	 **/
	void setParameters(std::map<std::string, std::string> parameters);

	

private:
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
	cv::Mat getForeground(int nb_erode, int nbdilate);

	/**
	 * Nombre d'itération de l'erosion lors de l'extraction de l'image d'avant plan (n'appartenant pas au fond).
	 **/
	int erode_iteration;

	/**
	 * Nombre d'itération de la dilatation lors de l'extraction de l'image d'avant plan (n'appartenant pas au fond).
	 **/
	int dilate_iteration;

	/**
	 * Indique si le modèle du fond a été initialisé. Faux si la méthode updateBackgroundModel n'a jamais étét appelée.
	 **/
	bool bg_model_initiated;

	/**
	 * Modèle du fond généré par OpenCV.
	 **/
	CvBGStatModel* background_model;

	/**
	 * Dernière image à avoir été soumise à la soustraction de fond. 
	 **/
	cv::Mat current_img;
};


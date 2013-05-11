#pragma once
#include <cv.h>
#include <string>

#include "Records.h"
#include "DetectionTool.h"


/**
 * Classe de gestion des échanges de données entre processus. Permet l'accès à la frame courante à tous les processus.
 **/

class Container
{
public:
	/**
	 * Initialisation du conteneur avec la résolution de la vidéo.
	 **/
	Container();
	
	virtual ~Container(void);

	

	/**
	 * Permet de récupérer la frame courante.
	 * @return Mat référence vers la frame courante.
	 **/
	cv::Mat& getImg();

	/**
	 * Met à jour le conteneur avec la frame suivante.
	 * @param frame Référence vers la frame en cours.
	 **/
	void setNewFrame(cv::Mat& frame);

	/**
	 * Renseigne la résolution de la vidéo.
	 **/
	void setResolution(int width, int height);

	/**
	 * Permet de réécupérer les zones cayant été détectées comme forme humaine pour la frame courante.
	 * @return vector<cRect> Vecteur de rectangles correspondant aux zones.
	 **/
	std::vector<cv::Rect>& getHumanDetections();

	/**
	 * Renvoie l'objet regroupant l'ensemble des objets suivis. Un objet est suivi si il a été détecté 
	 * au moins une fois comme forme humaine. Un objet change de position si une nouvelle détection a 
	 * été faite à un endroit proche de l'ancienne localisation ou bien avec le suivi de mouvement.
	 * @return Records objet gérant le suivi des objets.
	 **/
	Records& getRecords();

	/**
	 * Informe le conteneur du nom de la vidéo en cours d'analyse.
	 * @param file_name Chemin d'accès vers la vidéo.
	 **/
	void setVideoFileName(std::string file_name);

	/**
	 * Renvoie le chemin d'accès de la vidéo.
	 * @return string chemin d'accès de la vidéo.
	 **/
	std::string getVideoFileName();
	

protected:
	/**
	 * Image courante.
	 **/
	cv::Mat img;

	std::vector<cv::Rect> humanDetections;

	Records rec;

	std::string video_file_name;
	

};


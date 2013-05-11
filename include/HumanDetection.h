#pragma once
#include "DetectionProcessing.h"
#include "DetectionTool.h"

#include "cv.h"
#include "highgui.h"
#include "cvaux.h"

#include <string> 
using namespace std;

/**
 * Classe gérant la détection des formes humaine. Utilise la détection implémenté dans OpenCV avec la 
 * méthode detectMultiScale() qui est une implémentation de l'algorithme de Viola & Jones. Hérité de l'interface
 * DetectionProcessing ce qui lui permet d'être utilisé dans le cadre d'un AlgorithmManager.
 **/

class HumanDetection :
	public DetectionProcessing
{
public:
	HumanDetection(void);
	~HumanDetection(void);

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
	 * Effectue l'ensemble du processus de détection. Appelée automatiquement par la classe 
	 * AlgorithManager.
	 **/
	void run(Container&);

private:

	/**
    * Détecte les formes humaines contenues dans une image et place leurs coordonnées dans le vecteur de rectangle.
    * @param src Image à analyser.
    * @param rect Vecteur contenant le résultat sous la forme des emplacements des formes détectées.
    **/
	void detectShape( cv::Mat& src, std::vector<cv::Rect>& rect, double scale_factor, int min_neighbours, int flags);


	string xml_file;
	double scale_factor;
	int min_neighbours;
	int flags;
	bool load;
	float ceil_match;

	cv::CascadeClassifier cas;
};


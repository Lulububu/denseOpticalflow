#pragma once
#include "decisionprocessing.h"

/**
 * Classe affichant le résultat de l'algorithme dans la console.
 **/

class DecisionCout :
	public DecisionProcessing
{
public:
	DecisionCout(void);
	~DecisionCout(void);

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

private:
	
	int nb_detections_ceil;
	int distance_max_ceil;
	int total_distance_ceil;
	int max_update_ceil;
};


#pragma once
#include "decisionprocessing.h"
class DecisionFileSave :
	public DecisionProcessing
{
public:
	DecisionFileSave(void);
	~DecisionFileSave(void);
	/**
	 * M�thode impl�ment�e issue de la classe Processing. 
	 * Voir la documentation sur le chargement des param�tres.
	 **/
	std::string getClassName();

	/**
	 * M�thode impl�ment�e issue de la classe Processing.
	 * Voir la documentation sur le chargement des param�tres.
	 **/
	void setParameters(std::map<std::string, std::string>);

	/**
	 * M�thode impl�ment�e issue de la classe Processing.
	 * Effectue l'ensemble du processus de d�cision. Appel�e automatiquement par la classe 
	 * AlgorithManager.
	 **/
	void run(Container&);

private:
	int nb_detections_ceil;
	int distance_max_ceil;
	int total_distance_ceil;
	int max_update_ceil;
};


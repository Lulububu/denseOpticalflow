#pragma once

#include <vector>
#include <string>
#include <map>
using namespace std;

#include "Processing.h"
#include "PreProcessing.h"
#include "DetectionProcessing.h"
#include "DecisionProcessing.h"

/**
 * Classe de gestion des processus. Permet de gérer le lancement des processus qui lui ont été donnée par les méthodes add*().
 * Gère également le chargement des paramètres contenus dans le fichier INI de configuration et initialise chaque processus 
 * dont il a la charge.
 **/


class AlgorithmManager
{
public:
	AlgorithmManager(void);
	~AlgorithmManager(void);

	/**
	 * Ajoute un préprocessus au manager, celui ci sera exécuté lors de l'appel à preProcRun(). Plusieurs preprocessus 
	 * peuvent être ajouter par cette méthode, ils seront exécutés dans l'ordre d'ajout.
	 * @param preprocess PreProcessing que l'on veut ajouter à l'algorithmManager.
	 **/
	void addPreprocess(PreProcessing* preprocess);

	/**
	 * Lance l'exécution de l'ensemble des preprocessus ajoutés par la méthode addPreprocess().
	 * @param container Container contenant l'image courante et potentiellement d'autres données qui vont être 
	 * transférées entre preprocessus. le conteneur sera transmise aux processus de détection et aux processus de
	 * décision pour transférer toutes les données.
	 **/
	void preProcRun(Container& container);

	/**
	 * Ajoute un processus de détection au manager, celui ci sera exécuté lors de l'appel à detectionProcRun(). 
	 * Plusieurs processus de détection peuvent être ajouter par cette méthode, ils seront exécutés dans l'ordre d'ajout.
	 * @param detection DetectionProcessing que l'on veut ajouter à l'algorithmManager.
	 **/
	void addDetection(DetectionProcessing* detection);

	/**
	 * Lance l'exécution de l'ensemble des processus de détection ajoutés par la méthode addDetection().
	 * @param container Container contenant l'image courante et potentiellement d'autres données qui vont être 
	 * transférées entre processus de détection. le conteneur sera transmise aux processus de
	 * décision pour transférer toutes les données.
	 **/
	void detectionProcRun(Container&);
	
	/**
	 * Ajoute un processus de décision au manager, celui ci sera exécuté lors de l'appel à decisionRun(). 
	 * Plusieurs processus de decision peuvent être ajouter par cette méthode, ils seront exécutés dans l'ordre d'ajout.
	 * @param decision DecisionProcessing que l'on veut ajouter à l'algorithmManager.
	 **/
	void addDecision(DecisionProcessing* decision);

	/**
	 * Lance l'exécution de l'ensemble des processus de décision ajoutés par la méthode addDecision().
	 * @param container Container contenant les informations calculées par les processus précédent qui vont permettre 
	 * de prendre une décision.
	 **/
	void decisionRun(Container&);


	/**
	 * Charge les paramètres contenus dansle fichier INI dont le nom est file_name. Le fonctionnement du chargement 
	 * des paramètres est expliqués dans la documentation fourni avec le programme. Cette fonction n'a pas besoin d'être 
	 * modifier pour prendre en compte des nouveaux paramètres ou de nouvelles classes, seules les classes des processus 
	 * nécessitent d'être modifiées (méthode setParameters()).
	 * @param file_name chaine de caractère correspondant au chemin d'accès du fichier (config.ini par exemple).
	 **/
	bool loadParameters(string file_name);



private:
	/**
	 * Référence indifféremment n'importe quel type de processus. Tous les processus référencer par cette fonction
	 * sont éligible au chargement de paramètres par la méthode loadParameters().
	 * @param process Processing référencé par la classe et dont le nom va être consulté pour voir si il correspond à une classe
	 * du fichier INI de configuration.
	 **/
	void referenceProcessus(Processing* process);

	/**
	 * Ensemble des préprocessus.
	 **/
	vector<PreProcessing*> preprocesses;

	/**
	 * Ensemble des processus de détection.
	 **/
	vector<DetectionProcessing*> detectionsprocess;

	/**
	 * Ensemble des décision.
	 **/
	vector<DecisionProcessing*> decisionprocess;

	/**
	 * Ensemble mettant en relation chacun des algorihmes chargés dans cette classe avec son nom (identifiant).
	 * Ce nom est celui renvoyé par la méthode getClassName() de la classe Processing. Permet le chargement
	 * des paramètres. Le nom (identifiant) de la classe corresp à la chaine de caractère indiquée dans le fichier INI.
	 **/
	map<string, Processing*> allprocess;
};


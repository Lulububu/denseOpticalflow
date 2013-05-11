#include "..\include\PtransLauncher.h"
#include "../include/AlgorithmManager.h"
#include "../include/BackGroundSubstract.h"
#include "../include/HumanDetection.h"
#include "../include/ObjectFollowing.h"
#include "../include/DecisionCout.h"
#include "../include/DecisionFileSave.h"

PtransLauncher::PtransLauncher(string file_name):AlgoLauncher(file_name)
{
	//ajout de la soustraction de fond
	manager.addPreprocess(new BackgroundSubstract());

	//ajout de la méthode de suivie d'objet
	manager.addDetection(new ObjectFollowing());

	//ajout de la détection de forme humaine
	manager.addDetection(new HumanDetection());

	//ajout de l'algorithme de décision final (il peut y en avoir plusieurs)
	manager.addDecision(new DecisionCout());

	manager.addDecision(new DecisionFileSave());

}


PtransLauncher::~PtransLauncher(void)
{
}

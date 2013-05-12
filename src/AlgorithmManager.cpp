#include "..\include\AlgorithmManager.h"
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

AlgorithmManager::AlgorithmManager(void)
{
}


AlgorithmManager::~AlgorithmManager(void)
{
	allprocess.clear();
}

void AlgorithmManager::preProcRun(Container& container)
{
	for (vector<PreProcessing*>::iterator it = preprocesses.begin(); it!=preprocesses.end(); ++it)
		((*it))->run(container);
	
}

void AlgorithmManager::addPreprocess(PreProcessing* preprocess)
{
	referenceProcessus(preprocess);
	preprocesses.push_back(preprocess);
}

void AlgorithmManager::addDetection(DetectionProcessing* detection)
{
	referenceProcessus(detection);
	detectionsprocess.push_back(detection);
}
void AlgorithmManager::detectionProcRun(Container& container)
{
	for (vector<DetectionProcessing*>::iterator it = detectionsprocess.begin(); it!=detectionsprocess.end(); ++it)
		((*it))->run(container);
}

void AlgorithmManager::addDecision(DecisionProcessing* decision)
{
	referenceProcessus(decision);
	decisionprocess.push_back(decision);
}
void AlgorithmManager::decisionRun(Container& container)
{
	for (vector<DecisionProcessing*>::iterator it = decisionprocess.begin(); it!=decisionprocess.end(); ++it)
		((*it))->run(container);
}

bool AlgorithmManager::loadParameters(string file_name)
{
	//Map qui associe une classe à l'ensemble de ces paramètres
	//ces paramètres sont sous la forme de map associant un nom de paramètre à sa valeur
	//on conserve la valeur du paramètre sous forme de string pour pouvoir avoir des types quelconques
	map<string, map<string,string> > parameters; 

    ifstream file( file_name );
	
    if ( file ) // ce test échoue si le fichier n'est pas ouvert
    {
        string line; // variable contenant chaque ligne lue
		string class_name = "";
        // cette boucle s'arrête dès qu'une erreur de lecture survient
        while ( getline( file, line ) )
        {
			//analsye des ligne n'étant pas des commentaires ou vide
			if(line.size() > 0 && line.at(0) != ';')
			{
				//suppression des espaces dans la ligne
				line.erase(remove(line.begin(), line.end(), ' '));

				if(line.at(0) == '[')
				{
					//fin de la section
					int end_class_name = line.find_last_of(']');
					if(end_class_name > 0)
					{
						 class_name = line.substr(1,end_class_name -1);
						 //initialisation de la map pour cette section
						 parameters[class_name] = map<string, string>();
					}

				}else if(class_name != "")
				{
					int position = line.find_first_of('=');
					if(position > 0)
					{
						string param_name = line.substr(0, position);
						string param_value = line.substr(position + 1, line.size() - 1);
						parameters[class_name][param_name] = param_value;
					}
				}
			}
        }

		//le chargement est fini, il faut maintenant envoyer les paramètres aux bonnes classe
		for (map<string, map<string,string> >::iterator it=parameters.begin(); it!=parameters.end(); ++it)
		{
			Processing* proc = allprocess[it->first];
			if(proc!= NULL)
				proc->setParameters(it->second);
		}



		return true;
    }

	return false;
}

void AlgorithmManager::referenceProcessus(Processing* process)
{
	allprocess[process->getClassName()] = process;
}
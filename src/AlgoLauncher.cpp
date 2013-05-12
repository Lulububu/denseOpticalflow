#include "..\include\AlgoLauncher.h"
#include "../include/FileAccessException.h"

AlgoLauncher::AlgoLauncher(string file_name):cap(file_name)
{
	//ouverture de la vidéo
	if( !cap.isOpened() )
		throw FileAccessException(file_name);

	//lecture de la première image de la vidéo
	cap >> frame;

	//on ajoute les informations sur la vidéo dans le container
	container.setVideoFileName(file_name);
	container.setResolution(frame.size().width, frame.size().height);
}


AlgoLauncher::~AlgoLauncher(void)
{
}

bool AlgoLauncher::loadParameters(string file_name)
{
	//c'est le manager qui s'occuppe de la répartition des paramètres
	return manager.loadParameters(file_name);
}

void AlgoLauncher::execute()
{
	do
    {
		//c'est au travers du conteneur que l'algorithme va avoir accès aux images
		container.setNewFrame(frame);

		//lancement de la phase de pré-traitement
		manager.preProcRun(container);

		//lancement de la phase de détection
		manager.detectionProcRun(container);

		//chargement de l'image courante
        cap >> frame;
    }while(!frame.empty());
	
	//lancement du processus de décision qui écrit dans la console le résultat
	manager.decisionRun(container);
}
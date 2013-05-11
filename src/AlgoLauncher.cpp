#include "..\include\AlgoLauncher.h"
#include "../include/FileAccessException.h"

AlgoLauncher::AlgoLauncher(string file_name):cap(file_name)
{

	if( !cap.isOpened() )
		throw FileAccessException(file_name);

	cap >> frame;

	container.setVideoFileName(file_name);
	container.setResolution(frame.size().width, frame.size().height);
}


AlgoLauncher::~AlgoLauncher(void)
{
}

bool AlgoLauncher::loadParameters(string file_name)
{
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

        cap >> frame;
    }while(!frame.empty());
	
	//lancement du processus de décision qui écrit dans la console le résultat
	manager.decisionRun(container);
	system ("pause");
}
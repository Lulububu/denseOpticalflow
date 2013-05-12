#include "..\include\AlgoLauncher.h"
#include "../include/FileAccessException.h"

AlgoLauncher::AlgoLauncher(string file_name):cap(file_name)
{
	//ouverture de la vid�o
	if( !cap.isOpened() )
		throw FileAccessException(file_name);

	//lecture de la premi�re image de la vid�o
	cap >> frame;

	//on ajoute les informations sur la vid�o dans le container
	container.setVideoFileName(file_name);
	container.setResolution(frame.size().width, frame.size().height);
}


AlgoLauncher::~AlgoLauncher(void)
{
}

bool AlgoLauncher::loadParameters(string file_name)
{
	//c'est le manager qui s'occuppe de la r�partition des param�tres
	return manager.loadParameters(file_name);
}

void AlgoLauncher::execute()
{
	do
    {
		//c'est au travers du conteneur que l'algorithme va avoir acc�s aux images
		container.setNewFrame(frame);

		//lancement de la phase de pr�-traitement
		manager.preProcRun(container);

		//lancement de la phase de d�tection
		manager.detectionProcRun(container);

		//chargement de l'image courante
        cap >> frame;
    }while(!frame.empty());
	
	//lancement du processus de d�cision qui �crit dans la console le r�sultat
	manager.decisionRun(container);
}
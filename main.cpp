
#include "cv.h"
#include "highgui.h"


#include "./include/Records.h"
#include "./include/AlgorithmManager.h"
#include "./include/BackGroundSubstract.h"
#include "./include/HumanDetection.h"
#include "./include/MovementDetection.h"
#include "./include/ObjectFollowing.h"
#include "./include/DecisionCout.h"

#include <iostream>
#include <string>
using namespace std;

using namespace cv;


int main(int argc, char** argv)
{   
	string file_name;
	cout << argc << endl;
	if(argc > 1)
		file_name = argv[1];
	else
		file_name = "cafe.mov";

	VideoCapture cap(file_name);

	//fenêtre d'affichage, sera enlevé
    namedWindow("flow", 1);
    namedWindow("origin", 1);

	AlgorithmManager manager;

	//ajout de la soustraction de fond
	BackgroundSubstract bgsub; 
	manager.addPreprocess(&bgsub);

	//Ancienne méthode de suivie de mouvement
	//MovementDetection mdetect;
	//manager.addDetection(&mdetect);

	//ajout de la méthode de suivie d'objet
	ObjectFollowing objFoll;
	manager.addDetection(&objFoll);

	//ajout de la détection de forme humaine
	HumanDetection hdetect;
	manager.addDetection(&hdetect);

	//ajout de l'algorithme de décision final (il peut y en avoir plusieurs)
	DecisionCout decision;
	manager.addDecision(&decision);

	//à venir
	//manager.loadParameters("config.ini");

    if( !cap.isOpened() )
        return -1;



    Mat frame;
    cap >> frame;

	//initialisation de l'objet qui va permettre aux différentes parties de l'algorithme de se transmettre les informations
	Container container(frame.size().width, frame.size().height, 0.1);

    do
    {
		//c'est au travers du conteneur que l'algorithme va avoir accès aux images
		container.setNewFrame(frame);

		//lancement de la phase de pré-traitement
		manager.preProcRun(container);

		//lancement de la phase de détection
		manager.detectionProcRun(container);
		
                
		//affichage, sera supprimé.
  		for(unsigned int u = 0; u < container.getRecords().getObjects().size(); u++)
        {
			Rect r = container.getRecords().getObjects().at(u).getCurrentPosition();
			if(r.x >= 0)
			{
            rectangle( frame,
                 cvPoint( r.x, r.y ),
                 cvPoint( r.x + r.width, r.y + r.height ),
                 CV_RGB( 255, 0, 0 ), 1, 8, 0 );
			}

        }
		imshow("origin", container.getImg());
		imshow("flow", frame);
		

        if(waitKey(30)>=0)
            break;
		//fin affichage

        cap >> frame;
    }while(!frame.empty());
	
	//lancement du processus de décision qui écrit dans la console le résultat
	manager.decisionRun(container);
	system ("pause");
    return 0;






}





#include "include\TestObject.h"

#include "./include/AlgoLauncher.h"
#include "./include/PtransLauncher.h"

#include <iostream>
#include <string>
using namespace std;


int main(int argc, char** argv)
{   
	
	string video_file_name, config_file_name;

	if(argc > 1)
	{
		video_file_name = argv[1];

		if(argc > 2)
			config_file_name= argv[2];
		else
			config_file_name = "config.ini";


		AlgoLauncher* launcher = new PtransLauncher(video_file_name);
		cout << "étude de la vidéo " << video_file_name << endl;
	
		if(launcher->loadParameters(config_file_name))
			cout << "Chargement des paramètres depuis le fichier " << config_file_name << endl;
		else
			cout << "Impossible d'ouvrir le fichier " << config_file_name << ", chargement des paramètres par défaut." << endl;
		
		launcher->execute();
	}
	else
	{
		cout << "Le programme nécessite au moins un argument : le chemin d'accès à la vidéo." << endl;
	}


    return 0;

	

	//TestObject test;




}



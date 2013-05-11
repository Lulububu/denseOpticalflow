#include "..\include\DecisionCout.h"
#include <iostream>
using namespace std;

DecisionCout::DecisionCout(void)
{
	nb_detections_ceil = 2;
	distance_max_ceil = 50;
	total_distance_ceil = 100;
	max_update_ceil = 5;
}


DecisionCout::~DecisionCout(void)
{
}


void DecisionCout::run(Container& container)
{
	Records rec = container.getRecords();
    /*for(unsigned int u = 0; u < rec.getObjects().size(); u++)
    {
		cout << rec.getObjects().at(u).getDetectionNumber() << " " << rec.getObjects().at(u).getDistance() << " " << rec.getObjects().at(u).getMovementUpdateNumber() << endl;
    }*/

	int total_detection = 0;
	int max_distance = 0;
	int total_distance = 0;
	int nb_distance_not_null = 0;
	int max_update = 0;
	int total_update = 0;

	

	for(unsigned int u = 0; u < rec.getObjects().size(); u++)
    {
		Object obj = rec.getObjects().at(u);

		total_detection += obj.getDetectionNumber();

		if(max_distance < obj.getDistance())
			max_distance = obj.getDistance();

		total_distance += obj.getDistance();

		if(obj.getDistance() > 0)
			nb_distance_not_null++;

		if(max_update < obj.getMovementUpdateNumber())
			max_update = obj.getMovementUpdateNumber();

		total_update += obj.getMovementUpdateNumber();
	}

	bool human_presence = total_detection > nb_detections_ceil && max_distance > distance_max_ceil && total_distance > total_distance_ceil && max_update > max_update_ceil;

	if(nb_distance_not_null ==0)
		nb_distance_not_null++;
	int certainty = min(total_detection, 25) + min((total_distance/nb_distance_not_null)/3, 50) + min(total_update/2, 25);

	if(human_presence)
		cout << "Il y a au moins une forme humaine dans cette vidéo, la certitude de ce fait est de " << certainty << "%" << endl;
	else
		cout << "Il n'y a pas de formes humaines dans cette vidéo, la certitude de ce fait est de " << 100 - certainty << "%" << endl;

}

std::string DecisionCout::getClassName()
{
	return "DecisionCout";
}

void DecisionCout::setParameters(std::map<std::string, std::string> parameters)
{
	stringstream(parameters["nb_detections_ceil"]) >> nb_detections_ceil;
	stringstream(parameters["distance_max_ceil"]) >> distance_max_ceil;
	stringstream(parameters["total_distance_ceil"]) >> total_distance_ceil;
	stringstream(parameters["max_update_ceil"]) >> max_update_ceil;
}
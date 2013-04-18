#include "../include/Records.h"
#include "../include/DetectionTool.h"
using namespace std;

Records::Records(float ceil_): ceil(ceil_)
{
}

Records::~Records()
{
}


bool Records::checkMatchDetection(cv::Rect& coordinates)
{
    float match_value;
    int match_index;

    checkMatch(coordinates, match_value, match_index);

    //si le max est supérieur au seuil fixé, on considère que c'est le même et on met à jour les données
    if(match_index != -1 && match_value > ceil)
    {
        objects.at(match_index).addDetection();
		objects.at(match_index).updatePosition(coordinates);
        return true;
    }else
    {
        createObject(
            cv::Rect(coordinates.x, coordinates.y, coordinates.width, coordinates.height)
        );
        return false;
    }
}

bool Records::checkMatchMovement(cv::Rect& coordinates, cv::Point& direction)
{
    float match_value;
    int match_index;

    checkMatch(coordinates, match_value, match_index);

    //si le max est supérieur au seuil fixé, on considère que c'est le même et on met à jour les données
    if(match_index != -1 && match_value > ceil)
    {
        objects.at(match_index).updatePosition(direction);
        return true;
    }else
    {
        createObject(
            cv::Rect(coordinates.x + direction.x, coordinates.y + direction.y, coordinates.width, coordinates.height)
        );
        return false;
    }
}

void Records::checkMatch(cv::Rect& coordinates, float& match_value, int& match_index)
{
    //valeur maximale temporaire
    match_value = 0;
    //indice de l'élément le plus proche
    match_index = -1;

    //aire d'intersection de l'élément courant
    float tmp_intersect_area;

    //ratio de corespondance de l'élément courant avec celui passé en paramètre
    float tmp_match;

    for(unsigned int i = 0; i < objects.size(); i++)
    {
        tmp_intersect_area = (float) ((objects.at(i).getCurrentPosition() & coordinates).area());

        //on considère que le ration correspond à l'aire de l'intersection divisée par la somme des aires moins l'intersection
        tmp_match = tmp_intersect_area / (objects.at(i).getCurrentPosition().area() + coordinates.area() - tmp_intersect_area) ;

        //on conserve la valeur de ration la plus importante
        if(tmp_match > match_value)
        {
            match_value = tmp_match;
            match_index = i;
        }
    }
}

void Records::createObject(cv::Rect coordinates)
{
    objects.push_back((Object(coordinates)));	
}

std::vector<Object>& Records::getObjects()
{
    return objects;
}

void Records::checkMatchMovement(vector<cv::Rect>& zones, vector<cv::Point>& directions)
{
    cv::Rect zone;
    cv::Point direction;

	//vecteur enregistrant les associations en cours entre zones. Le premier élément correspond à l'indice de l'élément dans zones.
	//le deuxième correspond à la valeur de correspondance. Cela permet de ne garder que la meilleur correspondance.
    vector<pair<int, float> > current_matches(objects.size(), pair<int, float>(0, 0.f));

	for(unsigned int i = 0; i < zones.size(); i++)
    {
        float match_value = 0;
        int match_index = -1;

		//pour chaque élément de la zone, on vérifie si il correspond aux éléments déjà présent.
        checkMatch(zones.at(i), match_value, match_index);
        if(match_index == -1)
        {
			//si il n'existe pas on crée un nouvel objet
            zone = zones.at(i);
            createObject(
                cv::Rect(zone.x, zone.y, zone.width, zone.height)
            );
			//on ajoute une cellule pour enregistrer les éventuelles futures correspondances avec ce nouvel élément.
			current_matches.push_back(pair<int, float>(0, 0.f));
        }else if( current_matches.at(match_index).second < match_value)
        {
			//sinon, mise à jour de l'élément correspondant le plus.
            current_matches.at(match_index) = pair<int, float>(i, match_value);
        }
    }

	//A la fin du calcul, on ne garde que les correspondances supérieur au seuil.
    for(unsigned int i = 0; i < current_matches.size(); i++)
    {
        if(current_matches.at(i).second > ceil)
        {
            if(current_matches.at(i).first != -1)
            {
                objects.at(i).updatePosition(directions.at(current_matches.at(i).first));
            }
        }
    }


}
void Records::updatePosition(cv::Mat& flow)
{
	for(int i = 0; i < getObjects().size(); i++)
	{
		cv::Rect rect = getObjects().at(i).getCurrentPosition();

		cv::Point dir = DetectionTool::getDirectionFlow(flow(rect));
		if(dir.x != 0 || dir.y != 0)
		{
			//cout << "update position " << dir.x<< " " << dir.y<<endl;
			//cout << "rect " << rect.x << " " << rect.y << " " << rect.width << " " << rect.height << endl;
			objects.at(i).updatePosition(dir);
		}
	}
}
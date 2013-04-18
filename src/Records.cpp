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

    //si le max est sup�rieur au seuil fix�, on consid�re que c'est le m�me et on met � jour les donn�es
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

    //si le max est sup�rieur au seuil fix�, on consid�re que c'est le m�me et on met � jour les donn�es
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
    //indice de l'�l�ment le plus proche
    match_index = -1;

    //aire d'intersection de l'�l�ment courant
    float tmp_intersect_area;

    //ratio de corespondance de l'�l�ment courant avec celui pass� en param�tre
    float tmp_match;

    for(unsigned int i = 0; i < objects.size(); i++)
    {
        tmp_intersect_area = (float) ((objects.at(i).getCurrentPosition() & coordinates).area());

        //on consid�re que le ration correspond � l'aire de l'intersection divis�e par la somme des aires moins l'intersection
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

	//vecteur enregistrant les associations en cours entre zones. Le premier �l�ment correspond � l'indice de l'�l�ment dans zones.
	//le deuxi�me correspond � la valeur de correspondance. Cela permet de ne garder que la meilleur correspondance.
    vector<pair<int, float> > current_matches(objects.size(), pair<int, float>(0, 0.f));

	for(unsigned int i = 0; i < zones.size(); i++)
    {
        float match_value = 0;
        int match_index = -1;

		//pour chaque �l�ment de la zone, on v�rifie si il correspond aux �l�ments d�j� pr�sent.
        checkMatch(zones.at(i), match_value, match_index);
        if(match_index == -1)
        {
			//si il n'existe pas on cr�e un nouvel objet
            zone = zones.at(i);
            createObject(
                cv::Rect(zone.x, zone.y, zone.width, zone.height)
            );
			//on ajoute une cellule pour enregistrer les �ventuelles futures correspondances avec ce nouvel �l�ment.
			current_matches.push_back(pair<int, float>(0, 0.f));
        }else if( current_matches.at(match_index).second < match_value)
        {
			//sinon, mise � jour de l'�l�ment correspondant le plus.
            current_matches.at(match_index) = pair<int, float>(i, match_value);
        }
    }

	//A la fin du calcul, on ne garde que les correspondances sup�rieur au seuil.
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
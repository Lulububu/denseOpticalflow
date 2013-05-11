#include "../include/Object.h"


using namespace std;

Object::Object()
{
}

Object::Object(cv::Rect position): current_position(position), detection_number(0), distance(0), movemement_update_number(0)
{
}

Object::~Object()
{
}

cv::Rect Object::getCurrentPosition()
{
    return current_position;
}

unsigned int Object::getDetectionNumber()
{
    return detection_number;
}

unsigned int Object::getMovementUpdateNumber()
{
    return movemement_update_number;
}

void Object::updatePosition(cv::Point direction, int width_max, int height_max)
{
    current_position.x += direction.x;
    current_position.y += direction.y;

	checkPointBound(current_position, width_max, height_max);
	
	
	distance += sqrt(direction.x*direction.x + direction.y*direction.y);
    movemement_update_number++;
}

void Object::updatePosition(cv::Rect pos)
{
	int x = pos.x - current_position.x;
	int y = pos.y - current_position.y;
	distance+= sqrt(x*x + y*y);
    current_position = pos;

    movemement_update_number++;
}

void Object::addDetection()
{
    detection_number++;
}

unsigned int Object::getDistance()
{
	return distance;
}

void Object::checkPointBound(cv::Rect& rect, int width, int height)
{
	//le rectangle dépassant sur une extrémité, on "écrase" le rectangle sur ce côté.

	//dépassement à gauche
	if(rect.x < 0)
	{
		//dépasse  entièrement de l'image
		if(rect.x + rect.width < 0)
		{
			rect.x = 0;
			rect.width = 0;
		}
		else //dépasse en partie
		{
			rect.width = rect.width + rect.x;
			rect.x = 0;
		}
		
	}

	//dépassement à droite
	if(rect.x +  rect.width >= width)
	{
		//dépasse entièrement de l'image
		if(rect.x >= width)
		{
			rect.x = width - 1;
			rect.width = 0;
		}
		else //dépasse en partie
		{
			rect.width = width - rect.x - 1;
		}
	}

	//dépassement en haut de l'image
	if(rect.y < 0)
	{
		//dépasse  entièrement de l'image
		if(rect.y + rect.height < 0)
		{
			rect.y = 0;
			rect.height = 0;
		}
		else //dépasse en partie
		{
			rect.height = rect.height + rect.y;
			rect.y = 0;
		}
	}

	//dépassement en bas de l'image
	if(rect.y +  rect.height >= height)
	{
		//dépasse entièrement de l'image
		if(rect.y >= height)
		{
			rect.y = height - 1;
			rect.height = 0;
		}
		else //dépasse en partie
		{
			rect.height = height - rect.y - 1;
		}
	}
}
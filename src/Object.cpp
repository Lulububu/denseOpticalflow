#include "../include/Object.h"

using namespace std;

Object::Object()
{
}

Object::Object(cv::Rect position): current_position(position), detection_number(0)
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

void Object::updatePosition(cv::Point direction)
{
    current_position.x += direction.x;
    current_position.y += direction.y;
	if(current_position.x < 0)
		current_position.x = 0;

	if(current_position.y < 0)
		current_position.y = 0;

    movemement_update_number++;
}

void Object::updatePosition(cv::Rect pos)
{
    current_position = pos;

    movemement_update_number++;
}

void Object::addDetection()
{
    detection_number++;
}

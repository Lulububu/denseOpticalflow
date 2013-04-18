#ifndef OBJECT_H
#define OBJECT_H

#include <cv.h>


class Object
{
    public:
		Object();
        Object(cv::Rect);
        virtual ~Object();

        cv::Rect getCurrentPosition();
        unsigned int getDetectionNumber();
        unsigned int getMovementUpdateNumber();
        void updatePosition(cv::Point direction);
		void updatePosition(cv::Rect pos);

        void addDetection();

    protected:
        cv::Rect current_position;
        unsigned int detection_number;
        unsigned int movemement_update_number;

    private:
};

#endif // OBJECT_H

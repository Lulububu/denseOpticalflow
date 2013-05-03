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
        void updatePosition(cv::Point direction, int width_max, int height_max);
		void updatePosition(cv::Rect pos);

        void addDetection();
		unsigned int getDistance();

		static void checkPointBound(cv::Rect& rect, int width, int height);


    protected:
        cv::Rect current_position;
        unsigned int detection_number;
		unsigned int distance;
        unsigned int movemement_update_number;

    private:
};

#endif // OBJECT_H

#define _USE_MATH_CONSTANTS
#include <cmath>
#include "../include/Bearing.h"
Bearing::Bearing()
: angle(0.0)
{}

Bearing::Bearing(DIR Direction, int Degrees, int Minutes, double Seconds)
{
    angle = static_cast<double>(Degrees) + static_cast<double>(Minutes)/60.0 + static_cast<double>(Seconds)/3600.0;
    switch (Direction)
    {
    case DIR::SE:
        angle = 180 - angle;
        break;
    case DIR::SW:
        angle = 180 + angle;
        break;
    case DIR::NW:
        angle = 360 - angle;
        break;
    default:
        break;
    }
    angle = angle * M_PI/180.0;
}


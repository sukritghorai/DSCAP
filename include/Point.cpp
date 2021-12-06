#include "Point.h"

Point::Point()
: ID(0), x(0.0), y(0.0), z(0.0)
{}

Point::Point(unsigned int _ID, double _x, double _y, double _z)
: ID(_ID), x(_x), y(_y), z(_z)
{}

void Point::Set(unsigned int _ID, double _x, double _y, double _z)
{
    ID = _ID;
    x = _x;
    y = _y;
    z = _z;
}




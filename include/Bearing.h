#pragma once
#include <string>

class Bearing
{
private:
    double angle;
public:
    enum class DIR
    {NE, NW, SE, SW};

    Bearing();
    Bearing(DIR Direction, int Degrees, int Minutes, double Seconds);

};


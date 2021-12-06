#pragma once

class Point
{
private:
    unsigned int ID;
    double x, y, z;
public:
    Point(); 
    Point(unsigned int _ID, double x, double y, double z);

    // Setters
    void Set(unsigned int _ID, double x = 0, double y = 0, double z = 0);

    // Getters
    unsigned int GetID();
    double GetX();
    double GetY();
    double GetZ();

};

inline unsigned int Point::GetID() {return ID;}
inline double Point::GetX() {return x;}
inline double Point::GetY() {return y;}
inline double Point::GetZ() {return z;}

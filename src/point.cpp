#include <point.hpp>
#include <stdexcept>

Point::Point(int features_size)
{
    this->id = 0;
    this->clusterId = -1;
    this->r = 0;
    this->g = 0;
    this->b = 0;
}
//Point::Point(const int& id, const double& x, const double& y) : id(id), x(x), y(y), clusterId(-1) /*, minDist(std::numeric_limits<double>::max())*/ {}
Point::Point(const int& id, const std::vector<int>& coordinates)
{
    this->id = id;
    this->r=static_cast<unsigned char>(coordinates[0]);
    this->g=static_cast<unsigned char>(coordinates[1]);
    this->b=static_cast<unsigned char>(coordinates[2]);
    this->clusterId = -1;
}

Point::~Point() 
{
    
}

unsigned char& Point::getFeature(int index) 
{
     switch (index) 
     {
        case 0:
            return this->r;
        case 1:
            return this->g;
        case 2:
            return this->b;
        default:
            throw std::out_of_range("Index out of range");
     }
}

int Point::getFeature_int(int index) const
{
    switch (index) 
    {
        case 0:
            return static_cast<int>(this->r);
        case 1:
            return static_cast<int>(this->g);
        case 2:
            return static_cast<int>(this->b);
        default:
            throw std::out_of_range("Index out of range");
    }
}

double Point::distance(const Point& p) const
{
    double sum = 0.0;
    sum += pow(static_cast<int>(r) - static_cast<int>(p.r), 2);
    sum += pow(static_cast<int>(g) - static_cast<int>(p.g), 2);
    sum += pow(static_cast<int>(b) - static_cast<int>(p.b), 2);
    return sqrt(sum);
}


void Point::setFeature(int index, int value)
{
    if (index == 0)
        this->r = static_cast<unsigned char>(value);
    else if (index == 1)
        this->g = static_cast<unsigned char>(value);
    else if (index == 2)
        this->b = static_cast<unsigned char>(value);
}




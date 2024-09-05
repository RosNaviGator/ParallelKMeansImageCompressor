/**
 * @file point.cpp
 * @brief Implementation of the Point class for image compression algorithms.
 * @details This file contains the implementation of the `Point` class, which represents a pixel or data point in 
 *          a color space for use in image compression algorithms. The class provides methods to access and modify 
 *          color features, calculate distances between points, and manage cluster assignments. It is a core component 
 *          for K-means clustering and similar algorithms.
 */


#include <point.hpp>
#include <stdexcept>

km::Point::Point() = default;
//Point::Point(const int& id, const double& x, const double& y) : id(id), x(x), y(y), clusterId(-1) /*, minDist(std::numeric_limits<double>::max())*/ {}
km::Point::Point(const int &id, const std::vector<int> &coordinates) : id(id), r(static_cast<unsigned char>(coordinates[0])), g(static_cast<unsigned char>(coordinates[1])), b(static_cast<unsigned char>(coordinates[2])) 
{
}

auto km::Point::getFeature(int index) -> unsigned char&
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

auto km::Point::getFeature_int(int index) const -> int
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

auto km::Point::distance(const Point &p) const -> double
{
    double sum = 0.0;
    sum += pow(static_cast<int>(r) - static_cast<int>(p.r), 2);
    sum += pow(static_cast<int>(g) - static_cast<int>(p.g), 2);
    sum += pow(static_cast<int>(b) - static_cast<int>(p.b), 2);
    return sqrt(sum);
}


void km::Point::setFeature(int index, int value)
{
    if (index == 0)
        this->r = static_cast<unsigned char>(value);
    else if (index == 1)
        this->g = static_cast<unsigned char>(value);
    else if (index == 2)
        this->b = static_cast<unsigned char>(value);
}




#ifndef POINT_HPP
#define POINT_HPP


#include <cmath>
#include <vector>

class Point
{

public:
    int id;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    int clusterId;
    // double minDist;

    Point(int features_size);
    Point(const int& id, const std::vector <int>& coordinates);
    ~Point(); // Destructor
    double distance(const Point& p) const;

    unsigned char& getFeature(int index) ;
    int getFeature_int(int index) const;
    void setFeature(int index, int x);
};


#endif // POINT_HPP
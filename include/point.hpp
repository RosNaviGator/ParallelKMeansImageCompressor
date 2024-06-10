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
    [[nodiscard]] auto distance(const Point &p) const -> double;

    auto getFeature(int index) -> unsigned char &;
    [[nodiscard]] auto getFeature_int(int index) const -> int;
    void setFeature(int index, int x);
};


#endif // POINT_HPP
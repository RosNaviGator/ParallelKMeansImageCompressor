#ifndef POINT_HPP
#define POINT_HPP


#include <cmath>
#include <vector>
#include <mpi.h>

class Point
{

public:
    int id;
    std::vector<double> features;
    std::vector<double> centroidFeatures;
    int numberOfFeatures;
    int clusterId;
    // double minDist;

    Point(int features_size);
    Point(const int& id, const std::vector<double>& coordinates);
    double distance(const Point& p) const;

    friend void MPI_Bcast(Point& point, int count, MPI_Datatype datatype, int root, MPI_Comm communicator);

    double& getFeature(int index) ;
    void setFeature(int index, double x);
};


#endif // POINT_HPP
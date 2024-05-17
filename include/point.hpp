#ifndef POINT_HPP
#define POINT_HPP


#include <cmath>
#include <vector>
#include <mpi.h>

class Point
{

public:
    int id;
    std::vector<unsigned char> features;
    int clusterId;
    // double minDist;

    Point(int features_size);
    Point(const int& id, const std::vector<unsigned char>& coordinates);
    ~Point(); // Destructor
    double distance(const Point& p) const;

    friend void MPI_Bcast(Point& point, int count, MPI_Datatype datatype, int root, MPI_Comm communicator);

    unsigned char& getFeature(int index) ;
    void setFeature(int index, unsigned char x);
};


#endif // POINT_HPP
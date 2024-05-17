#include <point.hpp>

Point::Point(int features_size)
{
    this->id = 0;
    this->clusterId = -1;
    this->features = std::vector<unsigned char>(features_size, 0.0);
}
//Point::Point(const int& id, const double& x, const double& y) : id(id), x(x), y(y), clusterId(-1) /*, minDist(std::numeric_limits<double>::max())*/ {}
Point::Point(const int& id, const std::vector<unsigned char>& coordinates)
{
    this->id = id;
    this->features = coordinates;
    this->clusterId = -1;
}

Point::~Point() {
    // Destructor code - std::vector automatically handles memory cleanup
    features.clear();
    // Use swap trick to ensure memory is released
    std::vector<unsigned char>().swap(features);
}

double Point::distance(const Point& p) const
{    // Destructor code here
    double sum = 0.0;
    for (int i = 0; i < features.size(); ++i)
    {
        sum += (features[i] - p.features[i]) * (features[i] - p.features[i]);
    }
    return sqrt(sum);
}

unsigned char& Point::getFeature(int index) 
{
    return features[index];
}

void Point::setFeature(int index, unsigned char value)
{
    this->features[index] = value;
}

void MPI_Bcast(Point& point, int count, MPI_Datatype datatype, int root, MPI_Comm communicator)
{
    MPI_Bcast(&point.id, 1, MPI_INT, root, communicator);
    MPI_Bcast(&point.clusterId, 1, MPI_INT, root, communicator);
    MPI_Bcast(point.features.data(), count, datatype, root, communicator);
}
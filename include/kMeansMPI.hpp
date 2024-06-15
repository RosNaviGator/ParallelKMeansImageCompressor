#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <random>
#include <iostream>
#include <algorithm>

#include <mpi.h>

#include <point.hpp>



class KMeans
{
    public:
        KMeans(const int& k, const int& rank, const int& n_features, const std::vector<Point> points);    
        KMeans(const int& k, const int& rank, const int& n_features);

        void run(const int& rank, const int& world_size, const std::vector<std::pair<int, Point> > local_points);
        void printClusters() const;
        void plotClusters();
        std::vector<Point> getPoints();
        std::vector<Point> getCentroids();
        int getNumberOfIterationForConvergence();
        int numberOfIterationForConvergence;

    private:
        
        int k;
        std::vector<Point> points;
        std::vector<Point> centroids;
};


#endif // KMEANS_HPP
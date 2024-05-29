#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <random>
#include <iostream>

#include <thread>
#include <point.hpp>


class KMeans
{
public:
    KMeans(const int& k, const std::vector<Point> points);

    void run();
    void printClusters() const;
    void plotClusters();
    int getNumberOfIterationForConvergence();
    std::vector<Point> getPoints();
    std::vector<Point> getCentroids();
    int numberOfIterationForConvergence;

private:
    int k;
    std::vector<Point> points;
    std::vector<Point> centroids;
};


#endif // KMEANS_HPP

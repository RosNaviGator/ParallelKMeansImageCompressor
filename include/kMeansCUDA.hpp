#ifndef KMEANS_CUDA_HPP
#define KMEANS_CUDA_HPP

#include <random>
#include <iostream>
#include <vector>
#include <cuda_runtime.h>
#include "point.hpp"
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

#endif // KMEANS_CUDA_HPP
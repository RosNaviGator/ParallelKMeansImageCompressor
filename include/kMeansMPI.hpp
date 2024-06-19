/**
 * @file kMeansMPI.hpp
 * @brief Implementation of the K-means clustering algorithm using MPI
 */

#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <random>
#include <iostream>
#include <algorithm>
#include <mpi.h>
#include <point.hpp>

/**
 * @class KMeans
 * @brief Represents the K-means clustering algorithm using MPI
 */
class KMeans
{
public:
    /**
     * @brief Constructor for KMeans
     * @param k Number of clusters
     * @param rank Rank of the MPI process
     * @param n_features Number of features
     * @param points Vector of points
     */
    KMeans(const int& k, const std::vector<Point>& points);

    /**
     * @brief Constructor for KMeans
     * @param k Number of clusters
     * @param rank Rank of the MPI process
     * @param n_features Number of features
     */
    KMeans(const int& k);

    /**
     * @brief Runs the K-means clustering algorithm using MPI
     * @param rank Rank of the MPI process
     * @param world_size Number of MPI processes
     * @param local_points Vector of local points
     */
    void run(const int& rank, const int& world_size, const std::vector<std::pair<int, Point> > local_points);

    /**
     * @brief Gets the points
     * @return Vector of points
     */
    auto getPoints() -> std::vector<Point>; 

    /**
     * @brief Gets the centroids
     * @return Vector of centroids
     */
    auto getCentroids() -> std::vector<Point>;

    /**
     * @brief Gets the number of iterations
     * @return Number of iterations
     */
    auto getIterations() -> int;

private:
    int k; ///< Number of clusters
    std::vector<Point> points; ///< Vector of points
    std::vector<Point> centroids; ///< Vector of centroids
    int number_of_iterations; ///< Number of iterations
};

#endif // KMEANS_HPP
/**
 * @file kMeans.hpp
 * @brief Implementation of the K-means clustering algorithm
 */

#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <random>
#include <iostream>
#include <thread>
#include <point.hpp>

/**
 * @class KMeans
 * @brief Represents the K-means clustering algorithm
 */
class KMeans
{
public:
    /**
     * @brief Constructor for KMeans
     * @param k Number of clusters
     * @param points Vector of points
     */
    KMeans(const int& k, const std::vector<Point> &points);

    /**
     * @brief Runs the K-means clustering algorithm
     */
    void run();

    /**
     * @brief Prints the clusters
     */
    void printClusters() const;

    /**
     * @brief Plots the clusters
     */
    void plotClusters();

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

private:
    int k; ///< Number of clusters
    std::vector<Point> points; ///< Vector of points
    std::vector<Point> centroids; ///< Vector of centroids
};

#endif // KMEANS_HPP
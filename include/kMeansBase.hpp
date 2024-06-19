/**
 * @file kMeansBase.hpp
 * @brief Base class for K-means clustering algorithm
 */

#ifndef KMEANS_BASE_HPP
#define KMEANS_BASE_HPP

#include <vector>
#include "point.hpp"

/**
 * @class KMeansBase
 * @brief Base class for K-means clustering algorithm
 */
class KMeansBase
{
public:
    /**
     * @brief Constructor for KMeansBase
     * @param k Number of clusters
     * @param points Vector of points
     */
    KMeansBase(const int& k, const std::vector<Point>& points);

    /**
     * @brief Constructs a KMeansBase object only with the specified number of clusters.
     * 
     * @param k The number of clusters.
     */
    KMeansBase(const int& k);

    /**
     * @brief Virtual destructor for KMeansBase
     */
    virtual ~KMeansBase() = default;

    /**
     * @brief Runs the K-means clustering algorithm
     */
    virtual void run() = 0;

    /**
     * @brief Gets the points
     * @return Vector of points
     */
    std::vector<Point> getPoints() const;

    /**
     * @brief Gets the centroids
     * @return Vector of centroids
     */
    std::vector<Point> getCentroids() const;

    /**
     * @brief Gets the number of iterations
     * @return Number of iterations
     */
    int getIterations() const;

protected:
    int k; ///< Number of clusters
    std::vector<Point> points; ///< Vector of points
    std::vector<Point> centroids; ///< Vector of centroids
    int number_of_iterations; ///< Number of iterations
};

#endif // KMEANS_BASE_HPP
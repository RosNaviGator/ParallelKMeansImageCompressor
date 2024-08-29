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

namespace km
{
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
        virtual void run();

        /**
         * @brief Gets the points
         * @return Vector of points
         */
        [[nodiscard]] auto getPoints() const -> std::vector<Point>;

        /**
         * @brief Gets the centroids
         * @return Vector of centroids
         */
        [[nodiscard]] auto getCentroids() const -> std::vector<Point>;

        /**
         * @brief Gets the number of iterations
         * @return Number of iterations
         */
        [[nodiscard]] auto getIterations() const -> int;

    protected:
        int k; ///< Number of clusters
        std::vector<Point> points; ///< Vector of points
        std::vector<Point> centroids; ///< Vector of centroids
        int number_of_iterations; ///< Number of iterations
    };
} // namespace k

#endif // KMEANS_BASE_HPP
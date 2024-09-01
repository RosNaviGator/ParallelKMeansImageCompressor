/**
 * @file kMeansBase.hpp
 * @brief Base class for K-means clustering algorithm
 */

#ifndef KMEANS_BASE_HPP
#define KMEANS_BASE_HPP

#include <vector>
#include "point.hpp"

namespace km
{
    /**
     * @class KMeansBase
     * @brief Base class for K-means clustering algorithm
     * @details The KMeansBase class, part of the km namespace, serves as a foundational class for implementing the K-means clustering algorithm. It is designed to manage and execute the clustering process, providing a base for derived classes to build upon with specific implementations.

The class includes several key functionalities: it allows for the construction of an object with either a predefined number of clusters and a set of points or just the number of clusters. The run method, which is a pure virtual function, must be implemented by any derived class to execute the K-means algorithm. This structure ensures that the base class can provide the essential setup and data management, while specific clustering logic is handled by subclasses.

The KMeansBase class also includes methods to retrieve the points used for clustering, the centroids calculated by the algorithm, and the number of iterations the algorithm has undergone. These methods provide access to the internal state of the clustering process, enabling users to inspect and analyze the results. Protected member variables include the number of clusters, the points to be clustered, the centroids resulting from the clustering process, and the count of iterations performed, allowing derived classes to access and manipulate these values as needed.
     */
    
    class KMeansBase
    {

    public:
        /**
         * @brief Constructor for KMeansBase
         * @param k Number of clusters
         * @param points Vector of points
         */
        KMeansBase(const int &k, const std::vector<Point> &points);

        /**
         * @brief Constructs a KMeansBase object only with the specified number of clusters.
         *
         * @param k The number of clusters.
         */
        KMeansBase(const int &k);

        /**
         * @brief Virtual destructor for KMeansBase
         */
        virtual ~KMeansBase() = default;

        /**
         * @brief Runs the K-means clustering algorithm
         */
        virtual void run() = 0;

        /**
         * @brief Gets the poinots
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
        int k;                        ///< Number of clusters
        std::vector<Point> points;    ///< Vector of points
        std::vector<Point> centroids; ///< Vector of centroids
        int number_of_iterations;     ///< Number of iterations
    };
} // namespace k

#endif // KMEANS_BASE_HPP
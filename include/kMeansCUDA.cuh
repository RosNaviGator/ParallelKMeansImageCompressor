/**
 * @file kMeansCUDA.cuh
 * @brief Implementation of the K-means clustering algorithm using CUDA
 */

#ifndef KMEANS_CUDA_HPP
#define KMEANS_CUDA_HPP

#include <random>
#include <iostream>
#include <vector>
#include <cuda_runtime.h>
#include <point.hpp>


namespace km
{
    /**
     * @class KMeansCUDA
     * @brief Represents the K-means clustering algorithm using CUDA
     * @details The KMeansCUDA class, located in the km namespace, is designed to implement the K-means clustering algorithm using CUDA for enhanced performance through parallel processing on GPUs. This class extends the functionality of traditional K-means clustering by leveraging CUDA to accelerate computations, making it suitable for large datasets and complex clustering tasks.

The class provides a constructor that initializes the number of clusters and the vector of points to be clustered. It includes a run method that executes the K-means algorithm on the GPU, performing the clustering operations efficiently by taking advantage of parallel processing capabilities. Additionally, it offers methods to print and plot the clusters, allowing users to visualize the results of the clustering process. The getPoints, getCentroids, and getIterations methods provide access to the internal state of the clustering, including the input points, the resulting centroids, and the number of iterations the algorithm has undergone, respectively. This design ensures that users can both run and analyze the K-means clustering process using CUDA for improved performance.
     */

    class KMeansCUDA
    {
    public:
        /**
         * @brief Constructor for KMeans
         * @param k Number of clusters
         * @param points Vector of points
         */
        
        KMeansCUDA(const int &k, const std::vector<Point> &points);

        /**
         * @brief Runs the K-means clustering algorithm using CUDA
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
         *
         */
        auto getCentroids() -> std::vector<Point>;

        /**
         * @brief Gets the number of iterations
         * @return Number of iterations
         */
        auto getIterations() -> int;

    private:
        int k;                        ///< Number of clusters
        std::vector<Point> points;    ///< Vector of points
        std::vector<Point> centroids; ///< Vector of centroids
        int number_of_iterations;     ///< Number of iterations
    };
} // namespace km

#endif // KMEANS_CUDA_HPP
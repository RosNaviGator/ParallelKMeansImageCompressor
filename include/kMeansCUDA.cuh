/**
 * @file kMeansCUDA.cuh
 * @brief Implementation of the K-means clustering algorithm using CUDA
 */


/// @cond DOXYGEN_IGNORE
#ifndef KMEANS_CUDA_HPP
#define KMEANS_CUDA_HPP
/// @endcond

#include <random>
#include <iostream>
#include <vector>
#include <cuda_runtime.h>
#include <point.hpp>


namespace km
{
    /**
     * @brief CUDA kernel to calculate the new centroids based on the assigned clusters
     * @param data Pointer to the data points
     * @param centroids Pointer to the current centroids
     * @param labels Pointer to the labels (cluster assignments)
     * @param counts Pointer to the counts of points per cluster
     * @param n Number of data points
     * @param k Number of clusters
     * @param dim Number of dimensions for each data point
     * 
     * @details This kernel calculates the new centroids by summing the data points assigned to each centroid. The results are stored in the centroids array and the counts array records the number of points assigned to each centroid.
     */
    __global__ void calculate_new_centroids(int *data, int *centroids, int *labels, int *counts, int n, int k, int dim);

    /**
     * @brief CUDA kernel to average the calculated centroids
     * @param centroids Pointer to the current centroids
     * @param counts Pointer to the counts of points per cluster
     * @param k Number of clusters
     * @param dim Number of dimensions for each data point
     * 
     * @details This kernel averages the sum of the centroids from the `calculate_new_centroids` kernel by dividing the summed values by the number of points in each cluster.
     */
    __global__ void average_centroids(int *centroids, int *counts, int k, int dim);

    /**
     * @brief CUDA kernel to assign each point to the nearest centroid
     * @param data Pointer to the data points
     * @param centroids Pointer to the current centroids
     * @param labels Pointer to the labels (cluster assignments)
     * @param n Number of data points
     * @param k Number of clusters
     * @param dim Number of dimensions for each data point
     * 
     * @details This kernel assigns each point to the nearest centroid by calculating the Euclidean distance between each point and the centroids. The closest centroid's index is assigned to the corresponding position in the labels array.
     */
    __global__ void assign_clusters(int *data, int *centroids, int *labels, int n, int k, int dim);



    /**
     * @class KMeansCUDA
     * @brief Represents the K-means clustering algorithm using CUDA
     * @details The KMeansCUDA class, located in the km namespace, is designed to implement the K-means clustering algorithm using CUDA for enhanced performance through parallel processing on GPUs.
     *          This class extends the functionality of traditional K-means clustering by leveraging CUDA to accelerate computations, making it suitable for large datasets and complex clustering tasks.
     *          The class provides a constructor that initializes the number of clusters and the vector of points to be clustered. It includes a run method that executes the K-means algorithm on the GPU,
     *          performing the clustering operations efficiently by taking advantage of parallel processing capabilities. Additionally, it offers methods to print and plot the clusters, allowing users to
     *          visualize the results of the clustering process. The getPoints, getCentroids, and getIterations methods provide access to the internal state of the clustering, including the input points,
     *          the resulting centroids, and the number of iterations the algorithm has undergone, respectively. This design ensures that users can both run and analyze the K-means clustering process using
     *          CUDA for improved performance.
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
         * @brief Gets the points
         * @return Vector of constant points
         */
        auto getPoints() const -> const std::vector<Point>&;

        /**
         * @brief Gets the centroids
         * @return Vector of constant centroids
         *
         */
        auto getCentroids() const -> const std::vector<Point>&;

        /**
         * @brief Gets the points
         * @return Vector of modifiable points
         */
        auto getPoints() -> std::vector<Point>&;

        /**
         * @brief Gets the centroids
         * @return Vector of modifiable centroids
         *
         */
        auto getCentroids() -> std::vector<Point>&;

        /**
         * @brief Gets the number of iterations
         * @return Number of iterations
         */
        auto getIterations() const -> const int&;

    private:
        int k;                        ///< Number of clusters
        std::vector<Point> points;    ///< Vector of points
        std::vector<Point> centroids; ///< Vector of centroids
        int number_of_iterations;     ///< Number of iterations
    };
} // namespace km


/// @cond DOXYGEN_IGNORE
#endif // KMEANS_CUDA_HPP
/// @endcond
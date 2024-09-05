/**
 * @file kMeansMPI.hpp
 * @brief Implementation of the K-means clustering algorithm using MPI
 */

#ifndef KMEANS_MPI_HPP
#define KMEANS_MPI_HPP

#include "kMeansBase.hpp"
#include <mpi.h>

namespace km
{
    /**
     * @class KMeansMPI
     * @brief Represents the K-means clustering algorithm using MPI
     * @details The KMeansMPI class, located in the km namespace, is designed to implement the K-means clustering algorithm using MPI (Message Passing Interface) for parallel and distributed computing.
     *          This class extends the base KMeansBase class to enable clustering operations across multiple processes, leveraging MPI to handle large-scale data and computational tasks more efficiently. 
     *          The class includes two constructors: one that initializes the number of clusters, a vector of points, and a vector of local points distributed across MPI processes; and another that initializes
     *          only the number of clusters and local points. The run method, overridden from KMeansBase, is responsible for executing the K-means clustering algorithm using MPI, coordinating the clustering
     *          process across different processes in a distributed computing environment.
     *          The local_points member variable holds the points assigned to each MPI process, enabling the parallel execution of clustering tasks. This class is designed to handle clustering in a distributed
     *          setting, allowing for efficient processing of large datasets by distributing the workload across multiple computing nodes.
     */

    class KMeansMPI : public KMeansBase
    {
    public:
        /**
         * @brief Constructor for KMeansMPI
         * @param k Number of clusters
         * @param points Vector of points
         */
        KMeansMPI(const int &k, const std::vector<Point> &points, std::vector<std::pair<int, Point>> local_points);

        /**
         * @brief Constructor for KMeansMPI
         * @param k Number of clusters
         */
        KMeansMPI(const int &k, std::vector<std::pair<int, Point>> local_points);

        /**
         * @brief Runs the K-means clustering algorithm using MPI
         */
        void run() override;

    private:
        std::vector<std::pair<int, Point>> local_points; ///< Vector of local points
    };
} // namespace k

#endif // KMEANS_MPI_HPP
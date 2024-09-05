/**
 * @file kMeansOMP.hpp
 * @brief Implementation of the K-means clustering algorithm using OpenMP
 */

#ifndef KMEANS_OMP_HPP
#define KMEANS_OMP_HPP

#include "kMeansBase.hpp"
#include <omp.h>

namespace km
{
    /**
     * @class KMeansOMP
     * @brief Represents the K-means clustering algorithm using OpenMP
     * @details The KMeansOMP class, part of the km namespace, is designed to implement the K-means clustering algorithm using OpenMP, a parallel programming model for shared-memory architectures.
     *          This class extends the KMeansBase class to utilize OpenMP for parallelizing the clustering process, which can significantly speed up computations by leveraging multi-core processors.
     *          The class features a constructor that initializes the number of clusters and the vector of points to be clustered. The run method, which overrides the base class method, is responsible
     *          for executing the K-means clustering algorithm with parallelization support provided by OpenMP. This allows the algorithm to handle clustering operations more efficiently by distributing
     *          computational tasks across multiple threads.
     *          By integrating OpenMP, the KMeansOMP class aims to enhance the performance of the K-means clustering algorithm, making it suitable for processing larger datasets and improving computational
     *          efficiency in environments with multi-core CPUs.
     */

    class KMeansOMP : public KMeansBase
    {
    public:
        /**
         * @brief Constructor for KMeansOMP
         * @param k Number of clusters
         * @param points Vector of points
         */
        KMeansOMP(const int &k, const std::vector<Point> &points);

        /**
         * @brief Runs the K-means clustering algorithm using OpenMP
         */
        void run() override;
    };
} // namespace km

#endif // KMEANS_OMP_HPP
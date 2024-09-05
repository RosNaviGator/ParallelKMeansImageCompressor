/**
 * @file kMeansSequential.hpp
 * @brief Implementation of the K-means clustering algorithm
 */

#ifndef KMEANS_SEQUENTIAL_HPP
#define KMEANS_SEQUENTIAL_HPP

#include "kMeansBase.hpp"

namespace km
{
    /**
     * @class KMeansSequential
     * @brief Represents the K-means clustering algorithm
     * @details The KMeansSequential class, within the km namespace, provides a straightforward implementation of the K-means clustering algorithm. This class extends the KMeansBase
     *          class to implement the algorithm in a sequential manner, meaning that it performs all computations in a single-threaded, non-parallel fashion. The class includes a
     *          constructor that initializes the number of clusters and the vector of points to be clustered. The run method, which overrides the virtual method from KMeansBase,
     *          is responsible for executing the K-means clustering algorithm in a sequential, step-by-step process. This implementation is suitable for environments where parallel
     *          processing is not available or necessary, and it provides a foundational approach to K-means clustering that can be used for benchmarking or as a baseline for more
     *          complex implementations.
     *          The KMeansSequential class serves as a basic and direct implementation of K-means clustering, focusing on clarity and correctness of the algorithm in a non-parallelized context.
     */

    class KMeansSequential : public KMeansBase
    {
    public:
        /**
         * @brief Constructor for KMeansSequential
         * @param k Number of clusters
         * @param points Vector of points
         */
        KMeansSequential(const int &k, const std::vector<Point> &points);

        /**
         * @brief Runs the K-means clustering algorithm
         */
        void run() override;
    };
}

#endif // KMEANS_SEQUENTIAL_HPP
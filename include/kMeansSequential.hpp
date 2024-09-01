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
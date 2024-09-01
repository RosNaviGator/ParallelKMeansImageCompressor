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
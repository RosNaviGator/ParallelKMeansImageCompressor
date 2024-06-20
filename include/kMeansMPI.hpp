/**
 * @file kMeansMPI.hpp
 * @brief Implementation of the K-means clustering algorithm using MPI
 */

#ifndef KMEANS_MPI_HPP
#define KMEANS_MPI_HPP

#include "kMeansBase.hpp"
#include <mpi.h>

/**
 * @class KMeansMPI
 * @brief Represents the K-means clustering algorithm using MPI
 */

namespace km
{
    class KMeansMPI : public KMeansBase
    {
    public:
        /**
         * @brief Constructor for KMeansMPI
         * @param k Number of clusters
         * @param points Vector of points
         */
        KMeansMPI(const int& k, const std::vector<Point>& points,std::vector<std::pair<int, Point>> local_points);

        /**
         * @brief Constructor for KMeansMPI
         * @param k Number of clusters
         */
        KMeansMPI(const int& k,std::vector<std::pair<int, Point>> local_points);

        /**
         * @brief Runs the K-means clustering algorithm using MPI
         */
        void run() override;
    private:
        std::vector<std::pair<int, Point>> local_points; ///< Vector of local points
    };
} // namespace k

#endif // KMEANS_MPI_HPP
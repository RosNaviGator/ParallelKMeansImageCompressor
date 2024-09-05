/**
 * @file performanceEvaluation.hpp
 * @brief Performance evaluation class
 */

#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>

namespace km
{
    /**
     * @class Performance
     * @brief Represents the performance evaluation
     * @details The Performance class in the km namespace is designed for evaluating and recording the performance of clustering algorithms.
     *          It includes methods to write performance data to a CSV file, extract file names from paths, and fill in performance metrics
     *          based on various criteria. The class has a default constructor and methods for writing data to a CSV file, such as writeCSV
     *          for recording performance metrics, and fillPerformance for populating evaluation data. Private methods handle file operations,
     *          including creating or opening CSV files and appending data. The class manages internal details like image names and evaluation
     *          choices for performance analysis.
     */

    class Performance
    {
    public:
        /**
         * @brief Default constructor
         */
        Performance();

        /**
         * @brief Writes performance data to a CSV file
         * @param different_colors_size Number of different colors
         * @param k Number of clusters
         * @param n_points Number of points
         * @param elapsedKmeans Elapsed time for K-means clustering
         * @param num_processes Number of processes (optional, default=0)
         */
        auto writeCSV(int different_colors_size, int k, int n_points, double elapsedKmeans, int number_of_iterations, int num_processes = 0) -> void;

        /**
         * @brief Extracts the file name from the output path
         * @param outputPath Output path
         * @return Extracted file name
         */
        static auto extractFileName(const std::string &outputPath) -> std::string;

        /**
         * @brief Fills the performance data
         * @param choice Choice of performance evaluation
         * @param img Image name
         * @param method Method used
         */
        auto fillPerformance(int choice, const std::string &img, const std::string &method) -> void;

    private:
        /**
         * @brief Creates or opens a CSV file
         * @param filename Name of the CSV file
         */
        auto createOrOpenCSV(const std::string &filename) -> void;

        /**
         * @brief Appends performance data to the CSV file
         * @param filename Name of the CSV file
         * @param n_diff_colors Number of different colors
         * @param k Number of clusters
         * @param n_colors Number of colors
         * @param compType Compression type
         * @param time Elapsed time
         * @param num_processes Number of processes
         */
        auto appendToCSV(const std::string &filename, int n_diff_colors, int k, int n_colors, const std::string &compType, double time, int num_processes, int number_of_iteratios) -> void;

        std::string img;    ///< Image name
        int choice{};       ///< Choice of performance evaluation
        std::string method; ///< Method used
    };
}

#endif // PERFORMANCE_HPP
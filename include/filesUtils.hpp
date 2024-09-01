/**
 * @file filesUtils.hpp
 * @brief Utility functions for file handling
 */

#ifndef FILESUTILS_HPP
#define FILESUTILS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <filesystem>
#include <point.hpp>
#include <opencv2/opencv.hpp>

/**
 * @namespace km::filesUtils
 * @brief Provides utility functions for file handling
 */
namespace km
{
    namespace filesUtils
    {
        /**
         * @brief Creates output directories
         */
        auto createOutputDirectories() -> void;

        /**
         * @brief Writes data to a binary file
         * @param outputPath Path of the output file
         * @param width Width of the image
         * @param height Height of the image
         * @param k Number of clusters
         * @param points Vector of points
         * @param centroids Vector of centroids
         */
        auto writeBinaryFile(std::string& outputPath, int& width, int& height, int& k, std::vector<Point> points, std::vector<Point> centroids) -> void;

        /**
         * @brief Checks if a file has the correct extension
         * @param filePath Path of the file
         * @param correctExtension Correct extension to check
         * @return True if the file has the correct extension, false otherwise
         */
        auto isCorrectExtension(const std::filesystem::path &filePath, const std::string &correctExtension) -> bool;

        /**
         * @brief Creates a decoding menu
         * @param decodeDir Directory for decoding
         * @param imageNames Vector of image names
         */
        auto createDecodingMenu(std::filesystem::path& decodeDir, std::vector<std::filesystem::path>& imageNames) -> void;

        /**
         * @brief Reads a binary file and reconstructs the compressed image
         * @param path Path of the binary file
         * @param imageCompressed Compressed image matrix
         * @return Number of clusters
         */
        auto readBinaryFile(std::string& path, cv::Mat& imageCompressed) -> int;
    };
}

#endif // FILESUTILS_HPP
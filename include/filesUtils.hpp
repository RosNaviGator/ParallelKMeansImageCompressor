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
 * @details The filesUtils namespace within the km namespace offers a set of utility functions designed to handle various file operations crucial for image processing
 *          and data management. It includes functionalities to create necessary output directories, ensuring that the required directory structure is in place before
 *          any file operations are performed. The namespace provides a function to write data to a binary file, which includes parameters for the file path, image dimensions,
 *          the number of clusters, and vectors of points and centroids. This is particularly useful for saving compressed image data or related binary information. Additionally,
 *          it includes a function to verify whether a file has the correct extension, which is essential for validating file types before processing. The createDecodingMenu
 *          function facilitates the creation of a decoding menu by accepting a directory path and a vector of image names, which may be used for setting up decoding options.
 *          Lastly, the readBinaryFile function reads from a binary file to reconstruct a compressed image into an OpenCV matrix, returning the number of clusters present in the file.
 *          This set of functions is designed to streamline and manage file-related tasks, particularly in the context of image processing.
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
        auto writeBinaryFile(const std::string &outputPath,const int &width,const int &height,const int &k, std::vector<Point>& points, std::vector<Point>& centroids) -> void;

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
        auto createDecodingMenu(std::filesystem::path &decodeDir, std::vector<std::filesystem::path> &imageNames) -> void;

        /**
         * @brief Reads a binary file and reconstructs the compressed image
         * @param path Path of the binary file
         * @param imageCompressed Compressed image matrix
         * @return Number of clusters
         */
        auto readBinaryFile(const std::string &path, cv::Mat &imageCompressed) -> int;
    };
}

#endif // FILESUTILS_HPP
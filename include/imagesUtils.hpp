/**
 * @file imagesUtils.hpp
 * @brief Utility functions for image processing
 */

#ifndef IMAGEUTILS_HPP
#define IMAGEUTILS_HPP

#include <iostream>
#include <vector>
#include <set>
#include <opencv2/opencv.hpp>
#include <configReader.hpp>
#include <point.hpp>

/**
 * @namespace km::imageUtils
 * @brief Provides utility functions for image processing
 * @details The imageUtils namespace within the km namespace provides a suite of utility functions aimed at facilitating various image processing tasks.
 *          This namespace encompasses functions designed to preprocess images, determine the appropriate number of clusters for color-based compression, and extract
 *          points from images for further analysis. The preprocessing function is responsible for preparing an image for subsequent processing steps, adjusting it
 *          according to the specified type of compression. The defineKValue function calculates the number of clusters, or K, based on the chosen levels of colors
 *          and the distinct colors present in the image. This function helps in determining the optimal number of clusters for tasks such as color quantization.
 *          Lastly, the pointsFromImage function extracts points from the image and organizes them into a vector, using the set of distinct colors found in the image to
 *          aid in this process. These functions collectively support various aspects of image processing, ensuring efficient handling and analysis of image data.
 */

namespace km
{
    namespace imageUtils
    {
        /**
         * @brief Performs preprocessing on an image
         * @param image Input image
         * @param typeCompressionChoice Type of compression choice
         */
         void preprocessing(cv::Mat& image, int& typeCompressionChoice);

        /**
         * @brief Defines the value of K based on the color levels choice
         * @param k Value of K
         * @param levelsColorsChoice Levels of colors choice
         * @param different_colors Set of different colors in the image
         */
         void defineKValue(int& k, int levelsColorsChoice, std::set<std::vector<unsigned char>>& different_colors);

        /**
         * @brief Extracts points from an image
         * @param image Input image
         * @param points Vector of points
         * @param different_colors Set of different colors in the image
         */
         void pointsFromImage(cv::Mat& image, std::vector<Point>& points, std::set<std::vector<unsigned char>>& different_colors);
    };

}

#endif // IMAGEUTILS_HPP
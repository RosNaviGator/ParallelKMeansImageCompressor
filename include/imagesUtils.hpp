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
 * @class ImageUtils
 * @brief Provides utility functions for image processing
 */
class ImageUtils
{
public:
    /**
     * @brief Performs preprocessing on an image
     * @param image Input image
     * @param typeCompressionChoice Type of compression choice
     */
    static void preprocessing(cv::Mat& image, int& typeCompressionChoice);

    /**
     * @brief Defines the value of K based on the color levels choice
     * @param k Value of K
     * @param levelsColorsChoice Levels of colors choice
     * @param different_colors Set of different colors in the image
     */
    static void defineKValue(int& k, int levelsColorsChoice, std::set<std::vector<unsigned char>>& different_colors);

    /**
     * @brief Extracts points from an image
     * @param image Input image
     * @param points Vector of points
     * @param different_colors Set of different colors in the image
     */
    static void pointsFromImage(cv::Mat& image, std::vector<Point>& points, std::set<std::vector<unsigned char>>& different_colors);
};

#endif // IMAGEUTILS_HPP
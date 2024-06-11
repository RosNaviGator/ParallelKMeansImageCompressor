#ifndef IMAGEUTILS_HPP
#define IMAGEUTILS_HPP

#include <iostream>
#include <vector>
#include <set>
#include <opencv2/opencv.hpp>
#include <configReader.hpp>
#include <point.hpp>

class ImageUtils
{
public:
    static void preprocessing(cv::Mat& image, int& typeCompressionChoice);
    static void defineKValue(int& k, int levelsColorsChoice, std::set<std::vector<unsigned char>>& different_colors);
    static void pointsFromImage(cv::Mat& image, std::vector<Point>& points, std::set<std::vector<unsigned char>>& different_colors);
};

#endif // IMAGEUTILS_HPP
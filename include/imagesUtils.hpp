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
        static void preprocessing(cv::Mat& image, int& typeCompressionChoice)
        {
            ConfigReader configReader;
            double resizing_factor = configReader.getResizingFactor();

            cv::cvtColor(image, image, cv::COLOR_BGR2YCrCb);
            // apply chroma subsampling
            if (typeCompressionChoice == 3)
            {
                cv::resize(image, image, cv::Size(), resizing_factor, resizing_factor, cv::INTER_LINEAR);
            }else if (typeCompressionChoice == 2)
            {
                cv::resize(image, image, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
                cv::resize(image, image, cv::Size(), 2, 2, cv::INTER_LINEAR);
            }
        };
        static void defineKValue(int& k, int levelsColorsChioce, std::set < std::vector<unsigned char> > different_colors)
        {
            ConfigReader configReader;
            if (levelsColorsChioce == 1)
            {
                k = configReader.getFirstLevelCompressionColor() * different_colors.size() / 100; 
            }else if (levelsColorsChioce == 2)
            {
                k = configReader.getSecondLevelCompressionColor() * different_colors.size() / 100;
            }else if (levelsColorsChioce == 3)
            {
                k = configReader.getThirdLevelCompressionColor() * different_colors.size() / 100;
            }else if (levelsColorsChioce == 4)
            {
                k = configReader.getFourthLevelCompressionColor() * different_colors.size() / 100;
            }else if (levelsColorsChioce == 5)
            {
                k = configReader.getFifthLevelCompressionColor() * different_colors.size() / 100;
            }
        }
        static void pointsFromImage(cv::Mat& image, std::vector<Point>& points, std::set < std::vector<unsigned char> >& different_colors)
        {
            int height = image.rows;
            int width = image.cols;
            int id = 0;
            for(int y = 0 ; y < height ; y++)
            {
                for (int x = 0 ; x < width ; x++)
                {
                    points.emplace_back(Point(id, {image.at<cv::Vec3b>(y, x)[0],image.at<cv::Vec3b>(y, x)[1],image.at<cv::Vec3b>(y, x)[2]}));
                    different_colors.insert({image.at<cv::Vec3b>(y, x)[0],image.at<cv::Vec3b>(y, x)[1],image.at<cv::Vec3b>(y, x)[2]});
                    id += 1;
                }
            }
        }
};

#endif // IMAGEUTILS_HPP
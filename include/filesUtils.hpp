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

class FilesUtils
{
public:
    static void createOutputDirectories();
    static void writeBinaryFile(std::string& outputPath, int& width, int& height, int& k, std::vector<Point> points, std::vector<Point> centroids);
    static void writePerformanceEvaluation(std::string path, std::string program_name, int k, std::vector<Point> points, std::chrono::duration<double> elapsedKmeans);
    static bool isCorrectExtension(const std::filesystem::path &filePath, const std::string &correctExtension);
    static void createDecodingMenu(std::filesystem::path& decodeDir, std::vector<std::filesystem::path>& imageNames);
    static int readBinaryFile(std::string& path, cv::Mat& imageCompressed);
};

#endif // FILESUTILS_HPP
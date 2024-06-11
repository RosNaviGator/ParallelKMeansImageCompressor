#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>

class Performance
{
public:
    Performance(); // Default constructor
    void writeCSV(int different_colors_size, int k, int n_points, double elapsedKmeans, int num_processes = 0);
    static std::string extractFileName(const std::string &outputPath);
    void fillPerformance(int choice, std::string img, std::string method);

private:
    void createOrOpenCSV(const std::string &filename);
    void appendToCSV(std::string filename, int n_diff_colors, int k, int n_colors, const std::string &compType, double time, int num_processes);
    std::string img;
    int choice;
    std::string method;
};

#endif // PERFORMANCE_HPP
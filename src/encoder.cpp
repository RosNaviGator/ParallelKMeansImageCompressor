
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <random>
#include <thread>
#include <chrono>
#include <point.hpp>
#include <kMeans.hpp>
#include <utilsCLI.hpp>
#include <imagesUtils.hpp>
#include <filesUtils.hpp>

#include <opencv2/opencv.hpp>
#include <configReader.hpp>


int main(int argc, char *argv[])
{
    int k;
    std::string path;
    std::string outputPath;
    std::vector<Point> points;
    int height;
    int width;
    int n_points;
    std::vector<std::pair<int, Point> > local_points;
    int levelsColorsChioce;
    int typeCompressionChoice;
    cv::Mat image;
   
    UtilsCLI::compressionChoices(levelsColorsChioce, typeCompressionChoice, outputPath, image,1);

    int originalHeight = image.rows;
    int originalWidth = image.cols;

    ImageUtils::preprocessing(image, typeCompressionChoice);   

    height = image.rows;
    width = image.cols;

    std::set < std::vector<unsigned char> > different_colors; 
    
    ImageUtils::pointsFromImage(image, points, different_colors);

    n_points = points.size();

    ImageUtils::defineKValue(k, levelsColorsChioce, different_colors);

    int different_colors_size = different_colors.size();

    UtilsCLI::printCompressionInformations(originalWidth, originalHeight, width, height, k, different_colors_size);
    
    KMeans kmeans(k, points);

    // CLUSTERING (second time evaluation)
    auto startKmeans = std::chrono::high_resolution_clock::now();

    std::cout << "Press a key to start the compression..."<< std::endl;
    std::cin.ignore();
    std::cout << "Starting the Compression..." << std::endl;

    kmeans.run();

    auto endKmeans = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedKmeans = endKmeans - startKmeans;

    FilesUtils::createOutputDirectories();

    FilesUtils::writeBinaryFile(outputPath, width, height, k, kmeans);

    FilesUtils::writePerformanceEvaluation(outputPath, "Sequential", k, points, kmeans, elapsedKmeans);

    UtilsCLI::workDone();
    std::cout << "Compression done in " << elapsedKmeans.count() << std::endl;
    std::cout << std::endl;
    std::cout << "The compressed image has been saved in the outputs directory." << std::endl;
}

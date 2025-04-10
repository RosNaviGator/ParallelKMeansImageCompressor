/**
 * @file encoderOMP.cpp
 * @brief Main entry point for the OpenMP-based image compression application.
 *
 * @details This program compresses an image using the K-means clustering algorithm with OpenMP 
 *          for parallel processing across multiple threads. It reads input parameters from the command line, 
 *          processes the image, applies compression, and saves the compressed image to a binary file. 
 *          The program also evaluates performance metrics and writes them to a CSV file. The application uses OpenCV 
 *          for image processing and custom libraries for compression, file handling, and performance evaluation.
 */

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
#include <kMeansOMP.hpp>
#include <utilsCLI.hpp>
#include <imagesUtils.hpp>
#include <filesUtils.hpp>

#include <opencv2/opencv.hpp>
#include <configReader.hpp>


#include <performanceEvaluation.hpp>

using namespace km;
using namespace km::filesUtils;
using namespace km::utilsCLI;
using namespace km::imageUtils;

/**
 * @brief Main function for the OpenMP-based image compression application.
 *
 * @details This function initializes the program, processes input arguments, reads the input image,
 *          performs preprocessing, applies K-means clustering using OpenMP for image compression, 
 *          and saves the compressed image to a binary file. It also evaluates and logs the performance metrics.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return Returns 0 on successful execution, or 1 if an error occurs.
 */

auto main(int argc, char *argv[]) -> int
{

    int num_threads = 0;

    int k = 0;
    std::string path;
    std::string outputPath;
    std::string fileName;
    std::vector<Point> points;
    int height = 0;
    int width = 0;
    int n_points = 0;
    std::vector<std::pair<int, Point>> local_points;
    int levelsColorsChioce = 0;
    int typeCompressionChoice = 0;
    cv::Mat image;
    Performance performance;

    
    const int NUMBER_OF_ARGS_WITHOUT_THREADS = 4;
    const int NUMBER_OF_ARGS_DEFINING_THREADS = 5;

    auto args = std::span(argv, size_t(argc));

    if (argc == NUMBER_OF_ARGS_DEFINING_THREADS)
    {
        num_threads = std::stoi(args[4]);
        omp_set_num_threads(num_threads);
    }
    

    if (argc == NUMBER_OF_ARGS_DEFINING_THREADS || argc == NUMBER_OF_ARGS_WITHOUT_THREADS)
    {   
        path = args[1];
        levelsColorsChioce = std::stoi(args[2]);
        typeCompressionChoice = std::stoi(args[3]);

        fileName = Performance::extractFileName(path);
        outputPath = std::string("outputs/") + fileName + std::string(".kc");

        image = cv::imread(path);
        if (image.empty())
        {
            std::cerr << "Error: Image not found." << std::endl;
            return 1;
        }

        performance.fillPerformance(typeCompressionChoice, fileName, "OMP");

    }
    else
    {
        std::cerr << "Error: Invalid number of arguments." << std::endl;
        return 1;
    }

    int originalHeight = image.rows;
    int originalWidth = image.cols;

    preprocessing(image, typeCompressionChoice);

    height = image.rows;
    width = image.cols;

    std::set<std::vector<unsigned char>> different_colors;

    pointsFromImage(image, points, different_colors);

    n_points = points.size();

    defineKValue(k, levelsColorsChioce, different_colors);

    size_t different_colors_size = 0;
    different_colors_size = different_colors.size();

    printCompressionInformations(originalWidth, originalHeight, width, height, k, different_colors_size);

    KMeansOMP kmeans(k, points);

    // CLUSTERING (second time evaluation)

    // std::cout << "Press a key to start the compression..."<< std::endl;
    // std::cin.ignore();
    std::cout << "Starting the Compression..." << std::endl;

    auto startKmeans = std::chrono::high_resolution_clock::now();

    kmeans.run();

    auto endKmeans = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedKmeans = endKmeans - startKmeans;

    createOutputDirectories();

    writeBinaryFile(outputPath, width, height, k, kmeans.getPoints(), kmeans.getCentroids());

    performance.writeCSV(different_colors_size, k, n_points, elapsedKmeans.count(), kmeans.getIterations(),num_threads);

    workDone();
    std::cout << "Compression done in " << elapsedKmeans.count() << std::endl;
    std::cout << std::endl;
    std::cout << "The compressed image has been saved in the outputs directory." << std::endl;
}



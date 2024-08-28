
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
#include <kMeansSequential.hpp>
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


auto main(int argc, char *argv[]) -> int
{
    int k = 0;
    std::string path;
    std::string outputPath;
    std::string fileName;
    std::vector<Point> points;
    int height = 0;
    int width = 0;
    int n_points = 0;
    std::vector<std::pair<int, Point> > local_points;
    int levelsColorsChioce = 0;
    int typeCompressionChoice = 0;
    cv::Mat image;
    Performance performance;

    auto args = std::span(argv, size_t(argc));
    // pass inputs as args for performance evaluation
    if (4 == argc)
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

        performance.fillPerformance(typeCompressionChoice, fileName, "Sequential");

    }
    else
    {
        // ask inputs at runtime
        compressionChoices(levelsColorsChioce, typeCompressionChoice, outputPath, image,1);
    }

    int originalHeight = image.rows;
    int originalWidth = image.cols;

    preprocessing(image, typeCompressionChoice);   

    height = image.rows;
    width = image.cols;

    std::set < std::vector<unsigned char> > different_colors; 
    
    pointsFromImage(image, points, different_colors);

    n_points = points.size();

    defineKValue(k, levelsColorsChioce, different_colors);

    size_t different_colors_size = different_colors.size();

    printCompressionInformations(originalWidth, originalHeight, width, height, k, different_colors_size);
    
    KMeansSequential kmeans(k, points);

    // CLUSTERING (second time evaluation)

    //std::cout << "Press a key to start the compression..."<< std::endl;
    //std::cin.ignore();
    std::cout << "Starting the Compression..." << std::endl;

    auto startKmeans = std::chrono::high_resolution_clock::now();


    kmeans.run();

    auto endKmeans = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedKmeans = endKmeans - startKmeans;

    createOutputDirectories();

    writeBinaryFile(outputPath, width, height, k, kmeans.getPoints(), kmeans.getCentroids());

    // write perfomance data to csv
    if (4 == argc)
    {   
        performance.writeCSV(different_colors_size, k, n_points, elapsedKmeans.count(), kmeans.getIterations());
    }


    workDone();
    std::cout << "Compression done in " << elapsedKmeans.count() << std::endl;
    std::cout << std::endl;
    std::cout << "The compressed image has been saved in the outputs directory." << std::endl;

    return 0;
}


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


#include <performanceEvaluation.hpp>




int main(int argc, char *argv[])
{
    int k;
    std::string path;
    std::string outputPath;
    std::string fileName;
    std::vector<Point> points;
    int height;
    int width;
    int n_points;
    std::vector<std::pair<int, Point> > local_points;
    int levelsColorsChioce;
    int typeCompressionChoice;
    cv::Mat image;
    Performance performance;


    // pass inputs as args for performance evaluation
    if (4 == argc)
    {   
        path = argv[1];
        levelsColorsChioce = std::stoi(argv[2]);
        typeCompressionChoice = std::stoi(argv[3]);

        fileName = Performance::extractFileName(path);
        outputPath = "outputs/" + fileName + ".kc";

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
        UtilsCLI::compressionChoices(levelsColorsChioce, typeCompressionChoice, outputPath, image,1);
    }

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

    //std::cout << "Press a key to start the compression..."<< std::endl;
    //std::cin.ignore();
    std::cout << "Starting the Compression..." << std::endl;

    auto startKmeans = std::chrono::high_resolution_clock::now();


    kmeans.run();

    auto endKmeans = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedKmeans = endKmeans - startKmeans;

    FilesUtils::createOutputDirectories();

    FilesUtils::writeBinaryFile(outputPath, width, height, k, kmeans.getPoints(), kmeans.getCentroids());

    FilesUtils::writePerformanceEvaluation(outputPath, "Sequential", k, points, elapsedKmeans);


    // write perfomance data to csv
    if (4 == argc)
    {   
        performance.writeCSV(different_colors_size, k, n_points, elapsedKmeans.count());
    }


    UtilsCLI::workDone();
    std::cout << "Compression done in " << elapsedKmeans.count() << std::endl;
    std::cout << std::endl;
    std::cout << "The compressed image has been saved in the outputs directory." << std::endl;

    return 0;
}

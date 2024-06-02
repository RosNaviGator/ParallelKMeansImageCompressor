
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
#include <kMeansCUDA.hpp>
#include <utilsCLI.hpp>
#include <imagesUtils.hpp>
#include <filesUtils.hpp>

#include <opencv2/opencv.hpp>
#include <configReader.hpp>


std::string extractFileName(const std::string& outputPath) {
    // Find the position of the last '/' character
    size_t lastSlashPos = outputPath.find_last_of('/');
    
    // Find the position of the ".kc" extension
    size_t extensionPos = outputPath.find(".kc");

    // If both positions are found
    if (lastSlashPos != std::string::npos && extensionPos != std::string::npos) {
        // Extract the substring between the last '/' and ".kc"
        return outputPath.substr(lastSlashPos + 1, extensionPos - lastSlashPos - 1);
    }

    // If either position is not found, return an empty string
    return "";
}

void createOrOpenCSV(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.good()) {
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            std::cerr << "Error creating file!" << std::endl;
            return;
        }
        outfile << "img, method, staring colors, k, n_points, comp type, time" << std::endl; // Write custom header
        outfile.close(); // Close the file after creating it
    }
}

void appendToCSV(const std::string& filename, const std::string& imgName, const std::string& methodUsed,
                 int n_diff_colors, int k, int n, const std::string& compType, double time) {
    std::ofstream file(filename, std::ios::app); // Open file for appending
    if (!file.is_open()) {
        std::cerr << "Error opening file for appending!" << std::endl;
        return;
    }
    file << imgName << "," << methodUsed << "," << n_diff_colors << "," << k << "," << n << "," << compType << "," << time << std::endl;
}




int main(int argc, char *argv[])
{

    int deviceID;
    cudaGetDevice(&deviceID);
    cudaDeviceProp props;
    cudaGetDeviceProperties(&props, deviceID);
    std::cout << "Device: " << props.name << std::endl;


    int k;
    //std::string path;
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

    //std::cout << "Press a key to start the compression..."<< std::endl;
    //std::cin.ignore();
    std::cout << "Starting the Compression..." << std::endl;

    auto startKmeans = std::chrono::high_resolution_clock::now();


    kmeans.run();

    auto endKmeans = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedKmeans = endKmeans - startKmeans;

    FilesUtils::createOutputDirectories();

    FilesUtils::writeBinaryFile(outputPath, width, height, k, kmeans.getPoints(), kmeans.getCentroids());

    FilesUtils::writePerformanceEvaluation(outputPath, "CUDA", k, points, elapsedKmeans);


    // performanceData
    std::string filename = "performanceData.csv";
    createOrOpenCSV(filename);

    std::string imgName = extractFileName(outputPath);
    
    std::string compType;
    switch (typeCompressionChoice) {
        case 1:
            compType = "light";
            break;
        case 2:
            compType = "medium";
            break;
        case 3:
            compType = "heavy";
            break;
        default:
            std::cout << "something went wrong, typeCompressionChoice is not 1, 2 nor 3";
            exit(-1776);
            break;
    }

    appendToCSV(filename, imgName, "CUDA", different_colors_size, k, n_points, compType, elapsedKmeans.count());

    
    UtilsCLI::workDone();
    std::cout << "Compression done in " << elapsedKmeans.count() << std::endl;
    std::cout << std::endl;
    std::cout << "The compressed image has been saved in the outputs directory." << std::endl;


    cudaError_t lastError;
    lastError = cudaGetLastError();
    if (lastError != cudaSuccess) {
        std::cerr << "CUDA error: " << cudaGetErrorString(lastError) << std::endl;
    }


    std::string command = "sl";
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Error executing command: " << command << std::endl;
    }
    
    return 0;
}

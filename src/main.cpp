#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <sstream>
#include <random>
#include <thread>
#include <chrono>
#include "point.hpp"
#include "kMeans.hpp"
#include <mpi.h>


int main() {
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int k;
    std::string path;

     if(rank == 0)
    {
        
        std::cout << "#############################################################" << std::endl;
        std::cout << "#                                                           #" << std::endl;
        std::cout << "#           Parallel Kmeans Images Compressor               #" << std::endl;
        std::cout << "#                                                           #" << std::endl;
        std::cout << "#############################################################" << std::endl<< std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl<< std::endl;
        std::cout << "Please enter the number of colors you want to keep in the compressed image"<< std::endl;
        std::cout << "--> ";
        std::cin >> k;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Now please enter the global path of the image you want to compress" << std::endl<< std::endl;
        std::cout << "--> ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, path); 
        std::cout << std::endl;
        MPI_Bcast(path.data(), path.size() + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    } else {
        // Assuming a maximum size for the string
        const int maxStringLength = 200;
        char receivedString[maxStringLength];
        MPI_Bcast(receivedString, maxStringLength, MPI_CHAR, 0, MPI_COMM_WORLD);
        std::string receivedPath(receivedString);
        path = receivedPath;
    }
    MPI_Bcast(&k, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Read an image from file
    cv::Mat image = cv::imread(path);

    // Check if the image was loaded successfully
    while (image.empty()) {
        if (rank == 0)
        {
            std::cerr << "Error: Unable to load the image." << std::endl;
            std::cout << "Please enter the correct global path of the image you want to compress" << std::endl<< std::endl;
            std::cout << "--> ";
            std::getline(std::cin, path);
            std::cout << std::endl;
            MPI_Bcast(path.data(), path.size() + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
            cv::Mat image = cv::imread(path);
        }else{
            path = "";
            // Assuming a maximum size for the string
            const int maxStringLength = 100;
            char receivedString[maxStringLength];
            MPI_Bcast(receivedString, maxStringLength, MPI_CHAR, 0, MPI_COMM_WORLD);
            std::string receivedPath(receivedString);
            path = receivedPath;
            cv::Mat image = cv::imread(path);
        }
        std::cout<< "-------------------------" << path << std::endl;
    }
    std::vector<Point> points;

    // Get the image dimensions
    int height = image.rows;
    int width = image.cols;
    std::vector<cv::Vec3b> pixels;

    for(int y = 0 ; y < height ; y++)
    {
        for (int x = 0 ; x < width ; x++)
        {
            pixels.emplace_back(image.at<cv::Vec3b>(y, x));
            std::vector<double> rgb = {static_cast<double>(pixels.at(y * width + x)[0]), static_cast<double>(pixels.at(y * width + x)[1]), static_cast<double>(pixels.at(y * width + x)[2])};
            int id = y * width + x;
            Point pixel(id, rgb);
            points.push_back(pixel);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    KMeans kmeans(k, points);
    kmeans.run(rank, world_size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Display the image

    if(rank == 0)
    {
        cv::imshow("Original", image);
        cv::waitKey(1);
        for (Point &p : kmeans.getPoints())
        {
            pixels.at(p.id)[0] = p.centroidFeatures[0];
            pixels.at(p.id)[1] = p.centroidFeatures[1];
            pixels.at(p.id)[2] = p.centroidFeatures[2];
        }


        cv::Mat imageCompressed = cv::Mat(height, width, CV_8UC3);
        for(int y = 0 ; y < height ; y++)
        {
            for (int x = 0 ; x < width ; x++)
            {
                imageCompressed.at<cv::Vec3b>(y, x) = pixels.at(y * width + x);
            }
        }
        std::string outputPath = "outputImages/imageCompressed_" + std::to_string(k) + "_colors.jpg";
        cv::imwrite(outputPath, imageCompressed);
        std::ofstream outputFile("performanceEvaluation.txt", std::ios::app);
        outputFile << "--------------------------------------"<< std::endl;
        outputFile << "Image path: " << path << std::endl;
        outputFile << "Number of colors: " << k << std::endl;
        outputFile << "Number of points: " << points.size() << std::endl;
        outputFile << "Number of iterations: " << kmeans.numberOfIterationForConvergence << std::endl;
        outputFile << "Number of Processors: " << world_size << std::endl;
        outputFile << " ==>" << "Time: " << elapsed.count() << "s" << std::endl;
        outputFile << std::endl;
        outputFile << std::endl;
        outputFile << std::endl;
        
    }
    MPI_Finalize();
}


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

#include <opencv2/opencv.hpp>


int main(int argc, char *argv[]){

    int k;
    std::string path;
    std::string outputPath;
        
        std::cout << "##########################################################################################" << std::endl;
        std::cout << "#                                                                                        #" << std::endl;
        std::cout << "#                        Parallel Kmeans Images Encoder (omp)                            #" << std::endl;
        std::cout << "#                                                                                        #" << std::endl;
        std::cout << "##########################################################################################" << std::endl<< std::endl;
        std::cout << "------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "| This program allows you to compress an image by reducing the number of colors in it    |" << std::endl;
        std::cout << "| The output of this Encoder is a file .kc that you need to decode to obtain your image  |" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------" << std::endl<< std::endl;
        std::cout << "Please enter the number of colors you want to keep in the compressed image"<< std::endl;
        std::cout << "--> ";
        std::cin >> k;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Now please enter the global path of the image you want to compress" << std::endl;
        std::cout << "--> ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, path); // std::ws manages paths too long or with blankspaces
        std::cout << std::endl;
        std::cout << "Choose a name for your output (note that the output will be saved in the outputs directory)" << std::endl;
        std::cout << "You don't need to give any extension" << std::endl;
        std::cout << "--> ";
        std::getline(std::cin, outputPath);

        // create outputs if doesn't exist
        // Ensure "outputs" directory exists
        std::filesystem::path outputsDir = "./outputs";
        if (!std::filesystem::exists(outputsDir))
        {   std::cout << std::endl << "outputs directory doesn't exist, let's create it" << std::endl;

            if (!std::filesystem::create_directory(outputsDir))
            {
                std::cerr << "Error creating outputs directory." << std::endl;
                return 1; // Return an error code if directory creation fails
            }
        }

        outputPath = "./outputs/" + outputPath + ".kc";

    // Read an image from file
    cv::Mat image = cv::imread(path);

    // Check if the image was loaded successfully
    while (image.empty()) {
            std::cerr << "Error: Unable to load the image." << std::endl;
            std::cout << "Please enter the correct global path of the image you want to compress" << std::endl<< std::endl;
            std::cout << "--> ";
            std::getline(std::cin, path);
            std::cout << std::endl;
            cv::Mat image = cv::imread(path);
        std::cout<< "-------------------------" << path << std::endl;
    }
    std::vector<Point> points;

    // Get the image dimensions
    int height = image.rows;
    int width = image.cols;
        std::cout << "Creating the data structure..." << std::endl;
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
        std::cout << "Starting the Compression..." << std::endl;
    
    KMeans kmeans(k, points);
    kmeans.run();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Display the image
 
        std::cout << std::endl;
        std::cout << "Saving the Compressed Image..." << std::endl;
        std::ofstream outputFile(outputPath, std::ios::app);
        outputFile  << width << ","<< height << "," << k << std::endl;
        for (int i = 0 ; i < k ; i++)
        {
            outputFile << kmeans.getCentroids()[i].features[0];
            outputFile << ",";
            outputFile << kmeans.getCentroids()[i].features[1];
            outputFile << ",";
            outputFile << kmeans.getCentroids()[i].features[2] << std::endl;
        }

        // this is the part that takes a lot of time
        for (Point &p : kmeans.getPoints())
        {
            outputFile << p.clusterId << std::endl;
        }
        
            

        // cv::Mat imageCompressed = cv::Mat(height, width, CV_8UC3);
        // for(int y = 0 ; y < height ; y++)
        // {
        //     for (int x = 0 ; x < width ; x++)
        //     {
        //         imageCompressed.at<cv::Vec3b>(y, x) = pixels.at(y * width + x);
        //     }
        // }
        // std::string outputPath = "outputImages/imageCompressed_" + std::to_string(k) + "_colors.jpg";
        // cv::imwrite(outputPath, imageCompressed);

        std::ofstream perfEval("performanceEvaluation.txt", std::ios::app);
        perfEval << argv[0] << std::endl;
        perfEval << "--------------------------------------"<< std::endl;
        perfEval << "Image path: " << path << std::endl;
        perfEval << "Number of colors: " << k << std::endl;
        perfEval << "Number of points: " << points.size() << std::endl;
        perfEval << "Number of iterations: " << kmeans.numberOfIterationForConvergence << std::endl;
        perfEval << " ==>" << "Time: " << elapsed.count() << "s" << std::endl;
        perfEval << std::endl;
        perfEval << std::endl;
        perfEval << std::endl;

        // cv::imshow("Original", image);
        // cv::waitKey(1);
        // cv::imshow("Compressed", imageCompressed);
        // cv::waitKey(0);

        std::cout << std::endl;
        std::cout << "Work done!" << std::endl;
}

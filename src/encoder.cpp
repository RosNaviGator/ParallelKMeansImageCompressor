
#include <iostream>
#include <string>
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

#include <opencv2/opencv.hpp>


void useCallArguments(int &k, std::string &path, std::string &outputPath, char *argv[])
{

    // set number of clusters
    k = std::stoi(argv[2]); // if you wrote arguments in inverted order, it will crash (works as sanity check)

    // set path
    path = argv[1];

    // EXTRACT OUTPUT NAME FROM INPUT STRING

    // Find the position of the last '/' in the path
    size_t lastSlashPos = path.find_last_of('/');
    
    // Extract the substring after the last '/'
    std::string fileName = path.substr(lastSlashPos + 1);
    
    // Find the position of the last '.' in the filename
    size_t lastDotPos = fileName.find_last_of('.');
    
    // Extract the substring before the last '.'
    outputPath = fileName.substr(0, lastDotPos);

    // debug
    // std::cout << std::endl << outputPath << std::endl;
}



int main(int argc, char *argv[])
{

    int k;
    std::string path;
    std::string outputPath;

    // we can run the function with no argv or with two (needed for pefromance evaluation)
    if (3 < argc || 2 == argc)
    {
        std::cout << "Wrong number of arguments!\n"
                  << "Either no arguments (you will be asked to prompt info at runtime) or the following two:\n"
                  << "./seqEncoder <path_to_image> <number_of_colors>"
                  << std::endl
                  << std::endl;
        return 1;
    }
  
    if (3 == argc)
    {
        useCallArguments(k, path, outputPath, argv);
    }

    // if no arguments were given, we'll ask them at runtime
    if (1 == argc)
    {

        std::cout << "##########################################################################################" << std::endl;
        std::cout << "#                                                                                        #" << std::endl;
        std::cout << "#                    Parallel Kmeans Images Encoder (Sequential)                         #" << std::endl;
        std::cout << "#                                                                                        #" << std::endl;
        std::cout << "##########################################################################################" << std::endl
                  << std::endl;
        std::cout << "------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "| This program allows you to compress an image by reducing the number of colors in it    |" << std::endl;
        std::cout << "| The output of this Encoder is a file .kc that you need to decode to obtain your image  |" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------" << std::endl
                  << std::endl;
        std::cout << "Please enter the number of colors you want to keep in the compressed image" << std::endl;
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
    }

    // -----------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------

    // FOLLOWS CODE COMMON TO THE TWO VARIANTS OF INPUT

    // -----------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------

    // I need to retrieve executable path so that output paths don't get messed up

    // Obtain the path of the executable file
    std::filesystem::path exePath = std::filesystem::canonical("/proc/self/exe");
    // Get the parent path of the executable, which represents the directory containing the executable
    std::filesystem::path buildPath = exePath.parent_path();

    // create outputs if doesn't exist
    // Ensure "outputs" directory exists
    std::filesystem::path outputsDir = buildPath / ".." / "outputs";
    if (!std::filesystem::exists(outputsDir))
    {
        std::cout << std::endl
                  << "outputs directory doesn't exist, let's create it" << std::endl;

        if (!std::filesystem::create_directory(outputsDir))
        {
            std::cerr << "Error creating outputs directory." << std::endl;
            return 1; // Return an error code if directory creation fails
        }
    }

    // create output file path and extension
    outputPath = buildPath / ".." / "outputs" / outputPath;
    outputPath += ".kc";

    // -----------------------------------------------------------------------------------------
    // FIRST PART: reading (may have sense to evaluate performance if we parallelize)

    // Read an image from file
    cv::Mat image = cv::imread(path); // CAN BE PARALLELIZED IN OpenMP and CUDA! (with a gui or with a parallel region?)

    // Check if the image was loaded successfully
    while (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        std::cout << "Please enter the correct global path of the image you want to compress" << std::endl
                  << std::endl;
        std::cout << "--> ";
        std::getline(std::cin, path);
        std::cout << std::endl;
        cv::Mat image = cv::imread(path);
        std::cout << "-------------------------" << path << std::endl;
    }

    // -----------------------------------------------------------------------------------------
    // SECOND PART: creating the points structure

    std::vector<Point> points;

    // Get the image dimensions
    int height = image.rows;
    int width = image.cols;

    // CREATING DATA STRUCTURE (first time evaluation)
    std::cout << "Creating the data structure..." << std::endl;
    auto startPixels = std::chrono::high_resolution_clock::now();

    std::vector<cv::Vec3b> pixels;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            pixels.emplace_back(image.at<cv::Vec3b>(y, x));
            std::vector<double> rgb = {static_cast<double>(pixels.at(y * width + x)[0]), static_cast<double>(pixels.at(y * width + x)[1]), static_cast<double>(pixels.at(y * width + x)[2])};
            int id = y * width + x;
            Point pixel(id, rgb);
            points.push_back(pixel);
        }
    }

    auto endPixels = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedPixels = endPixels - startPixels;

    // -----------------------------------------------------------------------------------------
    // THIRD PART: kmeans clustering
    KMeans kmeans(k, points);

    // CLUSTERING (second time evaluation)
    std::cout << "Starting the Compression..." << std::endl;
    auto startKmeans = std::chrono::high_resolution_clock::now();

    kmeans.run();

    auto endKmeans = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedKmeans = endKmeans - startKmeans;

    /*
    // -----------------------------------------------------------------------------------------
    // FOURTH PART: saving encoded data (ENCODING STILL HAS TO BE CORRECTED)

    std::cout << std::endl;
    std::cout << "Saving the Compressed Image..." << std::endl;
    std::ofstream outputFile(outputPath, std::ios::trunc);
    outputFile << width << "," << height << "," << k << std::endl;
    for (int i = 0; i < k; i++)
    {
        outputFile << kmeans.getCentroids()[i].features[0];
        outputFile << ",";
        outputFile << kmeans.getCentroids()[i].features[1];
        outputFile << ",";
        outputFile << kmeans.getCentroids()[i].features[2] << std::endl;
    }


    // CREATING OUTPUT FILE .kc (third time evaluation)
    auto startEncoding = std::chrono::high_resolution_clock::now();

    for (Point &p : kmeans.getPoints())
    {
        outputFile << p.clusterId << std::endl; // this is the part that takes a lot of time
    }


    auto endEncoding = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedEncoding = endEncoding - startEncoding;

    */

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

    // -----------------------------------------------------------------------------------------
    // ***NEW*** PART: opencv jpeg compression

    std::cout << "Saving the Compressed Image..." << std::endl;
    auto startCompression = std::chrono::high_resolution_clock::now();

    std::vector<cv::Vec3b> newPixels;
    for (Point &p : kmeans.getPoints())
    {
        for (int i = 0; i < k; i++)
        {
            if (p.clusterId == i)
            {
                newPixels.emplace_back(cv::Vec3b(static_cast<uchar>(kmeans.getCentroids()[i].features[0]),
                                                 static_cast<uchar>(kmeans.getCentroids()[i].features[1]),
                                                 static_cast<uchar>(kmeans.getCentroids()[i].features[2])));
            }
        }
    }

    auto endCompression = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedCompression = endCompression - startCompression;

    // we now need to create a new image with the new pixels
    cv::Mat imageCompressed = cv::Mat(height, width, CV_8UC3);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            imageCompressed.at<cv::Vec3b>(y, x) = newPixels.at(y * width + x);
        }
    }

    // we now need to save the image
    std::string outputPathJpeg = buildPath / ".." / "outputs" / outputPath;
    // remove .kc extension
    outputPathJpeg.erase(outputPathJpeg.size() - 3, 3);
    outputPathJpeg = outputPathJpeg + "-Compr-seq-k" + std::to_string(k) + ".jpg";

    cv::imwrite(outputPathJpeg, imageCompressed);

    // -----------------------------------------------------------------------------------------
    // FIFTH PART: write performance evaluation files

    // create performSheet if doesn't exist
    // Ensure "performSheet" directory exists
    std::filesystem::path sheetsDir = buildPath / ".." / "performSheet";
    if (!std::filesystem::exists(sheetsDir))
    {
        std::cout << std::endl
                  << "performSheet directory doesn't exist, let's create it" << std::endl;

        if (!std::filesystem::create_directory(sheetsDir))
        {
            std::cerr << "Error creating outputs directory." << std::endl;
            return 1; // Return an error code if directory creation fails
        }
    }

    // save in a file the times:

    // we need image file name
    // EXTRACT OUTPUT NAME FROM INPUT STRING
    // Find the position of the last '/' in the path
    size_t lastSlashPos = path.find_last_of('/');
    // Extract the substring after the last '/'
    std::string fileName = path.substr(lastSlashPos + 1);
    // Find the position of the last '.' in the filename
    size_t lastDotPos = fileName.find_last_of('.');
    // Extract the substring before the last '.'
    std::string imgName = fileName.substr(0, lastDotPos);

    std::ofstream outFile(buildPath / ".." / "performSheet/kcPerformSheet.csv", std::ios_base::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << imgName << ","
                << k << ","
                << argv[0] << ","
                << std::fixed << std::setprecision(20) << elapsedPixels.count() << ","
                << std::fixed << std::setprecision(20) << elapsedKmeans.count() << ","
                << std::fixed << std::setprecision(20) << elapsedCompression.count() << ","
                << std::endl;

        outFile.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }

    std::ofstream perfEval(buildPath / ".." / "performanceEvaluation.txt", std::ios::app);
    perfEval << argv[0] << std::endl;
    perfEval << "--------------------------------------" << std::endl;
    perfEval << "Image path: " << path << std::endl;
    perfEval << "Number of colors: " << k << std::endl;
    perfEval << "Number of points: " << points.size() << std::endl;
    perfEval << "Number of iterations: " << kmeans.numberOfIterationForConvergence << std::endl;
    perfEval << " ==>"
             << "Kmeans time: " << elapsedKmeans.count() << "s" << std::endl;
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

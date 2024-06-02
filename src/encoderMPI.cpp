#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <sstream>
#include <random>
#include <thread>
#include <memory>
#include <set>
#include <chrono>

#include <point.hpp>
#include <kMeansMPI.hpp>
#include <configReader.hpp>
#include <utilsCLI.hpp>
#include <imagesUtils.hpp>
#include <filesUtils.hpp>

#include <mpi.h>

std::string extractFileName(const std::string &outputPath)
{
    // Find the position of the last '/' character
    size_t lastSlashPos = outputPath.find_last_of('/');

    // Find the position of the ".kc" extension
    size_t extensionPos = outputPath.find(".kc");

    // If both positions are found
    if (lastSlashPos != std::string::npos && extensionPos != std::string::npos)
    {
        // Extract the substring between the last '/' and ".kc"
        return outputPath.substr(lastSlashPos + 1, extensionPos - lastSlashPos - 1);
    }

    // If either position is not found, return an empty string
    return "";
}

void createOrOpenCSV(const std::string &filename)
{
    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::ofstream outfile(filename);
        if (!outfile.is_open())
        {
            std::cerr << "Error creating file!" << std::endl;
            return;
        }
        outfile << "img, method, staring colors, k, n_points, comp type, time" << std::endl; // Write custom header
        outfile.close();                                                                     // Close the file after creating it
    }
}

void appendToCSV(const std::string &filename, const std::string &imgName, const std::string &methodUsed,
                 int n_diff_colors, int k, int n, const std::string &compType, double time)
{
    std::ofstream file(filename, std::ios::app); // Open file for appending
    if (!file.is_open())
    {
        std::cerr << "Error opening file for appending!" << std::endl;
        return;
    }
    file << imgName << "," << methodUsed << "," << n_diff_colors << "," << k << "," << n << "," << compType << "," << time << std::endl;
}

int main(int argc, char *argv[])
{
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int k;
    int n_points;
    std::vector<Point> points;
    std::string path;
    std::string outputPath;
    int height;
    int width;
    std::vector<std::pair<int, Point>> local_points;
    int levelsColorsChioce;
    int typeCompressionChoice;
    ConfigReader configReader;
    long long int batch_size = configReader.getBatchSize();
    cv::Mat image;
    int different_colors_size;

    if (rank == 0)
    {
        UtilsCLI::compressionChoices(levelsColorsChioce, typeCompressionChoice, outputPath, image, 2);

        int originalHeight = image.rows;
        int originalWidth = image.cols;

        ImageUtils::preprocessing(image, typeCompressionChoice);

        height = image.rows;
        width = image.cols;

        std::set<std::vector<unsigned char>> different_colors;

        ImageUtils::pointsFromImage(image, points, different_colors);

        n_points = points.size();

        ImageUtils::defineKValue(k, levelsColorsChioce, different_colors);

        different_colors_size = different_colors.size();

        UtilsCLI::printCompressionInformations(originalWidth, originalHeight, width, height, k, different_colors_size);
    }

    MPI_Bcast(&k, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n_points, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int points_per_cluster = n_points / world_size;

    for (int i = 0; i < n_points; i++)
    {

        if (rank == 0)
        {
            for (int j = 0; j < world_size; j++)
            {
                int start = j * points_per_cluster;
                int end = (j == world_size - 1) ? n_points : (j + 1) * points_per_cluster;

                if (i >= start && i < end)
                {
                    MPI_Send(&i, 1, MPI_INT, j, 1, MPI_COMM_WORLD);
                    MPI_Send(&points.at(i).getFeature(0), 1, MPI_UNSIGNED_CHAR, j, 2, MPI_COMM_WORLD);
                    MPI_Send(&points.at(i).getFeature(1), 1, MPI_UNSIGNED_CHAR, j, 3, MPI_COMM_WORLD);
                    MPI_Send(&points.at(i).getFeature(2), 1, MPI_UNSIGNED_CHAR, j, 4, MPI_COMM_WORLD);
                }
            }
        }

        int start = rank * points_per_cluster;
        int end = (rank == world_size - 1) ? n_points : (rank + 1) * points_per_cluster;

        if (i >= start && i < end)
        {
            int id;
            std::vector<int> rgb(3);
            unsigned char r, g, b;
            MPI_Recv(&id, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&r, 1, MPI_UNSIGNED_CHAR, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&g, 1, MPI_UNSIGNED_CHAR, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&b, 1, MPI_UNSIGNED_CHAR, 0, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            rgb.at(0) = static_cast<int>(r);
            rgb.at(1) = static_cast<int>(g);
            rgb.at(2) = static_cast<int>(b);
            Point pixel(id, rgb);
            local_points.push_back({0, pixel});
        }
    }

    if (rank == 0)
    {
        //std::cout << "Press a key to start the compression..." << std::endl;
        //std::cin.ignore();
        std::cout << "Starting the Compression..." << std::endl;
    }

    std::unique_ptr<KMeans> kmeans;

    if (rank == 0)
    {
        kmeans = std::unique_ptr<KMeans>(new KMeans(k, rank, 3, points, batch_size));
    }
    else
    {
        kmeans = std::unique_ptr<KMeans>(new KMeans(k, rank, 3, batch_size));
    }
    auto start = std::chrono::high_resolution_clock::now();
    kmeans->run(rank, world_size, local_points);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Display the image

    if (rank == 0)
    {
        FilesUtils::createOutputDirectories();

        FilesUtils::writeBinaryFile(outputPath, width, height, k, kmeans->getPoints(), kmeans->getCentroids());

        FilesUtils::writePerformanceEvaluation(outputPath, "MPI", k, points, elapsed);

        // performanceData
        std::string filename = "performanceData.csv";
        createOrOpenCSV(filename);

        std::string imgName = extractFileName(outputPath);

        std::string compType;
        switch (typeCompressionChoice)
        {
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

        appendToCSV(filename, imgName, "MPI", different_colors_size, k, n_points, compType, elapsed.count());


        UtilsCLI::workDone();
        std::cout << "Compression done in " << elapsed.count() << std::endl;
        std::cout << std::endl;
        std::cout << "The compressed image has been saved in the outputs directory." << std::endl;
    }
    MPI_Finalize();
}

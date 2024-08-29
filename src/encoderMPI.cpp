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

#include <performanceEvaluation.hpp>
#include <span>

using namespace km;
using namespace km::filesUtils;
using namespace km::utilsCLI;
using namespace km::imageUtils;


auto main(int argc, char *argv[]) -> int
{
    MPI_Init(NULL, NULL);
    int world_size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int k = 0;
    int n_points = 0;
    std::vector<Point> points;
    std::string path = "";
    std::string outputPath = "";
    std::string fileName = "";
    int height = 0;
    int width = 0;
    std::vector<std::pair<int, Point>> local_points;
    int levelsColorsChioce = 0;
    int typeCompressionChoice = 0;
    ConfigReader configReader;
    cv::Mat image;
    size_t different_colors_size = 0;
    Performance performance;

    if (rank == 0)
    {
        auto args = std::span(argv, size_t(argc));
        if (4 == argc)
        {
            path = std::string(args[1]);
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

            performance.fillPerformance(typeCompressionChoice, fileName, "MPI");
        }
        else
        {
            std::cerr << "Error: Invalid number of arguments." << std::endl;
            MPI_Finalize();
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

        different_colors_size = different_colors.size();

        printCompressionInformations(originalWidth, originalHeight, width, height, k, different_colors_size);
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
            int id = 0;
            std::vector<int> rgb(3);
            unsigned char r = 0, g = 0, b = 0;
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
        // std::cout << "Press a key to start the compression..." << std::endl;
        // std::cin.ignore();
        std::cout << "Starting the Compression..." << std::endl;
    }


    std::unique_ptr<KMeansMPI> kmeans;

    if (rank == 0)
    {
        kmeans = std::unique_ptr<KMeansMPI>(new KMeansMPI(k, points, local_points));
    }
    else
    {
        
        kmeans = std::unique_ptr<KMeansMPI>(new KMeansMPI(k, local_points));
    }

    auto start = std::chrono::high_resolution_clock::now();
    kmeans->run();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    if (rank == 0)
    {
        createOutputDirectories();

        writeBinaryFile(outputPath, width, height, k, kmeans->getPoints(), kmeans->getCentroids());

        // write perfomance data to csv
        if (4 == argc)
        {
            performance.writeCSV(different_colors_size, k, n_points, elapsed.count(), kmeans->getIterations(), world_size);
        }

        workDone();
        std::cout << "Compression done in " << elapsed.count() << std::endl;
        std::cout << std::endl;
        std::cout << "The compressed image has been saved in the outputs directory." << std::endl;
    }
    MPI_Finalize();
}

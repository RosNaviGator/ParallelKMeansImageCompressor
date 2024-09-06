/**
 * @file mainMenu.cpp
 * @brief Main entry point for the Image Compressor application.
 * @details This file contains the main function that initializes the Image Compressor application. 
 *          It reads configuration settings, displays a command-line interface for users to choose 
 *          between image compression and decompression, and handles user input to run the appropriate 
 *          compression or decompression processes.
 */

#include <iostream>
#include <utilsCLI.hpp>
#include <filesystem>
#include <configReader.hpp>
#include <boost/process.hpp>

using namespace km;
using namespace km::utilsCLI;
using namespace km::filesUtils;

/**
 * @brief Main function that runs the Image Compressor application.
 * @details This function initializes necessary components, reads configuration settings, and provides 
 *          a command-line interface for users to choose between image compression and decompression options.
 *          It handles user inputs to determine the desired operation and calls the appropriate functions 
 *          or external processes to execute the selected option.
 * 
 * @return Returns 0 on successful execution.
 */

auto main() -> int
{
    namespace bp = boost::process;
    int color_choice = 0 ;
    int compressionChoice = 0;
    std::filesystem::path inputImageFilePath;
    ConfigReader configReader;
    color_choice = configReader.getColorChoice();
    compressionChoice = configReader.getCompressionChoice();
    inputImageFilePath = configReader.getInputImageFilePath();
    
    mainMenuHeader();
    int encodeOrDecode = 0;
    std::filesystem::path cuda_path = "./build/cudaEncoder";
    std::cout << "This is the Main Menu of the Image Compressor! What do you want to do?" << "\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout   << "(1)\tCompress an image \t \t \t \t \t (2)\tDecode a .kc file\n";
    std::cout << "\n";
    std::cin >> encodeOrDecode;
    while (std::cin.fail() || (encodeOrDecode != 1 && encodeOrDecode != 2)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Invalid input. Please enter 1 or 2: ";
        std::cin >> encodeOrDecode;
    }
    std::cout << "\n";

    if(encodeOrDecode == 2)
    {
        bp::system("./build/decoder");
    }else if (encodeOrDecode == 1)                      
    {
        std::cout << "You chose to compress an image!"<< "\n";
        std::cout << "\n";

        if (inputImageFilePath.empty())
        {
            std::cout << "Please enter the path of the image you want to compress: ";
            std::cin >> inputImageFilePath;
            std::cout << "\n";
            while (!std::filesystem::exists(inputImageFilePath)) {
                std::cout << "The path you entered does not exist. Please enter a valid path: ";
                std::cin >> inputImageFilePath;
                std::cout << "\n";
            }
        }else
        {
            std::cout << "The path of the image you want to compress is: " << inputImageFilePath.string() << "\n";
            std::cout << "\n";
        }
        if(color_choice==0)
        { 
            std::cout << "Now you can select the desired level of color preservation for your image:\n"
                    << "*You can modiify the percentage of colors preserved for each level in the config file*" << std::endl
                    << "\n"
                    << "(1)\tLow color preservation\n"
                    << "(2)\tMedium-low color preservation\n"
                    << "(3)\tModerate color preservation\n"
                    << "(4)\tMedium-high color preservation\n"
                    << "(5)\tHigh color preservation\n"
                    << "\n"
                    << "Please choose the level that best fits your needs" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cin >> color_choice;
            const int MIN_COLOR_CHOICE = 1;
            const int MAX_COLOR_CHOICE = 5;
            while (std::cin.fail() || (color_choice < MIN_COLOR_CHOICE || color_choice > MAX_COLOR_CHOICE)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid input. Please choose a level between 1 and 5 ";
                std::cin >> encodeOrDecode;
            }
        }else
        {
            std::cout << "The color preservation level you chose is: " << color_choice << "\n";
            std::cout << "\n";
        }
        if(compressionChoice==0)
        {
            std::cout << "Perfect! Now let's choose the type of compression for your image." << std::endl
                    << "\n"
                    << "(1)\tLight Compression (it may take more time but the result will be more defined) <-- Suggested for Small Images\n"
                    << "(2)\tMedium Compression (it applies chroma subsampling to reduce the dimension of the image and the time needed for the computation)\n"
                    << "(3)\tHeavy Compression (it applies chroma subsampling and image resizing) <-- Suggested for Big Images\n";
            std::cout << std::endl;
            std::cout << std::endl;

            std::cin >> compressionChoice;
            const int MIN_COMPRESSION_CHOICE = 1;
            const int MAX_COMPRESSION_CHOICE = 3;
            while (std::cin.fail()|| (compressionChoice < MIN_COMPRESSION_CHOICE || compressionChoice > MAX_COMPRESSION_CHOICE)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid input. Please choose a type between 1 and 3." << std::endl;
                std::cin >> compressionChoice;
            }
        }

        std::cout << "Now please choose what type of compressor you want to use:" << "\n";
        std::cout << "\n";
        std::cout << "(1)\tSequential Compressor \n";
        std::cout << "(2)\tMPI Compressor \n";
        std::cout << "(3)\tOpenMP Compressor \n";
        if(std::filesystem::exists(cuda_path))
        {
            std::cout << "(4)\tCUDA Compressor \n";
        }else
        {
            std::cout << "CUDA Compressor not available, make sure you have complied the program with the right flag!\n";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        int compressorChoice = 0;
        std::cin >> compressorChoice;
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input";
            std::cin >> compressorChoice;
        }
        if(std::filesystem::exists(cuda_path))
        {
            while ((compressorChoice != 1 && compressorChoice != 2 && compressorChoice != 3 && compressorChoice != 4) || std::cin.fail()) 
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid input. Please enter a number between 1 and 4: ";
                std::cin >> compressorChoice;    
            }
        }else{
            while ((compressorChoice != 1 && compressorChoice != 2 && compressorChoice != 3) || std::cin.fail()) 
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid input. Please enter a number between 1 and 3: ";
                std::cin >> compressorChoice;
            
            }
        }
        std::string command;
        if (compressorChoice == 1)
        {
            command = "./build/seqEncoder ";
        }else if (compressorChoice == 2)
        {
            mainMenuHeader();
            std::cout << "You chose the MPI compressor!" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "Now please choose the number of cores you want to use for the computation" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            int cores = 0;
            std::cin >> cores;
            while (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid input. Please enter a number: ";
                std::cin >> cores;
            }
            command = "mpirun -np " + std::to_string(cores) + " ./build/mpiEncoder ";
        }else if (compressorChoice == 3)
        {
            command = "./build/ompEncoder ";
        }
        else if (compressorChoice == 4)
        {
            command = "./build/cudaEncoder ";
        }

        command += inputImageFilePath.string() + " " + std::to_string(color_choice) + " " + std::to_string(compressionChoice);
        bp::system(command);
    }

    
}

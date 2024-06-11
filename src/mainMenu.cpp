#include <iostream>
#include <utilsCLI.hpp>
#include <filesystem>
int main(int argc, char** nargv)
{
    
    UtilsCLI::mainMenuHeader();
    int encodeOrDecode;
    std::filesystem::path cuda_path = "./build/cudaEncoder";
    std::cout << "This is the Main Menu of the Image Compressor! What do you want to do?" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout   << "(1)\tCompress an image \t \t \t \t \t (2)\tDecode a .kc file\n";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cin >> encodeOrDecode;
    while (encodeOrDecode != 1 && encodeOrDecode != 2) {
        std::cout << "Invalid input. Please enter 1 or 2: ";
        std::cin >> encodeOrDecode;
    }
    std::cout << std::endl;

    if(encodeOrDecode == 2)
    {
        std::system("./build/decoder");
    }else if (encodeOrDecode == 1)
    {
        UtilsCLI::mainMenuHeader();
        std::cout << "You chose to compress an image!" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Now please choose what type of compressor you want to use:" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        int compressorChoice;
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
        std::cin >> compressorChoice;
        if(std::filesystem::exists(cuda_path))
        {
            while (compressorChoice != 1 && compressorChoice != 2 && compressorChoice != 3 && compressorChoice != 4) {
            std::cout << "Invalid input. Please enter 1, 2, 3 or 4: ";
            std::cin >> compressorChoice;
        }else{
            while (compressorChoice != 1 && compressorChoice != 2 && compressorChoice != 3) {
            std::cout << "Invalid input. Please enter 1, 2 or 3: ";
            std::cin >> compressorChoice;
        }
        
        if (compressorChoice == 1)
        {
            std::system("./build/seqEncoder");
        }else if (compressorChoice == 2)
        {
            UtilsCLI::mainMenuHeader();
            std::cout << "You chose the MPI compressor!" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "Now please choose the number of cores you want to use for the computation" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            int cores;
            std::cin >> cores;
            std::string mpiCommand = "mpirun -np " + std::to_string(cores) + " ./build/mpiEncoder";
            std::system(mpiCommand.c_str());
        }else if (compressorChoice == 3)
        {
            std::system("./build/ompEncoder");
        }
        else if (compressorChoice == 4)
        {
            std::system("./build/cudaEncoder");
        }
        
    }

    
}

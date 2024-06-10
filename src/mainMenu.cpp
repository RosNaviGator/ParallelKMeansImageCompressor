#include <iostream>
#include <utilsCLI.hpp>
auto main(int argc, char **nargv) -> int
{
    
    UtilsCLI::mainMenuHeader();
    int encodeOrDecode=0;
    std::cout << "This is the Main Menu of the Image Compressor! What do you want to do?" << '\n';
    std::cout << '\n';
    std::cout << '\n';
    std::cout   << "(1)\tCompress an image \t \t \t \t \t (2)\tDecode a .kc file\n";
    std::cout << '\n';
    std::cout << '\n';
    std::cin >> encodeOrDecode;
    while (encodeOrDecode != 1 && encodeOrDecode != 2) {
        std::cout << "Invalid input. Please enter 1 or 2: ";
        std::cin >> encodeOrDecode;
    }
    std::cout << '\n';

    if(encodeOrDecode == 2)
    {
        std::system("./build/decoder");
    }else if (encodeOrDecode == 1)
    {
        UtilsCLI::mainMenuHeader();
        std::cout << "You chose to compress an image!" << '\n';
        std::cout << '\n';
        std::cout << '\n';
        std::cout << "Now please choose what type of compressor you want to use:" << '\n';
        std::cout << '\n';
        std::cout << '\n';
        int compressorChoice=0;
        std::cout << "(1)\tSequential Compressor \n";
        std::cout << "(2)\tMPI Compressor \n";
        std::cout << "(3)\tOpenMP Compressor \n";
        std::cout << '\n';
        std::cout << '\n';
        std::cin >> compressorChoice;
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
            std::cout << "You chose the MPI compressor!" << '\n';
            std::cout << '\n';
            std::cout << '\n';
            std::cout << "Now please choose the number of cores you want to use for the computation" << '\n';
            std::cout << '\n';
            std::cout << '\n';
            int cores=0;
            std::cin >> cores;
            std::string mpiCommand = "mpirun -np " + std::to_string(cores) + " ./build/mpiEncoder";
            std::system(mpiCommand.c_str());
        }else if (compressorChoice == 3)
        {
            std::system("./build/ompEncoder");
        }
        
    }

    return 0;

    
}

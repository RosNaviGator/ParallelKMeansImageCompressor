/**
 * @file utilsCLI.cpp
 * @brief Utility functions for command-line interface operations.
 * @details This file contains implementations of utility functions that facilitate command-line interactions 
 *          for the Image Compressor application. It includes functions to display headers, manage user inputs, 
 *          and provide feedback during compression and decompression processes.
 */


#include <utilsCLI.hpp>

void km::utilsCLI::mainMenuHeader()
{
    namespace bp = boost::process;
    bp::system("clear -x");
            std::cout
        << "  _____                _ _      _   _  __                                  _____                                                   \n";
    std::cout << " |  __ \\              | | |    | | | |/ /                                 / ____|                                                  \n";
    std::cout << " | |__) |_ _ _ __ __ _| | | ___| | | ' / _ __ ___   ___  __ _ _ __  ___  | |     ___  _ __ ___  _ __  _ __ ___  ___ ___  ___  _ __ \n";
    std::cout << " |  ___/ _` | '__/ _` | | |/ _ \\ | |  < | '_ ` _ \\ / _ \\/ _` | '_ \\/ __| | |    / _ \\| '_ ` _ \\| '_ \\| '__/ _ \\/ __/ __|/ _ \\| '__|\n";
    std::cout << " | |  | (_| | | | (_| | | |  __/ | | . \\| | | | | |  __/ (_| | | | \\__ \\ | |___| (_) | | | | | | |_) | | |  __/\\__ \\__ \\ (_) | |   \n";
    std::cout << " |_|   \\__,_|_|  \\__,_|_|_|\\___|_| |_|\\_\\_| |_| |_|\\___|\\__,_|_| |_|___/  \\_____\\___/|_| |_| |_| .__/|_|  \\___||___/___/\\___/|_|   \n";
    std::cout << "                                                                                               | |                                 \n";
    std::cout << "                                                                                               |_|                                 \n";
    std::cout << std::endl;
    std::cout << std::endl;
}

void km::utilsCLI::decoderHeader()
{
    namespace bp = boost::process;
    bp::system("clear -x");
            std::cout
        << "  _____                _ _      _   _  __                                  _____                                                   \n";
    std::cout << " |  __ \\              | | |    | | | |/ /                                 / ____|                                                  \n";
    std::cout << " | |__) |_ _ _ __ __ _| | | ___| | | ' / _ __ ___   ___  __ _ _ __  ___  | |     ___  _ __ ___  _ __  _ __ ___  ___ ___  ___  _ __ \n";
    std::cout << " |  ___/ _` | '__/ _` | | |/ _ \\ | |  < | '_ ` _ \\ / _ \\/ _` | '_ \\/ __| | |    / _ \\| '_ ` _ \\| '_ \\| '__/ _ \\/ __/ __|/ _ \\| '__|\n";
    std::cout << " | |  | (_| | | | (_| | | |  __/ | | . \\| | | | | |  __/ (_| | | | \\__ \\ | |___| (_) | | | | | | |_) | | |  __/\\__ \\__ \\ (_) | |   \n";
    std::cout << " |_|___\\__,_|_|  \\__,_|_|_|\\___|_| |_|\\_\\_| |_| |_|\\___|\\__,_|_| |_|___/  \\_____\\___/|_| |_| |_| .__/|_|  \\___||___/___/\\___/|_|   \n";
    std::cout << " |  __ \\                   | |                                                                 | |                                 \n";
    std::cout << " | |  | | ___  ___ ___   __| | ___ _ __                                                        |_|                                 \n";
    std::cout << " | |  | |/ _ \\/ __/ _ \\ / _` |/ _ \\ '__|                                                                                           \n";
    std::cout << " | |__| |  __/ (_| (_) | (_| |  __/ |                                                                                              \n";
    std::cout << " |_____/ \\___|\\___\\___/ \\__,_|\\___|_|                                                                                              \n";
    std::cout << "                                                                                                                                    \n";
    std::cout << "                                                                                                                                    \n";
}

void km::utilsCLI::workDone()
{
    namespace bp = boost::process;
    bp::system("clear -x");
            std::cout
        << " __          __        _      _____                     _ \n"
           " \\ \\        / /       | |    |  __ \\                   | |\n"
           "  \\ \\  /\\  / /__  _ __| | __ | |  | | ___  _ __   ___  | |\n"
           "   \\ \\/  \\/ / _ \\| '__| |/ / | |  | |/ _ \\| '_ \\ / _ \\ | |\n"
           "    \\  /\\  / (_) | |  |   <  | |__| | (_) | | | |  __/ |_|\n"
           "     \\/  \\/ \\___/|_|  |_|\\_\\ |_____/ \\___/|_| |_|\\___| (_)\n"
           "                                                          \n"
           "                                                          \n";
    std::cout << std::endl;
    std::cout << std::endl;
}

void km::utilsCLI::printCompressionInformations(int &originalWidth, int &originalHeight, int &width, int &height, int &k, size_t &different_colors_size)
{
    std::cout << "Your original image was " << originalWidth << "x" << originalHeight << " pixels and it has " << different_colors_size << " different colors." << std::endl;
    std::cout << std::endl;
    std::cout << "The compressed image will be " << width << "x" << height << " pixels and it will have " << k << " different colors." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void km::utilsCLI::displayDecodingMenu(std::string &path, std::vector<std::filesystem::path> &imageNames, std::filesystem::path &decodeDir)
{
    std::cout << "Select an image:" << std::endl;
    std::cout << std::endl;
    for (size_t i = 0; i < imageNames.size(); ++i)
    {
        std::cout << "(" << i + 1 << ") " << imageNames[i] << std::endl;
    }

    int choice = 0;
    std::cout << std::endl
              << "Enter your choice (write only the number {1, 2, 3, ...}):" << std::endl;
    std::cin >> choice;

    // check if choice makes sense
    if (choice < 1 || choice > static_cast<int>(imageNames.size()))
    {
        std::cerr << "Invalid choice.\n";
        exit(1);
    }

    path = decodeDir / imageNames[choice - 1];
}
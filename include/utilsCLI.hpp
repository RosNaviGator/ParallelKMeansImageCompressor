#ifndef UTILSCLI_HPP
#define UTILSCLI_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesUtils.hpp>
#include <filesystem>

class UtilsCLI
{
private:
    UtilsCLI() = default;
    static void sequentialEncoderHeader()
    {
        system("clear -x");
        std::cout << "  _____                _ _      _   _  __                                  _____                                                   \n";
        std::cout << " |  __ \\              | | |    | | | |/ /                                 / ____|                                                  \n";
        std::cout << " | |__) |_ _ _ __ __ _| | | ___| | | ' / _ __ ___   ___  __ _ _ __  ___  | |     ___  _ __ ___  _ __  _ __ ___  ___ ___  ___  _ __ \n";
        std::cout << " |  ___/ _` | '__/ _` | | |/ _ \\ | |  < | '_ ` _ \\ / _ \\/ _` | '_ \\/ __| | |    / _ \\| '_ ` _ \\| '_ \\| '__/ _ \\/ __/ __|/ _ \\| '__|\n";
        std::cout << " | |  | (_| | | | (_| | | |  __/ | | . \\| | | | | |  __/ (_| | | | \\__ \\ | |___| (_) | | | | | | |_) | | |  __/\\__ \\__ \\ (_) | |   \n";
        std::cout << " |_|___\\__,_|_|  \\__,_|_|_|\\___|_| |_|\\_\\_| |_| |_|\\___|\\__,_|_| |_|___/ _\\_____\\___/|_| |_| |_| .__/|_|  \\___||___/___/\\___/|_|   \n";
        std::cout << "  / ____|                           | | (_)     | | \\ \\    / /          (_)                    | |                                 \n";
        std::cout << " | (___   ___  __ _ _   _  ___ _ __ | |_ _  __ _| |  \\ \\  / /__ _ __ ___ _  ___  _ __          |_|                                 \n";
        std::cout << "  \\___ \\ / _ \\/ _` | | | |/ _ \\ '_ \\| __| |/ _` | |   \\ \\/ / _ \\ '__/ __| |/ _ \\| '_ \\                                             \n";
        std::cout << "  ____) |  __/ (_| | |_| |  __/ | | | |_| | (_| | |    \\  /  __/ |  \\__ \\ | (_) | | | |                                            \n";
        std::cout << " |_____/ \\___|\\__, |\\__,_|\\___|_| |_|\\__|_|\\__,_|_|     \\/ \\___|_|  |___/_|\\___/|_| |_|                                            \n";
        std::cout << "                 | |                                                                                                               \n";
        std::cout << "                 |_|                                                                                                               \n";
        std::cout << std::endl;
        std::cout << std::endl;
    }
    static void mpiEncoderHeader()
    {
        system("clear -x");
        std::cout << "  _____                _ _      _   _  __                                  _____                                                    \n";
        std::cout << " |  __ \\              | | |    | | | |/ /                                 / ____|                                                   \n";
        std::cout << " | |__) |_ _ _ __ __ _| | | ___| | | ' / _ __ ___   ___  __ _ _ __  ___  | |     ___  _ __ ___  _ __  _ __ ___  ___ ___  ___  _ __  \n";
        std::cout << " |  ___/ _` | '__/ _` | | |/ _ \\ | |  < | '_ ` _ \\ / _ \\/ _` | '_ \\/ __| | |    / _ \\| '_ ` _ \\| '_ \\| '__/ _ \\/ __/ __|/ _ \\| '__| \n";
        std::cout << " | |  | (_| | | | (_| | | |  __/ | | . \\| | | | | |  __/ (_| | | | \\__ \\ | |___| (_) | | | | | | |_) | | |  __/\\__ \\__ \\ (_) | |    \n";
        std::cout << " |_|   \\__,_|_|  \\__,_|_|_|\\___|_| |_|\\_\\_| |_| |_|\\___|\\__,_|_| |_|___/  \\_____\\___/|_| |_| |_| .__/|_|  \\___||___/___/\\___/|_|    \n";
        std::cout << "  __  __ _____ _____   __      __           _                                                  | |                                 \n";
        std::cout << " |  \\/  |  __ \\_   _|  \\ \\    / /          (_)                                                 |_|                                 \n";
        std::cout << " | \\  / | |__) || |     \\ \\  / /__ _ __ ___ _  ___  _ __                                                                            \n";
        std::cout << " | |\\/| |  ___/ | |      \\ \\/ / _ \\ '__/ __| |/ _ \\| '_ \\                                                                           \n";
        std::cout << " | |  | | |    _| |_      \\  /  __/ |  \\__ \\ | (_) | | | |                                                                          \n";
        std::cout << " |_|  |_|_|   |_____|      \\/ \\___|_|  |___/_|\\___/|_| |_|                                                                          \n";

        std::cout << std::endl;
        std::cout << std::endl;
    }
    static void ompEncoderHeader()
    {
        system("clear -x");
        std::cout << "  _____                _ _      _   _  __                                  _____                                                   \n";
        std::cout << " |  __ \\              | | |    | | | |/ /                                 / ____|                                                  \n";
        std::cout << " | |__) |_ _ _ __ __ _| | | ___| | | ' / _ __ ___   ___  __ _ _ __  ___  | |     ___  _ __ ___  _ __  _ __ ___  ___ ___  ___  _ __ \n";
        std::cout << " |  ___/ _` | '__/ _` | | |/ _ \\ | |  < | '_ ` _ \\ / _ \\/ _` | '_ \\/ __| | |    / _ \\| '_ ` _ \\| '_ \\| '__/ _ \\/ __/ __|/ _ \\| '__|\n";
        std::cout << " | |  | (_| | | | (_| | | |  __/ | | . \\| | | | | |  __/ (_| | | | \\__ \\ | |___| (_) | | | | | | |_) | | |  __/\\__ \\__ \\ (_) | |   \n";
        std::cout << " |_|   \\__,_|_|  \\__,_|_|_|\\___|_| |_|\\_\\_| |_| |_|\\___|\\__,_|_| |_|___/  \\_____\\___/|_| |_| |_| .__/|_|  \\___||___/___/\\___/|_|   \n";
        std::cout << "   ____  __  __ _____   __      __           _                                                 | |                                 \n";
        std::cout << "  / __ \\|  \\/  |  __ \\  \\ \\    / /          (_)                                                |_|                                 \n";
        std::cout << " | |  | | \\  / | |__) |  \\ \\  / /__ _ __ ___ _  ___  _ __                                                                          \n";
        std::cout << " | |  | | |\\/| |  ___/    \\ \\/ / _ \\ '__/ __| |/ _ \\| '_ \\                                                                         \n";
        std::cout << " | |__| | |  | | |         \\  /  __/ |  \\__ \\ | (_) | | | |                                                                        \n";
        std::cout << "  \\____/|_|  |_|_|          \\/ \\___|_|  |___/_|\\___/|_| |_|                                                                        \n";
        std::cout << "                                                                                                                                    \n";
        std::cout << "                                                                                                                                    \n";
        std::cout << std::endl;
        std::cout << std::endl;
    }

public:
    static void mainMenuHeader()
    {
        std::system("clear -x");
        std::cout << "  _____                _ _      _   _  __                                  _____                                                   \n";
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
    static void decoderHeader()
    {
        system("clear -x");
        std::cout << "  _____                _ _      _   _  __                                  _____                                                   \n";
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
    static void workDone()
    {
        system("clear -x");
        std::cout << " __          __        _      _____                     _ \n"
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
    static void compressionChoices(int &levelsColorsChioce, int &typeCompressionChoice, std::string &outputPath, cv::Mat &image, int executionStandard)
    {
        std::string path;

        // performance evaluation
        bool flag = true;
        if (true == flag)
        {
            std::string exePath = std::filesystem::canonical("/proc/self/exe").parent_path().string();
            path = exePath + "/../benchmarkImages/odettte3000x4000.jpg";
            std::filesystem::path fullPath(path);
            std::string fileName = fullPath.filename().string();
            outputPath = "outputs/" + fileName + ".kc";

            levelsColorsChioce = 4;
            typeCompressionChoice = 3;
            
            image = cv::imread(path);
            
            return;
        }

        if (executionStandard == 1)
        {
            UtilsCLI::sequentialEncoderHeader();
        }
        else if (executionStandard == 2)
        {
            UtilsCLI::mpiEncoderHeader();
        }
        else if (executionStandard == 3)
        {
            UtilsCLI::ompEncoderHeader();
        }
        std::cout << "The following program will reduce the number of colors int he original image in order to decrease its size." << std::endl;
        std::cout << std::endl;
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
        do
        {
            std::cin >> levelsColorsChioce;
            if (levelsColorsChioce < 1 || levelsColorsChioce > 5)
            {
                std::cout << "Invalid input. Please choose a level between 1 and 5." << std::endl;
            }
        } while (levelsColorsChioce < 1 || levelsColorsChioce > 5);

        if (executionStandard == 1)
        {
            UtilsCLI::sequentialEncoderHeader();
        }
        else if (executionStandard == 2)
        {
            UtilsCLI::mpiEncoderHeader();
        }
        else if (executionStandard == 3)
        {
            UtilsCLI::ompEncoderHeader();
        }
        std::cout << "Perfect! Now let's choose the type of compression for your image." << std::endl
                  << "\n"
                  << "(1)\tLight Compression (it may take more time bot the result will be more defined) <-- Suggested for Small Images\n"
                  << "(2)\tMedium Compression (it applies chroma subsampling to reduce the dimension of the image and the time needed for the computation)\n"
                  << "(3)\tHeavy Compression (it applies chroma subsampling and image resizing) <-- Suggested for Big Images\n";
        std::cout << std::endl;
        std::cout << std::endl;
        do
        {
            std::cin >> typeCompressionChoice;
            if (typeCompressionChoice < 1 || typeCompressionChoice > 3)
            {
                std::cout << "Invalid input. Please choose a type between 1 and 3." << std::endl;
            }
        } while (typeCompressionChoice < 1 || typeCompressionChoice > 3);
        if (executionStandard == 1)
        {
            UtilsCLI::sequentialEncoderHeader();
        }
        else if (executionStandard == 2)
        {
            UtilsCLI::mpiEncoderHeader();
        }
        else if (executionStandard == 3)
        {
            UtilsCLI::ompEncoderHeader();
        }
        std::cout << "Now please enter the global path of the image you want to compress" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, path);
        if (executionStandard == 1)
        {
            UtilsCLI::sequentialEncoderHeader();
        }
        else if (executionStandard == 2)
        {
            UtilsCLI::mpiEncoderHeader();
        }
        else if (executionStandard == 3)
        {
            UtilsCLI::ompEncoderHeader();
        }
        std::cout << "Choose a name for your output (note that the output will be saved in the outputs directory)" << std::endl;
        std::cout << "You don't need to give any extension" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::getline(std::cin, outputPath);
        outputPath = "outputs/" + outputPath + ".kc";
        image = cv::imread(path);
        while (image.empty())
        {
            std::cerr << "Error: Unable to load the image." << std::endl;
            std::cout << "Please enter the correct global path of the image you want to compress" << std::endl
                      << std::endl;
            std::cout << "--> ";
            std::getline(std::cin, path);
            std::cout << std::endl;
            cv::Mat image = cv::imread(path);
        }

        if (executionStandard == 1)
        {
            UtilsCLI::sequentialEncoderHeader();
        }
        else if (executionStandard == 2)
        {
            UtilsCLI::mpiEncoderHeader();
        }
        else if (executionStandard == 3)
        {
            UtilsCLI::ompEncoderHeader();
        }
        std::cout << "Well done! The program is now ready to compress your image." << std::endl;
        std::cout << std::endl;
    }
    static void printCompressionInformations(int &originalWidth, int &originalHeight, int &width, int &height, int &k, int &different_colors_size)
    {
        std::cout << "Your original image was " << originalWidth << "x" << originalHeight << " pixels and it has " << different_colors_size << " different colors." << std::endl;
        std::cout << std::endl;
        std::cout << "The compressed image will be " << width << "x" << height << " pixels and it will have " << k << " different colors." << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }

    static void displayDecodingMenu(std::string &path, std::vector<std::filesystem::path> &imageNames, std::filesystem::path &decodeDir)
    {

        std::cout << "Select an image:" << std::endl;
        std::cout << std::endl;
        for (size_t i = 0; i < imageNames.size(); ++i)
        {
            std::cout << "(" << i + 1 << ") " << imageNames[i] << std::endl;
        }

        int choice;
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
};

#endif // UTILSCLI_HPP
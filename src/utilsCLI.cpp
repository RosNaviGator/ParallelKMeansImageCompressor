#include <utilsCLI.hpp>

void km::utilsCLI::sequentialEncoderHeader()
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

void km::utilsCLI::mpiEncoderHeader()
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

void km::utilsCLI::ompEncoderHeader()
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

void km::utilsCLI::mainMenuHeader()
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

void km::utilsCLI::decoderHeader()
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

void km::utilsCLI::workDone()
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

void km::utilsCLI::compressionChoices(int &levelsColorsChoice, int &typeCompressionChoice, std::string &outputPath, cv::Mat &image, int executionStandard)
{
    std::string path;

        if (executionStandard == 1)
        {
            km::utilsCLI::sequentialEncoderHeader();
        }
        else if (executionStandard == 2)
        {
            km::utilsCLI::mpiEncoderHeader();
        }
        else if (executionStandard == 3)
        {
            km::utilsCLI::ompEncoderHeader();
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

        const int MIN_COLOR_CHOICE = 1;
        const int MAX_COLOR_CHOICE = 5;

        std::cin >> levelsColorsChoice;
        while (levelsColorsChoice < MIN_COLOR_CHOICE || levelsColorsChoice > MAX_COLOR_CHOICE)
        {
            std::cout << "Invalid input. Please choose a level between 1 and 5." << std::endl;
            std::cin >> levelsColorsChoice;
        }

        if (executionStandard == 1)
        {
            km::utilsCLI::sequentialEncoderHeader();
        }
        else if (executionStandard == 2)
        {
            km::utilsCLI::mpiEncoderHeader();
        }
        else if (executionStandard == 3)
        {
            km::utilsCLI::ompEncoderHeader();
        }
        std::cout << "Perfect! Now let's choose the type of compression for your image." << std::endl
                  << "\n"
                  << "(1)\tLight Compression (it may take more time bot the result will be more defined) <-- Suggested for Small Images\n"
                  << "(2)\tMedium Compression (it applies chroma subsampling to reduce the dimension of the image and the time needed for the computation)\n"
                  << "(3)\tHeavy Compression (it applies chroma subsampling and image resizing) <-- Suggested for Big Images\n";
        std::cout << std::endl;
        std::cout << std::endl;

        std::cin >> typeCompressionChoice;

        const int MIN_COMPRESSION_CHOICE = 1;
        const int MAX_COMPRESSION_CHOICE = 3;

        while (typeCompressionChoice < MIN_COMPRESSION_CHOICE || typeCompressionChoice > MAX_COMPRESSION_CHOICE) {
            std::cout << "Invalid input. Please choose a type between 1 and 3." << std::endl;
            std::cin >> typeCompressionChoice;
        }

        if (executionStandard == 1)
        {
            km::utilsCLI::sequentialEncoderHeader();
        }
        else if (executionStandard == 2)
        {
            km::utilsCLI::mpiEncoderHeader();
        }
        else if (executionStandard == 3)
        {
            km::utilsCLI::ompEncoderHeader();
        }
        std::cout << "Now please enter the global path of the image you want to compress" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, path);
        if (executionStandard == 1)
        {
            km::utilsCLI::sequentialEncoderHeader();
        }
        else if (executionStandard == 2)
        {
            km::utilsCLI::mpiEncoderHeader();
        }
        else if (executionStandard == 3)
        {
            km::utilsCLI::ompEncoderHeader();
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
            km::utilsCLI::sequentialEncoderHeader();
        }
        else if (executionStandard == 2)
        {
            km::utilsCLI::mpiEncoderHeader();
        }
        else if (executionStandard == 3)
        {
            km::utilsCLI::ompEncoderHeader();
        }
        std::cout << "Well done! The program is now ready to compress your image." << std::endl;
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
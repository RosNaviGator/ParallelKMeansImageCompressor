#ifndef UTILSCLI_HPP
#define UTILSCLI_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesUtils.hpp>

class UtilsCLI
{
private:
    UtilsCLI() = default;
    static void sequentialEncoderHeader();
    static void mpiEncoderHeader();
    static void ompEncoderHeader();

public:
    static void mainMenuHeader();
    static void decoderHeader();
    static void workDone();
    static void compressionChoices(int &levelsColorsChoice, int &typeCompressionChoice, std::string &outputPath, cv::Mat &image, int executionStandard);
    static void printCompressionInformations(int &originalWidth, int &originalHeight, int &width, int &height, int &k, int &different_colors_size);
    static void displayDecodingMenu(std::string &path, std::vector<std::filesystem::path> &imageNames, std::filesystem::path &decodeDir);
};

#endif // UTILSCLI_HPP
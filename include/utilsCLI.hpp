/**
 * @file utilsCLI.hpp
 * @brief Utility functions for the command-line interface
 */

#ifndef UTILSCLI_HPP
#define UTILSCLI_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesUtils.hpp>
#include <boost/process.hpp>

/**
 * @namespace km::utilsCLI
 * @brief Provides utility functions for the command-line interface
 * @details The utilsCLI namespace within the km namespace provides a collection of utility functions for enhancing command-line interface(CLI)
 *          interactions. The mainMenuHeader function displays the main menu header, while decoderHeader shows the header for the decoder section.
 *          The workDone function outputs a completion message to indicate that work has been finished. The printCompressionInformations function
 *          prints detailed compression data, including the original and compressed image dimensions, the number of clusters, and the count of
 *          different colors. Lastly, the displayDecodingMenu function presents a menu for decoding, showing image names and the path of the decoding
 *          directory. These functions facilitate user interaction and provide essential information during CLI operations.
 */

namespace km
{
    namespace utilsCLI
    {
        
        /**
         * @brief Displays the main menu header
         */
        auto mainMenuHeader() -> void;

        /**
         * @brief Displays the decoder header
         */
        auto decoderHeader() -> void;

        /**
         * @brief Displays the work done message
         */
        auto workDone() -> void;

        /**
         * @brief Prints the compression information
         * @param originalWidth Original width of the image\subsection{Utilities Overview}

         * @param originalHeight Original height of the image
         * @param width Width of the compressed image
         * @param height Height of the compressed image
         * @param k Number of clusters
         * @param different_colors_size Number of different colors
         */
        auto printCompressionInformations(int &originalWidth, int &originalHeight, int &width, int &height, int &k, size_t &different_colors_size) -> void;

        /**
         * @brief Displays the decoding menu
         * @param path Path of the directory containing the compressed images
         * @param imageNames Vector of image names
         * @param decodeDir Path of the decoding directory
         */
        auto displayDecodingMenu(std::string &path, std::vector<std::filesystem::path> &imageNames, std::filesystem::path &decodeDir) -> void;
    };
}

#endif // UTILSCLI_HPP
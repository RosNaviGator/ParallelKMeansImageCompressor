/**
 * @file configReader.hpp
 * @brief ConfigReader class declaration
 */

#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

#include <string>
#include <regex>
#include <unordered_set>
#include <filesystem>

namespace km
{
    /**
     * @class ConfigReader
     * @brief Reads and stores configuration values from a file
     * @details The ConfigReader class, located within the km namespace, is designed to handle the reading and storage of configuration settings from a file.
     *          This class is particularly focused on managing settings for image processing and compression. It holds various parameters such as compression color values for different levels,
     *          resizing factors, color choices, and compression choices, which are essential for tailoring the behavior of image processing operations. The class also manages the input image file path,
     *          allowing it to reference the specific files needed for processing. A regular expression pattern is included for validating or extracting configuration details, and a set of required variables
     *          is maintained to ensure that all necessary configuration options are present. 
     *          The class provides several getter methods to access these stored settings, ensuring that they can be easily retrieved by other parts of the application.
     *          Additionally, it includes a method to read and validate the configuration file, ensuring that all required parameters are correctly set up before proceeding with any image processing tasks.
     */

    class ConfigReader
    {
    private:
        double first_level_compression_color = 0.;              ///< First level compression color value
        double second_level_compression_color = 0.;             ///< Second level compression color value
        double third_level_compression_color = 0.;              ///< Third level compression color value
        double fourth_level_compression_color = 0.;             ///< Fourth level compression color value
        double fifth_level_compression_color = 0.;              ///< Fifth level compression color value
        double resizing_factor = 0.;                            ///< Resizing factor
        int color_choice = 0;                                   ///< Color choice
        int compression_choice = 0;                             ///< Compression choice
        std::filesystem::path inputImageFilePath;               ///< Input image file path
        std::regex pattern;                                     ///< Regular expression pattern
        std::unordered_set<std::string> requiredVariables = {}; ///< Set of required variables

        [[nodiscard]] auto checkVariableExists(const std::string &variableName) const -> bool;

        /**
         * @brief Gets the first level compression color value
         * @return First level compression color value
         */

    public:
        [[nodiscard]] auto getFirstLevelCompressionColor() const -> double;

        /**
         * @brief Gets the second level compression color value
         * @return Second level compression color value
         */
        [[nodiscard]] auto getSecondLevelCompressionColor() const -> double;

        /**
         * @brief Gets the third level compression color value
         * @return Third level compression color value
         */
        [[nodiscard]] auto getThirdLevelCompressionColor() const -> double;

        /**
         * @brief Gets the fourth level compression color value
         * @return Fourth level compression color value
         */
        [[nodiscard]] auto getFourthLevelCompressionColor() const -> double;

        /**
         * @brief Gets the fifth level compression color value
         * @return Fifth level compression color value
         */
        [[nodiscard]] auto getFifthLevelCompressionColor() const -> double;

        /**
         * @brief Gets the color choice
         * @return Color choice
         */
        [[nodiscard]] auto getColorChoice() const -> int;

        /**
         * @brief Gets the compression choice
         * @return Compression choice
         */
        [[nodiscard]] auto getCompressionChoice() const -> int;

        /**
         * @brief Gets the input image file path
         * @return Input image file path
         */
        [[nodiscard]] auto getInputImageFilePath() const -> std::filesystem::path;

        /**
         * @brief Gets the resizing factor
         * @return Resizing factor
         */
        [[nodiscard]] auto getResizingFactor() const -> double;

        /**
         * @brief Reads the configuration file
         * @return True if the configuration file is read successfully, false otherwise
         */
        [[nodiscard]] auto readConfigFile() -> bool;

        ConfigReader();
    };
} // namespace km

#endif // CONFIG_READER_HPP
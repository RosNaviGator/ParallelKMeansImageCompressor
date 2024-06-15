#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

#include <string>
#include <regex>
#include <unordered_set>
#include <filesystem>

class ConfigReader {
private:
    double first_level_compression_color;
    double second_level_compression_color;
    double third_level_compression_color;
    double fourth_level_compression_color;
    double fifth_level_compression_color;
    double resizing_factor;
    int color_choice = 0 ;
    int compression_choice = 0;
    std::filesystem::path inputImageFilePath="";



    std::unordered_set<std::string> requiredVariables;
    std::regex pattern;

    
    bool checkVariableExists(const std::string& variableName) const;

public:
    ConfigReader();
    ~ConfigReader();
    auto getFirstLevelCompressionColor() const      -> double;
    auto getSecondLevelCompressionColor() const     -> double;
    auto getThirdLevelCompressionColor() const      -> double;
    auto getFourthLevelCompressionColor() const     -> double;
    auto getFifthLevelCompressionColor() const      -> double;
    auto getColorChoice() const                     -> int;
    auto getCompressionChoice() const               -> int;
    auto getInputImageFilePath() const              -> std::filesystem::path;
    auto getResizingFactor() const                  -> double;
    auto readConfigFile()                           -> bool;
};


#endif // CONFIG_READER_HPP
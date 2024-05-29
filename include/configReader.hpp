#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

#include <string>
#include <regex>
#include <unordered_set>

class ConfigReader {
private:
    double first_level_compression_color;
    double second_level_compression_color;
    double third_level_compression_color;
    double fourth_level_compression_color;
    double fifth_level_compression_color;
    long long int batch_size;
    double resizing_factor;

    std::unordered_set<std::string> requiredVariables;
    std::regex pattern;

    
    bool checkVariableExists(const std::string& variableName) const;

public:
    ConfigReader();
    ~ConfigReader();
    double getFirstLevelCompressionColor() const;
    double getSecondLevelCompressionColor() const;
    double getThirdLevelCompressionColor() const;
    double getFourthLevelCompressionColor() const;
    double getFifthLevelCompressionColor() const;
    long long int getBatchSize() const;
    double getResizingFactor() const;
    bool readConfigFile();
};

#endif // CONFIG_READER_HPP
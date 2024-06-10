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

    
    auto checkVariableExists(const std::string& variableName) const -> bool;

public:
    ConfigReader();
    ~ConfigReader();
    auto getFirstLevelCompressionColor() const -> double;
    auto getSecondLevelCompressionColor() const -> double;
    auto getThirdLevelCompressionColor() const -> double;
    auto getFourthLevelCompressionColor() const -> double;
    auto getFifthLevelCompressionColor() const -> double;
    auto getBatchSize() const -> long long int;
    auto getResizingFactor() const -> double;
    auto readConfigFile() -> bool;
};

#endif // CONFIG_READER_HPP
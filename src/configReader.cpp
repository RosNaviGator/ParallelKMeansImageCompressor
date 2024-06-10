#include <configReader.hpp>
#include <iostream>
#include <fstream>
#include <string>

ConfigReader::ConfigReader() {
    requiredVariables = {
        "first_level_compression_color",
        "second_level_compression_color",
        "third_level_compression_color",
        "fourth_level_compression_color",
        "fifth_level_compression_color",
        "batch_size",
        "resizing_factor"
    };

    pattern = std::regex("^(\\w+)\\s*=\\s*([^\\s]+)\\s*$");

    readConfigFile();
}

ConfigReader::~ConfigReader() = default;

auto ConfigReader::readConfigFile() -> bool
{
    std::ifstream file(".config");
    if (!file.is_open()) {
        std::cerr << "Error: .config file not found." << '\n';
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip commented lines and empty lines
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::smatch match;
        if (std::regex_match(line, match, pattern)) {
            std::string variableName = match[1];
            std::string variableValue = match[2];

            if (variableName == "first_level_compression_color") {
                first_level_compression_color = std::stod(variableValue);
            } else if (variableName == "second_level_compression_color") {
                second_level_compression_color = std::stod(variableValue);
            } else if (variableName == "third_level_compression_color") {
                third_level_compression_color = std::stod(variableValue);
            } else if (variableName == "fourth_level_compression_color") {
                fourth_level_compression_color = std::stod(variableValue);
            } else if (variableName == "fifth_level_compression_color") {
                fifth_level_compression_color = std::stod(variableValue);
            } else if (variableName == "batch_size") {
                batch_size = std::stoll(variableValue);
            } else if (variableName == "resizing_factor") {
                resizing_factor = std::stod(variableValue);
            } else {
                std::cerr << "Warning: Unknown variable '" << variableName << "' in .config file." << '\n';
            }
        } else {
            std::cerr << "Error: Invalid format in line: " << line << '\n';
            return false;
        }
    }

    file.close();

    // Check if any required variables are missing
    for (const std::string& var : requiredVariables) {
        if (!checkVariableExists(var)) {
            std::cerr << "Error: Required variable '" << var << "' is missing in .config file." << '\n';
            return false;
        }
    }

    return true;
}

auto ConfigReader::checkVariableExists(const std::string &variableName) const -> bool
{
    if (variableName == "first_level_compression_color") {
        return true;
    } else if (variableName == "second_level_compression_color") {
        return true;
    } else if (variableName == "third_level_compression_color") {
        return true;
    } else if (variableName == "fourth_level_compression_color") {
        return true;
    } else if (variableName == "fifth_level_compression_color") {
        return true;
    } else if (variableName == "batch_size") {
        return true;
    } else if (variableName == "resizing_factor") {
        return true;
    }
    return false;
}

auto ConfigReader::getFirstLevelCompressionColor() const -> double {
    return first_level_compression_color;
}

auto ConfigReader::getSecondLevelCompressionColor() const -> double {
    return second_level_compression_color;
}

auto ConfigReader::getThirdLevelCompressionColor() const -> double {
    return third_level_compression_color;
}

auto ConfigReader::getFourthLevelCompressionColor() const -> double {
    return fourth_level_compression_color;
}

auto ConfigReader::getFifthLevelCompressionColor() const -> double {
    return fifth_level_compression_color;
}

auto ConfigReader::getBatchSize() const -> long long int {
    return batch_size;
}

auto ConfigReader::getResizingFactor() const -> double {
    return resizing_factor;
}
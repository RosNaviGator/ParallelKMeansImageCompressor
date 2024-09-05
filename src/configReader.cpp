/**
 * @file configReader.cpp
 * @brief Implementation of the ConfigReader class for reading and parsing configuration files.
 * @details This source file contains the implementation of the ConfigReader class, which provides functionalities
 *          for reading, validating, and storing configuration settings from a .config file. The class is designed
 *          to handle configuration variables related to image processing, such as compression colors and resizing
 *          factors, and stores them for use in other parts of the application.
 */

#include <configReader.hpp>
#include <iostream>
#include <fstream>
#include <string>

km::ConfigReader::ConfigReader() {
    requiredVariables = {
        "first_level_compression_color",
        "second_level_compression_color",
        "third_level_compression_color",
        "fourth_level_compression_color",
        "fifth_level_compression_color",
        "resizing_factor"
    };

    pattern = std::regex(R"(^(\w+)\s*=\s*([^\s]+)\s*$)");

    if (!readConfigFile()) {
        std::cerr << "Error: Failed to read .config file." << '\n';
    }
}

auto km::ConfigReader::readConfigFile() -> bool
{
    std::ifstream file("./.config");
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
            } else if (variableName == "resizing_factor") {
                resizing_factor = std::stod(variableValue);
            } else if (variableName == "color_choice") {
                color_choice = std::stoi(variableValue);
            } else if (variableName == "compression_choice") {
                compression_choice = std::stoi(variableValue);
            } else if (variableName == "input_image_file_path") {
                inputImageFilePath = variableValue;
            }else {
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

auto km::ConfigReader::checkVariableExists(const std::string &variableName) const -> bool
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
    } else if (variableName == "resizing_factor") {
        return true;
    }
    return false;
}

auto km::ConfigReader::getFirstLevelCompressionColor() const -> double
{
    return first_level_compression_color;
}

auto km::ConfigReader::getSecondLevelCompressionColor() const -> double
{
    return second_level_compression_color;
}

auto km::ConfigReader::getThirdLevelCompressionColor() const -> double
{
    return third_level_compression_color;
}

auto km::ConfigReader::getFourthLevelCompressionColor() const -> double
{
    return fourth_level_compression_color;
}

auto km::ConfigReader::getFifthLevelCompressionColor() const -> double{
    return fifth_level_compression_color;
}

auto km::ConfigReader::getResizingFactor() const -> double{
    return resizing_factor;
}

auto km::ConfigReader::getColorChoice() const -> int{
    return color_choice;
}

auto km::ConfigReader::getCompressionChoice() const -> int{
    return compression_choice;
}

auto km::ConfigReader::getInputImageFilePath() const -> std::filesystem::path{
    return inputImageFilePath;
}
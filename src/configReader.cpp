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
        "resizing_factor"
    };

    pattern = std::regex("^(\\w+)\\s*=\\s*([^\\s]+)\\s*$");

    readConfigFile();
}

ConfigReader::~ConfigReader() = default;

bool ConfigReader::readConfigFile() {
    std::ifstream file(".config");
    if (!file.is_open()) {
        std::cerr << "Error: .config file not found." << std::endl;
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
                std::cerr << "Warning: Unknown variable '" << variableName << "' in .config file." << std::endl;
            }
        } else {
            std::cerr << "Error: Invalid format in line: " << line << std::endl;
            return false;
        }
    }

    file.close();

    // Check if any required variables are missing
    for (const std::string& var : requiredVariables) {
        if (!checkVariableExists(var)) {
            std::cerr << "Error: Required variable '" << var << "' is missing in .config file." << std::endl;
            return false;
        }
    }

    return true;
}

bool ConfigReader::checkVariableExists(const std::string& variableName) const {
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

double ConfigReader::getFirstLevelCompressionColor() const {
    return first_level_compression_color;
}

double ConfigReader::getSecondLevelCompressionColor() const {
    return second_level_compression_color;
}

double ConfigReader::getThirdLevelCompressionColor() const {
    return third_level_compression_color;
}

double ConfigReader::getFourthLevelCompressionColor() const {
    return fourth_level_compression_color;
}

double ConfigReader::getFifthLevelCompressionColor() const {
    return fifth_level_compression_color;
}

double ConfigReader::getResizingFactor() const {
    return resizing_factor;
}

int ConfigReader::getColorChoice() const {
    return color_choice;
}

int ConfigReader::getCompressionChoice() const {
    return compression_choice;
}

std::filesystem::path ConfigReader::getInputImageFilePath() const {
    return inputImageFilePath;
}
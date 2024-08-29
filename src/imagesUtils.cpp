#include <imagesUtils.hpp>

void km::imageUtils::preprocessing(cv::Mat& image, int& typeCompressionChoice)
{
    ConfigReader configReader;
    double resizing_factor = configReader.getResizingFactor();
    cv::cvtColor(image, image, cv::COLOR_BGR2YCrCb);

    // apply chroma subsampling
    if (typeCompressionChoice == 3)
    {
        cv::resize(image, image, cv::Size(), resizing_factor, resizing_factor, cv::INTER_LINEAR);
    }
    else if (typeCompressionChoice == 2)
    {
        const int REDUCTION_FACTOR_CHROMA = 2;
        cv::resize(image, image, cv::Size(), REDUCTION_FACTOR_CHROMA, REDUCTION_FACTOR_CHROMA, cv::INTER_LINEAR);
        cv::resize(image, image, cv::Size(), 1./REDUCTION_FACTOR_CHROMA, 1./REDUCTION_FACTOR_CHROMA, cv::INTER_LINEAR);
    }else if (typeCompressionChoice == 1)
    {
        // do nothing
    }else{
        std::cerr << "Invalid compression type." << std::endl;
        exit(1);
    } 
}

void km::imageUtils::defineKValue(int& k, int levelsColorsChoice, std::set<std::vector<unsigned char>>& different_colors)
{
    const int PERCENTAGE_SCALING_FACTOR = 100;

    ConfigReader configReader;
    switch (levelsColorsChoice)
    {
        case 1:
            k = configReader.getFirstLevelCompressionColor() * different_colors.size() / PERCENTAGE_SCALING_FACTOR;
            break;
        case 2:
            k = configReader.getSecondLevelCompressionColor() * different_colors.size() / PERCENTAGE_SCALING_FACTOR;
            break;
        case 3:
            k = configReader.getThirdLevelCompressionColor() * different_colors.size() / PERCENTAGE_SCALING_FACTOR;
            break;
        case 4:
            k = configReader.getFourthLevelCompressionColor() * different_colors.size() / PERCENTAGE_SCALING_FACTOR;
            break;
        case 5:
            k = configReader.getFifthLevelCompressionColor() * different_colors.size() / PERCENTAGE_SCALING_FACTOR;
            break;
        default:
            std::cerr << "Invalid color preservation level." << std::endl;
            exit(1);
            break;
    }
}

void km::imageUtils::pointsFromImage(cv::Mat& image, std::vector<Point>& points, std::set<std::vector<unsigned char>>& different_colors)
{
    int height = image.rows;
    int width = image.cols;
    int id = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            points.emplace_back(Point(id, {image.at<cv::Vec3b>(y, x)[0], image.at<cv::Vec3b>(y, x)[1], image.at<cv::Vec3b>(y, x)[2]}));
            different_colors.insert({image.at<cv::Vec3b>(y, x)[0], image.at<cv::Vec3b>(y, x)[1], image.at<cv::Vec3b>(y, x)[2]});
            id += 1;
        }
    }
}
#include <filesUtils.hpp>

void km::filesUtils::createOutputDirectories()
{
    // Obtain the path of the executable file
    std::filesystem::path exePath = std::filesystem::canonical("/proc/self/exe");
    // Get the parent path of the executable, which represents the directory containing the executable
    std::filesystem::path buildPath = exePath.parent_path();

    // create outputs if doesn't exist
    // Ensure "outputs" directory exists
    std::filesystem::path outputsDir = buildPath / ".." / "outputs";
    std::filesystem::path outputsDirJpg = buildPath / ".." / "outputs" / "outputsjpg";
    if (!std::filesystem::exists(outputsDir))
    {
        std::cout << std::endl
                  << "outputs directory doesn't exist, let's create it" << std::endl;

        if (!std::filesystem::create_directory(outputsDir))
        {
            std::cerr << "Error creating outputs directory." << std::endl;
            exit(1); // Return an error code if directory creation fails
        }
    }
    if (!std::filesystem::exists(outputsDirJpg))
    {
        std::cout << std::endl
                  << "outputs directory for .jpg images doesn't exist, let's create it" << std::endl;

        if (!std::filesystem::create_directory(outputsDirJpg))
        {
            std::cerr << "Error creating outputs directory." << std::endl;
            exit(1); // Return an error code if directory creation fails
        }
    }
}

void km::filesUtils::writeBinaryFile(std::string& outputPath, int& width, int& height, int& k, std::vector<Point> points , std::vector<Point> centroids)
{
    std::cout << "Saving the Compressed Image..." << std::endl;
    std::ofstream outputFile(outputPath, std::ios::app);
    auto startcompression = std::chrono::high_resolution_clock::now();
    std::vector<uint8_t> buffer;

    // Helper function to write data to buffer
    auto writeToBuffer = [&buffer](const void *data, size_t size)
    {
        const auto *byteData = static_cast<const uint8_t *>(data);
        buffer.insert(buffer.end(), byteData, byteData + size);
    };

    auto width16bit = static_cast<u_int16_t>(width);
    auto height16bit = static_cast<u_int16_t>(height);
    auto k16bit = static_cast<u_int16_t>(k);

    // Scrivi width, height e k
    writeToBuffer(&width16bit, sizeof(width16bit));
    writeToBuffer(&height16bit, sizeof(height16bit));
    writeToBuffer(&k16bit, sizeof(k16bit));

    // Scrivi i centroidi
    for (Point& centroid : centroids) 
    {
        for (int i = 0; i < 3; ++i) 
        {
            int feature = centroid.getFeature(i);
            writeToBuffer(&feature, sizeof(feature));
        }
    }

    int pointId = 0;
    int n_points = points.size();
    while (pointId < n_points)
    {
        int pointId_start = pointId;
        auto clusterId = static_cast<uint8_t>(points[pointId_start].clusterId);
        const int MAX_CLUSTER_SIZE = 254;
        while(pointId < n_points && points[pointId].clusterId == clusterId && pointId - pointId_start < MAX_CLUSTER_SIZE)
        {
            ++pointId;
        }
        uint8_t count = pointId - pointId_start;
        writeToBuffer(&count, sizeof(count));
        writeToBuffer(&clusterId, sizeof(clusterId));

    }

    outputFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    auto endcompression = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsedcompression = endcompression - startcompression;
    std::cout << "Compression done in " << elapsedcompression.count() << std::endl;
}

auto km::filesUtils::isCorrectExtension(const std::filesystem::path &filePath, const std::string &correctExtension) -> bool
{
    static const std::vector<std::string> imageExtensions = {correctExtension};
    const std::string extension = filePath.extension().string();
    return std::find_if(imageExtensions.begin(), imageExtensions.end(),
                        [&extension](const std::string &ext)
                        { return extension == ext; }) != imageExtensions.end();
}

void km::filesUtils::createDecodingMenu(std::filesystem::path& decodeDir, std::vector<std::filesystem::path>& imageNames)
{
    std::filesystem::path exePath = std::filesystem::canonical("/proc/self/exe");
    std::filesystem::path buildPath = exePath.parent_path();
    decodeDir = buildPath / ".." / "outputs";

    // Check if the directory exists
    if (!std::filesystem::exists(decodeDir))
    {
        // Directory doesn't exist, throw an error
        std::cerr << "Error: Directory " << decodeDir << " does not exist.\n";
        exit(1);
    }

    // Populate the vector with image names
    for (const auto &entry : std::filesystem::directory_iterator(decodeDir))
    {
        if (entry.is_regular_file() && isCorrectExtension(entry.path(),".kc"))
        {
            imageNames.push_back(entry.path().filename());
        }
    }

    // Check if no images were found
    if (imageNames.empty())
    {
        std::cerr << "No images found in the directory." << std::endl;
        exit(1); // Return 1 to indicate an error
    }
}

auto km::filesUtils::readBinaryFile(std::string &path, cv::Mat &imageCompressed) -> int
{
    std::ifstream inputFile(path, std::ios::binary);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
    
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    size_t pos = 0;
    auto readFromBuffer = [&buffer, &pos](void *data, size_t size)
    {
        auto *byteData = static_cast<uint8_t *>(data);
        std::copy(buffer.begin() + pos, buffer.begin() + pos + size, byteData);
        pos += size;
    };

    uint16_t width = 0, height = 0, k = 0;
    readFromBuffer(&width, sizeof(width));
    readFromBuffer(&height, sizeof(height));
    readFromBuffer(&k, sizeof(k));

    std::vector<std::vector<int>> clustersColors;
    std::vector<cv::Vec3b> pixels;

    for (int i = 0; i < k; ++i) 
    {
        std::vector<int> features(3);
        for (int& feature : features) 
        {
            readFromBuffer(&feature, sizeof(feature));
        }
        clustersColors.push_back(features);
    }
    int n_points = width * height;
    int pointId = 0;

    while (pointId < n_points) 
    {
        uint8_t counter = 0;
        uint8_t clusterId = 0;
        readFromBuffer(&counter, sizeof(counter));
        readFromBuffer(&clusterId, sizeof(clusterId));
        for (int i = 0; i < static_cast<int> (counter); ++i) 
        {
            pixels.emplace_back(clustersColors.at(clusterId).at(0), clustersColors.at(clusterId).at(1), clustersColors.at(clusterId).at(2));
            pointId++;
        }
    }

    imageCompressed = cv::Mat(height, width, CV_8UC3);
    for(int y = 0 ; y < height ; y++) 
    {
        for (int x = 0 ; x < width ; x++) 
        {
            imageCompressed.at<cv::Vec3b>(y, x) = pixels.at(y * width + x);
        }
    }
    return 0;
}
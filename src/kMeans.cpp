#include <kMeans.hpp>

KMeans::KMeans(const int& k, const std::vector<Point> points) : k(k), points(points), gp("gnuplot -persist")
{
    int size = points.size();
    std::random_device rd;                            // Initialize a random device
    std::mt19937 gen(23456789);                       // Initialize a Mersenne Twister random number generator with the random device
    std::uniform_int_distribution<> dis(0, size - 1); // Create a uniform distribution between 0 and size - 1

    for (int i = 0; i < k; ++i)
    {
        centroids.emplace_back(points[dis(gen)]); // Generate a random index and use it to select a point
    }
}

void KMeans::run()
{
    bool change = true;
    int iter = 0;
    int iter_max = 1000;
    std::vector<int> counts(k, 0);
    while (change && iter < iter_max)
    {
        change = false;
        // --------------------------------------------
        for (Point &p : points)
        {
            double minDist = std::numeric_limits<double>::max();
            int nearest = 0;
            for (int j = 0; j < k; ++j)
            {
                double tempDist = p.distance(centroids[j]);
                if (tempDist < minDist)
                {
                    minDist = tempDist;
                    nearest = j;
                }
            }
            if (p.clusterId != nearest)
            {
                p.clusterId = nearest;
                change = true;
            }
        }

        counts = std::vector<int>(k, 0);
        centroids = std::vector<Point>(k, Point(3));
        for (Point p : points)
        {
            for (int i = 0; i < 3; ++i)
            {
                centroids[p.clusterId].setFeature(i, centroids[p.clusterId].getFeature_int(i) + p.getFeature_int(i));
            }
            counts[p.clusterId] += 1;
        }

        for (int i = 0; i < k; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                centroids[i].setFeature(j,(centroids[i].getFeature_int(j) / counts[i]));
            }
        }

        iter++;
        std::cout << "." << std::flush;
    }
    numberOfIterationForConvergence = iter;
}

void KMeans::printClusters() const
{
    for (int i = 0; i < k; ++i)
    {
        std::cout << "Cluster " << i + 1 << ":\n";
        for (Point p : points)
        {
            if (p.clusterId == i)
            {
                std::cout << "Point " << p.id << ": (";
                for (int j = 0; j < 3; ++j)
                {
                    std::cout << p.getFeature(j);
                    if (j < 3 - 1)
                        std::cout << ", ";
                }
                std::cout << ")" << std::endl;
            }
        }
    }
}

void KMeans::plotClusters()
{
    if (3 != 2)
    {
        std::cout << "Cannot plot clusters with more than 2 features" << std::endl;
        return;
    }
    gp << "set xrange [20:70]\nset yrange [0:30]\n";
    gp << "set key outside\n"; // Add this line to place the legend outside the plot
    std::vector<std::string> colors = {"red", "blue", "green", "brown", "purple", "orange", "cyan", "violet"};
    gp << "plot ";
    for (int i = 0; i < k; ++i)
    {
        std::vector<std::pair<double, double>> pts;
        for (Point p : points)
        {
            if (p.clusterId == i)
            {
                pts.emplace_back(std::make_pair(p.getFeature(0), p.getFeature(1)));
            }
        }
        gp << "'-' with points pointtype 7 pointsize 1 lc rgb '" << colors[i % colors.size()] << "' title 'Cluster " << i + 1 << "'"; // Add a title to each plot command
        if (i < k - 1)
        {
            gp << ", ";
        }
    }
    gp << ", '-' with points pointtype 7 pointsize 2 lc rgb 'black' title 'Centroids'"; // Add a title to the centroids \ command
    gp << "\n";
    for (int i = 0; i < k; ++i)
    {
        std::vector<std::pair<double, double>> pts;
        for (Point p : points)
        {
            if (p.clusterId == i)
            {
                pts.push_back(std::make_pair(p.getFeature(0), p.getFeature(1)));
            }
        }
        gp.send1d(pts);
    }
    std::vector<std::pair<double, double>> centroid_pts;
    for (Point c : centroids)
    {
        centroid_pts.push_back(std::make_pair(c.getFeature(0), c.getFeature(1)));
    }
    gp.send1d(centroid_pts);
}

std::vector<Point> KMeans::getCentroids()
    {
        return centroids;
    }

std::vector<Point> KMeans::getPoints()
    {
        return points;
    }

int KMeans::getNumberOfIterationForConvergence()
{
    return numberOfIterationForConvergence;
}

#include <kMeansOMP.hpp>

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
    bool change = true; // boolean initialize to true (change=true loop continues)
    int iter = 0;
    int iter_max = 1000;  // max number of iterations
    std::vector<int> counts(k, 0);
    while (change && iter < iter_max)
    {
        change = false; 
        // if no point will change this to true, no point has changed centroid
        // we break the while, kmeans is done
        // --------------------------------------------

        #pragma omp parallel 
        
        {
            #pragma omp for
            for (Point &p : points) // loop through all points
            {
                // init. minDist to a very large value, nearest = 0
                double minDist = std::numeric_limits<double>::max();
                int nearest = 0;
                for (int j = 0; j < k; ++j) // loop through all centroids
                {
                    // compute distance between p and centroid[j]
                    double tempDist = p.distance(centroids[j]);
                    // update if we found closer than previous iter closer centroid
                    if (tempDist < minDist)
                    {
                        minDist = tempDist;
                        nearest = j;
                    }
                }
                // update clusterId of point there's a new nearest
                if (p.clusterId != nearest)
                {
                    // denugging print
                    //std::cout << "Point " << p.id << " changed cluster from " << p.clusterId << " to " << nearest << std::endl;
                    //std::cout << "omp: thread " << omp_get_thread_num() << " out of " << omp_get_num_threads() << std::endl;

                    p.clusterId = nearest;
                    change = true;  // boolean: mark that change happened
                }
            }

        }

        
        // create a vector of k integers, all initialized to 0 for each centroid we'll count how many points are assigned to it
        counts = std::vector<int>(k, 0);
        // create a vect of k points, initialized with Point construtor
        centroids = std::vector<Point>(k, Point(points[0].numberOfFeatures));

        for (Point p : points) // loop through all points
        {
            for (int i = 0; i < p.numberOfFeatures; ++i) // loop through all features of the current point
            {
                // each feature of the current centroid for CURRENT POINT is "moved" by CURRENT POINT feature's value
                // PARALLELIZATION NOTE: can't parallelize, concurrent write to same centroid
                centroids[p.clusterId].setFeature(i, centroids[p.clusterId].getFeature(i) + p.getFeature(i));
            }
            counts[p.clusterId] += 1; // we count how many points
        }

        #pragma omp parallel
        {
            #pragma omp for                    
            for (int i = 0; i < k; ++i) // loop through all centroids
            {
                for (int j = 0; j < centroids[i].numberOfFeatures; ++j) // loop through all features of the current centroid
                {
                    // we divide each feature of the current centroid by the number of points assigned to it
                    centroids[i].setFeature(j, centroids[i].getFeature(j) / counts[i]);
                }
            }
        }
        std::cout << "." << std::flush;
        iter++;
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
                for (int j = 0; j < p.numberOfFeatures; ++j)
                {
                    std::cout << p.getFeature(j);
                    if (j < p.numberOfFeatures - 1)
                        std::cout << ", ";
                }
                std::cout << ")" << std::endl;
            }
        }
    }
}

void KMeans::plotClusters()
{
    if (centroids[0].numberOfFeatures != 2)
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

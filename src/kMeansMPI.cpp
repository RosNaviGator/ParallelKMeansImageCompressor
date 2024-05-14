#include <kMeansMPI.hpp>

    KMeans::KMeans(const int& k, const int& rank, const int& n_features, const std::vector<Point> points) : k(k), points(points)/*,gp("gnuplot -persist")*/
    {
        centroids = std::vector<Point>(k, Point(n_features));
        if (rank == 0)
        {
            int size = points.size();
            std::random_device rd;                              // Initialize a random device
            std::mt19937 gen(23456789);                         // Initialize a Mersenne Twister random number generator with the random device
            std::uniform_int_distribution<> dis(0, size - 1);   // Create a uniform distribution between 0 and size - 1
            for (int i = 0; i < k; ++i)
            {
                centroids[i]=points[dis(gen)];       // Generate a random index and use it to select a point
            }
        }
        for(int i = 0; i < k; ++i)
        {
            MPI_Bcast(&(centroids[i].features[0]), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            MPI_Bcast(&(centroids[i].features[1]), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            MPI_Bcast(&(centroids[i].features[2]), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }
    }

    void KMeans::run(const int& rank,  const int& world_size)
    {
       
        bool change = true;
        int iter = 0;
        int iter_max = 1000;

        
        while (iter < iter_max && change)
        {
            change = false;
            for(Point& p : points)
            {
                double minDist = std::numeric_limits<double>::max();
                for (int i = 0; i < k; ++i)
                {
                    double dist = p.distance(centroids[i]);
                    if (dist < minDist)
                    {
                        minDist = dist;
                        old_cluster = p.clusterId;
                        p.clusterId = i;
                    }
                }
                if (p.clusterId != old_cluster)
                {
                    change = true;
                }

            }
        }
    }
    void KMeans::printClusters()  const
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
                    std::cout << ")"<< std::endl;
                }
            }
        }
    }

    std::vector<Point> KMeans::getCentroids()
    {
        return centroids;
    }

    std::vector<Point> KMeans::getPoints()
    {
        return points;
    }

    // void KMeans::plotClusters()
    // {
    //     if(centroids[0].numberOfFeatures != 2)
    //     {
    //         std::cout << "Cannot plot clusters with more than 2 features" << std::endl;
    //         return;
    //     }
    //     gp << "set xrange [20:70]\nset yrange [0:30]\n";
    //     gp << "set key outside\n"; // Add this line to place the legend outside the plot
    //     std::vector<std::string> colors = {"red", "blue", "green", "brown", "purple", "orange", "cyan", "violet"};
    //     gp << "plot ";
    //     for (int i = 0; i < k; ++i)
    //     {
    //         std::vector<std::pair<double, double>> pts;
    //         for (Point p : points)
    //         {
    //             if (p.clusterId == i)
    //             {
    //                 pts.emplace_back(std::make_pair(p.getFeature(0), p.getFeature(1)));
    //             }
    //         }
    //         gp << "'-' with points pointtype 7 pointsize 1 lc rgb '" << colors[i % colors.size()] << "' title 'Cluster " << i + 1 << "'"; // Add a title to each plot command
    //         if (i < k - 1)
    //         {
    //             gp << ", ";
    //         }
    //     }
    //     gp << ", '-' with points pointtype 7 pointsize 2 lc rgb 'black' title 'Centroids'"; // Add a title to the centroids \ command
    //     gp << "\n";
    //     for (int i = 0; i < k; ++i)
    //     {
    //         std::vector<std::pair<double, double>> pts;
    //         for (Point p : points)
    //         {
    //             if (p.clusterId == i)
    //             {
    //                 pts.push_back(std::make_pair(p.getFeature(0), p.getFeature(1)));
    //             }
    //         }
    //         gp.send1d(pts);
    //     }
    //     std::vector<std::pair<double, double>> centroid_pts;
    //     for (Point c : centroids)
    //     {
    //         centroid_pts.push_back(std::make_pair(c.getFeature(0), c.getFeature(1)));
    //     }
    //     gp.send1d(centroid_pts);
    // }

    int KMeans::getNumberOfIterationForConvergence()
    {
        return numberOfIterationForConvergence;
    } 
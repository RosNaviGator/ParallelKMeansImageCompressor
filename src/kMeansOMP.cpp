#include <kMeansOMP.hpp>

KMeans::KMeans(const int& k, const std::vector<Point> &points) : k(k), points(points)
{
    size_t size = points.size();
    std::random_device rd;                            // Initialize a random device
    std::mt19937 gen(rd());                       // Initialize a Mersenne Twister random number generator with the random device
    std::uniform_int_distribution<size_t> dis(0, size - 1); // Create a uniform distribution between 0 and size - 1

    for (int i = 0; i < k; ++i)
    {
        centroids.emplace_back(points[dis(gen)]); // Generate a random index and use it to select a point
    }
}

void KMeans::run()
{
    bool change = true; // boolean initialize to true (change=true loop continues)
    int iter = 0;
    const int iter_max = 1000;  // max number of iterations
    
    while (change && iter < iter_max)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::vector<int> counts(k, 0);
        change = false; 
        // if no point will change this to true, no point has changed centroid
        // we break the while, kmeans is done
        // --------------------------------------------
        counts = std::vector<int>(k, 0);
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
            #pragma omp master
            {
                std::vector<std::vector<double> > partial_sum(k, {0.0,0.0,0.0});
                std::vector<int> cluster_size(k,0);

                for (int i = 0 ; i < k ; ++i)
                {
                    for (auto &point : points)
                    {
                        if (point.clusterId == i)
                        {
                            for (int x = 0 ; x < 3; x++)
                            {
                                partial_sum[i][x] += point.getFeature_int(x);
                            }
                            cluster_size[i]++;
                        }
                    }
                }

                for (int i = 0 ; i < k ; ++i)
                {
                    for (int j = 0 ; j < 3; j++)
                    {
                        int result = static_cast<int>(partial_sum[i][j] / cluster_size[i]);
                        centroids[i].setFeature(j, result);
                    }
                }
               
            }
        }
        iter++;
        #pragma omp master 
        {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Iteration " << iter << " completed in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << '\n';
        }
        
    }
}

auto KMeans::getCentroids() -> std::vector<Point>
{
return centroids;
}

auto KMeans::getPoints() -> std::vector<Point>
{
    return points;
}

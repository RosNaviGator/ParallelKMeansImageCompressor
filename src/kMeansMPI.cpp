#include <kMeansMPI.hpp>
#include <algorithm>
#include <chrono>

    KMeans::KMeans(const int& k, const int& rank, const int& n_features)
    {
        this->k = k;
        this->centroids = std::vector<Point>(k, Point(n_features));
    }
    KMeans::KMeans(const int& k, const int& rank, const int& n_features,  const std::vector<Point> points) : points(points) {
        
        this->k = k;
        centroids = std::vector<Point>(k, Point(n_features));     
        int size = points.size();
        std::random_device rd;                              // Initialize a random device
        std::mt19937 gen(23456789);                         // Initialize a Mersenne Twister random number generator with the random device
        std::uniform_int_distribution<> dis(0, size - 1);   // Create a uniform distribution between 0 and size - 1
        for (int i = 0; i < k; ++i)
        {
            centroids[i]=points[dis(gen)];       // Generate a random index and use it to select a point
        }
        
    }


    void KMeans::run(const int& rank,  const int& world_size, std::vector < std::pair < int , Point > >local_points)
    {
        bool changed = true;
        int iter = 0;
        int iter_max = 1000;
        std::vector<int> changed_points(world_size, 0);

        for(int i = 0; i < k; ++i)
        {
            MPI_Bcast(&(centroids[i].getFeature(0)), 1, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
            MPI_Bcast(&(centroids[i].getFeature(1)), 1, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
            MPI_Bcast(&(centroids[i].getFeature(2)), 1, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
        }

        while (iter < iter_max && changed)
        {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            std::fill(changed_points.begin(), changed_points.end(), 0);
            changed = false;
            for(auto& p : local_points)
            {
                //std::cout << "point " << p.second.id << " clusterId " << p.second.clusterId << std::endl;
                double minDist = std::numeric_limits<double>::max();
                for (int i = 0; i < k; ++i)
                {
                    double dist = p.second.distance(centroids[i]);
                    if (dist < minDist)
                    {
                        minDist = dist;
                        if (p.second.clusterId != i)
                        {
                            p.second.clusterId = i;
                            p.first = 1;

                        }
                    }
                }
            }
            // calcolo dei centroidi

            // calcolo delle somme parziali per ogni processo 

            std::vector<std::vector<double> > partial_sum(k, {0.0,0.0,0.0});
            std::vector<int> cluster_size(k,0);

            for (int i = 0 ; i < k ; ++i)
            {
                for (int j = 0 ; j < local_points.size(); j++)
                {
                    if(local_points[j].second.clusterId == i)
                    {
                        for (int x = 0 ; x < 3; x++)
                        {
                            partial_sum[i][x] += local_points[j].second.getFeature_int(x);
                        }
                        cluster_size[i]++;
                    }
                }
            }
            
            if (rank != 0)
            {
                for (int i = 0 ; i < k ; ++i)
                {
                    MPI_Send(partial_sum[i].data(), 3, MPI_DOUBLE, 0, k*rank+i, MPI_COMM_WORLD);
                }
                int max_index = k*world_size+k-1; // rappresenta il massimo indice che può essere usato per inviare le somme parziali
                // a partire da questo punto si inviano i cluster size
                MPI_Send(cluster_size.data(), k, MPI_INT, 0, max_index + rank, MPI_COMM_WORLD);
            }

            if (rank == 0)
            {
                
                
                for (int i = 1; i < world_size; i++)
                {
                    std::vector<std::vector<double> > partial_sum_recived(k,{0.0,0.0,0.0});
                    for (int j = 0 ; j < k ; ++j)
                    {
                        MPI_Recv(partial_sum_recived[j].data(), 3, MPI_DOUBLE, i, k*i+j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    }
                    std::vector<int> cluster_size_recived(k,0);
                    int max_index = k*world_size+k-1;
                    MPI_Recv(cluster_size_recived.data(), k, MPI_INT, i, max_index + i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    for (int j = 0 ; j < k ; ++j)
                    {
                        for (int x = 0 ; x < 3; x++)
                        {
                            partial_sum[j][x] += partial_sum_recived[j][x];
                        }
                        cluster_size[j] += cluster_size_recived[j];
                    }
                }
             
            }

            // calcolo dei nuovi centroidi
            std::vector<Point> old_centroids = centroids;
            if (rank == 0)
            {
                for (int i = 0 ; i < k ; ++i)
                {
                    for (int j = 0 ; j < 3; j++)
                    {
                        int  result = partial_sum[i][j]/cluster_size[i];
                        centroids[i].setFeature(j,result);
                    }
                }
            }



            for (int i = 0; i < k; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    MPI_Bcast(&centroids[i].getFeature(j), 1, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
                }
            }

            iter++;

            for (int i = 0; i < k; ++i)
            {
                if (centroids[i].distance(old_centroids[i]) > 0) // approssimato?
                {
                    changed = true;
                    break;
                }
            }

            if (rank == 0)
            {
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                std::cout << "Iteration " << iter << " completed in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
            }

        }

        for (auto& p : local_points)
        {
            MPI_Send(&p.second.clusterId, 1, MPI_INT, 0, p.second.id, MPI_COMM_WORLD);
        }

        if (rank == 0)
        {
            int points_per_cluster = points.size() / world_size;
            for (int i = 0; i < world_size; i++)
            {
                int start = i * points_per_cluster;
                int end = (i == world_size - 1) ? points.size() : (i + 1) * points_per_cluster;
                for (int j = start; j < end; j++)
                {
                    int clusterId;
                    MPI_Recv(&clusterId, 1, MPI_INT, i, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    points[j].clusterId = clusterId;
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
                    for (int j = 0; j < 3; ++j)
                    {
                        std::cout << p.getFeature(j);
                        if (j < 3 - 1)
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

    int KMeans::getNumberOfIterationForConvergence()
    {
        return numberOfIterationForConvergence;
    } 
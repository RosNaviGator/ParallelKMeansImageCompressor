#include <kMeansMPI.hpp>

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
        

        for(int i = 0; i < k; ++i)
        {
            MPI_Bcast(&(centroids[i].getFeature(0)), 1, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
            MPI_Bcast(&(centroids[i].getFeature(1)), 1, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
            MPI_Bcast(&(centroids[i].getFeature(2)), 1, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
        }
        // std::cout << "staaart" << std::endl;

        while (iter < iter_max && changed)
        {
            std::vector<int> changed_points(world_size, 0);
            changed = false;
            for(auto& p : local_points)
            {
                //std::cout << "point " << p.second.id << " clusterId " << p.second.clusterId << std::endl;
                p.first = 0;
                double minDist = std::numeric_limits<double>::max();
                for (int i = 0; i < k; ++i)
                {
                    double dist = p.second.distance(centroids[i]);
                    if (dist < minDist)
                    {
                        minDist = dist;
                        if (p.second.clusterId != i)
                        {
                            // std::cout << "point " << p.second.id << " changed cluster " << "from " << p.second.clusterId << " to " << i << std::endl;

                            p.second.clusterId = i;
                            p.first = 1;

                        }
                    }
                }
            }
            for (int i = 0 ; i < local_points.size(); i++)
            {
                changed_points[rank] += local_points[i].first;
            }

            
            for (int i = 0 ; i < world_size; i++)
            {
                int changed = changed_points[rank];
                MPI_Bcast(&changed, 1, MPI_INT, i, MPI_COMM_WORLD);
                changed_points[i] = changed;
            }
            
            changed_points.insert(changed_points.begin(), 0);
            
            for (int i = 1 ; i < changed_points.size(); ++i )
            {
                changed_points[i] = changed_points[i]*2 + changed_points[i-1];
            }
            // std::cout << "-------------- LEO DEBUGGER ----------------"<< std::endl;
            int comm_counter = changed_points[rank];

            // changed_poits[wordrank] ha il numero totale di comunicazioni che devono essere eseguite 
            // Possiamo usarlo per dichiarare l'MPI_Request
            int num_operations = changed_points[world_size];

            for (int i = 0 ; i < local_points.size(); i++)
            {
                if(local_points[i].first == 1)
                {
                    MPI_Send(&local_points[i].second.id, 1, MPI_INT, 0, comm_counter, MPI_COMM_WORLD);
                    MPI_Send(&local_points[i].second.clusterId, 1, MPI_INT, 0, comm_counter + 1, MPI_COMM_WORLD);

                    comm_counter += 2;
                }
                // std::cout << "ultimo valore di comm_counter per rank " << rank << " è " << comm_counter + 1 << std::endl;
            }
            

            if (rank == 0)
            {
                for (int i = 0; i < world_size; i++)
                {
                    for (int j = changed_points[i]; j < changed_points[i+1]; j+=2)
                    {
                        int id, clusterId;
                        // std::cout << "valore atteso di comm_count " << j + 1 << " from process " << i << std::endl;
                        MPI_Recv(&id, 1, MPI_INT, i, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        MPI_Recv(&clusterId, 1, MPI_INT, i, j + 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


                        points[id].clusterId = clusterId;

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
            std::cout << "." << std::flush;
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
    //         std::vector<std::std::pair<double, double>> pts;
    //         for (Point p : points)
    //         {
    //             if (p.clusterId == i)
    //             {
    //                 pts.emplace_back(std::make_std::pair(p.getFeature(0), p.getFeature(1)));
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
    //         std::vector<std::std::pair<double, double>> pts;
    //         for (Point p : points)
    //         {
    //             if (p.clusterId == i)
    //             {
    //                 pts.push_back(std::make_std::pair(p.getFeature(0), p.getFeature(1)));
    //             }
    //         }
    //         gp.send1d(pts);
    //     }
    //     std::vector<std::std::pair<double, double>> centroid_pts;
    //     for (Point c : centroids)
    //     {
    //         centroid_pts.push_back(std::make_std::pair(c.getFeature(0), c.getFeature(1)));
    //     }
    //     gp.send1d(centroid_pts);
    // }

    int KMeans::getNumberOfIterationForConvergence()
    {
        return numberOfIterationForConvergence;
    } 
#include <kMeansCUDA.cuh>

km::KMeansCUDA::KMeansCUDA(const int &k, const std::vector<Point> &points) : k(k), points(points)
{
    int size = points.size();
    std::random_device rd;                            // Initialize a random device
    std::mt19937 gen(rd());                       // Initialize a Mersenne Twister random number generator with the random device
    std::uniform_int_distribution<> dis(0, size - 1); // Create a uniform distribution between 0 and size - 1

    for (int i = 0; i < k; ++i)
    {
        centroids.emplace_back(points[dis(gen)]); // Generate a random index and use it to select a point
    }
}

__global__ void km::KMeansCUDA::assign_clusters(int *data, int *centroids, int *labels, int n, int k, int dim) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= n) return;

    // let's print the centrids
    // for (int i = 0; i < k; i++) {
    //    printf("Centroid %d: %d %d %d\n", i, centroids[i * dim], centroids[i * dim + 1], centroids[i * dim + 2]);
    // }

    int closest = 0;
    int min_dist = 1 << 30;

    for (int i = 0; i < k; ++i) {
        int dist = 0.0f;
        for (int j = 0; j < dim; ++j) {
            int diff = data[idx * dim + j] - centroids[i * dim + j];
            dist += diff * diff;
        }
        if (dist < min_dist) {
            min_dist = dist;
            closest = i;
        }
    }
    labels[idx] = closest;
    //printf("Point %d assigned to cluster %d\n", idx, closest);
}

__global__ void km::KMeansCUDA::calculate_new_centroids(int *data, int *centroids, int *labels, int *counts, int n, int k, int dim) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= n) return;

    int cluster_id = labels[idx];
    for (int j = 0; j < dim; ++j) {
        atomicAdd(&centroids[cluster_id * dim + j], data[idx * dim + j]);
    }
    atomicAdd(&counts[cluster_id], 1);
}

__global__ void km::KMeansCUDA::average_centroids(int *centroids, int *counts, int k, int dim) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= k) return;

    for (int j = 0; j < dim; ++j) {
        if (counts[idx] > 0) {
            centroids[idx * dim + j] /= counts[idx];
        }
    }
}

void km::KMeansCUDA::run()
{
    int MAX_ITER = 100;
    int n = points.size();
    int dim = 3;
    int* labels = new int[n];
    int* centroids_data =  new int[k*dim];
    int* points_data = new int[n * dim];


    for (int i = 0; i < points.size(); i++) 
    {
        for (int j = 0; j < 3; j++) 
        {  
            points_data[i * 3 + j] = points.at(i).getFeature_int(j);   
        }
    }

    for (int i = 0; i < centroids.size(); i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            centroids_data[i * 3 + j] = centroids.at(i).getFeature_int(j);
        }
    }


    int *d_data, *d_centroids;
    int *d_labels, *d_counts;
    int* temp = new int[k * dim];
    memccpy(temp, centroids_data, sizeof(int) * k * dim, sizeof(int) * k * dim);
    

    cudaMalloc(&d_data, sizeof(int) * n * dim);
    cudaMalloc(&d_centroids, sizeof(int) * k * dim);
    cudaMalloc(&d_labels, n * sizeof(int));
    cudaMalloc(&d_counts, k * sizeof(int));

    cudaMemcpy(d_data, points_data, sizeof(int) * n * dim, cudaMemcpyHostToDevice);
    cudaMemcpy(d_centroids, centroids_data, sizeof(int) * k * dim, cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocksN = (n + blockSize - 1) / blockSize;
    int numBlocksK = (k + blockSize - 1) / blockSize;

    bool converged = false;

    for (int iter = 0; iter < MAX_ITER || !converged; ++iter) {
        std::cout << "Iteration " << iter << std::endl;
        assign_clusters<<<numBlocksN, blockSize>>>(d_data, d_centroids, d_labels, n, k, dim);
        cudaDeviceSynchronize();
        
        cudaMemset(d_centroids, 0, sizeof(int) * k * dim);
        cudaMemset(d_counts, 0, k * sizeof(int));
        calculate_new_centroids<<<numBlocksN, blockSize>>>(d_data, d_centroids, d_labels, d_counts, n, k, dim);
        cudaDeviceSynchronize();

        average_centroids<<<numBlocksK, blockSize>>>(d_centroids, d_counts, k, dim);
        cudaDeviceSynchronize();


        int* returnedCentroids;
        returnedCentroids = new int[k * dim];
        cudaMemcpy(returnedCentroids, d_centroids, sizeof(int) * k * dim, cudaMemcpyDeviceToHost);

        // check if the centroids have changed
        converged = true;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < dim; j++) {
                if (temp[i * dim + j] != returnedCentroids[i * dim + j]) {
                    converged = false;
                    temp[i * dim + j] = returnedCentroids[i * dim + j];
                    break;
                }
            }
        }

        if (converged)
        {
            number_of_iterations = iter;
            break;
        } 

    }

    cudaMemcpy(labels, d_labels, n * sizeof(int), cudaMemcpyDeviceToHost);
    cudaMemcpy(centroids_data, d_centroids, sizeof(int) * k * dim, cudaMemcpyDeviceToHost);

    for (int i = 0 ; i < points.size() ; i++)
    {
        points.at(i).clusterId = labels[i];
        //std::cout << "Point " << i << " clusterId: " << points.at(i).clusterId << std::endl;
    }

    for (int i = 0; i < centroids.size(); i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            centroids.at(i).setFeature(j, centroids_data[i * 3 + j]);
        }
    }
    cudaFree(d_data);
    cudaFree(d_centroids);
    cudaFree(d_labels);
    cudaFree(d_counts);
}

auto km::KMeansCUDA::getCentroids() -> std::vector<Point>
{
    return centroids;
}

auto km::KMeansCUDA::getPoints() -> std::vector<Point>
{
    return points;
}

auto km::KMeansCUDA::getIterations() -> int
{
    return number_of_iterations;
}
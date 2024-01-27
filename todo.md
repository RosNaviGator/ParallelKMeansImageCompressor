0. ~~work on compressed Images~~
1. ~~add gitignore~~
2. ~~remove compilation alert~~  All -deprecated warnings suppressed, BEWARE!
3. constraint on inputs
4. performance evaluation 
5. ~~openmp parallelization~~ 
6. datastructure on kmeans(?)
7. OS string + conversion
8. ~~/encoder MUST throw an error if you run without mpirun~~ NOT TRUE
9. ~~App does NOT work on Francesco's computer~~ NOT TRUE
10. ~~file only works if run form inside build folder~~
11. ~~make an actual compression algortihm (WHY DON"T WE SIMPLY USE OPENCV???!!!)~~ I did do it with opencv but IT WASN'T SIMPLE AT ALL :( also not efficent
12. fix mpi kmeans
13. try kd-tree (instead of kmeans)
14. CUDA? (makes no sense unless we find massive number of super "simple" operation to parallelize?)
15. better stopping criteria for kmeans
16. paralellelize re-creation of .jpeg after kmeans (don't use emplace_back, preallocate memory and access with points index, they are always in same order)





POSSIBLE MPI PARALLELIZATION
In the context of the scikit-learn library, the KMeans class is used for performing k-means clustering.
Let's discuss the two arguments you mentioned:

* n_clusters: This parameter represents the number of clusters you want the algorithm to form.
In your example, n_clusters=30 indicates that you want the k-means algorithm to create 30 clusters.

* n_init: This parameter determines the number of times the k-means algorithm will be run with different centroid seeds.
The algorithm initializes cluster centers randomly and runs the algorithm multiple times to find the configuration that results
in the lowest inertia. Inertia is the sum of squared distances from each point to its assigned cluster center. Setting n_init=10 
means that the algorithm will run 10 times with different initializations, and the final result will be the one with the lowest inertia.

n_init -> we can use MPI to run with different seeds, then at the end we'll gather the results and "find the configuration that results in the lowest inertia"

I = sum(points): { sum(clusters): (x_i,c_i)^2 } where x_i point value, c_i centroid value


!!! PROBLEM: if you split processes on all the CPUs you might lose speed with OpenMP mulithreading because processors are all taken :(





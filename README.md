# Parallel Kmeans Images Compressor 
![milano](.readmePictures/milanoCompressed.png)

This program compresses images by reducing the number of colors using k-means clustering. It offers enhanced performance through the implementation of several parallelization techniques. By clustering pixels into k color groups, the program reduces the image's color palette, thereby compressing the image while maintaining visual quality.

## Prerequisites 
In order to be able to compile and run the program, there are a few programs that need to be installed.

### Boost C++ Library
A powerful C++ library for enhanced performance and productivity

You can refer to the [official page](https://www.boost.org/users/download/) to download.

### OpenCV C++ Library
A comprehensive library for computer vision and image processing tasks.

You can refer to the [official page](https://opencv.org/releases/) to download.

### Mpicc
A C compiler wrapper for parallel programming with the MPI library.


### OpenMP
A C++ API for parallel programming on shared-memory systems.

## Getting Started 
To compile the project, navigate to the project root directory in your terminal and run the following command:

```
make
```

Once you have compiled you can execute the main program by:
```
./exe
```

## What to expect
Once the program is started, the following screen appears, through which it is possible to compress a new image or decompress an already compressed image.

![alt text](.readmePictures/mainMenuScreenshot.png)

If you choose the "Compress an image" option you can select one type of compressor (sequential, MPI or OpenMP), the type of compression and the path of the original image.

The result image will be created in the output folder and you can rerun ```./exe``` selecting the decoding function to decode it.

## Project Structure

The project is organized as follows:
#### Folders
- ```benchmarkImages```: This folder contains the images used for benchmarking the program. It can be used to test the program's performance.
- ```outputs```: This folder contains the compressed images. After installing the program, you may notice that the outputs folder is not present. However, don't worry! It will be automatically created during the first execution of the program. 
- ```include```: This folder contains the header files of the project. These define the classes and functions that are used in the program.
- ```src```: This folder contains the source files of the project. These files contain the implementation of the classes and functions defined in the header files.
- ```build```: This folder contains the object files generated during the compilation process.

#### Files and Executables
- ```exe```: This is the executable file generated after compiling the project. It is the main program that can be executed to compress or decompress images.
- ```Makefile```: This file contains the instructions for compiling the project. It specifies the dependencies and the commands to compile the project.
- ```.config```: This file contains the configuration of the program. It is used to store some hyperparameters that can be modified to change the behavior of the program.

## How does it work?
The program compresses images by reducing the number of colors in the image. It does this by clustering the pixels into k color groups using the k-means clustering algorithm. The k-means algorithm is an unsupervised learning algorithm that partitions the data into k clusters based on the similarity of the data points. In the context of image compression, the data points are the pixels of the image, and the clusters are the colors that represent the image.
<div align="center">
    <img src=".readmePictures/Albero-removebg-preview.png" width=400>
</div>

The k-means algorithm works as follows:
1. Initialize k centroids randomly.
2. Assign each data point to the nearest centroid.
3. Recompute the centroids based on the data points assigned to them.
4. Repeat steps 2 and 3 until convergence.

The k-means algorithm is an iterative algorithm that converges to a local minimum. The quality of the compression depends on the value of k, the number of clusters. A higher value of k will result in a better representation of the image but will require more memory to store the centroids.

## Parallelization Techniques
The program uses several parallelization techniques to enhance performance. These techniques include:
- **OpenMP**: OpenMP is an API for parallel programming on shared-memory systems. It allows the program to parallelize the computation of the k-means algorithm by distributing the work among multiple threads.
- **MPI**: MPI is a message-passing library for parallel programming on distributed-memory systems. It allows the program to parallelize the computation of the k-means algorithm by distributing the work among multiple processes running on different nodes.

## Benchmarking
The program includes a benchmarking feature that allows you to test the performance of the program on different images. The benchmarking feature measures the time taken to compress an image using different compression techniques and different values of k. The benchmarking results are displayed in a table that shows the time taken to compress the image for each value of k and each compression technique.

## Authors
- [Leonardo Ignazio Pagliochini](https://github.com/leonardopagliochini)
- [Francesco Rosnati](https://github.com/RosNaviGator)
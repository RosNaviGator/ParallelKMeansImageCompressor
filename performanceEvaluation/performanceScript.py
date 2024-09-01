import os
import math
import pandas as pd
import matplotlib.pyplot as plt
import cv2 as cv # OpenCV for image processing
import matplotlib.pyplot as plt

class PerformancePlotter:
    def __init__(self, csv_file):
        self.data = pd.read_csv(csv_file)

    def plot_weak_scalability(self):
        omp_data = self.data[
            (self.data['n_points'] != 1000000) &
            (self.data['method'] == 'OMP') & 
            (self.data['img'] != 'strong')
        ]
        mpi_data = self.data[
            (self.data['n_points'] != 1000000) &
            (self.data['method'] == 'MPI')& 
            (self.data['img'] != 'strong')
        ]
        sequential_data = self.data[
            (self.data['n_points'] != 1000000) &
            (self.data['method'] == 'Sequential')& 
            (self.data['img'] != 'strong')
        ]

        omp_data.loc[:, 'img'] = pd.to_numeric(omp_data['img'], errors='coerce').astype('Int64')
        mpi_data.loc[:, 'img'] = pd.to_numeric(mpi_data['img'], errors='coerce').astype('Int64')
        sequential_data.loc[:, 'img'] = pd.to_numeric(sequential_data['img'], errors='coerce').astype('Int64')

        # Calculate mean time grouped by 'img'
        mpi_data = mpi_data.groupby('img')['time'].mean().reset_index()
        omp_data = omp_data.groupby('img')['time'].mean().reset_index()
        sequential_data = sequential_data.groupby('img')['time'].mean().reset_index()

        # Create new empty DataFrames for speedup calculations
        mpi_data_speedup = pd.DataFrame(columns=['img', 'speedup'])
        omp_data_speedup = pd.DataFrame(columns=['img', 'speedup'])

        # Calculate speedup for MPI and OMP
        for i in range(len(mpi_data)):
            if i < len(sequential_data):  # Ensure no out-of-bounds error
                speedup = sequential_data['time'].iloc[i] / mpi_data['time'].iloc[i]
                new_row = pd.DataFrame({'img': [mpi_data['img'].iloc[i]], 'speedup': [speedup]})
                mpi_data_speedup = pd.concat([mpi_data_speedup, new_row], ignore_index=True)

        for i in range(len(omp_data)):
            if i < len(sequential_data):  # Ensure no out-of-bounds error
                speedup = sequential_data['time'].iloc[i] / omp_data['time'].iloc[i]
                new_row = pd.DataFrame({'img': [omp_data['img'].iloc[i]], 'speedup': [speedup]})
                omp_data_speedup = pd.concat([omp_data_speedup, new_row], ignore_index=True)

        # Plotting the speedup
        plt.figure(figsize=(8, 6))
        plt.plot(mpi_data_speedup['img'], mpi_data_speedup['speedup'], marker='o', linestyle='-', label='MPI')
        plt.plot(omp_data_speedup['img'], omp_data_speedup['speedup'], marker='o', linestyle='-', label='OMP')
        plt.xlabel('Number of Processes/Threads')
        plt.ylabel('Speedup')
        plt.title('Speedup vs Number of Processes/Threads')
        plt.legend()
        plt.grid(True)

        # Save and show the plot
        plt.savefig('plots/weakScalability.png')
        plt.show()
        plt.close()


    
    def plot_strong_scalability(self, n_points, output_dir='plots/strong_scalability'):
        filtered_data = self.data[self.data['n_points'] == n_points]
        methods = filtered_data['method'].unique()

        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        plt.figure(figsize=(8, 6))
        for method in methods:
            method_data = filtered_data[filtered_data['method'] == method]
            grouped_data = 0.224533 / method_data.groupby('world_size')['time'].mean()
            plt.plot(grouped_data.index, grouped_data.values, marker='o', linestyle='-', label=method)

        plt.xlabel('World Size')
        plt.ylabel('Mean Time')
        plt.title(f'Time vs World Size (n_points={n_points})')
        plt.legend()
        plt.grid(True)

        output_path = os.path.join(output_dir, f'strongScalability.png')
        plt.savefig(output_path)
        plt.close()

class ImageGenerator:
    def __init__(self, simulation_number, image_path):
        self.simulation_number = simulation_number
        self.image_path = image_path

    def create_images(self, scalability_type):
        print(f"Creating {scalability_type} images for performance evaluation ...")
        os.system(f"mkdir -p performanceImages/{scalability_type}")
        for i in range(self.simulation_number):
            img = cv.imread(self.image_path)
            print(f"Generating image {i + 1} ...")
            new_width = int(img.shape[1] * math.sqrt(i + 1))
            new_height = int(img.shape[0] * math.sqrt(i + 1))
            resized_img = cv.resize(img, (new_width, new_height),interpolation = cv.INTER_NEAREST)
            cv.imwrite(f"./performanceImages/{scalability_type}/{i + 1}.png", resized_img)
            # # Get the number of unique colors in the image
            # unique_colors = len(set(tuple(pixel) for row in resized_img for pixel in row))
            # print(f"Number of unique colors in the image: {unique_colors}")
        print("Image generation completed.")

weakScalability = True
strongScalability = False
generalPerformanceEvaluation = False
plotWeakScalability = True
plotStrongScalability = False

if weakScalability:

    folder_path = "./performanceImages/weakScalability"

    # Define number of simulations
    OMP = True
    MPI = False

    # Define number of processes (only MPI)
    processorStart = 1
    processorEnd = 14

    # Define number of threads (only OMP)
    threadsStart = 1
    threadsEnd = 20

    # number of simulations
    M = 4

    # Define percentage of colors (1-5)
    colorsStart = 3
    colorsEnd = 3

    # Define compression type (1-3)
    compressionStart = 1
    compressionEnd = 1

    if OMP:
        image_generator = ImageGenerator(threadsEnd - threadsStart + 1, "../benchmarkImages/lena-512x512.png")
        image_generator.create_images("weakScalability")
        for colors in range(colorsStart, colorsEnd + 1):
            for compression in range(compressionStart, compressionEnd + 1):
                for i in range(M):
                    for threads in range(threadsStart, threadsEnd + 1):
                        file_path = folder_path + "/" + str(threads) + ".png"
                        os.system(f"../build/ompEncoder {file_path} {colors} {compression} {threads}")
                        # os.system(f"../build/seqEncoder {file_path} {colors} {compression}")
        os.system("rm -rf performanceImages/")

    if MPI:
        image_generator = ImageGenerator(processorEnd - processorStart + 1, "../benchmarkImages/lena-512x512.png")
        image_generator.create_images("weakScalability")
        for colors in range(colorsStart, colorsEnd + 1):
            for compression in range(compressionStart, compressionEnd + 1):
                for i in range(M):
                    for processor in range(processorStart, processorEnd + 1):
                        file_path = folder_path + "/" + str(processor) + ".png"
                        os.system(f"mpirun -n {processor} ../build/mpiEncoder {file_path} {colors} {compression}")
                        #os.system(f"../build/seqEncoder {file_path} {colors} {compression}")
        os.system("rm -rf performanceImages/")

if strongScalability:
    os.system("mkdir -p performanceImages/strongScalability")
    print("Strong Scalability Image Generation ...")
    os.system("magick ../benchmarkImages/lena-512x512.png -resize 1000x ./performanceImages/strongScalability/strong.png")
    file_path = "./performanceImages/strongScalability/strong.jpg"

    OMP = True
    MPI = False

    # number of simulations
    M = 20

    # Define percentage of colors (1-5)
    colorsStart = 3
    colorsEnd = 3

    # Define compression type (1-3)
    compressionStart = 1
    compressionEnd = 1

    # Define number of processes (only MPI)
    processorStart = 1
    processorEnd = 14

    # Define number of threads (only OMP)
    threadsStart = 1
    threadsEnd = 20
    
    if OMP:
        for colors in range(colorsStart, colorsEnd + 1):
            for compression in range(compressionStart, compressionEnd + 1):
                for i in range(M):
                    for threads in range(threadsStart, threadsEnd + 1):
                        #os.system(f"../build/ompEncoder {file_path} {colors} {compression} {threads}")
                        os.system(f"../build/seqEncoder {file_path} {colors} {compression}")
    
    if MPI:
        for colors in range(colorsStart, colorsEnd + 1):
            for compression in range(compressionStart, compressionEnd + 1):
                for i in range(M):
                    for processor in range(processorStart, processorEnd + 1):
                        os.system(f"mpirun -n {processor} ../build/mpiEncoder {file_path} {colors} {compression}")
                        #os.system(f"../build/seqEncoder {file_path} {colors} {compression}")
    
    os.system("rm -rf performanceImages/")


if plotWeakScalability:
    performance_plotter = PerformancePlotter('performanceData.csv')
    performance_plotter.plot_weak_scalability()

if plotStrongScalability:
    performance_plotter = PerformancePlotter('performanceData.csv')
    performance_plotter.plot_strong_scalability(1000000)
import os
import math
import pandas as pd
import matplotlib.pyplot as plt
import cv2 as cv # OpenCV for image processing
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
class PerformancePlotter:
    def __init__(self, csv_file):
        self.data = pd.read_csv(csv_file)

    def plot_weak_scalability(self):
        omp_data = self.data[
            (self.data['n_points'] != 1000000) &
            (self.data['method'] == 'OMP') & 
            (self.data['img'] != 'strong') 
        ].copy()  # Ensure we're working with a copy

        mpi_data = self.data[
            (self.data['n_points'] != 1000000) &
            (self.data['method'] == 'MPI')& 
            (self.data['img'] != 'strong')
        ].copy()  # Ensure we're working with a copy

        sequential_data = self.data[
            (self.data['n_points'] != 1000000) &
            (self.data['method'] == 'Sequential')
        ].copy()  # Ensure we're working with a copy

        # Convert 'img' column to numeric
        omp_data.loc[:, 'img'] = pd.to_numeric(omp_data['img'], errors='coerce')
        mpi_data.loc[:, 'img'] = pd.to_numeric(mpi_data['img'], errors='coerce')
        sequential_data.loc[:, 'img'] = pd.to_numeric(sequential_data['img'], errors='coerce')

        # Remove rows with NaN values
        omp_data = omp_data.dropna(subset=['img'])
        mpi_data = mpi_data.dropna(subset=['img'])
        sequential_data = sequential_data.dropna(subset=['img'])

        # Calculate mean time grouped by 'img'
        mpi_data = mpi_data.groupby('img')['time'].mean().reset_index()
        omp_data = omp_data.groupby('img')['time'].mean().reset_index()
        sequential_data = sequential_data.groupby('img')['time'].mean().reset_index()

        # Merge DataFrames on 'img' to align data for speedup calculation
        mpi_data = mpi_data.merge(sequential_data[['img', 'time']], on='img', suffixes=('', '_seq'))
        omp_data = omp_data.merge(sequential_data[['img', 'time']], on='img', suffixes=('', '_seq'))

        # Calculate speedup for MPI and OMP
        mpi_data['speedup'] =  0.010740550000000001 * mpi_data['img'] / mpi_data['time']

        omp_data['speedup'] =  0.010740550000000001 * omp_data['img'] / omp_data['time']

        # Perform linear regression
        def linear_regression(x, y):
            A = np.vstack([x, np.ones(len(x))]).T
            m, c = np.linalg.lstsq(A, y, rcond=None)[0]
            return m, c

        # Ensure numeric data types
        mpi_x = mpi_data['img'].astype(float).values
        mpi_y = mpi_data['speedup'].astype(float).values
        omp_x = omp_data['img'].astype(float).values
        omp_y = omp_data['speedup'].astype(float).values

        mpi_slope, mpi_intercept = linear_regression(mpi_x, mpi_y)
        omp_slope, omp_intercept = linear_regression(omp_x, omp_y)

        # Define the range for the regression lines
        x_range = np.linspace(min(mpi_x.min(), omp_x.min()), max(mpi_x.max(), omp_x.max()), 100)

        # Compute the regression lines
        mpi_regression_line = mpi_slope * x_range + mpi_intercept
        omp_regression_line = omp_slope * x_range + omp_intercept

        # Set the Seaborn style and palette
        sns.set(style='whitegrid')
        palette = sns.color_palette('mako', 4)  # Choose a pleasant color palette

        # Plotting the speedup
        plt.figure(figsize=(8, 6))
        plt.plot(mpi_data['img'], mpi_data['speedup'], marker='o', linestyle='-', color=palette[0], label='MPI')
        plt.plot(omp_data['img'], omp_data['speedup'], marker='o', linestyle='-', color=palette[1], label='OMP')
        # plt.plot(x_range, mpi_regression_line, linestyle='--', color=palette[2], label='MPI Regression')
        # plt.plot(x_range, omp_regression_line, linestyle='--', color=palette[2], label='OMP Regression')
        plt.xlabel('Number of Processes/Threads')
        plt.ylabel('Speedup')
        plt.title('Weak Scalability')
        plt.legend()
        plt.grid(True)

        # Save and show the plot
        plt.savefig('plots/weakScalability.png')
        plt.show()
        plt.close()


    
    def plot_strong_scalability(self, n_points, output_dir='plots/strong_scalability'):
        filtered_data = self.data[self.data['n_points'] == n_points]
        methods = filtered_data['method'].unique()
        methods = [method for method in methods if method != 'Sequential']

        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        plt.figure(figsize=(8, 6))
        count = 0
        sns.set(style='whitegrid')
        palette = sns.color_palette('mako', 4)  # Choose a pleasant color palette
        for method in methods:
            method_data = filtered_data[filtered_data['method'] == method]
            grouped_data = 0.224533 / method_data.groupby('world_size')['time'].mean()

            plt.plot(grouped_data.index, grouped_data.values, marker='o', linestyle='-', label=method, color=palette[count])
            count += 1

        plt.xlabel('Number of Processes/Threads')
        plt.ylabel('Speedup')
        plt.title(f'Strong Scalability (n_points={n_points})')
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

weakScalability = False
strongScalability = False
generalPerformanceEvaluation = False
plotWeakScalability = True
plotStrongScalability = False
plotGeneralPerformanceEvaluation = False

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
    M = 6

    # Define percentage of colors (1-5)
    colorsStart = 2
    colorsEnd = 2

    # Define compression type (1-3)
    compressionStart = 1
    compressionEnd = 1

    if OMP:
        image_generator = ImageGenerator(threadsEnd - threadsStart + 1, "../benchmarkImages/piazzaDuomo-612x612.jpg")
        image_generator.create_images("weakScalability")
        for colors in range(colorsStart, colorsEnd + 1):
            for compression in range(compressionStart, compressionEnd + 1):
                for i in range(M):
                    for threads in range(threadsStart, threadsEnd + 1):
                        file_path = folder_path + "/" + str(threads) + ".png"
                        # os.system(f"../build/ompEncoder {file_path} {colors} {compression} {threads}")
                        os.system(f"../build/seqEncoder {file_path} {colors} {compression}")

    if MPI:
        image_generator = ImageGenerator(processorEnd - processorStart + 1, "../benchmarkImages/piazzaDuomo-612x612.jpg")
        image_generator.create_images("weakScalability")
        for colors in range(colorsStart, colorsEnd + 1):
            for compression in range(compressionStart, compressionEnd + 1):
                for i in range(M):
                    for processor in range(processorStart, processorEnd + 1):
                        file_path = folder_path + "/" + str(processor) + ".png"
                        os.system(f"mpirun -n {processor} ../build/mpiEncoder {file_path} {colors} {compression}")
                        #os.system(f"../build/seqEncoder {file_path} {colors} {compression}")

if strongScalability:
    os.system("mkdir -p performanceImages/strongScalability")
    print("Strong Scalability Image Generation ...")
    os.system("magick ../benchmarkImages/piazzaDuomo-612x612.jpg -resize 10000x ./performanceImages/strongScalability/strong.jpg")
    file_path = "./performanceImages/strongScalability/strong.jpg"

    OMP = True
    MPI = True

    # number of simulations
    M = 6

    # Define percentage of colors (1-5)
    colorsStart = 2
    colorsEnd = 2

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


if plotWeakScalability:
    performance_plotter = PerformancePlotter('performanceData.csv')
    performance_plotter.plot_weak_scalability()

if plotStrongScalability:
    performance_plotter = PerformancePlotter('performanceData.csv')
    performance_plotter.plot_strong_scalability(1000000)


if generalPerformanceEvaluation:
    numer_of_points_on_plot = 12;
    image_generator = ImageGenerator(numer_of_points_on_plot, "../benchmarkImages/lena-512x512.png")
    # Define number of simulations
    OMP     = True
    MPI     = True
    SEQ     = True
    CUDA    = False

    # Define number of processes (only MPI)
    processorStart = 2
    processorEnd = 4

    # Define number of threads (only OMP)
    threadsStart = 4
    threadsEnd = 8

    number_simulations = 10

    for y in range(1, number_simulations):
        for i in range(numer_of_points_on_plot):
            image_generator.create_images("generalPerformanceEvaluation")
            file_path = f"./performanceImages/generalPerformanceEvaluation/{i + 1}.png"
            if OMP:
                for x in range(threadsStart, threadsEnd + 1, 2):
                    os.system(f"../build/ompEncoder {file_path} 3 1 {x}")
            if MPI:
                for x in range(processorStart, processorEnd + 1):
                    os.system(f"mpirun -n {x} ../build/mpiEncoder {file_path} 3 1")
            if SEQ:
                os.system(f"../build/seqEncoder {file_path} 3 1")
            if CUDA:
                os.system(f"../build/cudaEncoder {file_path} 3 1")

if plotGeneralPerformanceEvaluation:
    import pandas as pd
    import matplotlib.pyplot as plt

    # Load the CSV data into a pandas DataFrame
    data = pd.read_csv('performanceData.csv')

    # Group by the necessary columns and calculate the mean time
    grouped_data = data.groupby(['n_points', 'method', 'world_size']).agg({'time': 'mean'}).reset_index()

    # Create separate DataFrames for each method
    omp_data = grouped_data[grouped_data['method'] == 'OMP']
    mpi_data = grouped_data[grouped_data['method'] == 'MPI']
    seq_data = grouped_data[grouped_data['method'] == 'Sequential']
    cuda_data = grouped_data[grouped_data['method'] == 'CUDA']

    # Plotting
    plt.figure(figsize=(10, 6))
    sns.set(style='whitegrid')
    palette = sns.color_palette('mako', 8)  # Choose a pleasant color palette
    count = 0
    # OMP line plot
    for world_size in omp_data['world_size'].unique():
        subset = omp_data[omp_data['world_size'] == world_size]
        plt.plot(subset['n_points'], subset['time'], label=f'OMP (world_size={world_size})', marker='o',color = palette[count])
        count += 1

    # MPI line plot
    for world_size in mpi_data['world_size'].unique():
        subset = mpi_data[mpi_data['world_size'] == world_size]
        plt.plot(subset['n_points'], subset['time'], label=f'MPI (world_size={world_size})', marker='o',color = palette[count])
        count += 1

    # Sequential line plot
    plt.plot(seq_data['n_points'], seq_data['time'], label='Sequential', marker='o', color = palette[count])
    count += 1
    plt.plot(cuda_data['n_points'], cuda_data['time'], label='CUDA', marker='o', color = palette[count])

    # Plot settings
    plt.xlabel('Number of Points')
    plt.ylabel('Time (s)')
    plt.title('Compression Time vs Number of Points')
    plt.legend()
    plt.grid(True)
    plt.savefig('plots/generalPerformanceEvaluation.png')
    plt.show()

    
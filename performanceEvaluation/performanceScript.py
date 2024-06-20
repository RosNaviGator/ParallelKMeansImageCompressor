import os
import math
import pandas as pd
import matplotlib.pyplot as plt
import cv2 as cv # OpenCV for image processing


class PerformancePlotter:
    def __init__(self, csv_file):
        self.data = pd.read_csv(csv_file)

    def plot_weak_scalability(self, output_dir='plots/weak_scalability'):
        # Get unique methods, excluding the 'strong' scalability case
        methods = self.data[self.data['img'] != 'strong']['method'].unique()

        # Check if the output directory exists, if not, create it
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        # Filter out the data for the sequential method (assuming it is labeled as 'Sequential')
        seq_data = self.data[(self.data['method'] == 'Sequential') & (self.data['img'] != 'strong')]
        seq_grouped_data = seq_data.groupby('world_size')['time'].mean()
        print("Sequential Grouped Data:")
        print(seq_grouped_data)

        # Iterate over each method to generate the plots
        for method in methods:
            if method == 'Sequential':
                continue  # Skip the sequential method as it's our baseline
            
            # Filter the data for the current method
            method_data = self.data[(self.data['method'] == method) & (self.data['img'] != 'strong') & (self.data['method'] != 'sequential') & (self.data['method'] != 'cuda')]
            grouped_data = method_data.groupby('world_size')['time'].mean()
            print(f"Grouped Data for Method {method}:")
            print(grouped_data)

            # Check if there are entries in the grouped data
            if grouped_data.empty or seq_grouped_data.empty:
                print(f"No data available for method {method} or sequential baseline.")
                continue

            # Calculate speedup: sequential time / method time
            speedup = seq_grouped_data / grouped_data
            print(f"Speedup for Method {method}:")
            print(speedup)

            # Plot the speedup
            plt.figure(figsize=(8, 6))
            plt.plot(speedup.index, speedup.values, marker='o', linestyle='-')
            plt.xlabel('World Size')
            plt.ylabel('Speedup')
            plt.title(f'Weak Scalability Speedup - {method}')
            plt.grid(True)

            # Save the plot to the specified output path
            output_path = os.path.join(output_dir, f'weak_scalability_speedup_{method}.png')
            plt.savefig(output_path)
            plt.close()


    
    def plot_strong_scalability(self, n_points, output_dir='plots/strong_scalability'):
        filtered_data = self.data[self.data['n_points'] == n_points]
        methods = filtered_data['method'].unique()

        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        plt.figure(figsize=(8, 6))
        for method in methods:
            if method == 'Sequential':
                continue
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
            cv.imwrite(f"./performanceImages/{scalability_type}/{i + 1}.jpg", resized_img)
            # # Get the number of unique colors in the image
            # unique_colors = len(set(tuple(pixel) for row in resized_img for pixel in row))
            # print(f"Number of unique colors in the image: {unique_colors}")
        print("Image generation completed.")

weakScalability = False
strongScalability = False
generalPerformanceEvaluation = False
plotWeakScalability = False
plotStrongScalability = True

if weakScalability:

    folder_path = "./performanceImages/weakScalability"

    # Define number of simulations
    OMP = True
    MPI = True

    # Define number of processes (only MPI)
    processorStart = 1
    processorEnd = 14

    # Define number of threads (only OMP)
    threadsStart = 1
    threadsEnd = 20

    # number of simulations
    M = 10

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
                        file_path = folder_path + "/" + str(threads) + ".jpg"
                        os.system(f"../build/ompEncoder {file_path} {colors} {compression} {threads}")
                        #os.system(f"../build/seqEncoder {file_path} {colors} {compression}")
        os.system("rm -rf performanceImages/")

    if MPI:
        image_generator = ImageGenerator(processorEnd - processorStart + 1, "../benchmarkImages/lena-512x512.png")
        image_generator.create_images("weakScalability")
        for colors in range(colorsStart, colorsEnd + 1):
            for compression in range(compressionStart, compressionEnd + 1):
                for i in range(M):
                    for processor in range(processorStart, processorEnd + 1):
                        f
                        ile_path = folder_path + "/" + str(processor) + ".jpg"
                        os.system(f"mpirun -n {processor} ../build/mpiEncoder {file_path} {colors} {compression}")
                        #os.system(f"../build/seqEncoder {file_path} {colors} {compression}")
        os.system("rm -rf performanceImages/")

if strongScalability:
    os.system("mkdir -p performanceImages/strongScalability")
    print("Strong Scalability Image Generation ...")
    os.system("magick ../benchmarkImages/lena-512x512.png -resize 1000x ./performanceImages/strongScalability/strong.jpg")
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
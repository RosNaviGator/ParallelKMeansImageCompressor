import os
import math
import pandas as pd
import matplotlib.pyplot as plt


class PerformancePlotter:
    def __init__(self, csv_file):
        self.data = pd.read_csv(csv_file)

    def plot_weak_scalability(self, output_dir='plots/weak_scalability'):
        methods = self.data[self.data['img'] != 'strong']['method'].unique()
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        for i, method in enumerate(methods):
            method_data = self.data[(self.data['method'] == method) & (self.data['img'] != 'strong')]
            grouped_data = method_data.groupby('world_size')['time'].mean()
            plt.figure(figsize=(8, 6))
            plt.plot(grouped_data.index, grouped_data.values, marker='o', linestyle='-')
            plt.xlabel('World Size')
            plt.ylabel('Mean Time')
            plt.title(f'Weak Scalability - {method}')
            plt.grid(True)
            output_path = os.path.join(output_dir, f'weak_scalability_{method}.png')
            plt.savefig(output_path)
            plt.close()
    
    def plot_strong_scalability(self, n_points, output_dir='plots/strong_scalability'):
        filtered_data = self.data[self.data['n_points'] == n_points]
        methods = filtered_data['method'].unique()

        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        plt.figure(figsize=(8, 6))
        for method in methods:
            method_data = filtered_data[filtered_data['method'] == method]
            grouped_data = method_data.groupby('world_size')['time'].mean()
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

        image_width = os.popen("identify -format %w " + self.image_path).read()

        for i in range(self.simulation_number):
            print(f"Generating image {i + 1} ...")
            instruction = f"magick {self.image_path} -resize {int(int(image_width) * math.sqrt(i + 1))}x ./performanceImages/{scalability_type}/{i + 1}.jpg"
            os.system(instruction)


folder_path = "./performanceImages/weakScalability"
weakScalability = False
strongScalability = True
generalPerformanceEvaluation = False
plotWeakScalability = True
plotStrongScalability = True

if weakScalability:
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
        os.system("rm -rf performanceImages/")

    if MPI:
        image_generator = ImageGenerator(processorEnd - processorStart + 1, "../benchmarkImages/lena-512x512.png")
        image_generator.create_images("weakScalability")
        for colors in range(colorsStart, colorsEnd + 1):
            for compression in range(compressionStart, compressionEnd + 1):
                for i in range(M):
                    for processor in range(processorStart, processorEnd + 1):
                        file_path = folder_path + "/" + str(processor) + ".jpg"
                        os.system(f"mpirun -n {processor} ../build/mpiEncoder {file_path} {colors} {compression}")
        os.system("rm -rf performanceImages/")

if strongScalability:
    os.system("mkdir -p performanceImages/strongScalability")
    print("Strong Scalability Image Generation ...")
    os.system("magick ../benchmarkImages/lena-512x512.png -resize 2000x ./performanceImages/strongScalability/strong.jpg")
    file_path = "./performanceImages/strongScalability/strong.jpg"

    OMP = False
    MPI = True

    # number of simulations
    M = 30

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
                        os.system(f"../build/ompEncoder {file_path} {colors} {compression} {threads}")
    
    if MPI:
        for colors in range(colorsStart, colorsEnd + 1):
            for compression in range(compressionStart, compressionEnd + 1):
                for i in range(M):
                    for processor in range(processorStart, processorEnd + 1):
                        os.system(f"mpirun -n {processor} ../build/mpiEncoder {file_path} {colors} {compression}")
    
    os.system("rm -rf performanceImages/")


if plotWeakScalability:
    performance_plotter = PerformancePlotter('performanceData.csv')
    performance_plotter.plot_weak_scalability()

if plotStrongScalability:
    performance_plotter = PerformancePlotter('performanceData.csv')
    performance_plotter.plot_strong_scalability(4000000)
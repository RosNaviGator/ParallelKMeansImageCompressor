import os
import argparse
import math

# Create an argument parser
parser = argparse.ArgumentParser(description='Create images for performance evaluation.')
parser.add_argument('--simulationNumber', type=int, default=20, help='Number of simulations')

# Parse the command-line arguments
args = parser.parse_args()

image_path = "../benchmarkImages/lena-512x512.png"

weakScalability = True
strongScalability = False

print("Creating images for performance evaluation ...")

print("Creating performanceImages folder ...")
os.system("mkdir performanceImages")

if weakScalability:
    os.system("mkdir performanceImages/weakScalability")
    print("Weak Scalability Image Generation ...")
    simulationNumber = args.simulationNumber
    image_width = os.popen("identify -format %w " + image_path).read()

    for i in range(simulationNumber):
        print("Generating image " + str(i + 1) + " ...")
        instruction = "magick " + image_path + " -resize " + str(int(int(image_width) * math.sqrt(i + 1))) + "x" + " ./performanceImages/weakScalability/" + str(i + 1) + ".jpg"
        os.system(instruction)

if strongScalability:
    os.system("mkdir performanceImages/strongScalability")
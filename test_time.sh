#!/bin/bash

# FILEPATH: **project root folder**/test_time.sh

# This bash script will test k={i range}, executing {j range} times each value of k
# The outputs will be appended to the file ./performSheet/kcPerformSheet.csv


# YOU MUST RUN THE SCRIPT FROM THE PROJECT ROOT FOLDER !!!


# go to build dir
cd build || exit 1

# Check if the required encoder files exist
if [ ! -f "seqEncoder" ] || [ ! -f "ompEncoder" ] || [ ! -f "mpiEncoder" ]; then
	echo "Required encoder files not found."
	exit 1
fi


# choose the image path
path=../benchmarkImages/lena-512x512.png

# glassBall-1888x2826.jpg  --  piazzaDuomo-612x612.jpg  --  odettte3000x4000.jpg  --  lena-512x512.png


# Outer loop with index k number of colors/clusters
for k in 3 6 9 18 32 64; do
    echo "k=$k"

    # Inner loop with index m: choose exe
    for m in 1 2; do
        if [ $m -eq 1 ]; then
            exe=seqEncoder
        elif [ $m -eq 2 ]; then
            exe=ompEncoder
        elif [ $m -eq 3 ]; then
            exe=mpiEncoder
        fi

        echo "exe=$exe"

        # Loop N: repeat same k for N times
        for N in {1..25}; do
            echo "."
            # echo "Running $exe with $k iteration $j"
            ./$exe $path $k
        done
    done
done

cd ..

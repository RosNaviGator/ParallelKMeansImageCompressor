#!/bin/bash

# This bash script will test k={i range}, executing {j range} times each value of k
# The outputs will be appended to the file kmeans_run_time.csv

# Outer loop with index i
for i in {8..8}; do
	echo "k=$i"

	# Inner loop with index j
	for j in {1..100}; do
		echo "k=$i"
		# echo "Running ./exe $i iteration $j od 10"
		./exe $i
	done
done


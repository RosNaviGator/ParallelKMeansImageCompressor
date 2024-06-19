image_path="./benchmarkImages/goosw.jpg"



# Define with metohods to test
seqFlag=1;
ompFlag=1;
cudaFlag=0; 
mpiFLag=1;


# Define how many times to run each single test (beware: life is short)
M=4;

# Define percentage of colors (1-5)
colorsStart=1;
colorsEnd=5;

# Define compression type (1-3)
compressionStart=1;
compressionEnd=3;

# Define number of processes (only MPI)
processorStart=2;
processorEnd=10;

# Loop over colors
for ((colors=colorsStart; colors<=colorsEnd; colors++))
do
    # Loop over compType
    for ((compType=compressionStart; compType<=compressionEnd; compType++))
    do
        # Launch a command M times
        for ((i=1; i<=M; i++))
        do
            if [ 1 -eq $seqFlag ]
            then
            ./build/seqEncoder $image_path $colors $compType
            fi

            if [ 1 -eq $ompFlag ]
            then
            ./build/ompEncoder $image_path $colors $compType
            fi

            if [ 1 -eq $cudaFlag ]
            then
            ./build/cudaEncoder $image_path $colors $compType
            fi

            if [ 1 -eq $mpiFLag ]
            then
            for ((num_proc=processorStart; num_proc<=processorEnd; num_proc++))
            do
                mpirun -np $num_proc ./build/mpiEncoder $image_path $colors $compType
            done
            fi

        done
    done
done

# Compiler
CC = mpic++

SRC_DIR = ./src
INC_DIR = ./include
BUILD_DIR = ./build

# Compiler flags
CFLAGS = -std=c++20 -I/usr/include/boost -I$(INC_DIR) `pkg-config --cflags opencv4` -Wno-deprecated -fopenmp -g

# Libraries
LIBS = -lutil -lboost_iostreams -lz -lboost_system -lboost_filesystem -L/usr/lib `pkg-config --libs opencv4`

LDFLAGS = -rpath

# Target executables, different kmeans have different targets
SEQ_ENCODER_TARGET = $(BUILD_DIR)/seqEncoder
OMP_ENCODER_TARGET = $(BUILD_DIR)/ompEncoder
MPI_ENCODER_TARGET = $(BUILD_DIR)/mpiEncoder
DECODER_TARGET = $(BUILD_DIR)/decoder

# Source files, different kmenas have different source files
SEQ_ENCODER_SRCS = $(wildcard $(SRC_DIR)/encoder.cpp) $(SRC_DIR)/point.cpp $(SRC_DIR)/kMeans.cpp
OMP_ENCODER_SRCS = $(wildcard $(SRC_DIR)/encoderOMP.cpp) $(SRC_DIR)/point.cpp $(SRC_DIR)/kMeansOMP.cpp
MPI_ENCODER_SRCS = $(wildcard $(SRC_DIR)/encoderMPI.cpp) $(SRC_DIR)/point.cpp $(SRC_DIR)/kMeansMPI.cpp
DECODER_SRCS = $(wildcard $(SRC_DIR)/decoder.cpp)

# Object files that will be created, different kmeans have different object files
SEQ_ENCODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SEQ_ENCODER_SRCS))
OMP_ENCODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(OMP_ENCODER_SRCS))
MPI_ENCODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(MPI_ENCODER_SRCS))
DECODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(DECODER_SRCS))

all: $(SEQ_ENCODER_TARGET) $(OMP_ENCODER_TARGET) $(MPI_ENCODER_TARGET) $(DECODER_TARGET)

$(SEQ_ENCODER_TARGET): $(SEQ_ENCODER_OBJS)
	$(CC) $(CFLAGS) -o $(SEQ_ENCODER_TARGET) $(SEQ_ENCODER_OBJS) $(LIBS)

$(OMP_ENCODER_TARGET): $(OMP_ENCODER_OBJS)
	$(CC) $(CFLAGS) -o $(OMP_ENCODER_TARGET) $(OMP_ENCODER_OBJS) $(LIBS)

$(MPI_ENCODER_TARGET): $(MPI_ENCODER_OBJS)
	$(CC) $(CFLAGS) -o $(MPI_ENCODER_TARGET) $(MPI_ENCODER_OBJS) $(LIBS)

$(DECODER_TARGET): $(DECODER_OBJS)
	$(CC) $(CFLAGS) -o $(DECODER_TARGET) $(DECODER_OBJS) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(SEQ_ENCODER_TARGET) $(OMP_ENCODER_TARGET) $(MPI_ENCODER_TARGET) $(DECODER_TARGET) $(SEQ_ENCODER_OBJS) $(OMP_ENCODER_OBJS) $(MPI_ENCODER_OBJS) $(DECODER_OBJS) 

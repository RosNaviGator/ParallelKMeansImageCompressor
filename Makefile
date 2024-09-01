# Compiler
MPICC = mpic++
NVCC = nvcc

SRC_DIR = ./src
INC_DIR = ./include
BUILD_DIR = ./build

# Compiler flags
CFLAGS = -std=c++20 -I$(INC_DIR) `pkg-config --cflags opencv4` -fopenmp -O3 -Wall -Wextra -Wno-deprecated-anon-enum-enum-conversion -Wno-deprecated-enum-enum-conversion -lboost_system -lboost_filesystem
NVCCFLAGS = -std=c++17 -I$(INC_DIR) `pkg-config --cflags opencv4` -O3


# Libraries
LIBS = -lutil -L/usr/lib `pkg-config --libs opencv4`
NVCCLIBS = -L/usr/lib `pkg-config --libs opencv4`

LDFLAGS = -rpath

# Target executables, different kmeans have different targets
SEQ_ENCODER_TARGET = $(BUILD_DIR)/seqEncoder
OMP_ENCODER_TARGET = $(BUILD_DIR)/ompEncoder
MPI_ENCODER_TARGET = $(BUILD_DIR)/mpiEncoder
CUDA_ENCODER_TARGET = $(BUILD_DIR)/cudaEncoder
DECODER_TARGET = $(BUILD_DIR)/decoder
MAINMENU_TARGET = menu

# Source files, different kmeans have different source files

SEQ_ENCODER_SRCS = $(wildcard $(SRC_DIR)/encoder.cpp) $(SRC_DIR)/point.cpp $(SRC_DIR)/kMeansSequential.cpp $(SRC_DIR)/configReader.cpp $(SRC_DIR)/performanceEvaluation.cpp $(SRC_DIR)/utilsCLI.cpp $(SRC_DIR)/filesUtils.cpp $(SRC_DIR)/imagesUtils.cpp $(SRC_DIR)/kMeansBase.cpp
OMP_ENCODER_SRCS = $(wildcard $(SRC_DIR)/encoderOMP.cpp) $(SRC_DIR)/point.cpp $(SRC_DIR)/kMeansOMP.cpp $(SRC_DIR)/configReader.cpp $(SRC_DIR)/performanceEvaluation.cpp $(SRC_DIR)/utilsCLI.cpp $(SRC_DIR)/filesUtils.cpp $(SRC_DIR)/imagesUtils.cpp $(SRC_DIR)/kMeansBase.cpp
MPI_ENCODER_SRCS = $(wildcard $(SRC_DIR)/encoderMPI.cpp) $(SRC_DIR)/point.cpp $(SRC_DIR)/kMeansMPI.cpp $(SRC_DIR)/configReader.cpp $(SRC_DIR)/performanceEvaluation.cpp $(SRC_DIR)/utilsCLI.cpp $(SRC_DIR)/filesUtils.cpp $(SRC_DIR)/imagesUtils.cpp $(SRC_DIR)/kMeansBase.cpp
CUDA_ENCODER_SRCS = $(wildcard $(SRC_DIR)/encoderCUDA.cpp) $(SRC_DIR)/point.cpp $(SRC_DIR)/kMeansCUDA.cu $(SRC_DIR)/configReader.cpp $(SRC_DIR)/performanceEvaluation.cpp $(SRC_DIR)/utilsCLI.cpp $(SRC_DIR)/filesUtils.cpp $(SRC_DIR)/imagesUtils.cpp $(SRC_DIR)/kMeansBase.cpp
DECODER_SRCS = $(wildcard $(SRC_DIR)/decoder.cpp) $(SRC_DIR)/filesUtils.cpp $(SRC_DIR)/imagesUtils.cpp $(SRC_DIR)/utilsCLI.cpp $(SRC_DIR)/point.cpp $(SRC_DIR)/configReader.cpp
MAINMENU_SRCS = $(wildcard $(SRC_DIR)/mainMenu.cpp) $(SRC_DIR)/utilsCLI.cpp $(SRC_DIR)/configReader.cpp

# Object files that will be created, different kmeans have different object files
SEQ_ENCODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SEQ_ENCODER_SRCS))
OMP_ENCODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(OMP_ENCODER_SRCS))
MPI_ENCODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(MPI_ENCODER_SRCS))

ifeq ($(ENABLE_CUDA),0)
	CUDA_ENCODER_OBJS =
else
	CUDA_ENCODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(patsubst $(SRC_DIR)/%.cu,$(BUILD_DIR)/%.o,$(CUDA_ENCODER_SRCS)))
endif

DECODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(DECODER_SRCS))
MAINMENU_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(MAINMENU_SRCS))

all: $(SEQ_ENCODER_TARGET) $(OMP_ENCODER_TARGET) $(MPI_ENCODER_TARGET) $(DECODER_TARGET) $(MAINMENU_TARGET)
ifeq ($(ENABLE_CUDA),1)
all: $(CUDA_ENCODER_TARGET)
endif

$(SEQ_ENCODER_TARGET): $(SEQ_ENCODER_OBJS)
	$(MPICC) $(CFLAGS) -o $(SEQ_ENCODER_TARGET) $(SEQ_ENCODER_OBJS) $(LIBS)

$(OMP_ENCODER_TARGET): $(OMP_ENCODER_OBJS)
	$(MPICC) $(CFLAGS) -o $(OMP_ENCODER_TARGET) $(OMP_ENCODER_OBJS) $(LIBS)

$(MPI_ENCODER_TARGET): $(MPI_ENCODER_OBJS)
	$(MPICC) $(CFLAGS) -o $(MPI_ENCODER_TARGET) $(MPI_ENCODER_OBJS) $(LIBS)

ifeq ($(ENABLE_CUDA),1)
$(CUDA_ENCODER_TARGET): $(CUDA_ENCODER_OBJS)
	$(NVCC) $(NVCCFLAGS) -o $(CUDA_ENCODER_TARGET) $(CUDA_ENCODER_OBJS) $(NVCCLIBS)
endif

$(DECODER_TARGET): $(DECODER_OBJS)
	$(MPICC) $(CFLAGS) -o $(DECODER_TARGET) $(DECODER_OBJS) $(LIBS)

$(MAINMENU_TARGET): $(MAINMENU_OBJS)
	$(MPICC) $(CFLAGS) -o $(MAINMENU_TARGET) $(MAINMENU_OBJS) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(MPICC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cu
	mkdir -p $(BUILD_DIR)
	$(NVCC) $(NVCCFLAGS) -c -o $@ $<

run: menu
		make && ./$(MAINMENU_TARGET)

cuda:
		make ENABLE_CUDA=1

cudarun:
		make ENABLE_CUDA=1 && ./$(MAINMENU_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(SEQ_ENCODER_TARGET) $(OMP_ENCODER_TARGET) $(MPI_ENCODER_TARGET) $(DECODER_TARGET) $(MAINMENU_TARGET) $(SEQ_ENCODER_OBJS) $(OMP_ENCODER_OBJS) $(MPI_ENCODER_OBJS) $(DECODER_OBJS) $(MAINMENU_OBJS) $(CUDA_ENCODER_OBJS)

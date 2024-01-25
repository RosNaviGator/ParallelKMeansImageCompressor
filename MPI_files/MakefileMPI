# Compiler
CC = mpic++

SRC_DIR = ./src
INC_DIR = ./include
BUILD_DIR = ./build
OUTPUTS_DIR = ./Outputs

# Compiler flags
CFLAGS = -std=c++20 -I/usr/include/boost -I$(INC_DIR) `pkg-config --cflags opencv4` -Wno-deprecated

# Libraries
LIBS = -lutil -lboost_iostreams -lz -lboost_system -lboost_filesystem -L/usr/lib `pkg-config --libs opencv4`

LDFLAGS = -rpath

# Target executables
ENCODER_TARGET = encoder
DECODER_TARGET = decoder

# Source files
ENCODER_SRCS = $(wildcard $(SRC_DIR)/encoder.cpp) $(SRC_DIR)/point.cpp $(SRC_DIR)/kMeans.cpp
DECODER_SRCS = $(wildcard $(SRC_DIR)/decoder.cpp)

ENCODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(ENCODER_SRCS))
DECODER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(DECODER_SRCS))

all: $(ENCODER_TARGET) $(DECODER_TARGET)

$(ENCODER_TARGET): $(ENCODER_OBJS)
	$(CC) $(CFLAGS) -o $(ENCODER_TARGET) $(ENCODER_OBJS) $(LIBS)

$(DECODER_TARGET): $(DECODER_OBJS)
	$(CC) $(CFLAGS) -o $(DECODER_TARGET) $(DECODER_OBJS) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OUTPUTS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(ENCODER_TARGET) $(DECODER_TARGET) $(ENCODER_OBJS) $(DECODER_OBJS)

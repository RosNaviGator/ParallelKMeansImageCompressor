# CC = g++
# CFLAGS = -Wall -std=c++11
# LIBS = -lutil `pkg-config --cflags --libs opencv4`
# LDFLAGS = -rpath

# all: main

# main: main.cpp
# 	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# clean:
# 	rm -f main



# Compiler
CC = mpic++

SRC_DIR = ./src
INC_DIR = ./include
BUILD_DIR = ./build

# Compiler flags
CFLAGS = -std=c++20 -I/usr/include/boost -I$(INC_DIR) -Wall `pkg-config --cflags opencv4`

# Libraries
LIBS = -lutil -lboost_iostreams -lboost_system -lboost_filesystem -L/usr/lib `pkg-config --libs opencv4`

LDFLAGS = -rpath

# Target executable name
TARGET = exe

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(OBJS)

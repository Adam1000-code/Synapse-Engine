CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LIBS = -lSDL2 -lGL -lSDL2_image

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

EXECUTABLE = demo_synapse.out

all: $(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f *.out

.PHONY: all clean

CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LIBS_LINUX = $(shell pkg-config --libs sdl2) -lGL -lSDL2_image
LIBS_MACOS = -I/usr/local/include -L/usr/local/lib -lSDL2 -framework OpenGL -lSDL2_image

SRC_DIR = src
BUILD_DIR = build

EXECUTABLE = demo_synapse

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

ifeq ($(shell uname), Darwin)
    LIBS = $(LIBS_MACOS)
else
    LIBS = $(LIBS_LINUX)
endif

all: $(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(EXECUTABLE)
#	rm -f *.out

.PHONY: all clean
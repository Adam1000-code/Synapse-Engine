CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -g
LIBS_LINUX = $(shell pkg-config --libs sdl2) -lGL -lSDL2_image
LIBS_MACOS = -I/usr/local/include -L/usr/local/lib -lSDL2 -framework OpenGL -lSDL2_image

SRC_DIR = src
BUILD_DIR = build

EXECUTABLE = demo_synapse

SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

ifeq ($(shell uname), Darwin)
    LIBS = $(LIBS_MACOS)
else
    LIBS = $(LIBS_LINUX)
endif

all: $(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(EXECUTABLE)

.PHONY: all clean
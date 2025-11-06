CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O3

TARGET = cmdutil
SOURCE_DIR = src
SRCS = src/main.cpp src/dice.cpp src/mathutils.cpp src/commands.cpp src/modules.cpp src/parsing.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp | $(SOURCE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SOURCE_DIR)/*.o

install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
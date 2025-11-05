CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

TARGET = cmdutil
SOURCE_DIR = src
SRCS = src/main.cpp src/dice.cpp src/mathutils.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp | $(SOURCE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SOURCE_DIR)/*.o
CXX=g++
CXXFLAGS=-std=c++11 -I./include `pkg-config --cflags opencv`
LDFLAGS=`pkg-config --libs opencv`
SRC_DIR=src
SRCS=$(wildcard $(SRC_DIR)/*.cpp)
TARGET=main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -O2

clean:
	rm -f $(TARGET)

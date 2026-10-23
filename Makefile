CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 $(shell pkg-config --cflags sdl3)
LDLIBS = $(shell pkg-config --libs sdl3)

first_sdl_app: main.cpp ppm.cpp ppm.h
	$(CXX) $(CXXFLAGS) main.cpp ppm.cpp -o ppm-image-viewer $(LDLIBS)

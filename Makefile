all: main.cpp
	g++ -Wall -Wextra `pkg-config --libs opencv4` main.cpp

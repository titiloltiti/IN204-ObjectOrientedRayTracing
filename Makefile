CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wshadow -ansi -pedantic -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system

project: main.o
	$(CXX) main.o -o exec/main $(CXXFLAGS)
	rm main.o

preprocessing: main.cpp
	$(CXX) -c main.cpp

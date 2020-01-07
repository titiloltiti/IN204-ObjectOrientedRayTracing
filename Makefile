CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wshadow -ansi -pedantic -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS2 = -g -Wall -Wextra -Wshadow -ansi -pedantic -std=c++11

project: main.o
	$(CXX) main.o -o exec/main $(CXXFLAGS)
	rm main.o

preprocessing: main.cpp
	$(CXX) -c main.cpp

test: main.cpp
	$(CXX) $(CXXFLAGS2) main.cpp -o exec/main 
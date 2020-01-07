CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wshadow -ansi -pedantic -std=c++11 
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
EXEC = main

project: $(EXEC).o
	$(CXX) src/$(EXEC).o -o bin/$(EXEC) $(CXXFLAGS) $(LDLFLAGS)
	rm src/$(EXEC).o

preprocessing: $(EXEC).cpp
	$(CXX) -c src/$(EXEC).cpp

test: main
	bin/main

main: src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o bin/main

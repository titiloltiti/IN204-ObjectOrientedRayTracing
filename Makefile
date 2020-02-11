CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wshadow -ansi -pedantic -std=c++11 
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
EXEC = main

project: $(EXEC).o
	$(CXX) src/$(EXEC).o -o bin/$(EXEC) $(CXXFLAGS) $(LDFLAGS)
	rm src/$(EXEC).o

preprocessing: $(EXEC).cpp
	$(CXX) -c src/$(EXEC).cpp

test: bin/main
	./bin/main

main: src/main.cpp
	$(CXX) -fopenmp $(CXXFLAGS) src/main.cpp -o bin/main

sfml: src/sfml.test.o
	$(CXX) sfml.test.o -o bin/sfml.test $(CXXFLAGS) $(LDFLAGS)
	rm sfml.test.o

src/sfml.test.o:
	$(CXX) -c src/sfml.test.cpp

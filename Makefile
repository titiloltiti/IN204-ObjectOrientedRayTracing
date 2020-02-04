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

sfml: sfml.test.o
	$(CXX) sfml.test.o -o sfml.test $(CXXFLAGS) $(LDFLAGS)
	rm sfml.test.o

sfml.test.cpp:
	$(CXX) -c sfml.test.cpp

CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic

# Define the executable target
proj1.x: proj1.o
	$(CXX) $(CXXFLAGS) -o proj1.x proj1.o

# Rule to compile the source file into an object file
proj1.o: proj1.cpp
	$(CXX) $(CXXFLAGS) -c proj1.cpp

# Clean target to remove object and executable files
.PHONY: clean
clean:
	rm -f *.o proj1.x

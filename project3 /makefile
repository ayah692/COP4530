# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic # -g

# Targets
all: test_stack1.x in2post.x

# Target for the test stack executable
test_stack1.x: Stack.hpp Stack.h test_stack1.o
	$(CXX) $(CXXFLAGS) -o $@ test_stack1.o

# Target for the in2post executable
in2post.x: Stack.hpp Stack.h in2post.o
	$(CXX) $(CXXFLAGS) -o $@ in2post.o

# Compile test_stack1.cpp to test_stack1.o
test_stack1.o: test_stack1.cpp Stack.hpp Stack.h
	$(CXX) $(CXXFLAGS) -c test_stack1.cpp

# Compile in2post.cpp to in2post.o
in2post.o: in2post.cpp Stack.hpp Stack.h
	$(CXX) $(CXXFLAGS) -c in2post.cpp

# Phony target for cleaning
.PHONY: clean
clean:
	rm -f test_stack1.x in2post.x *.o

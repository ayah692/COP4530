# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic

# Target executable
TARGET = proj4.x

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): proj4_driver.o BET.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) proj4_driver.o BET.o

# Compile proj4_driver.cpp to proj4_driver.o
proj4_driver.o: proj4_driver.cpp BET.h
	$(CXX) $(CXXFLAGS) -c proj4_driver.cpp -o $@

# Compile BET.cpp to BET.o
BET.o: BET.cpp BET.h
	$(CXX) $(CXXFLAGS) -c BET.cpp -o $@

# Phony target for cleaning up generated files
.PHONY: clean
clean:
	rm -f $(TARGET) *.o core.*

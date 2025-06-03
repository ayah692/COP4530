# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Targets and files
TARGET = proj5.x
STARGET = sproj5.x
OBJS = proj5.o passserver.o
SOBJS = sproj5.o passserver.o

# Rules
all: $(TARGET) $(STARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lcrypt

$(STARGET): $(SOBJS)
	$(CXX) $(CXXFLAGS) -o $(STARGET) $(SOBJS) -lcrypt

proj5.o: proj5.cpp passserver.h
	$(CXX) $(CXXFLAGS) -c proj5.cpp

sproj5.o: sproj5.cpp passserver.h
	$(CXX) $(CXXFLAGS) -c sproj5.cpp

passserver.o: passserver.cpp passserver.h hashtable.h
	$(CXX) $(CXXFLAGS) -c passserver.cpp

clean:
	rm -f $(OBJS) $(SOBJS) $(TARGET) $(STARGET)

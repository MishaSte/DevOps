TARGET = lr1

SOURCES = main.cpp FuncA.cpp
OBJECTS = $(SOURCES:.cpp=.o)

CXX = g++
CXXFLAGS = -Wall -g

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

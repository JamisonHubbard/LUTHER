CXX=g++
CXXFLAGS=-Wall -std=c++17
DEPS=DFA.h SourceFile.h Scanner.h
OBJ=main.o DFA.o SourceFile.o Scanner.o

LUTHER: main.o DFA.o SourceFile.o Scanner.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp $(DEPS)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

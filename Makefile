CXX=g++
CXXFLAGS=-Wall -std=c++17
DEPS=utils.h DFA.h Sigma.h Scanner.h
OBJ=main.o DFA.o Sigma.o Scanner.o

LUTHER: main.o DFA.o Sigma.o Scanner.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp $(DEPS)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

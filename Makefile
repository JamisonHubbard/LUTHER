CXX=g++
CXXFLAGS=-Wall -std=c++14
DEPS=utils.h DFA.h Sigma.h
OBJ=main.o DFA.o Sigma.o

LUTHER: main.o DFA.o Sigma.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

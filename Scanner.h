/* 
    Jamison Hubbard and Josh Dorsey
    CSCI 498A - Compilers
    Project LUTHER
    March 2020
    Scanner.h
*/

#ifndef SCANNER_H
#define SCANNER_H

using namespace std;

#include <string>
#include <map>
#include "DFA.h"

class Scanner {
public:
    // Constructor
    Scanner(string filename);

    // Access Functions
    vector<DFA> getTokens();
    int getAlphabetSize();
    map<char, string> getAlphabet();

    // Other
    int processAlphabet(string line);
    void print(); // for testing
    int hexValue(char c);

    void parseFile(string filename);
    void outputParseData(string filename);

private:
    vector<DFA> tokens;
    int sigmaSize; // size of alphabet
    map<char, string> alphabet; // saving hex codes
    map<char, int> alphabetIndex; // saving the alphabet order

    vector<size_t> tokenList; // tokens for output
    vector<string> dataList; // data for output
    vector<string> locationList; // locations for output
};

#endif /*SCANNER_H*/
/* 
    Jamison Hubbard and Josh Dorsey
    CSCI 498A - Compilers
    Project LUTHER
    March 2020
    DFA.h
*/

#ifndef DFA_H
#define DFA_H

using namespace std;

#include <map>
#include <vector>
#include <string>

class DFA{
public:
    // Constructor
    DFA(string filename, string tok);

    // Access Functions
    map<int, vector<int>> getTable();
    vector<int> getAcceptingStates();
    string getToken();
    string getData();
    void setData(string d);

    // Other
    void print(); // for testing

    int stateMidParse(string phrase, map<char, int> alphabetIndex);

private:
    map<int, vector<int>> ttable;
    vector<int> acceptingStates;
    string token;
    string data;
};

#endif /*DFA_H*/
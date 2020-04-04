/* 
    Jamison Hubbard and Josh Dorsey
    CSCI 498A - Compilers
    Project LUTHER
    March 2020
    DFA.cpp
*/

using namespace std;

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "DFA.h"

// Constructor
DFA::DFA(string filename, string tok) {
    // open file
    ifstream inFile("./dfas/" + filename);
    if (!inFile) exit(2);

    string line;
    while (getline(inFile, line)) {
        // correct for the last line being empty
        if (line == "") break;

        string accepts;
        int nodeID;
        istringstream lineIn(line);

        // retrieve accepting state and node name
        lineIn >> accepts;
        lineIn >> nodeID;

        // load the remaining values into a vector as int
        vector<int> columns;
        string transString;
        lineIn >> transString;

        while (transString != "") {
            int transInt;

            // if the value is E, convert to -1
            if (transString == "E") transInt = -1;
            else transInt = stoi(transString);

            columns.push_back(transInt);

            transString = "";
            lineIn >> transString;
        }

        // load values into table
        ttable[nodeID] = columns;

        if (accepts == "+") acceptingStates.push_back(nodeID);
    }

    inFile.close();

    // set token value
    token = tok;

    // set data to empty
    data = "";
}

// Access Functions
map<int, vector<int>> DFA::getTable() {return ttable;}
vector<int> DFA::getAcceptingStates() {return acceptingStates;}
string DFA::getToken() {return token;}
string DFA::getData() {return data;}
void DFA::setData(string d) {data = d;}

// Other
void DFA::print() {
    map<int, vector<int>>::iterator mit = ttable.begin();
    for (pair<int, vector<int>> row : ttable) {
        // print accepting character
        bool isAccepting = false;
        for (int i = 0; i < acceptingStates.size(); ++i) {
            if (acceptingStates[i] == row.first) isAccepting = true;
        }

        if (isAccepting) cout << "+ ";
        else cout << "- ";

        // print node ID
        cout << to_string(row.first) << " ";

        // print each column value, if it's -1 print E
        for (int i = 0; i < row.second.size(); ++i) {
            if (row.second[i] == -1) cout << "E ";
            else cout << to_string(row.second[i]) << " ";
        }

        cout << endl;
    }

    cout << endl;
}

int DFA::stateMidParse(string phrase, map<char, int> alphabetIndex) {
    // models transitions until the end of the
    // phrase, or it can no longer model the phrase
    
    // returns 0 if it cannot model the phrase
    // returns 1 if the phrase ends when the active node
    // is not accepting
    // returns 2 if the phrase ends when the active node
    // is accepting

    istringstream inPhrase(phrase);
    char c;
    int currentNode = 0;
    int nextNode;

    while (inPhrase.get(c)) {
        // access the table to find the next state
        int indexOfC = alphabetIndex[c];
        nextNode = ttable[currentNode][indexOfC];

        // if no next state
        if (nextNode == -1) return 0;
    }

    // if next node is accepting
    for (int i = 0; i < acceptingStates.size(); ++i) {
        if (nextNode == acceptingStates[i]) return 2;
    }

    // if next node is not accepting
    return 1;
}
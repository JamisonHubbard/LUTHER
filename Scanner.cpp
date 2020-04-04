/* 
    Jamison Hubbard and Josh Dorsey
    CSCI 498A - Compilers
    Project LUTHER
    March 2020
    Scanner.cpp
*/

using namespace std;

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "DFA.h"
#include "Scanner.h"

// Constructor

Scanner::Scanner(string filename) {
    // open the file and get the alphabet definition
    ifstream inFile("./scanners/" + filename);
    if (!inFile) exit(2);

    string alphabetLine;
    getline(inFile, alphabetLine);

    // get the alphabet size and process alphabet
    sigmaSize = processAlphabet(alphabetLine);

    // process the lines giving dfa files
    string line;
    while (getline(inFile, line)) {
        istringstream lineIn(line);
        string dfaFile, token, data;

        // load the three possible inputs
        lineIn >> dfaFile;
        lineIn >> token;
        lineIn >> data;

        // convert dfa filepath to a DFA object
        DFA dfa(dfaFile, token);

        // if data was given, pass to DFA object
        if (data != "") {
            dfa.setData(data);
        }

        // push the DFA to the Scanner
        tokens.push_back(dfa);
    }

    inFile.close();
}

// Access Functions
vector<DFA> Scanner::getTokens() {return tokens;}
int Scanner::getAlphabetSize() {return sigmaSize;}
map<char, string> Scanner::getAlphabet() {return alphabet;}

// Other
int Scanner::processAlphabet(string line) {
    int count = 0;
    istringstream lineIn(line);
    char c;

    // read in each character, determine if a hex code
    // skip whitespace, and count
    while (lineIn.get(c)) {
        // detect whitespace
        // space, form feed, newline, carriage return, h tab, v tab
        if (isspace(c)) continue;

        // detect a hex code
        if (c == 'x') {
            string hexCode = "x";
            int hex16, hex1;
            // grab next two chars and count as one character
            lineIn.get(c);
            hexCode += c;
            hex16 = hexValue(c);
            lineIn.get(c);
            hexCode += c;
            hex1 = hexValue(c);

            // convert hex value to decimal ascii code
            int asciiCode = 16*(hex16) + (hex1);
            char asciiChar = asciiCode;

            // load into maps
            alphabet.insert(pair<char, string>(asciiChar, hexCode));
            alphabetIndex.insert(pair<char, int>(asciiChar, count));
            
            // increment count
            ++count;
        }
        else {
            string asString = "";
            asString += c;

            alphabet.insert(pair<char, string>(c, asString));
            alphabetIndex.insert(pair<char, int>(c, count));
            
            ++count;
        }
    }

    // return size of alphabet
    return count;
}
void Scanner::print() {
    // print alphabet and it's size
    cout << "Alphabet\n";
    map<char, string>::iterator mit = alphabet.begin();
    for (pair<char, string> character : alphabet) {
        cout << character.second << "\t";
    }
    cout << endl;
    for (pair<char, string> character : alphabet) {
        if (!isspace(character.first)){
            cout << string(1, character.first) << "\t";
        } else {
            cout << "N/A\t";
        }
    }
    cout << "\nSize: " << to_string(sigmaSize) << "\n\n";

    // print each DFA's token, transition table, and data
    for (int i = 0; i < tokens.size(); ++i) {
        cout << "Token: " << tokens[i].getToken() << endl;
        cout << "Data: " << tokens[i].getData() << endl;
        tokens[i].print();
    }
}
int Scanner::hexValue(char c) {
	c = (char) std::tolower(c);

	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	else if (c >= 'a' && c <= 'f') {
		return (c - 'a') + 10;
	}
	else {
		return -1;
	}
}

void Scanner::parseFile(string filename) {
    // open file
    fstream inFile(filename);
    if (!inFile) exit(2);
    bool fileEmpty = false;

    while (!fileEmpty) {
        // vector stores the count of how many characters
        // each dfa was able to tokenize
        vector<int> charCount;

        // map stores the state of each dfa for each
        // successive addition of a new character
        map<string, vector<int>> dfaStates;

        // iterate through the file char by char
        char c;
        string phrase;
        while (inFile.get(c)) {
            // check if eof
            if (c == EOF) {
                fileEmpty = true;
                break;
            }

            phrase += c;

            // iterate through the dfas and get their 
            // state given the cumulative parse phrase
            int validCount = 0;
            vector<int> states;
            for (int i = 0; i < tokens.size(); ++i) {
                int state = tokens[i].stateMidParse(phrase, alphabetIndex);
                states.push_back(state);

                // count the number that are valid
                if (state > 0) ++validCount;
            }
            dfaStates.insert(pair<string, vector<int>>(phrase, states));

            // if none are valid, break b/c we've gone too far
            if (validCount == 0) break;
        }

        // respond to case where the file is empty
        if (fileEmpty) {
            
        }

        // otherwise

        // remove the last char from phrase and put it back
        char putBack = phrase[phrase.length()-1];
        phrase = phrase.substr(0, phrase.length()-1);
        inFile.putback(putBack);

        // iterate through the dfa state records backwards
        // the first dfa to be in an accepting state, or the
        // top one if a tie, is the one selected
        vector<string> lastAcceptingPhrase;

        map<string, vector<int>>::iterator mit = dfaStates.begin();
        for (pair<string, vector<int>> stateRecords)

    }

    inFile.close();
    
}
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
#include "SourceFile.h"

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
    SourceFile inFile("./sources/" + filename);
    if (!inFile.file_open()) exit(2);
    bool fileEmpty = false;

    while (!fileEmpty) {
        // vector stores longest phrase accepted by a dfa
        // and set vector size
        vector<string> longestAcceptPhrases(tokens.size());

        // iterate through the file char by char
        char c = 0;
        string phrase;

        // check if eof
        if (inFile.empty()) {
            fileEmpty = true;
        }

        auto startPosition = inFile.position();

        while (inFile.get(c)) {
            phrase += c;

            // iterate through the dfas and get their 
            // state given the cumulative parse phrase
            int validCount = 0;
            vector<DFA::state_t> states;
            for (int i = 0; i < tokens.size(); ++i) {
                DFA::state_t state = tokens[i].stateMidParse(phrase, alphabetIndex);
                states.push_back(state);

                // count the number that are valid
                if (state != DFA::INVALID) ++validCount;
            }

            // if none are valid, back up one character and
            // break b/c we've gone too far
            if (validCount == 0) {
                break;
            }

            // if any are accepting, store phrase
            for (size_t i = 0; i < states.size(); ++i) {
                if (states[i] == DFA::ACCEPTING) {
                    longestAcceptPhrases[i] = phrase;
                }
            }
        }

        // check through the longest phrase accepted for each
        // dfa and take the longest one, or the first one if a tie
        string longest;
        size_t indexOfDFA;
        for (size_t i = 0; i < longestAcceptPhrases.size(); ++i) {
            if (longestAcceptPhrases[i].size() > longest.size()) {
                longest = longestAcceptPhrases[i];
                indexOfDFA = i;
            }
        }

        // put back characters to match longest phrase
        inFile.put_back(phrase.substr(longest.size()));

        // save index of matched DFA in tokens vector
        tokenList.push_back(indexOfDFA);

        // save data, which is data provided or phrase if none
        if (tokens[indexOfDFA].getData() == "") {
            phrase = longestAcceptPhrases[indexOfDFA];
            string newPhrase;
            istringstream inPhrase(phrase);
            char c2;
            while (inPhrase.get(c2)) {
                newPhrase += alphabet[c2];
            }

            dataList.push_back(newPhrase);
        }
        else {
            dataList.push_back(tokens[indexOfDFA].getData());
        }

        // save location info
        locationList.push_back(startPosition.str());
    }
}
void Scanner::outputParseData(string filename) {
    // open file to write to
    ofstream outFile("./outputs/" + filename);
    if (!outFile) exit(5);

    // outputting information for each match
    for (size_t i = 0; i < tokenList.size(); ++i) {
        string token = tokens[tokenList[i]].getToken();
        outFile << token << " ";
        outFile << dataList[i] << " ";
        outFile << locationList[i] << " \n";
    }

    outFile.close();
}
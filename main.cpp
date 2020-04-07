/* 
    Jamison Hubbard and Josh Dorsey
    CSCI 498A - Compilers
    Project LUTHER
    March 2020
    main.cpp
*/

#include <string>
#include <iostream>
#include "Scanner.h"
#include "SourceFile.h"

using namespace std;

int main(int argc, char* argv[]) {
    // We need 3 arguments + the program name
    if (argc != 4) exit(1);

    // organizing filepaths
    string scannerFile = argv[1];
    string sourceFile = argv[2];
    string outputFile = argv[3];

    Scanner scanner(scannerFile);
    scanner.parseFile(sourceFile);
    scanner.outputParseData(outputFile);

    return 0;
}
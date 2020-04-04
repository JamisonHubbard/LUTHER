/* 
    Jamison Hubbard and Josh Dorsey
    CSCI 498A - Compilers
    Project LUTHER
    March 2020
    main.cpp
*/

using namespace std;

#include <string>
#include "Scanner.h"

int main(int argc, char* argv[]) {
    if (argc != 4) exit(1);

    // organizing filepaths
    string scannerFile = argv[1];
    string sourceFile = argv[2];
    string outputFile = argv[3];

    Scanner scan(scannerFile);
    scan.print();

    return 0;
}
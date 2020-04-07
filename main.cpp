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
    /*
    SourceFile file("./sources/source.txt");

    string parse = "";
    // Read 20 characters from stream
    int i = 20;
    while (i) {
        auto pos = file.position();
        char got = file.get();
        parse += got;
        cout << "\'" << got << "\' (" << pos.line << ":" << pos.column << ")\n";
        i--;
    }

    // Put some back
    cout << "putting " << (parse.substr(10).size()) << " characters back.\n";
    file.put_back(parse.substr(10));

    // Read again
    i = 20;
    while (i) {
        char got = file.get();
        parse += got;
        auto pos = file.position();
        cout << "\'" << got << "\' (" << pos.line << ":" << pos.column << ")\n";
        i--;
    }

    return 0;*/

    if (argc != 4) exit(1);

    // organizing filepaths
    string scannerFile = argv[1];
    string sourceFile = argv[2];
    string outputFile = argv[3];

    Scanner scan(scannerFile);
    scan.parseFile(sourceFile);
    scan.outputParseData(outputFile);

    return 0;
}
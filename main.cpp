#include <iostream> // std::cout
#include <fstream>  // std::ifstream
#include <string>   // std::string
#include <vector>   // std::vector
#include <limits>   // std::numeric_limits
#include <optional> // std::optional
#include <cassert>  // assert

#include "util.h"
#include "Sigma.h"
#include "DFA.h"
#include "Scanner.h"

using std::cout;
using std::ifstream;
using std::string;
using std::vector;
using std::optional;

optional<Scanner> loadScannerDefinition(char* fname);

int main(int argc, char** argv) {
	//// Test stuff
	cout << "Sigma Test:\n";
	Sigma testSigma = Sigma::fromString("  x0ax20 x5C  x6fpqrx73   ");

	assert(testSigma.size() == 8 && "Loaded sigma incorrectly.");
	cout << testSigma << "\n";

	cout << "\nDFA Test:\n";
	optional<DFA> testTable = DFA::fromFile(testSigma, "example/noto22.tt");
	assert(testTable && "Unable to load DFA from file.");

	cout << testTable.value();

	//// Actual program stuff
	// Check for wrong number of arguments
	if (argc != 1 + 3) {
		return 2;
	}

	optional<Scanner> scanner = loadScannerDefinition(argv[1]);
	if (!scanner) {
		return 1;
	}

	return 0;
}

optional<Scanner> loadScannerDefinition(char* fname) {
	// Load input file
	ifstream inFile(fname, ifstream::in);
	if (!inFile.good()) {
		// Couldn't open file
		return std::nullopt;
	}

	Sigma sigma;
	string line;
	if (std::getline(inFile, line)) {
		// Grab the alphabet from the first line
		sigma = Sigma::fromString(line);
	}
	else {
		// Unable to read the first line
		return std::nullopt;
	}

	// TODO read the rest of the scanner definition file into some
	// kind of useful data structure (a list of DFAs?)
	// also need to map the DFAs to token/value pairs
	while (std::getline(inFile, line)) {
		vector<string> split = util::split(line);
	}

	inFile.close();
	return std::nullopt;
}
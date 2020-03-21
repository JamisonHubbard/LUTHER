#include <memory>   // std::shared_ptr
#include <iostream> // std::cout
#include <fstream>  // std::ifstream
#include <string>   // std::string
#include <vector>   // std::vector
#include <limits>   // std::numeric_limits

#include "util.h"
#include "Sigma.h"
#include "DFA.h"

using std::shared_ptr;
using std::cout;
using std::ifstream;
using std::string;
using std::vector;

bool loadScannerDefinition(
	char* fname,
	shared_ptr<Sigma> sigma,
	vector<shared_ptr<DFA>> tables
);

int main(int argc, char** argv) {
	//// Test stuff
	cout << "Sigma Test:\n";
	shared_ptr<Sigma> testSigma = Sigma::fromString("  x0ax20 x5C  x6fpqrx73   ");
	cout << testSigma << "\n";

	cout << "\nDFA Test:\n";
	shared_ptr<DFA> testTable = DFA::fromFile(testSigma, "example/noto.tt");
	cout << testTable;

	//// Actual program stuff
	// Check for wrong number of arguments
	if (argc != 1 + 3) {
		return 2;
	}

	shared_ptr<Sigma> sigma;
	vector<shared_ptr<DFA>> tables;

	if (!loadScannerDefinition(argv[1], sigma, tables)) {
		return 1;
	}

	return 0;
}

bool loadScannerDefinition(
	char* fname,
	shared_ptr<Sigma> sigma,
	vector<shared_ptr<DFA>> dfas
) {
	// Load input file
	ifstream inFile(fname, ifstream::in);
	if (!inFile.good()) {
		// Couldn't open file
		return false;
	}

	string line;
	if (std::getline(inFile, line)) {
		// Grab the alphabet from the first line
		sigma = Sigma::fromString(line);
	}
	else {
		// Unable to read the first line
		return false;
	}

	// TODO read the rest of the scanner definition file into some
	// kind of useful data structure (a list of DFAs?)
	// also need to map the DFAs to token/value pairs
	while (std::getline(inFile, line)) {
		vector<string> split = util::split(line);
	}

	inFile.close();
}
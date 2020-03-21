// This is just for the debug logging in DFA::fromFile
//#include <iostream> // std::cout
#include <ostream>  // std::ostream
#include <iomanip>  // std::setw, std::left

#include "DFA.h"
#include "util.h"

using std::shared_ptr;
using std::make_shared;
using std::string;
using std::ifstream;
using std::ostream;
using std::vector;
using std::map;

shared_ptr<DFA> DFA::fromFile(shared_ptr<Sigma> sigma, const char* fname) {
	ifstream file(fname, ifstream::in);

	if (!file.good()) {
		return nullptr;
	}

	shared_ptr<DFA> dfa = make_shared<DFA>();
	dfa->name = string(fname);
	dfa->sigma = sigma;

	string line;
	bool readValidInput = false;

	while (std::getline(file, line)) {
		// First, split the line by whitespace
		vector<string> split = util::split(line);

		// We need exactly sizeof(sigma)+2 items in the split
		// <accepting> <state number> <transitions...>
		if (split.size() != 2 + sigma->size()) continue;

		readValidInput = true;

		// What state are these transitions for?
		size_t fromState = std::stoi(split[1]);

		// Is the state accepting or not?
		bool accept = split[0] == "+";
		dfa->accepting[fromState] = accept;

		// Go through this row, we start at 2 to skip
		// both the +/- at the beginning and also the
		// state number.
		for (size_t i = 2; i < split.size(); i++) {
			size_t sigmaIdx = i - 2;
			if (split[i] != "E") {
				size_t toState = std::stoi(split[i]);

				// Add the transition
				dfa->transitionTable[fromState][sigmaIdx] = toState;
			}
		}
	}

	file.close();
	
	if (readValidInput) {
		return dfa;
	}
	else {
		return nullptr;
	}
}

size_t DFA::numRows() const {
	return transitionTable.size();
}

state_t DFA::getState() const {
	return this->state;
}

state_t DFA::transition(char inputChar) {
	// TODO
	// This function performs a transition on this DFA, and changes its current state.
	// This function is incomplete and needs to do bookkeeping about the last match
	// and its position in the program source.
	size_t inputIdx = sigma->indexToChar(inputChar);

	map<size_t, statenum_t> transitionRow = transitionTable[stateNum];

	if (transitionRow.find(inputIdx) != transitionRow.end()) {
		stateNum = transitionRow[inputIdx];
		state = accepting[stateNum];
	}
	else {
		stateNum = 0;
		state = accepting[stateNum];
	}

	return state;
}


ostream& operator<<(ostream& out, const DFA& dfa) {
	using std::setw;
	using std::streamsize;

	// Save off old stream format flags so we can restore them
	// at the end of the function
	const std::ios_base::fmtflags flags(out.flags());

	// Since the max size of an entry is approximately 3 (due to the
	// alphabet notation in sigma), there's a lot of setw(4) a lot
	// to make a nice grid.
	const int colWidth = 4;

	out << setw(0) << dfa.name << ":\n";

	// Print sigma
	out << string(colWidth * 2, ' '); // two empty columns
	for (char c : *dfa.sigma) {
		out << std::left << setw(colWidth) << Sigma::print(c);
	}
	out << "\n";

	auto ttable = dfa.transitionTable;
	for (auto entry : ttable) {
		size_t stateNum = entry.first;
		map<size_t, statenum_t> transitions = entry.second;

		// Print accepting state and state number
		out << setw(colWidth) << (dfa.accepting.at(stateNum) ? "+" : "-");
		out << setw(colWidth) << stateNum;

		// Print transitions
		for (size_t i = 0; i < dfa.sigma->size(); i++) {
			if (transitions.find(i) != transitions.end()) {
				out << setw(colWidth) << transitions[i];
			}
			else {
				out << setw(colWidth) << "E";
			}
		}
		out << "\n";
	}

	// Restore old format flags
	out.flags(flags);

	return out;
}

ostream& operator<<(ostream& out, const shared_ptr<DFA>& dfa) {
	if (dfa == nullptr) {
		return out << "<null dfa>";
	}
	return out << *dfa;
}
#ifndef TRANSITION_TABLE_H
#define TRANSITION_TABLE_H

#include <memory>  // std::shared_ptr, std::make_shared
#include <string>  // std::string, std::getline, std::isblank, std::stoi
#include <map>     // std::map
#include <vector>  // std::vector
#include <fstream> // std::ifstream

#include "Sigma.h"

typedef size_t statenum_t;
typedef unsigned short state_t;
typedef std::map<statenum_t, std::map<size_t, statenum_t>> ttable_t;

class DFA {
public:
	static std::shared_ptr<DFA> fromFile(std::shared_ptr<Sigma> sigma, const char* fname);

	// The two possible DFA states
	static const state_t WILL_NOT_MATCH = 0;
	static const state_t MATCHING = 1;

	// Accessors
	size_t numRows() const;
	state_t getState() const;

	// Parsing function(s)
	state_t transition(char input);

	// Printing stuff
	friend std::ostream& operator<<(std::ostream& out, const DFA& dfa);
	friend std::ostream& operator<<(std::ostream& out, const std::shared_ptr<DFA>& dfa);

private:
	// Used for printing
	std::string name;
	// The current state number
	statenum_t stateNum = 0;
	// The current accepting state
	state_t state = WILL_NOT_MATCH;

	// The transition table
	ttable_t transitionTable;
	// Each state's acceptance value
	std::map<size_t, bool> accepting;

	// Reference to sigma
	std::shared_ptr<Sigma> sigma;
};

#endif // TRANSITION_TABLE_H
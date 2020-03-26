#include <string>     // std::string
#include <iomanip>    // std::hex, std::setw, std::setw
#include <sstream>    // std::stringstream

#include "Sigma.h"
#include "util.h"

using std::string;
using std::set;
using std::ostream;

Sigma Sigma::fromString(string line) {
	Sigma sigma;

	while (!line.empty()) {
		char c = line[0];

		// Literal
		if (Sigma::isLiteralChar(c)) {
			sigma.addItem(c);

			// Advance one item
			line = line.substr(1);
		}
		// Alphabet Notation
		else if (c == 'x' && line.size() >= 3) {
			int msb = Sigma::hexValue(line[1]);
			int lsb = Sigma::hexValue(line[2]);

			// If both values were valid
			if (msb + lsb != -2) {
				char newItem = (char)((msb << 4) + lsb);
				sigma.addItem(newItem);

				// Advance the string
				line = line.substr(3);
			}
			else {
				// There was an invalid alphabet notation thing
				break;
			}
		}
		// Whitespace
		else if (util::isblank(c)) {
			// Skip the whitespace
			line = line.substr(1);
		}
	}

	return sigma;
}

string Sigma::print(const char c) {
	using std::stringstream;

	stringstream s;
	if (Sigma::isLiteralChar(c)) {
		s << c;
	}
	else {
		s << "x" << std::setw(2) << std::setfill('0') << std::hex << (int)c;
	}

	return s.str();
}

bool Sigma::isLiteralChar(char c) {
	bool isNum = (c <= '9' && c >= '0');
	bool isUpper = (c <= 'Z' && c >= 'A');
	bool isLowerNotX = (c >= 'a' && c <= 'w') || (c >= 'y' && c <= 'z');

	return isNum || isUpper || isLowerNotX;
}

int Sigma::hexValue(char c) {
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

void Sigma::addItem(char item) {
	size_t id = sigma.size();
	sigma.insert(item);
	forwardIdMap[item] = id;
	backwardIdMap[id] = item;
}

size_t Sigma::size() const {
	return sigma.size();
}

set<char>::const_iterator Sigma::begin() const {
	return sigma.begin();
}

set<char>::const_iterator Sigma::end() const {
	return sigma.end();
}

bool Sigma::hasIndex(size_t idx) {
	return backwardIdMap.find(idx) != backwardIdMap.end();
}

bool Sigma::hasChar(char c) {
	return forwardIdMap.find(c) != forwardIdMap.end();
}

char Sigma::indexToChar(size_t idx) {
	return backwardIdMap[idx];
}

size_t Sigma::charToIndex(char c) {
	return forwardIdMap[c];
}

ostream& operator<<(ostream& out, const Sigma& sigma) {
	out << "{";

	auto sigmaIter = sigma.begin();

	if (sigmaIter != sigma.end()) {
		out << Sigma::print(*sigmaIter);

		sigmaIter++;
	}

	while (sigmaIter != sigma.end()) {
		out << ", " << Sigma::print(*sigmaIter);

		sigmaIter++;
	}

	return out << "}";
}